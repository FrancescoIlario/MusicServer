//
// Created by fra on 12/10/18.
//

#include "Song.hpp"

const AlbumInfo &Song::album() const {
    return this->albumInfo_;
}

std::string Song::title() const {
    return this->title_;
}

const ArtistInfo &Song::artist() const {
    return this->artistInfo_;
}

ulong Song::id() const {
    return this->song_id_;
}

uint Song::year() const {
    return this->year_;
}

uint Song::trackNumber() const {
    return this->track_no_;
}

std::string Song::path() const {
    return this->path_;
}

json11::Json Song::toJson() const {
    json11::Json jsonSong = json11::Json::object{
            {"id",           std::to_string(this->id())},
            {"album",        this->albumInfo_.toJson()},
            {"artist",       this->artistInfo_.toJson()},

            {"title",        this->title()},
            {"year",         std::to_string(this->year())},
            {"track_number", std::to_string(this->trackNumber())}
    };

    return jsonSong;
}
