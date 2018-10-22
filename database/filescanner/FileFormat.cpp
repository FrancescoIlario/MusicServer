#include "FileFormat.hpp"

const std::vector<std::string> FileFormat::FORMATS = {"mp3", "wav", "wave", "aac",
                                                      "flac"};

std::string FileFormat::filepath() const { return filepath_; }

std::string FileFormat::filename() const { return filename_; }

std::string FileFormat::format() const { return format_; }

bool FileFormat::isAudioFile() const { return isAudioFile_; }

FileFormat::FileFormat(const std::string &filepath) : complete_filepath_{filepath} {
    auto tp = filepath.find_last_of('/');

    this->filepath_ = (tp > 0) ? filepath.substr(0, tp) : std::string{};
    this->filename_ = (tp > 0) ? filepath.substr(tp + 1) : filepath;
    this->format_ = this->filename_.substr(this->filename_.find_last_of(".") + 1);

    auto res = std::find(FileFormat::FORMATS.begin(), FileFormat::FORMATS.end(),
                         this->format());
    this->isAudioFile_ = res != FORMATS.end();
}

std::string FileFormat::completeFilepath() const {
    return this->complete_filepath_;
}
