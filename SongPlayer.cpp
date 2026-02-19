#include "SongPlayer.h"

SongPlayer::SongPlayer() : m_filename(FILE_NAME) {}

SongPlayer::SongPlayer(string filename) : m_filename(filename) {}

SongPlayer::~SongPlayer() {
    int size = (int) m_songCatalog.size();

    // De-allocate every song in catalog.
    for (int i = 0; i < size; i++) {
        delete m_songCatalog[i];
        m_songCatalog[i] = nullptr;
    }

    // Clear the vector so it no longer holds dangling pointers.
    m_songCatalog.clear();

    // Ensure that the playlist is also cleared.
    m_playList.Clear();
}

string SongPlayer::ToLower(string word) {
    int length = word.size();

    // Convert each letter in the word.
    for (int i = 0; i < length; i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}

void SongPlayer::LoadCatalog() {
    ifstream songFile;
    songFile.open(m_filename);

    // Check that file opened successfully.
    if (!songFile) {
        cout << "Error in opening file.";
        return;
    }

    string title, album, artist, spotify, youtube, tiktok;  // holds data extracted from file.

    // Loop runs until data corresponding to a Song object is not found, indicating the end of the file.
    while (getline(songFile, title, '|') && getline(songFile, album, '|') && getline(songFile, artist, '|') &&
           getline(songFile, spotify, '|') && getline(songFile, youtube, '|') && getline(songFile, tiktok)) {

        long spotifyConversion = stol(spotify); // convert before assignment.
        long youtubeConversion = stol(youtube);
        long tiktokConversion = stol(tiktok);

        // Add song with data to catalog.
        Song* newSong = new Song(title, album, artist, spotifyConversion, youtubeConversion, tiktokConversion);
        m_songCatalog.push_back(newSong);
    }

    songFile.close();
}

void SongPlayer::MainMenu() {
    int choice = 0;

    // Keep showing menu until user chooses to quit.
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Display Song by Title, Artist, and Album" << endl;
        cout << "2. Add Song to Playlist" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Sort Playlist by Spotify Streams" << endl;
        cout << "5. Quit" << endl;

        cin >> choice;

        switch (choice) {
            case 1:
                // User searches catalog to find matching songs.
                cout << DisplaySong() << " songs found." << endl;
                break;
            case 2:
                // User adds a song to their playlist.
                cout << "Choose the song you would like to add to the playlist." << endl;
                AddSong();
                break;
            case 3:
                // The current playlist is shown in order.
                DisplayPlaylist();
                break;
            case 4:
                // The playlist is organized by number of Spotify streams.
                SortPlaylist();
                break;
            case 5:
                // End of program.
                cout << "Thank you for using the UMBC Song Player!" << endl;
                break;
            default:
                // Ensure user choice is valid.
                cout << "Invalid choice. Choose an option (1-5)" << endl;
        }
    }while (choice != 5);
}

int SongPlayer::DisplaySong() {
    int choice = SearchOptions(); // ask user to search by artist or title.
    int songCount = 0; // keeps track of songs found.

    // Determine how user wants to search.
    string type;
    if (choice == 1) {
        type = "artist";
    }else {
        type = "title";
    }

    string searchFor = ToLower(SearchType(type)); // determine what user specifically wants to search for.

    // Search through song catalog.
    for (vector<Song*>::iterator it = m_songCatalog.begin(); it != m_songCatalog.end(); it++) {

        Song* currentSong = *it;

        // Determine which part of the song object we need to search for.
        string searchIn;
        if (type == "artist") {
            searchIn = ToLower(currentSong->GetArtist());
        }else {
            searchIn = ToLower(currentSong->GetTitle());
        }

        // Now, check if the user's word shows up anywhere in the song's title or artist data.
        bool match = false;

        int searchInLength = searchIn.length();
        int searchForLength = searchFor.length();

        // Only check user's input if it is at least the size of a given song's data.
        if ((searchForLength > 0) && (searchForLength <= searchInLength)) {

            // Try starting at each position in the song text.
            for (int i = 0; i <= (searchInLength - searchForLength) && (!match); i ++) {
                int j = 0;

                // Move forward while characters keep matching.
                while (j < searchForLength && searchIn[i + j] == searchFor[j]) {
                    j++;
                }

                // If every character was matched, then this means the user's word appears there.
                if (j == searchForLength) {
                    match = true;
                }
            }
        }

        // Executes if song is found.
        if (match == true) {
            // Determine the song's position in the vector.
            int index = it - m_songCatalog.begin();

            // Output songs that contain a match.
            cout << index << " " << (**it);

            songCount++;
        }
    }
    return songCount;
}

int SongPlayer::SearchOptions() {
    int option;

    // Ensures that user chooses a valid menu option.
    do {
        cout << "Would you rather search by artist or title?" << endl << "1. Artist" << endl << "2. Title" << endl;
        cin >> option;
    }while (option != 1 && option != 2);

    return option;
}

string SongPlayer::SearchType(string type) {
    string choice;

    // Determine artist name.
    if (type == "artist") {
        cout << "Which artist would you like to display?" << endl;
        cin >> choice;
        return choice;
    }
    // Determine title.
    if (type == "title") {
        cout << "Which title would you like to display?" << endl;
        cin >> choice;
        return choice;
    }

    return "";
}

void SongPlayer::AddSong() {
    // User searches for song of their choice.
    int numSongs = DisplaySong();
    cout << numSongs << " songs found." << endl;

    // If no songs were found, there is nothing to add.
    if (numSongs == 0) {
        return;
    }

    // User chooses which song to add to their playlist by index.
    int addSong;
    int catalogSize = (int)m_songCatalog.size();
    do {
        cout << "Enter the number of the song you would like to add:" << endl;
        cin >> addSong;
    }while ((addSong < 0) || (addSong >= catalogSize));

    // Retrieve chosen song from the catalog and add to playlist.
    Song* songChoice = m_songCatalog[addSong];
    m_playList.PushBack(songChoice);
    cout << (*songChoice) << " added to the playlist." << endl;
}

void SongPlayer::SortPlaylist() {
    // If there are no songs, we cannot sort anything.
    if (m_playList.IsEmpty()) {
        cout << "No songs in playlist." << endl;
        return;
    }

    // Sort the playlist.
    m_playList.Sort();
    cout << "Done sorting by Spotify streams" << endl;
    cout << m_playList.GetSize() << " items sorted." << endl;
}

void SongPlayer::DisplayPlaylist() {
    // If there are no songs in the playlist, notify user.
    if (m_playList.IsEmpty()) {
        cout << "No songs in playlist." << endl;
        return;
    }

    Queue<Song*> copy = m_playList; // make a copy of the playlist so that we can make changes without affecting the original.
    int index = 1;

    // Go through the copied playlist front to end and show each song.
    while (copy.IsEmpty() == false) {
        Song* currentSong = copy.PopFront();
        cout << index << ". " << (*currentSong) << endl;
        index++;
    }
}

void SongPlayer::StartPlayer() {
    // Load all the songs from the file into our song catalog.
    LoadCatalog();

    // Tell user how many songs were loaded.
    int size = (int) m_songCatalog.size();
    cout << size << " song files loaded." << endl;

    // Now, rest of program logic runs.
    MainMenu();
}
