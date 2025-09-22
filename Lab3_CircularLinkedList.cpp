#include <iostream>
using namespace std;

struct Player {
    string name;
    Player* next;
};

void addPlayer(Player*& head, string name);
void removePlayer(Player*& head, string name);
void displayPlayers(Player* head);
void simulateTournament(Player*& head);

void addPlayer(Player*& head, string name) {
    Player* newPlayer = new Player;
    newPlayer->name = name;
    
    if (head == nullptr) {
        head = newPlayer;
        head->next = head;
        return;
    }
    
    Player* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    
    temp->next = newPlayer;
    newPlayer->next = head;
}

void removePlayer(Player*& head, string name) {
    if (head == nullptr) return;
    
    Player* current = head;
    Player* prev = nullptr;
    
    do {
        if (current->name == name) {
            if (prev != nullptr) {
                prev->next = current->next;
            }
            
            if (current == head) {
                if (current->next == head) {
                    head = nullptr;
                } else {
                    Player* last = head;
                    while (last->next != head) {
                        last = last->next;
                    }
                    head = head->next;
                    last->next = head;
                }
            }
            
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    } while (current != head);
}

void displayPlayers(Player* head) {
    if (head == nullptr) {
        cout << "No players in the tournament.\n";
        return;
    }
    
    Player* temp = head;
    int count = 1;
    do {
        cout << count << ". " << temp->name << endl;
        temp = temp->next;
        count++;
    } while (temp != head);
}

void simulateTournament(Player*& head) {
    if (head == nullptr) return;
    
    int round = 1;
    Player* current = head;
    
    while (head->next != head) {
        cout << "\nRound " << round << ":\n";
        cout << "Current circle: ";
        
        Player* temp = head;
        do {
            cout << temp->name;
            if (temp->next != head) cout << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
        
        Player* toRemove = current->next;
        cout << "Removing: " << toRemove->name << endl;
        removePlayer(head, toRemove->name);
        
        current = toRemove->next;
        if (current == nullptr) current = head;
        
        round++;
    }
    
    cout << "\nWinner: " << head->name << "!" << endl;
}

int main() {
    Player* head = nullptr;

    addPlayer(head, "Arabella");
    addPlayer(head, "Ara");
    addPlayer(head, "Glinda");
    addPlayer(head, "Cleo");
    addPlayer(head, "Belinda");
    addPlayer(head, "Jane");

    cout << "Initial Players:\n";
    displayPlayers(head);

    cout << "\nSimulating Tournament (Musical Chairs)...\n";
    simulateTournament(head);

    return 0;
}
