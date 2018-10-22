//
// Created by fra on 15/10/18.
//

#include "AlbumApi.hpp"

void AlbumApi::getArtistAlbum(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    if (!request.hasParam(":arid") || !request.hasParam(":alid")) {
        response.send(Pistache::Http::Code::Bad_Request);
        return;
    }
    auto artistId = request.param(":arid").as<uint>();
    auto albumId = request.param(":alid").as<uint>();

    auto ml = MusicLibraryFactory{}.musicLibrary();
    if (!ml->existArtist(artistId)) {
        response.send(Pistache::Http::Code::Not_Found, "Artist not found");
        return;
    }

    std::unique_ptr <Album> album{ml->getAlbum(albumId)};
    if (!album || album->artistInfo().id() != artistId) {
        std::cout << "Album artist has id " << album->artistInfo().id() << " and the passed id is " << artistId
                  << std::endl;
        response.send(Pistache::Http::Code::Not_Found, "Album not found for the given artist");
        return;
    }

    response.send(Pistache::Http::Code::Ok, album->toJson(true).dump());
}
