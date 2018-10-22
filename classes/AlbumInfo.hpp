//
// Created by fra on 14/10/18.
//

#ifndef MUSICSERVER_ALBUMINFO_HPP
#define MUSICSERVER_ALBUMINFO_HPP

#include <string>

#include <json11.hpp>

class AlbumInfo {
private:
    ulong id_;
    uint year_;
    std::string title_;

public:
    AlbumInfo() = delete;

    AlbumInfo(ulong id, std::string title, uint year = 0) : id_{id}, title_{std::move(title)}, year_{year} {
        if (this->title_.empty())
            this->title_ = "Unknown Album";
    }

    std::string title() const;

    ulong id() const;

    uint year() const;

    json11::Json toJson() const;
};


#endif //MUSICSERVER_ALBUMINFO_HPP
