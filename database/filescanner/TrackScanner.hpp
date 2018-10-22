#ifndef TRACKSCANNER_HPP
#define TRACKSCANNER_HPP

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <MediaInfoDLL/MediaInfoDLL.h>

#include "FileFormat.hpp"

class TrackScanner {
private:
    std::string rootPath_;

    std::shared_ptr<std::vector<std::string>> V_{nullptr};

public:
    TrackScanner() = delete;

    ~TrackScanner() = default;

    TrackScanner(const TrackScanner &) = delete;

    TrackScanner &operator=(const TrackScanner &) = delete;

    TrackScanner(TrackScanner &&) = default;

    TrackScanner &operator=(TrackScanner &&) = default;

    explicit TrackScanner(std::string rootPath) : rootPath_{std::move(rootPath)} {}

    std::shared_ptr<std::vector<std::string>> getData() const;

    void start();

private:
    bool isAudioFileHeavy(const std::string &pathToFile) const;

    bool isAudioFileLight(const std::string &pathToFile) const;

    void scanDir(std::string path, bool verbose = false, uint level = 0) const;
};

#endif // TRACKSCANNER_HPP
