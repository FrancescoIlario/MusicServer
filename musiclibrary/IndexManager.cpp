//
// Created by fra on 15/10/18.
//

#include "IndexManager.hpp"

std::mutex IndexManager::fileMutex_{};
std::mutex IndexManager::tmpFileMutex_{};

Index<AudioInfoData> *IndexManager::readIndex() {
    std::filesystem::path _pathIndex{this->index_path_};
    _pathIndex += IndexManager::kIndexFilename;

    std::vector<std::string> indexString{};

    std::unique_ptr<IndexMetadata> metadata{this->readMetadata()};
    if (!metadata) return nullptr;

    {
        std::lock_guard lock_guard(IndexManager::fileMutex_);
        std::ifstream indexStream{_pathIndex};
        if (!indexStream.good()) return nullptr;

        while (!indexStream.eof()) {
            std::string buf{};
            std::getline(indexStream, buf);
            indexString.push_back(std::move(buf));
        }
    }

    auto index = new Index<AudioInfoData>{metadata->creation_time};
    for (auto &indexLine: indexString) {
        std::string err{};
        auto jsonLine = json11::Json::parse(indexLine, err);
        if (jsonLine != json11::Json()) {
            std::unique_ptr<AudioInfoData> infoData{AudioInfoData::fromJson(jsonLine)};
            if (infoData)
                index->data_.push_back(*infoData);
        }
    }
    return index;
}

void IndexManager::flush(const std::vector<AudioInfoData> &data) {
    std::lock_guard lock(IndexManager::tmpFileMutex_);

    std::filesystem::path _path{this->index_path_};
    _path += IndexManager::kIndexTmpFilename;
    std::ofstream indexStream{_path, std::ios::app};

    for (auto &d : data)
        indexStream << d.toJson().dump() << "\n";
}

void IndexManager::collect(AudioInfoData audio) {
    std::unique_lock lock(this->dataMutex_);
    this->data_.push_back(std::move(audio));
    ++this->collected;

    if (this->data_.size() == IndexManager::MAX_DATA) {
        std::vector<AudioInfoData> temp{std::move(this->data_)};
        lock.unlock();

        new std::thread{
                [=]() {
                    this->flush(temp);
                }
        };
    }
}

void IndexManager::closeIndex() {
    {
        std::lock_guard lock(this->dataMutex_);
        this->flush(data_);
        this->data_.clear();
    }
    {
        std::lock(IndexManager::fileMutex_, IndexManager::tmpFileMutex_);
        std::filesystem::path _pathTmp{this->index_path_};
        _pathTmp += IndexManager::kIndexTmpFilename;

        std::filesystem::path _path{this->index_path_};
        _path += IndexManager::kIndexFilename;

        std::filesystem::rename(_pathTmp, _path);
    }
    writeMetadata();
}

void IndexManager::writeMetadata() {
    std::filesystem::path _path{this->index_path_};
    _path += IndexManager::kIndexMetadataFilename;
    std::ofstream metadata_file{_path};

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    metadata_file << "date=" << std::put_time(std::localtime(&now), "%F %T") << "\n";
    metadata_file << "songs=" << this->collected << "\n";
    this->collected = 0;
}

void IndexManager::discardIndex() {
    std::lock(this->dataMutex_, IndexManager::tmpFileMutex_);
    this->data_.clear();
    this->collected = 0;

    std::filesystem::path _path{this->index_path_};
    _path += IndexManager::kIndexTmpFilename;
    std::remove(_path.c_str());
}

IndexManager::IndexMetadata *IndexManager::readMetadata() {
    std::lock_guard lock_guard(IndexManager::fileMutex_);

    std::filesystem::path _path{this->index_path_};
    _path += IndexManager::kIndexMetadataFilename;
    std::ifstream metadata_file{_path};

    if (!metadata_file.good())
        return nullptr;

    std::string line{};
    auto metadata = new IndexMetadata{};
    while (!metadata_file.eof()) {
        metadata_file >> line;
        std::istringstream tokenStream{line};

        std::string key{}, value{};

        std::getline(tokenStream, key, '=');
        std::getline(tokenStream, value);

        if (key == "date") {
            std::tm tm{};
            std::stringstream ss(value);
            ss >> std::get_time(&tm, "%F %T");
            metadata->creation_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
    }
    return metadata;
}
