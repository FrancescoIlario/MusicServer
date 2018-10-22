#include "TrackScanner.hpp"


std::shared_ptr<std::vector<std::string>> TrackScanner::getData() const {
    return this->V_;
}

bool TrackScanner::isAudioFileHeavy(const std::string &pathToFile) const {
    MediaInfoDLL::MediaInfo mediainfo;
    mediainfo.Open(pathToFile);
    bool res = !mediainfo.Get(MediaInfoDLL::Stream_Audio, 0, 0).empty() &&
               mediainfo.Get(MediaInfoDLL::Stream_Video, 0, 0).empty();
    mediainfo.Close();
    return res;
}

bool TrackScanner::isAudioFileLight(const std::string &pathToFile) const {
    FileFormat fF{pathToFile};
    return fF.isAudioFile();
}

void TrackScanner::start() {
    this->V_ = std::make_unique<std::vector<std::string>>();
    scanDir(this->rootPath_, true);
}

void TrackScanner::scanDir(std::string path, bool verbose, uint level) const {
    std::filesystem::path _path{std::move(path)};
    std::filesystem::directory_iterator start(_path), end;

    if (verbose && level == 1) {
        std::cout << "\r[SCAN]\t" << _path << std::flush;
    }

    for (; start != end; start++) {
        if (start->is_regular_file()) {
            auto s = start->path().string();
            if (this->isAudioFileLight(s))
                this->V_->push_back(s);
        } else if (start->is_directory())
            scanDir(start->path().string(), verbose, level + 1);
    }
}
