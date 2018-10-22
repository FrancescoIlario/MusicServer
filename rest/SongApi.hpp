//
// Created by fra on 15/10/18.
//

#ifndef MUSICSERVER_SONGAPI_HPP
#define MUSICSERVER_SONGAPI_HPP

#include <memory>
#include <fstream>

#include <json11.hpp>
#include <pistache/http.h>

#include <pistache/router.h>
#include <Song.hpp>
#include "../musiclibrary/MusicLibrary.hpp"


class SongApi {
private:
    inline std::string serializeSong(std::string path) const;

public:
    void getSong(const Pistache::Rest::Request &request,
                    Pistache::Http::ResponseWriter response);

    void getSongComplete(const Pistache::Rest::Request &request,
                 Pistache::Http::ResponseWriter response);

};


#endif //MUSICSERVER_SONGAPI_HPP
