// Description: Describes the class named Song

#include <iostream>
#include <string>
using namespace std;

#ifndef SONG_H
#define SONG_H

class Song{
 public:

  // Name: Song - Default Constructor
  // Pre-condition: None
  // Post-condition: Creates a default song
  Song();

  // Name: Song - Overloaded Constructor
  // Pre-condition: Requires title, album, artist, Spotify streams, YouTube views, and TikTok views
  // Post-condition: Creates a song entry based on passed parameters
  Song(string title, string album, string artist, long spotify, long youtube, long tiktok);

  // Name: Mutators and Accessors
  // Pre-condition: None
  // Post-condition: Sets and Gets private member variables
  string GetTitle()const; // return title
  string GetAlbum()const; // return album
  string GetArtist()const; //return artist
  long GetSpotify() const; // returns Spotify streams
  long GetYouTube() const; // returns YouTube views
  long GetTikTok() const; // returns TikTok views
  void SetTitle(string title); // sets title
  void SetAlbum(string album); // sets album
  void SetArtist(string artist); // sets artist
  void SetSpotify(long spotify); // sets spotify streams
  void SetYouTube(long youTube); //sets youtube views
  void SetTikTok(long tikTok); // sets tiktok views

  // Name: Overloaded << operator
  // Pre-condition: song available
  // Post-condition: Returns output stream including title and artist
  friend ostream& operator<<(ostream& out, Song& m);

  // Name: Overloaded Relational Operator (<)
  // Pre-condition: Two song objects required
  // Post-condition: if passed song's spotify streams is less than first return true else false
  bool operator<(const Song& m);

private:
  string m_title; // Title of song
  string m_album; // Album of song
  string m_artist; // Artist of song
  long int m_spotify; // Number of Spotify streams
  long int m_youtube; // Number of YouTube views
  long int m_tiktok; // Number of TikTok views
};

#endif

