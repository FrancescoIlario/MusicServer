//
// Created by fra on 13/10/18.
//

#ifndef MUSICSERVER_RESTSERVICE_HPP
#define MUSICSERVER_RESTSERVICE_HPP

#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "ArtistApi.hpp"
#include "AlbumApi.hpp"
#include "SongApi.hpp"

class RestService {

private:
    uint16_t port_{9080};
    uint threads_{1};

protected:
    Pistache::Http::Endpoint *endpoint;

private:
    void init();

public:
    RestService();
    explicit RestService(uint16_t port);
    explicit RestService(uint threads);
    RestService(uint16_t port, uint threads);

    void start();

    void stop();
};


#endif //MUSICSERVER_RESTSERVICE_HPP
