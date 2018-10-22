#include <iostream>
#include <thread>

#include <cxxopts.hpp>

#include "rest/RestService.hpp"

int main(int argc, char **argv) {
    cxxopts::Options options{"MusicServer", "Lightweight REST MusicServer"};

    options.add_options()
            ("m,music-dir", "Directory where to look for music", cxxopts::value<std::string>())
            ("i,index-dir", "Directory where to look for index", cxxopts::value<std::string>())
            ("p,create-index-dir", "Create index directory if needed", cxxopts::value<bool>())
            ("h,help", "print help", cxxopts::value<bool>());

    auto result = options.parse(argc, argv);

    if (result.count("h")) {
        std::cout << options.help();
        return 0;
    }

    MusicLibraryFactory factory{};
    if (result.count("m")) {
        std::filesystem::path path{result["m"].as<std::string>()};

        if (!std::filesystem::exists(path)) {
            std::cerr << path << " is not a valid music directory path" << std::endl;
            return -1;
        }

        // Init Music Library Factory
        factory.setMusicPath(path);
    } else {
        std::cerr << "A valid music directory path is required" << std::endl;
        std::cout << options.help();
        return -1;
    }


    if (result.count("i")) {
        std::filesystem::path path{result["i"].as<std::string>()};
        if (result.count("p")) {
            std::filesystem::create_directories(path);
        }

        if (!std::filesystem::exists(path)) {
            std::cerr << path << " is not a valid path for index" << std::endl;
            return -1;
        }
        factory.setIndexPath(path);
    }
    factory.build();

    // launch server
    std::unique_ptr<std::thread> rs{new std::thread{[]() {
        RestService restService{};
        restService.start();
    }}};
    rs->join();

    return 0;
}


