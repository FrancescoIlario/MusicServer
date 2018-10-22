//
// Created by fra on 13/10/18.
//

#ifndef MUSICSERVER_ARTISTAPI_HPP
#define MUSICSERVER_ARTISTAPI_HPP

#include <json11.hpp>
#include <pistache/http.h>
#include <pistache/router.h>

#include "../musiclibrary/MusicLibrary.hpp"

class ArtistApi {

public:
    ArtistApi() = default;

public:
    void getArtistInfo(const Pistache::Rest::Request &request,
                       Pistache::Http::ResponseWriter response);

    void getArtists(const Pistache::Rest::Request &request,
                    Pistache::Http::ResponseWriter response);

    void getArtistAlbums(const Pistache::Rest::Request &request,
                         Pistache::Http::ResponseWriter response);

};


#endif //MUSICSERVER_ARTISTAPI_HPP
