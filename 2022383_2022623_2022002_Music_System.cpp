#include <iostream>
#include <string>
#include <vector>
#include <Windows.h> // Include Windows.h for PlaySound

#pragma comment(lib, "winmm.lib")
class Song
{
public:
    Song(std::string title, std::string artist) : title_{title}, artist_{artist} {}

    std::string getTitle() const
    {
        return title_;
    }

    std::string getArtist() const
    {
        return artist_;
    }

private:
    std::string title_;
    std::string artist_;
};

class Playlist
{
public:
    Playlist() = default; // Default constructor

    Playlist(std::string name) : name_{name} {}

    void addSong(const Song &song)
    {
        songs_.push_back(song);
        std::cout << "Added song: " << song.getTitle() << std::endl;
    }

    void removeSong(const Song &song)
    {
        for (auto it = songs_.begin(); it != songs_.end(); ++it)
        {
            if (it->getTitle() == song.getTitle())
            {
                songs_.erase(it);
                std::cout << "Removed song: " << song.getTitle() << std::endl;
                return;
            }
        }
        std::cout << "Song not found in playlist." << std::endl;
    }

    void printPlaylist() const
    {
        std::cout << "Playlist: " << std::endl;
        for (int i = 0; i < songs_.size(); ++i)
        {
            std::cout << i << ": " << songs_[i].getTitle() << " by " << songs_[i].getArtist() << std::endl;
        }
    }

    void play() const
    {
        if (songs_.empty())
        {
            std::cout << "Playlist is empty." << std::endl;
            return;
        }

        // Print playlists
        std::cout << "Playlists: " << std::endl;
        for (int i = 0; i < playlists_.size(); ++i)
        {
            std::cout << i << ": " << playlists_[i].name_ << std::endl;
        }

        nt playlistChoice;
        std::cout << "Choose a playlist: ";
        std::cin >> playlistChoice;

        if (playlistChoice < 0 || playlistChoice >= playlists_.size())
        {
            std::cout << "Invalid playlist choice." << std::endl;
            return;
        }

        const Playlist &selectedPlaylist = playlists_[playlistChoice];
        selectedPlaylist.printPlaylist();

        int songChoice;
        std::cout << "Choose a song from the playlist: ";
        std::cin >> songChoice;

        if (songChoice < 0 || songChoice >= selectedPlaylist.songs_.size())
        {
            std::cout << "Invalid song choice." << std::endl;
            return;
        }

        const Song &selectedSong = selectedPlaylist.songs_[songChoice];
        std::cout << "Playing: " << selectedSong.getTitle() << std::endl;
        PlaySound(TEXT("song.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }

    void pause() const
    {
        PlaySound(NULL, NULL, SND_ASYNC); // Stop the playback
        std::cout << "Pausing the song." << std::endl;
    }

    void changeVolume(int volume)
    {
        // Add your implementation to adjust the volume
        std::cout << "Changing volume to: " << volume << std::endl;
    }

    static std::vector<Playlist> playlists_;

private:
    std::string name_;
    std::vector<Song> songs_;
};

std::vector<Playlist> Playlist::playlists_;
int main() {
    
        Playlist::playlists_.push_back(Playlist("My Playlist"));

    int choice;
    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add Song" << std::endl;
        std::cout << "2. Remove Song" << std::endl;
        std::cout << "3. Print Playlist" << std::endl;
        std::cout << "4. Play Song" << std::endl;
        std::cout << "5. Pause Song" << std::endl;
        std::cout << "6. Change Volume" << std::endl;
        std::cout << "7. Exit" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string title, artist;
            std::cout << "Enter song title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter artist name: ";
            std::getline(std::cin, artist);

            Song song(title, artist);
            Playlist::playlists_[0].addSong(song);
            break;
        }
        case 2: {
            std::string title, artist;
            std::cout << "Enter song title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter artist name: ";
            std::getline(std::cin, artist);

            Song song(title, artist);
            Playlist::playlists_[0].removeSong(song);
            break;
        }
        case 3:
            Playlist::playlists_[0].printPlaylist();
            break;
        case 4:
            Playlist::playlists_[0].play();
            break;
        case 5:
            Playlist::playlists_[0].pause();
            break;
        case 6: {
            int volume;
            std::cout << "Enter volume level: ";
            std::cin >> volume;
            Playlist::playlists_[0].changeVolume(volume);
            break;
        }
        case 7:
            std::cout << "Exiting the program." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }

    return 0;
}
