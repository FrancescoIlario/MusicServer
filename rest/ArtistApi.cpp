//
// Created by fra on 13/10/18.
//

#include "ArtistApi.hpp"

void ArtistApi::getArtistInfo(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    if (!request.hasParam((":id"))) {
        response.send(Pistache::Http::Code::Bad_Request, "Artist id not found");
        return;
    }

    auto idS = request.param(":id").as<std::string>();
    auto id = static_cast<uint>(std::stoul(idS, nullptr, 10));
    if (std::to_string(id) != idS) {
        response.send(Pistache::Http::Code::Bad_Request, "Artist id not valid");
        return;
    }

    auto musicLibrary = MusicLibraryFactory{}.musicLibrary();
    std::unique_ptr<Artist> artist{musicLibrary->getArtistInfo(id)};

    if (!artist) {
        response.send(Pistache::Http::Code::Not_Found, "Artist not found");
        return;
    }

    response.send(Pistache::Http::Code::Ok, artist->artistInfo().toJson().dump());
}


void ArtistApi::getArtists(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    std::cout << "Get Artists Query received" << std::endl;
    auto dbm = MusicLibraryFactory{}.musicLibrary();
    auto artists = dbm->getArtistsInfo();

    json11::Json::array jsonArray{};
    for (auto &artist: artists)
        jsonArray.push_back(artist.toJson());

    response.send(Pistache::Http::Code::Ok, json11::Json{jsonArray}.dump());
}

void ArtistApi::getArtistAlbums(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    if (!request.hasParam(":id")) {
        response.send(Pistache::Http::Code::Bad_Request, "Artist id not found");
        return;
    }

    auto idS = request.param(":id").as<std::string>();
    auto id = static_cast<uint>(std::stoul(idS, nullptr, 10));
    if (std::to_string(id) != idS) {
        response.send(Pistache::Http::Code::Bad_Request, "Artist id not valid");
        return;
    }
    auto musicLibrary = MusicLibraryFactory{}.musicLibrary();

    if (!musicLibrary->existArtist(id)) {
        response.send(Pistache::Http::Code::Not_Found, "Artist not found");
        return;
    }

    auto albums = musicLibrary->getArtistAlbums(id);
    json11::Json::array albumsJson{};
    for (auto &album : albums)
        albumsJson.push_back(album.toJson());

    response.send(Pistache::Http::Code::Ok, json11::Json{albumsJson}.dump());
}


