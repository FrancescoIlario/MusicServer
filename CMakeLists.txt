cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project(MusicServer)

include_directories(classes database database/filescanner musiclibrary rest)

add_executable(${PROJECT_NAME}
        database/filescanner/AudioInfo.cpp
        database/filescanner/AudioInfo.hpp
        database/filescanner/FileFormat.cpp
        database/filescanner/FileFormat.hpp
        database/filescanner/TrackScanner.cpp
        database/filescanner/TrackScanner.hpp
        classes/Song.cpp
        classes/Song.hpp
        classes/Album.cpp
        classes/Album.hpp
        classes/Artist.cpp
        classes/Artist.hpp
        classes/ArtistInfo.cpp
        classes/ArtistInfo.hpp
        classes/AlbumInfo.cpp
        classes/AlbumInfo.hpp
        rest/ArtistApi.cpp
        rest/ArtistApi.hpp
        rest/RestService.cpp
        rest/RestService.hpp
        musiclibrary/MusicLibrary.cpp
        musiclibrary/MusicLibrary.hpp
        rest/SongApi.cpp
        rest/SongApi.hpp
        rest/AlbumApi.cpp
        rest/AlbumApi.hpp
        musiclibrary/IndexManager.cpp
        musiclibrary/IndexManager.hpp
        main.cpp)

target_link_libraries(${PROJECT_NAME} stdc++fs zen dl mediainfo pthread tag pistache json11)
