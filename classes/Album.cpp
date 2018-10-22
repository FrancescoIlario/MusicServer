//
// Created by fra on 12/10/18.
//

#include <json11.hpp>
#include <iostream>
#include "Album.hpp"

uint Album::year() const {
    return this->albumInfo_.year();
}

std::string Album::title() const {
    return this->albumInfo_.title();
}

std::vector <Song> Album::songs() const {
    return this->songs_;
}

json11::Json Album::toJson(bool songs) {
    auto jsonAlbum = this->albumInfo().toJson();
    auto jsonArtist = this->artistInfo().toJson();

    auto jsonComplete = json11::Json::object{{"album_info", jsonAlbum},
                                             {"artist_info",  jsonArtist}};
    if (songs) {
        json11::Json::array jsonSongs{};
        for (auto &song : this->songs()) {
            jsonSongs.push_back(song.toJson());
        }
        jsonComplete["songs"] = jsonSongs;
    }

    return std::move(jsonComplete);
}


ulong Album::id() const {
    return this->albumInfo_.id();
}

void Album::addSong(Song &song) {
    this->songs_.push_back(song);
}

const ArtistInfo &Album::artistInfo() const {
    return this->artistInfo_;
}

const AlbumInfo &Album::albumInfo() const {
    return this->albumInfo_;
}
