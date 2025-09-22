#include <iostream>
using namespace std;

struct Song {
    string title;
    string artist;
    Song* next;
};

void insertAtBeginning(Song*& head, string title, string artist);  
void insertAtEnd(Song*& head, string title, string artist);  
void insertAtPosition(Song*& head, string title, string artist, int position);  
void deleteSong(Song*& head, string title);  
void displayPlayList(Song* head);

void insertAtBeginning(Song*& head, string title, string artist) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    newSong->next = head;
    head = newSong;
}

void insertAtEnd(Song*& head, string title, string artist) {
    Song* newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    newSong->next = nullptr;
    
    if (head == nullptr) {
        head = newSong;
        return;
    }
    
    Song* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newSong;
}

void insertAtPosition(Song*& head, string title, string artist, int position) {
    if (position <= 1) {
        insertAtBeginning(head, title, artist);
        return;
    }
    
    Song* newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    
    Song* current = head;
    for (int i = 1; i < position - 1 && current != nullptr; i++) {
        current = current->next;
    }
    
    if (current == nullptr) {

        insertAtEnd(head, title, artist);
    } else {
        newSong->next = current->next;
        current->next = newSong;
    }
}

void deleteSong(Song*& head, string title) {
    if (head == nullptr) {
        cout << "Playlist is empty!\n";
        return;
    }
    
    if (head->title == title) {
        Song* temp = head;
        head = head->next;
        delete temp;
        cout << "Song '" << title << "' deleted successfully.\n";
        return;
    }
    
    Song* current = head;
    while (current->next != nullptr && current->next->title != title) {
        current = current->next;
    }
    
    if (current->next == nullptr) {
        cout << "Song '" << title << "' not found in the playlist.\n";
    } else {
        Song* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Song '" << title << "' deleted successfully.\n";
    }
}

void displayPlayList(Song* head) {
    if (head == nullptr) {
        cout << "Playlist is empty!\n";
        return;
    }
    
    cout << "Current Playlist:\n";
    cout << "================\n";
    
    Song* current = head;
    int songNumber = 1;
    while (current != nullptr) {
        cout << songNumber << ". \"" << current->title << "\" by " << current->artist << endl;
        current = current->next;
        songNumber++;
    }
    cout << "================\n\n";
}

int main() {
    Song* head = nullptr;
    
    cout << "Building playlist...\n\n";
    
    insertAtEnd(head, "Song A", "Artist 1");
    insertAtEnd(head, "Song B", "Artist 2");
    insertAtBeginning(head, "Song C", "Artist 3");
    insertAtPosition(head, "Song D", "Artist 4", 2);
    insertAtEnd(head, "Song E", "Artist 5");

    cout << "Initial Playlist:\n";
    displayPlayList(head);

    cout << "Deleting 'Song B'...\n";
    deleteSong(head, "Song B");
    displayPlayList(head);
    
    cout << "Adding 'Song F' at position 3...\n";
    insertAtPosition(head, "Song F", "Artist 6", 3);
    displayPlayList(head);
    
    cout << "Adding 'Song G' at the beginning...\n";
    insertAtBeginning(head, "Song G", "Artist 7");
    displayPlayList(head);
    
    cout << "Adding 'Song H' at the end...\n";
    insertAtEnd(head, "Song H", "Artist 8");
    displayPlayList(head);
    
    cout << "Attempting to delete non-existent song...\n";
    deleteSong(head, "Song X");
    displayPlayList(head);

    return 0;
}
