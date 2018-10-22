#include <utility>

//
// Created by fra on 14/10/18.
//

#ifndef MUSICSERVER_MUSICLIBRARY_HPP
#define MUSICSERVER_MUSICLIBRARY_HPP

#include <vector>
#include <atomic>
#include <cassert>
#include <mutex>

#include <Artist.hpp>
#include <Album.hpp>
#include <Song.hpp>
#include <AudioInfo.hpp>
#include <TrackScanner.hpp>

class AbstractMusicLibrary {
protected:
    std::mutex ds_m_;
    std::vector<Artist> artists_{};
    std::vector<Album> albums_{};
    std::vector<Song> songs_{};

    std::string music_path_{};
    std::string index_path_{};
public:
    AbstractMusicLibrary() = delete;

    explicit AbstractMusicLibrary(std::string music_path, std::string index_path = "") : music_path_{
            std::move(music_path)}, index_path_{std::move(index_path)} {}

    virtual ~AbstractMusicLibrary() = 0;

    virtual bool existArtist(uint id) = 0;

    virtual Artist *getArtistInfo(uint i) = 0;

    virtual std::vector<ArtistInfo> getArtistsInfo() = 0;

    virtual std::vector<AlbumInfo> getArtistAlbums(uint artistId) = 0;

    virtual Album *getAlbum(uint albumId) = 0;

    virtual Song *getSong(uint songId) = 0;
};

class MusicLibraryFactory {
private:
    class MusicLibrary : public AbstractMusicLibrary {
    private:
        void registerSong(const AudioInfo &audioInfo);

    public:
        MusicLibrary() = delete;

        MusicLibrary(std::string music_path, std::string index_path = "");

        MusicLibrary(const MusicLibrary &) = delete;

        MusicLibrary &operator=(const MusicLibrary &) = delete;

        MusicLibrary(MusicLibrary &&) = delete;

        MusicLibrary &operator=(MusicLibrary &&) = delete;

        ~MusicLibrary() override = default;

        bool existArtist(uint id) override;

        Artist *getArtistInfo(uint artistId) override;

        std::vector<ArtistInfo> getArtistsInfo() override;

        std::vector<AlbumInfo> getArtistAlbums(uint artistId) override;

        Album *getAlbum(uint albumId) override;

        Song *getSong(uint songId) override;
    };

private:
    static AbstractMusicLibrary *MusicLibrary_;

    std::string music_path_, index_path_;

public:
    MusicLibraryFactory setMusicPath(std::string path);

    MusicLibraryFactory setIndexPath(std::string path);

    void build();

    AbstractMusicLibrary *musicLibrary();
};


#endif //MUSICSERVER_MUSICLIBRARY_HPP
