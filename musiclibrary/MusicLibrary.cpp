//
// Created by fra on 14/10/18.
//

#include <thread>
#include "MusicLibrary.hpp"
#include "IndexManager.hpp"

void MusicLibraryFactory::MusicLibrary::registerSong(const AudioInfo &audioInfo) {
    std::lock_guard lock{this->ds_m_};
    auto audioData = audioInfo.getAudioData();
    auto artistName = audioData.author_;
    auto albumTitle = audioData.album_;

    // find artist
    auto artistIterator = std::find_if(artists_.begin(), artists_.end(),
                                       [&artistName](const Artist &artist) { return artist.name() == artistName; });
    Artist *artist = (artistIterator == artists_.end()) ? &artists_.emplace_back(artists_.size() + 1, artistName)
                                                        : artistIterator.base();

    // find album
    auto albumsInfo = artist->albumsInfo();
    auto albumIterator = std::find_if(albumsInfo.begin(), albumsInfo.end(), [&albumTitle](const AlbumInfo &lAlbum) {
        return lAlbum.title() == albumTitle;
    });

    ulong albumId{};
    if (albumIterator == albumsInfo.end()) {
        AlbumInfo albumInfo{albums_.size(), albumTitle};
        artist->addAlbum(albumInfo);
        Album album{albumInfo, artist->artistInfo()};
        this->albums_.push_back(std::move(album));
        albumId = albumInfo.id();
    } else {
        albumId = albumIterator->id();
    }
    Album &album = albums_.at(albumId);

    // add song to album
    Song song{songs_.size(), audioData.title_, audioData.year_, audioData.track_no_, album.albumInfo(),
              artist->artistInfo(), audioData.completeFilepath_};
    album.addSong(song);
    songs_.push_back(std::move(song));
}

std::vector<ArtistInfo> MusicLibraryFactory::MusicLibrary::getArtistsInfo() {
    std::lock_guard lock{this->ds_m_};
    std::vector<ArtistInfo> artistsInfo{};
    for (const auto &artist: artists_) {
        artistsInfo.push_back(artist.artistInfo());
    }
    return artistsInfo;
}

std::vector<AlbumInfo> MusicLibraryFactory::MusicLibrary::getArtistAlbums(uint artistId) {
    std::lock_guard lock{this->ds_m_};
    return (artists_.size() > artistId) ? artists_[artistId - 1].albumsInfo() : std::vector<AlbumInfo>{};
}

MusicLibraryFactory::MusicLibrary::MusicLibrary(std::string music_path, std::string index_path) : AbstractMusicLibrary{
        std::move(music_path), std::move(index_path)} {
    new std::thread{
            [=]() {

                std::unique_ptr<Index<AudioInfoData>> idx{IndexManager{index_path_}.readIndex()};
                auto count = 0;
                if (!idx) {
                    TrackScanner scanner{this->music_path_};
                    scanner.start();
                    auto data = scanner.getData();

                    IndexManager idxManager{this->index_path_};
                    for (auto &d: *data) {
                        AudioInfo audioInfo{d};
                        this->registerSong(audioInfo);
                        idxManager.collect(audioInfo.getAudioData());
                        std::cout << "\r" << ++count << "/" << data->size() << std::flush;
                    }
                    idxManager.closeIndex();
                } else {
                    for (auto &d : idx->getData()) {
                        AudioInfo audioInfo{d};
                        this->registerSong(audioInfo);
                        std::cout << "\r" << ++count << "/" << idx->getData().size() << std::flush;
                    }
                    std::cout << std::endl;
                }
            }
    };
}

bool MusicLibraryFactory::MusicLibrary::existArtist(uint artistId) {
    std::lock_guard lock{this->ds_m_};
    return this->artists_.size() > artistId;
}

Song *MusicLibraryFactory::MusicLibrary::getSong(uint songId) {
    std::lock_guard lock{this->ds_m_};
    return (songs_.size() > songId) ? new Song{songs_[songId]} : nullptr;
}

Album *MusicLibraryFactory::MusicLibrary::getAlbum(uint albumId) {
    std::lock_guard lock{this->ds_m_};
    return (albums_.size() > albumId) ? new Album{albums_[albumId]} : nullptr;
}

Artist *MusicLibraryFactory::MusicLibrary::getArtistInfo(uint artistId) {
    std::lock_guard lock{this->ds_m_};
    return (this->artists_.size() > artistId) ? new Artist{artists_[artistId]} : nullptr;
}

AbstractMusicLibrary::~AbstractMusicLibrary() = default;

// MusicLibraryFactory
AbstractMusicLibrary *MusicLibraryFactory::MusicLibrary_{nullptr};

void MusicLibraryFactory::build() {
    if (!MusicLibraryFactory::MusicLibrary_)
        MusicLibraryFactory::MusicLibrary_ = new MusicLibrary{this->music_path_, this->index_path_};
}

AbstractMusicLibrary *MusicLibraryFactory::musicLibrary() {
    assert(MusicLibrary_);
    return MusicLibraryFactory::MusicLibrary_;
}

MusicLibraryFactory MusicLibraryFactory::setMusicPath(std::string path) {
    this->music_path_ = std::move(path);
    return *this;
}

MusicLibraryFactory MusicLibraryFactory::setIndexPath(std::string path) {
    this->index_path_ = std::move(path);
    return *this;
}
