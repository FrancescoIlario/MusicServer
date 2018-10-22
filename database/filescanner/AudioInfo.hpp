#ifndef AUDIOINFO_HPP
#define AUDIOINFO_HPP

#include <string>
#include <ostream>
#include <json11.hpp>

#include "FileFormat.hpp"

class AudioInfoData {
public:
    std::string completeFilepath_, filename_, filepath_, format_;
    std::string title_, author_, album_;
    uint year_, track_no_;

    AudioInfoData() = default;

    AudioInfoData(std::string completeFilepath, std::string filename, std::string filepath, std::string format,
                  std::string title, std::string author, std::string album, uint year, uint track_no)
            : completeFilepath_{std::move(completeFilepath)}, filename_{std::move(filename)},
              filepath_{std::move(filepath)}, format_{std::move(format)}, title_{std::move(title)},
              author_{std::move(author)}, album_{std::move(album)}, year_{year}, track_no_{track_no} {}

    static AudioInfoData *fromJson(const json11::Json &json);

    json11::Json toJson() const;
};

class AudioInfo {
private:
    AudioInfoData data_;

public:
    AudioInfo() = delete;

    explicit AudioInfo(AudioInfoData data) : data_{std::move(data)} {}

    explicit AudioInfo(std::string filepath);

    explicit AudioInfo(FileFormat fileFormat);

    const AudioInfoData getAudioData() const;

    friend inline std::ostream &operator<<(std::ostream &out, const AudioInfo &audioInfo) {
        auto d = audioInfo.data_;
        out << "[" << d.filepath_ << ", " << d.filename_ << ", " << d.format_ << ", " << d.title_ << ", " << d.album_
            << ", " << d.author_ << ", " << d.year_ << "]";
        return out;
    }

private:
    void buildData(FileFormat &fileFormat);
};

#endif // AUDIOINFO_HPP
