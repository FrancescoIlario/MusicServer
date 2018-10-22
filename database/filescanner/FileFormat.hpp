#ifndef FILEFORMAT_HPP
#define FILEFORMAT_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class FileFormat {
private:
  std::string complete_filepath_, filepath_, filename_, format_;
  bool isAudioFile_ = false;

public:
  static const std::vector<std::string> FORMATS;

public:
  FileFormat() = delete;

  explicit FileFormat(const std::string &filepath);

  FileFormat(const FileFormat &) = default;
  FileFormat &operator=(const FileFormat &) = default;

  FileFormat(FileFormat &&) = default;
  FileFormat &operator=(FileFormat &&) = default;

  std::string completeFilepath() const;
  std::string filepath() const;
  std::string filename() const;
  std::string format() const;

  friend inline std::ostream &operator<<(std::ostream &out,
                                         const FileFormat &format) {
    out << "[" << format.filepath() << ", " << format.filename() << ", "
        << format.format() << ", Audio: " << (format.isAudioFile() ? "Y" : "N")
        << "]";
    return out;
  }
  bool isAudioFile() const;
};

#endif // FILEFORMAT_HPP
