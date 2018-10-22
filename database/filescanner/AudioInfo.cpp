#include "AudioInfo.hpp"

#include <taglib/fileref.h>

typedef AudioInfoData *pData;

AudioInfo::AudioInfo(std::string filepath) {
    FileFormat f{filepath};
    buildData(f);
}

AudioInfo::AudioInfo(FileFormat fileFormat) {
    buildData(fileFormat);
}

void AudioInfo::buildData(FileFormat &fileFormat) {
    if (fileFormat.isAudioFile()) {
        data_.completeFilepath_ = fileFormat.completeFilepath();
        data_.filepath_ = fileFormat.filepath();
        data_.filename_ = fileFormat.filename();
        data_.format_ = fileFormat.format();

        TagLib::FileRef fr{fileFormat.completeFilepath().c_str()};
        auto tag = fr.tag();
        if (tag) {
            data_.title_ = tag->title().toCString(true);
            data_.author_ = tag->artist().toCString(true);
            data_.album_ = tag->album().toCString(true);
            data_.year_ = tag->year();
            data_.track_no_ = tag->track();
        }
    } else
        throw std::runtime_error("given file is not a correct audio file");
}

const AudioInfoData AudioInfo::getAudioData() const {
    return this->data_;
}

AudioInfoData *AudioInfoData::fromJson(const json11::Json &json) {
    if (!json.is_object()) return nullptr;

    return new AudioInfoData{
            json["completeFilepath"].string_value(),
            json["filename"].string_value(),
            json["filepath"].string_value(),
            json["format"].string_value(),
            json["title"].string_value(),
            json["author"].string_value(),
            json["album"].string_value(),
            static_cast<uint>(std::strtoul(json["year"].string_value().c_str(), nullptr, 10)),
            static_cast<uint>(std::strtoul(json["track_no"].string_value().c_str(), nullptr, 10))};
}

json11::Json AudioInfoData::toJson() const {
    return json11::Json::object{
            {"completeFilepath", this->completeFilepath_},
            {"filename",         this->filename_},
            {"filepath",         this->filepath_},
            {"format",           this->format_},
            {"title",            this->title_},
            {"author",           this->author_},
            {"album",            this->album_},
            {"year",             std::to_string(this->year_)},
            {"track_no",         std::to_string(this->track_no_)}
    };
}
