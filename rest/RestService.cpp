//
// Created by fra on 13/10/18.
//

#include "RestService.hpp"

RestService::RestService(uint16_t port, uint threads) : port_{port}, threads_{threads} {
    init();
}

void RestService::start() {
    this->endpoint->serve();
}

void RestService::stop() {
    this->endpoint->shutdown();
}

void RestService::init() {
// set up rest server
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port_));
    auto opts = Pistache::Http::Endpoint::options().threads(threads_).flags(
            Pistache::Tcp::Options::InstallSignalHandler |
            Pistache::Tcp::Options::ReuseAddr);

    this->endpoint = new Pistache::Http::Endpoint(addr);
    this->endpoint->init(opts);

    ArtistApi artistApi;
    AlbumApi albumApi;
    SongApi songApi;

    Pistache::Rest::Router router{};

    // Artist
    Pistache::Rest::Routes::Get(router, "/artist/", Pistache::Rest::Routes::bind(&ArtistApi::getArtists, &artistApi));
    Pistache::Rest::Routes::Get(router, "/artist/:id",
                                Pistache::Rest::Routes::bind(&ArtistApi::getArtistInfo, &artistApi));
    Pistache::Rest::Routes::Get(router, "/artist/:id/album",
                                Pistache::Rest::Routes::bind(&ArtistApi::getArtistAlbums, &artistApi));

    Pistache::Rest::Routes::Get(router, "/artist/:arid/album/:alid/song/:sid",
                                Pistache::Rest::Routes::bind(&SongApi::getSongComplete, &songApi));
    // Song
    Pistache::Rest::Routes::Get(router, "/song/:id",
                                Pistache::Rest::Routes::bind(&SongApi::getSong, &songApi));
    // Album
    Pistache::Rest::Routes::Get(router, "/artist/:arid/album/:alid",
                                Pistache::Rest::Routes::bind(&AlbumApi::getArtistAlbum, &albumApi));

    this->endpoint->setHandler(router.handler());
}

RestService::RestService(uint threads) : threads_{threads} {
    init();
}

RestService::RestService(uint16_t port) : port_{port} {
    init();
}

RestService::RestService() {
    init();
}


