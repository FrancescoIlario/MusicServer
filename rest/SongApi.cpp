//
// Created by fra on 15/10/18.
//

#include "SongApi.hpp"

void SongApi::getSong(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    if (!request.hasParam(":id")) {
        response.send(Pistache::Http::Code::Bad_Request);
        return;
    }

    auto songId = request.param(":id").as<uint>();
    auto musicLibrary = MusicLibraryFactory{}.musicLibrary();
    std::unique_ptr<Song> song{musicLibrary->getSong(songId)};
    if (!song) {
        response.send(Pistache::Http::Code::Not_Found, "Song not found");
        return;
    }

    response.send(Pistache::Http::Code::Ok, serializeSong(song->path()));
}

void SongApi::getSongComplete(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    if (!request.hasParam(":arid") || !request.hasParam(":alid") || !request.hasParam(":sid")) {
        response.send(Pistache::Http::Code::Bad_Request);
        return;
    }

    auto artistId = request.param(":arid").as<uint>();
    auto albumId = request.param(":alid").as<uint>();
    auto songId = request.param(":sid").as<uint>();

    auto ml = MusicLibraryFactory{}.musicLibrary();
    if (!ml->existArtist(artistId)) {
        response.send(Pistache::Http::Code::Not_Found, "Artist not found");
        return;
    }

    std::unique_ptr<Album> album{ml->getAlbum(albumId)};
    if (!album) {
        response.send(Pistache::Http::Code::Not_Found, "Album not found");
        return;
    }
    if (album->artistInfo().id() != artistId) {
        response.send(Pistache::Http::Code::Not_Found, "Album not found for the given artist");
        return;
    }

    std::unique_ptr<Song> song{ml->getSong(songId)};
    if (!song) {
        response.send(Pistache::Http::Code::Not_Found, "Song not found");
        return;
    }

    if (song->album().id() != albumId) {
        response.send(Pistache::Http::Code::Not_Found, "Song not found in the given album");
        return;
    }

    // send song
    response.send(Pistache::Http::Code::Ok, serializeSong(song->path()));
}

std::string SongApi::serializeSong(std::string path) const {
    std::filesystem::path _path{std::move(path)};
    std::ifstream isong{_path, std::ios::binary};
    std::ostringstream ostringstream{};

    std::copy(
            std::istreambuf_iterator<char>(isong),
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(ostringstream));

    return ostringstream.str();
}

