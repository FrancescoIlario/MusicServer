#include <utility>

//
// Created by fra on 12/10/18.
//

#ifndef MUSICSERVER_ARTIST_HPP
#define MUSICSERVER_ARTIST_HPP

#include <string>
#include <vector>

#include <json11.hpp>

#include <Album.hpp>

class Artist {
private:
    ArtistInfo artistInfo_;
    std::vector<AlbumInfo> albumsInfo_{};

public:
    Artist(ulong id, std::string name) : artistInfo_{id, std::move(name)} {}

    std::string name() const;

    ulong id() const;

    void addAlbum(AlbumInfo albumInfo);

    const ArtistInfo &artistInfo() const;

    std::vector<AlbumInfo> &albumsInfo();

    std::string toJson(bool albumsInfo = false);
};

#endif //MUSICSERVER_ARTIST_HPP
