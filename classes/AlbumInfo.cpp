//
// Created by fra on 14/10/18.
//

#include "AlbumInfo.hpp"

std::string AlbumInfo::title() const {
    return this->title_;
}

ulong AlbumInfo::id() const {
    return this->id_;
}

uint AlbumInfo::year() const {
    return this->year_;
}

json11::Json AlbumInfo::toJson() const {
    json11::Json albumJson = json11::Json::object{
            {"id",    std::to_string(this->id())},
            {"title", this->title()},
            {"year",  std::to_string(this->year())}
    };
    return albumJson;
}
