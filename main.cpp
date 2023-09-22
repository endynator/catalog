#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Song {
    string name;
    string artist;
    int year;
    string lyrics;
};

void addSong(vector<Song>& catalog) {
    Song newSong;
    cout << "Enter the name of the song: ";
    getline(cin, newSong.name);
    cout << "Enter the artist: ";
    getline(cin, newSong.artist);
    cout << "Enter the year of release: ";
    cin >> newSong.year;
    cin.ignore(); 
    cout << "Enter the lyrics (press Enter on an empty line to finish):\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) {
            break;
        }
        newSong.lyrics += line + '\n';
    }
    catalog.push_back(newSong);
    cout << "Song added successfully!\n";
}

void removeSong(vector<Song>& catalog) {
    cout << "Enter the name of the song to remove: ";
    string songName;
    getline(cin, songName);

    for (auto it = catalog.begin(); it != catalog.end(); ++it) {
        if (it->name == songName) {
            catalog.erase(it);
            cout << "Song removed successfully!\n";
            return;
        }
    }

    cout << "Song not found in the catalog.\n";
}

void editSong(vector<Song>& catalog) {
    cout << "Enter the name of the song to edit: ";
    string songName;
    getline(cin, songName);


    for (auto& song : catalog) {
        
        if (song.name == songName) {
            cout << "Enter the new name of the song (or press Enter to keep it the same): ";
            string newName;
            
            getline(cin, newName);
            if (!newName.empty()) {
                song.name = newName;
            }
            cout << "Enter the new artist (or press Enter to keep it the same): ";
            string newArtist;
            getline(cin, newArtist);
            if (!newArtist.empty()) {
                song.artist = newArtist;
            }
            cout << "Enter the new year of release (or press Enter to keep it the same): ";
            string newYear;
            getline(cin, newYear);
            if (!newYear.empty()) {
                song.year = stoi(newYear);
            }
            cout << "Enter the new lyrics (or press Enter to keep them the same):\n";
            string newLyrics;
            string line;
            while (true) {
                getline(cin, line);
                if (line.empty()) {
                    break;
                }
                newLyrics += line + '\n';
            }
            if (!newLyrics.empty()) {
                song.lyrics = newLyrics;
            }
            cout << "Song edited successfully!\n";
            return;
        }
    }

    cout << "Song not found in the catalog.\n";
}

void displayCatalog(const vector<Song>& catalog) {
    cout << "Song Catalog:\n\n";
    for (const Song& song : catalog) {
        cout << "Name: " << song.name << endl;
        cout << "Artist: " << song.artist << endl;
        cout << "Year of Release: " << song.year << endl;
        cout << "Lyrics:\n" << song.lyrics << endl;
        cout << "-------------------------------------\n";
    }
}

void saveCatalog(const vector<Song>& catalog) {
    ofstream outFile("songs_catalog.txt");
    if (outFile.is_open()) {
        for (const Song& song : catalog) {
            outFile << "Name: " << song.name << endl;
            outFile << "Artist: " << song.artist << endl;
            outFile << "Year of Release: " << song.year << endl;
            outFile << "Lyrics:\n" << song.lyrics << endl;
            outFile << "-------------------------------------\n";
        }
        outFile.close();
        cout << "Catalog saved to 'songs_catalog.txt'.\n";
    }
    else {
        cout << "Error: Unable to save catalog to file.\n";
    }
}

int main() {
    vector<Song> catalog;

    ifstream inFile("songs_catalog.txt");
    if (inFile.is_open()) {
        string line;
        Song currentSong;
        while (getline(inFile, line)) {
            if (line.find("Name: ") == 0) {
                currentSong.name = line.substr(6);
            }
            else if (line.find("Artist: ") == 0) {
                currentSong.artist = line.substr(8);
            }
            else if (line.find("Year of Release: ") == 0) {
                currentSong.year = stoi(line.substr(17));
            }
            else if (line == "Lyrics:") {
                currentSong.lyrics = "";
                while (getline(inFile, line) && line != "-------------------------------------") {
                    currentSong.lyrics += line + '\n';
                }
                catalog.push_back(currentSong);
            }
        }
        inFile.close();
        cout << "Catalog loaded from 'songs_catalog.txt'.\n";
    }
    else {
        cout << "Creating a new catalog.\n";
    }

    while (true) {
        int choice;

        cout << "\nSong's Lyrics Catalog Menu:\n";
        cout << "1. Add Song\n";
        cout << "2. Remove Song\n";
        cout << "3. Edit Song\n";
        cout << "4. Display Catalog\n";
        cout << "5. Save Catalog\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        
        cin >> choice; cin.ignore();

        switch (choice) {
        case 1:
            addSong(catalog);
            break;
        case 2:
            removeSong(catalog);
            break;
        case 3:
            editSong(catalog);
            break;
        case 4:
            displayCatalog(catalog);
            break;
        case 5:
            saveCatalog(catalog);
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
            cin.clear();
            cin.ignore();
            break;
        }
    }

    return 0;
}
