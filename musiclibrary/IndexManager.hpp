//
// Created by fra on 15/10/18.
//

#ifndef MUSICSERVER_INDEXMANAGER_HPP
#define MUSICSERVER_INDEXMANAGER_HPP

#include <filesystem>
#include <fstream>
#include <vector>
#include <mutex>
#include <iterator>
#include <thread>
#include <iomanip>

#include <AudioInfo.hpp>


template<typename T>
class Index {
    friend class IndexManager;

protected:
    std::vector<T> data_;
    std::chrono::system_clock::time_point creationTime_;

public:
    Index() = delete;

    explicit Index(std::chrono::system_clock::time_point creationTime = std::chrono::system_clock::now())
            : data_{}, creationTime_{creationTime} {}

    const std::vector<T> &getData() { return this->data_; }

};


class IndexManager {
private:
    static constexpr char kIndexFilename[] = "MusicLibrary.idx", kIndexTmpFilename[] = "MusicLibrary.idx.tmp",
            kIndexMetadataFilename[] = "MusicLibrary.meta.ini";

    struct IndexMetadata {
        std::chrono::system_clock::time_point creation_time;
    };

private:
    static std::mutex tmpFileMutex_, fileMutex_;
    std::mutex dataMutex_;
    std::vector<AudioInfoData> data_{};

    ulong collected{0};

    std::string index_path_{};

public:
    IndexManager() = default;

    explicit IndexManager(std::string index_path) : index_path_{std::move(index_path)} {}

    Index<AudioInfoData> *readIndex();

    void collect(AudioInfoData audio);

    void discardIndex();

    void closeIndex();

    constexpr static unsigned long MAX_DATA = 1000;

private:
    void flush(const std::vector<AudioInfoData> &data);

    void writeMetadata();

    IndexMetadata *readMetadata();
};

#endif //MUSICSERVER_INDEXMANAGER_HPP
