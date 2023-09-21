#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Song {
    string title;
    string author;
    int year;
    string lyrics;
};

void addSongToFile(const Song& song, ofstream& file) {
    file << "Title: " << song.title << endl;
    file << "Author: " << song.author << endl;
    file << "Year: " << song.year << endl;
    file << "Lyrics: " << endl << song.lyrics << endl;
    file << "--------------------------" << endl;
}

int main() {
    ofstream catalogFile("songs_catalog.txt", ios::app);

    if (!catalogFile.is_open()) {
        cerr << "Error oppening file." << endl;
        return 1;
    }

    Song newSong;
    cout << "Song name: ";
    getline(cin, newSong.title);

    cout << "Artist name: ";
    getline(cin, newSong.author);

    cout << "Release year: ";
    cin >> newSong.year;
    cin.ignore(); // Очистка буфера после ввода числа

    cout << "Song lyrics (enter '.' in the new line, to end):" << endl;
    string line;
    while (true) {
        getline(cin, line);
        if (line == ".")
            break;
        newSong.lyrics += line + '\n';
    }

    addSongToFile(newSong, catalogFile);
    catalogFile.close();

    cout << "Song was added in catalog successfuly." << endl;

    return 0;
}