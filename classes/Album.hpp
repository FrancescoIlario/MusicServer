//
// Created by fra on 12/10/18.
//

#ifndef MUSICSERVER_ALBUM_HPP
#define MUSICSERVER_ALBUM_HPP

#include <vector>
#include <Song.hpp>
#include "AlbumInfo.hpp"

class Album {
private:
    std::vector<Song> songs_{};
    AlbumInfo albumInfo_;
    ArtistInfo artistInfo_;

public:
    Album() = delete;

    Album(AlbumInfo albumInfo, ArtistInfo artistInfo, std::vector<Song> songs = {}, uint year = 0) : albumInfo_{
            std::move(albumInfo)}, artistInfo_{std::move(artistInfo)}, songs_{std::move(songs)} {}

    Album(const Album &) = default;

    Album &operator=(const Album &) = default;

    Album(Album &&) = default;

    Album &operator=(Album &&) = default;

    std::vector<Song> songs() const;

    std::string title() const;

    uint year() const;

    ulong id() const;

    const AlbumInfo &albumInfo() const;

    const ArtistInfo &artistInfo() const;

    json11::Json toJson(bool songs = false);

    // internal
    void addSong(Song &song);
};


#endif //MUSICSERVER_ALBUM_HPP
