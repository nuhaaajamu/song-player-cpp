//Title: proj5.cpp                                                                                                                                                                                              
//Author: Jeremy Dixon                                                                                                                                                                                          
//Date: 11/10/2025                                                                                                                                                                                              
//Description: Creates a new SongPlayer                                                                                                                                                                         

#include <iostream>
#include "SongPlayer.h"
#include "Song.h"

using namespace std;

int main (int argc, char* argv[]) {
  string songFile; // Used to populate the m_fileName in SongPlayer
  cout << "Welcome to UMBC Song Player"<< endl;

  // If there is at least one thing passed, set songFile to argv[1]
  if(argc > 1){
    songFile = argv[1];
  } else{
    cout << "One song files required - try again" << endl;
    return 0;
  }
  SongPlayer* mySong = new SongPlayer(songFile); // Creates a new SongPlayer
  mySong->StartPlayer(); // Calls StartPlayer
  delete mySong; // Deallocates SongPlayer
  return 0;
}

