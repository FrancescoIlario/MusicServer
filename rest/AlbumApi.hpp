//
// Created by fra on 15/10/18.
//

#ifndef MUSICSERVER_ALBUMAPI_HPP
#define MUSICSERVER_ALBUMAPI_HPP

#include <fstream>

#include <json11.hpp>
#include <pistache/http.h>

#include <pistache/router.h>
#include <Album.hpp>
#include "../musiclibrary/MusicLibrary.hpp"


class AlbumApi {
public:
    void getArtistAlbum(const Pistache::Rest::Request &request,
                        Pistache::Http::ResponseWriter response);

};


#endif //MUSICSERVER_ALBUMAPI_HPP
