
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void display() {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: ";

        if (issued)
            cout << "Issued";
        else
            cout << "Available";

        cout << "\n--------------------------";
    }
};

vector<Book> books;

void saveToFile() {
    ofstream file("input.csv");

    file << "ID,Title,Author,Status\n";

    for (auto &b : books) {
        file << b.id << "," << b.title << ","
             << b.author << ",";

        if (b.issued)
            file << "Issued\n";
        else
            file << "Available\n";
    }

    file.close();
}

void loadFromFile() {
    books.clear();

    ifstream file("input.csv");
    string line;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Book b;

        getline(ss, temp, ',');
        b.id = stoi(temp);

        getline(ss, b.title, ',');
        getline(ss, b.author, ',');
        getline(ss, temp, ',');

        b.issued = (temp == "Issued");

        books.push_back(b);
    }

    file.close();
}

void addBook() {
    Book b;
    b.input();

    books.push_back(b);
    saveToFile();

    cout << "\nBook Added Successfully!\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "\nNo Books Available!\n";
        return;
    }

    for (auto &b : books)
        b.display();
}

void searchByTitle() {
    string searchTitle;

    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, searchTitle);

    bool found = false;

    for (auto &b : books) {
        if (b.title == searchTitle) {
            b.display();
            found = true;
        }
    }

    if (!found)
        cout << "\nBook Not Found!\n";
}

void searchByAuthor() {
    string searchAuthor;

    cin.ignore();
    cout << "Enter Author Name: ";
    getline(cin, searchAuthor);

    bool found = false;

    for (auto &b : books) {
        if (b.author == searchAuthor) {
            b.display();
            found = true;
        }
    }

    if (!found)
        cout << "\nNo Books Found!\n";
}

void issueBook() {
    int id;

    cout << "Enter Book ID to Issue: ";
    cin >> id;

    for (auto &b : books) {
        if (b.id == id) {
            if (!b.issued) {
                b.issued = true;
                saveToFile();
                cout << "\nBook Issued Successfully!\n";
            } else {
                cout << "\nBook Already Issued!\n";
            }
            return;
        }
    }

    cout << "\nBook Not Found!\n";
}

void returnBook() {
    int id;

    cout << "Enter Book ID to Return: ";
    cin >> id;

    for (auto &b : books) {
        if (b.id == id) {
            if (b.issued) {
                b.issued = false;
                saveToFile();
                cout << "\nBook Returned Successfully!\n";
            } else {
                cout << "\nBook Was Not Issued!\n";
            }
            return;
        }
    }

    cout << "\nBook Not Found!\n";
}

int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n====== LIBRARY MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search By Title\n";
        cout << "4. Search By Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter Your Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchByTitle();
                break;
            case 4:
                searchByAuthor();
                break;
            case 5:
                issueBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                cout << "\nExiting Program...\n";
                break;
            default:
                cout << "\nInvalid Choice!\n";
        }
    } while (choice != 7);

    return 0;
}
