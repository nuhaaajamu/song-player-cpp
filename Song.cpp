#include "Song.h"

Song::Song() : m_title("unknown"), m_album("unknown"), m_artist("unknown"), m_spotify(0), m_youtube(0), m_tiktok(0) {}

Song::Song(string title, string album, string artist, long spotify, long youtube, long tiktok) :
m_title(title), m_album(album), m_artist(artist), m_spotify(spotify), m_youtube(youtube), m_tiktok(tiktok) {}

string Song::GetTitle()const{return m_title;}

string Song::GetAlbum()const{return m_album;}

string Song::GetArtist()const{return m_artist;}

long Song::GetSpotify()const{return m_spotify;}

long Song::GetYouTube()const{return m_youtube;}

long Song::GetTikTok()const{return m_tiktok;}

void Song::SetTitle(string title){m_title = title;}

void Song::SetAlbum(string album){ m_album = album;}

void Song::SetArtist(string artist){m_artist = artist;}

void Song::SetSpotify(long spotify){m_spotify = spotify;}

void Song::SetYouTube(long youtube){m_youtube = youtube;}

void Song::SetTikTok(long tiktok){m_tiktok = tiktok;}

ostream& operator<<(ostream& out, Song& m) {
    // Format the song data.
    out << m.m_title << " by " << m.m_artist << " from " << m.m_album;
    return out;
}

bool Song::operator<(const Song& m) {
    if (m.m_spotify < m_spotify) {
        return true;
    }
    return false;
}







