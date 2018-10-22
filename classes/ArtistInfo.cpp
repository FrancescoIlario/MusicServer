//
// Created by fra on 14/10/18.
//

#include "ArtistInfo.hpp"

ulong ArtistInfo::id() const {
    return this->id_;
}

std::string ArtistInfo::name() const {
    return this->name_;
}

json11::Json ArtistInfo::toJson() const {
    json11::Json artistJson = json11::Json::object{
            {"id",   std::to_string(this->id())},
            {"name", this->name()}
    };
    return artistJson;
}
