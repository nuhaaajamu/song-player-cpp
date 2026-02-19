// Description: Describes the class named SongPlayer

#ifndef SONG_PLAYER_H
#define SONG_PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include "Song.h"
#include "Queue.cpp"

using namespace std;

const string FILE_NAME = "proj5_songs.txt"; // Used in default SongPlayer constructor

class SongPlayer{
 public:
  // Name: SongPlayer - Default Constructor
  // Pre-condition: None
  // Post-condition: Creates a new SongPlayer with m_filename of FILE_NAME
  SongPlayer();

  // Name: SongPlayer - Overloaded Constructor
  // Pre-condition: None
  // Post-condition: Creates a new SongPlayer with passed filename
  SongPlayer(string filename);

  // Name: ~SongPlayer - Destructor
  // Pre-condition: None
  // Post-condition: Deallocates songs from m_songCatalog
  ~SongPlayer();

  // Name: ToLower()
  // Pre-condition: Requires a string to be passed
  // Post-condition: Makes word lowercase (used for finding an artist or title)
  string ToLower(string word);

  // Name: LoadCatalog()
  // Pre-condition: Requires m_filename to be populated
  // Post-condition: Dynamically allocates each song and inserts into m_songCatalog
  void LoadCatalog();

  // Name: MainMenu
  // Pre-condition: None
  // Post-condition: Manages the menu
  void MainMenu();

  //Name: DisplaySong
  //Desc: Asks user to search by artist or title (1 for Artist and 2 for Title)
  //      Asks user for search string (converts to lower case)
  //      If 1 chosen, displays all artists with the search string (or all titles if 2)
  //      Uses iterators
  // Pre-condition: m_songCatalog is populated
  // Post-condition: Returns count of songs meeting search criteria else 0
  int DisplaySong();

  // Name: SearchType
  // Desc: Helper function for DisplaySong
  //       Asks the user if they want search by artist or title
  //Pre-condition: m_songCatalog is populated
  //Post-condition: Returns 1 for artist and 2 for title
  int SearchOptions();

  // Name: SearchType
  // Desc: Prompts the user for what string they want to search for (can be artist or title)
  // Pre-condition: m_songCatalog is populated
  // Post-condition: Returns string to search for
  string SearchType(string type);

  // Name: AddSong
  // Desc: Calls DisplaySong where user chooses artist or title and search string
  //       User enters index of song to choose
  //       Validates for number to be between 0 - m_songCatalog size
  //       Does NOT validate that song chosen was from results of search
  //       Uses overloaded << operator to display the example below
  // Pre-condition: m_songCatalog is populated
  // Post-condition: Adds pointer from m_songCatalog and inserts into m_playList
  void AddSong();

  // Name: DisplayPlaylist
  // Pre-condition: None (will indicate if list is empty)
  // Post-condition: Displays the playlist using the overloaded << operator
  void DisplayPlaylist();

  // Name: SortPlaylist
  // Pre-condition: None (will indicate if list is empty)
  // Post-condition: Sorts the playlist by Spotify streams
  void SortPlaylist();

  // Name: StartPlayer
  // Pre-condition: None (file name has already been provided)
  // Post-condition: Loads file and calls main menu
  void StartPlayer();

private:
    string m_filename; // Name of input file
    vector<Song*> m_songCatalog; // Holds all songs in file
    Queue<Song*> m_playList; // Holds all songs in play list
};


#endif

