//
// Created by fra on 14/10/18.
//

#ifndef MUSICSERVER_ARTISTINFO_HPP
#define MUSICSERVER_ARTISTINFO_HPP

#include <string>
#include <json11.hpp>

class ArtistInfo {
private:
    ulong id_;
    std::string name_;

public:
    ArtistInfo() = delete;

    ArtistInfo(ulong id, std::string name) : id_{id}, name_{std::move(name)} {
        if (this->name_.empty())
            this->name_ = "Unknown Artist";
    }

    ulong id() const;

    std::string name() const;

    json11::Json toJson() const;
};


#endif //MUSICSERVER_ARTISTINFO_HPP
