# Music Playlist Manager

Menu-driven C++ application that loads a song catalog from a text file and allows users to search by title or artist, build a playlist, and sort songs by Spotify streams.

## Architecture
- `Song` – Stores song metadata (title, artist, album, streaming metrics)
- `Node<T>` – Templated singly linked list node
- `Queue<T>` – Templated queue implemented using a singly linked list
- `SongPlayer` – Manages catalog loading, playlist behavior, and user interaction

## Key Concepts Demonstrated
- Implementation of a templated Queue ADT
- Singly linked list data structure
- Dynamic memory management and destructor logic
- File I/O for loading catalog data
- Polymorphic-style object interaction through pointer-based containers
- Sorting and swapping logic within a custom data structure
- Menu-driven interface with input validation and edge case handling

## Data Structures Used
- `vector<Song*>` for storing the full song catalog
- `Queue<Song*>` (linked list–backed) for managing the user playlist

## Features
- Load songs from input file
- Search by title or artist
- Add songs to playlist
- Display playlist contents
- Sort playlist by Spotify streams
- Handle invalid input and empty playlist conditions

## How to Compile

Compile all source files in the project directory:

g++ *.cpp -o song_player

Run:

./song_player
