#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ================= TRACK =================
class Track {
private:
    static int idCounter;
    int id;
    string title;
    string artist;
    int duration;
    string link;
    int playCount;

public:
    Track(string t, string a, int d, string l) {
        id = ++idCounter;
        title = t;
        artist = a;
        duration = d;
        link = l;
        playCount = 0;
    }

    int getId() const { return id; }
    string getTitle() const { return title; }
    int getDuration() const { return duration; }
    int getPlayCount() const { return playCount; }

    void play() { playCount++; }
};

int Track::idCounter = 0;

// ================= USER =================
class User {
private:
    string name;

public:
    User(string n) { name = n; }
    string getName() const { return name; }
};

// ================= PLAYLIST =================
class Playlist {
private:
    string name;
    vector<Track*> tracks;

public:
    Playlist(string n) { name = n; }

    void addTrack(Track* track) {
        tracks.push_back(track);
    }

    string getName() const { return name; }
};

// ================= REPOSITORY =================
class InMemoryTrackRepository {
private:
    vector<Track*> tracks;

public:
    void save(Track* track) {
        tracks.push_back(track);
    }

    vector<Track*> findAll() {
        return tracks;
    }

    Track* findById(int id) {
        for (auto t : tracks) {
            if (t->getId() == id)
                return t;
        }
        return nullptr;
    }
};

// ================= SERVICE =================
class StreamService {
private:
    InMemoryTrackRepository* repo;

public:
    StreamService(InMemoryTrackRepository* r) {
        repo = r;
    }

    void addTrack(Track* track) {
        repo->save(track);
    }

    Playlist* createPlaylistForUser(User& user, string name) {
        return new Playlist(name);
    }

    void addTrackToPlaylist(Playlist* playlist, Track* track) {
        playlist->addTrack(track);
    }

    void playTrack(int id) {
        Track* track = repo->findById(id);
        if (track) {
            track->play();
            cout << "Playing: " << track->getTitle() << endl;
        } else {
            cout << "Track not found!" << endl;
        }
    }

    vector<Track*> topTracks(int n) {
        vector<Track*> all = repo->findAll();

        sort(all.begin(), all.end(), [](Track* a, Track* b) {
            return a->getPlayCount() > b->getPlayCount();
        });

        if (n > all.size()) n = all.size();

        return vector<Track*>(all.begin(), all.begin() + n);
    }
};

// ================= MAIN =================
int main() {
    cout << "Student Name: Shashank Kumar\n\n";
    cout << "******** MUSIC PLAYER SYSTEM ********\n\n";

    InMemoryTrackRepository repo;
    StreamService service(&repo);

    // Admin Upload Songs
    cout << "Admin Uploading Songs...\n\n";

    Track* song1 = new Track("Song1", "Admin", 180, "link://song1");
    Track* song2 = new Track("Song2", "Admin", 210, "link://song2");
    Track* song3 = new Track("Song3", "Admin", 150, "link://song3");

    service.addTrack(song1);
    service.addTrack(song2);
    service.addTrack(song3);

    cout << "Songs Uploaded Successfully\n\n";

    // Show Database
    cout << "All Songs In Database:\n";
    vector<Track*> allSongs = repo.findAll();

    for (auto t : allSongs) {
        cout << t->getId() << " - "
             << t->getTitle() << " ("
             << t->getDuration() << " sec)\n";
    }

    // Create User
    User user("Nishant");
    Playlist* playlist = service.createPlaylistForUser(user, "MyPlaylist");

    cout << "\nUser Created: " << user.getName() << endl;
    cout << "Playlist Created: MyPlaylist\n\n";

    // Add Songs To Playlist
    service.addTrackToPlaylist(playlist, song1);
    service.addTrackToPlaylist(playlist, song2);

    cout << "Songs Added To Playlist\n\n";

    // Play Songs
    cout << "Playing Song1...\n";
    service.playTrack(song1->getId());

    cout << "Stopping Song1\n\n";

    cout << "Playing Song2...\n";
    service.playTrack(song2->getId());
    service.playTrack(song2->getId());

    cout << "Stopping Song2\n\n";

    // Top Songs
    cout << "Most Played Songs:\n";
    vector<Track*> topSongs = service.topTracks(2);

    for (auto t : topSongs) {
        cout << t->getTitle() << " -> "
             << t->getPlayCount() << " plays\n";
    }

    cout << "\nSystem Finished\n";

    return 0;
}