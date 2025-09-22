#include <iostream>
using namespace std;

struct Page {
    string url;
    Page* prev;
    Page* next;
};

void visitPage(Page*& head, Page*& tail, Page*& current, string url);
void goBack(Page*& current);
void goForward(Page*& current);
void deleteCurrentPage(Page*& head, Page*& tail, Page*& current);
void displayForward(Page* head);
void displayBackward(Page* tail);

void visitPage(Page*& head, Page*& tail, Page*& current, string url) {
    Page* newPage = new Page;
    newPage->url = url;
    newPage->prev = current;
    newPage->next = nullptr;
    
    if (head == nullptr) {
        head = newPage;
        tail = newPage;
    } else {
        if (current != nullptr) {
            newPage->prev = current;
            current->next = newPage;
        }
        tail = newPage;
    }
    current = newPage;
}

void goBack(Page*& current) {
    if (current == nullptr || current->prev == nullptr) {
        cout << "Cannot go back further.\n";
        return;
    }
    current = current->prev;
    cout << "Back to: " << current->url << endl;
}

void goForward(Page*& current) {
    if (current == nullptr || current->next == nullptr) {
        cout << "Cannot go forward further.\n";
        return;
    }
    current = current->next;
    cout << "Forward to: " << current->url << endl;
}

void deleteCurrentPage(Page*& head, Page*& tail, Page*& current) {
    if (current == nullptr) {
        cout << "No page to delete.\n";
        return;
    }
    
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }
    
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }
    
    Page* temp = current;
    if (current->prev != nullptr) {
        current = current->prev;
    } else if (current->next != nullptr) {
        current = current->next;
    } else {
        current = nullptr;
    }
    
    delete temp;
    cout << "Current page deleted.\n";
}

void displayForward(Page* head) {
    if (head == nullptr) {
        cout << "History is empty.\n";
        return;
    }
    
    cout << "Browser History (Forward):\n";
    Page* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << count << ". " << current->url << endl;
        current = current->next;
        count++;
    }
}

void displayBackward(Page* tail) {
    if (tail == nullptr) {
        cout << "History is empty.\n";
        return;
    }
    
    cout << "Browser History (Backward):\n";
    Page* current = tail;
    int count = 1;
    while (current != nullptr) {
        cout << count << ". " << current->url << endl;
        current = current->prev;
        count++;
    }
}

int main() {
    Page* head = nullptr;
    Page* tail = nullptr;
    Page* current = nullptr;

    visitPage(head, tail, current, "www.google.com");
    visitPage(head, tail, current, "www.youtube.com");
    visitPage(head, tail, current, "www.github.com");
    visitPage(head, tail, current, "www.reddit.com");
    visitPage(head, tail, current, "www.stackoverflow.com");

    cout << "Browser History (Forward):\n";
    displayForward(head);

    cout << "\nSimulating Back Navigation...\n";
    goBack(current);
    goBack(current);

    cout << "\nSimulating Forward Navigation...\n";
    goForward(current);

    cout << "\nDeleting Current Page...\n";
    deleteCurrentPage(head, tail, current);
    displayForward(head);

    cout << "\nDisplaying History Backward:\n";
    displayBackward(tail);

    return 0;
}
