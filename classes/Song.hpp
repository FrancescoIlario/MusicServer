#include <utility>

//
// Created by fra on 12/10/18.
//

#ifndef MUSICSERVER_SONG_HPP
#define MUSICSERVER_SONG_HPP

#include <string>
#include <json11.hpp>
#include "ArtistInfo.hpp"
#include "AlbumInfo.hpp"

class Song {
private:
    ulong song_id_;
    std::string title_;
    uint track_no_, year_;

    ArtistInfo artistInfo_;
    AlbumInfo albumInfo_;

    /* internal */
    std::string path_;

public:
    Song() = delete;

    Song(ulong song_id, std::string title, uint year, uint track_no, AlbumInfo albumInfo, ArtistInfo artistInfo,
         std::string path) : song_id_{song_id}, title_{std::move(title)}, year_{year}, track_no_{track_no},
                             albumInfo_{std::move(albumInfo)}, artistInfo_{std::move(artistInfo)},
                             path_{std::move(path)} {
        if (this->title_.empty())
            this->title_ = "Unknown Song";
    }

    std::string title() const;

    const AlbumInfo &album() const;

    const ArtistInfo &artist() const;

    ulong id() const;

    uint year() const;

    uint trackNumber() const;

    std::string path() const;

    json11::Json toJson() const;
};


#endif //MUSICSERVER_SONG_HPP
