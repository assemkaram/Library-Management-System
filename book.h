#ifndef UNTITLED3_BOOK_H
#define UNTITLED3_BOOK_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

//Primary Index ID
class primaryindex_book {
public:
    int id;
    int offset;
    bool operator<(const primaryindex_book& pib) const {
        return id < pib.id;
    }
};
vector<primaryindex_book> pri_book;

void writeprimaryindex_book() {
    ofstream outfile("primaryindex_books.txt", ios::out | ios::binary);
    for (int i = 0; i < pri_book.size(); i++) {
        outfile.write((char*)&pri_book[i], sizeof(pri_book[i]));
    }
    outfile.close();
}

void readprimaryindex_book() {
    pri_book.clear();
    primaryindex_book pib;
    ifstream infile("primaryindex_books.txt", ios::in | ios::binary);
    while (infile.read((char*)&pib, sizeof(pib))) {
        pri_book.push_back(pib);
    }
    infile.close();
}

void addtoprimaryindex_book(primaryindex_book &pib) {
    pri_book.push_back(pib);
    sort(pri_book.begin(), pri_book.end());
}

void deletefromprimaryindex_book(const int &id) {
    int low = 0, high = pri_book.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (pri_book[mid].id == id) {
            pri_book.erase(pri_book.begin() + mid);
            return;
        }
        else if (pri_book[mid].id > id) high = mid - 1;
        else low = mid + 1;
    }
}

int searchinprimaryindex_book(const int &id) {
    int low = 0, high = pri_book.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (pri_book[mid].id == id)
            return pri_book[mid].offset;
        else if (pri_book[mid].id > id)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

//Secondary Index Author
class secondaryindex_book_author {
public:
    char author[100];
    int id;
    bool operator<(const secondaryindex_book_author& sec) const {
        if (strcmp(author, sec.author) == 0) return id < sec.id;
        return strcmp(author, sec.author) < 0;
    }
};
vector<secondaryindex_book_author> sec_idx_book;

void writesecondaryindex_book() {
    ofstream outfile("secondaryindex_book_author.txt", ios::out | ios::binary);
    for (int i = 0; i < sec_idx_book.size(); i++) {
        outfile.write((char*)&sec_idx_book[i], sizeof(sec_idx_book[i]));
    }
    outfile.close();
}

void readsecondaryindex_book() {
    sec_idx_book.clear();
    secondaryindex_book_author sib;
    ifstream infile("secondaryindex_book_author.txt", ios::in | ios::binary);
    while (infile.read((char*)&sib, sizeof(sib))) {
        sec_idx_book.push_back(sib);
    }
    infile.close();
}

void addtosecondaryindex_book(char* auth, int id) {
    secondaryindex_book_author sib;
    strcpy(sib.author, auth);
    sib.id = id;
    sec_idx_book.push_back(sib);
    sort(sec_idx_book.begin(), sec_idx_book.end());
}

void deletefromsecondaryindex_book(char* auth, int id) {
    for (int i = 0; i < sec_idx_book.size(); i++) {
        if (strcmp(sec_idx_book[i].author, auth) == 0 && sec_idx_book[i].id == id) {
            sec_idx_book.erase(sec_idx_book.begin() + i);
            return;
        }
    }
}

//Free List Available List
struct BookFreeSlot {
    int offset;
    int size;
};
vector<BookFreeSlot> avail_list_book;

void writeavail_list_book() {
    ofstream outfile("avail_list_book.txt", ios::out | ios::binary);
    for (int i = 0; i < avail_list_book.size(); i++) {
        outfile.write((char*)&avail_list_book[i], sizeof(avail_list_book[i]));
    }
    outfile.close();
}

void readavail_list_book() {
    avail_list_book.clear();
    BookFreeSlot fs;
    ifstream infile("avail_list_book.txt", ios::in | ios::binary);
    while (infile.read((char*)&fs, sizeof(fs))) {
        avail_list_book.push_back(fs);
    }
    infile.close();
}

//Book Class
class book {
public:
    int id;
    char title[100];
    char author[100];

    void solve_getLineProblem() {
        if (cin.peek() == '\n')
            cin.ignore(1000, '\n');
    }

    void read_book_data_from_user(bool isUpdate = false) {
        if (!isUpdate) {
            while (true) {
                int tempId;
                cout << "Enter Book ID: ";
                cin >> tempId;
                if (searchinprimaryindex_book(tempId) != -1)
                    cout << "Book ID already exists.\n";
                else {
                    id = tempId;
                    break;
                }
            }
        }
        cout << "Enter Author Name: ";
        solve_getLineProblem();
        cin.getline(author, 100);
        cout << "Enter Book Title: ";
        cin.getline(title, 100);
    }

    void display() {
        cout << "ID: " << id  << " | Author: " << author << " | Title: " << title << endl;
    }

    int calclength() const {
        return sizeof(int) + 2 * sizeof(short) + strlen(title) + strlen(author);
    }

    void addbook(fstream &iofile, const book &b);
    void searchbook_byid(fstream &iofile, const int &id);
    void searchbook_byauthor(fstream &iofile, char* auth);
    void deletebook(fstream &iofile, const int &id);
    void updatebook(fstream &iofile, const int &id);
    void deletebook_byauthor(fstream &iofile, char* auth);
    void updatebook_byauthor(fstream &iofile, char* auth);
    void displayTOP5Books(fstream& file);
    void displaybooks(fstream &iofile);
};

//File Manager
class book_file_manager {
public:
    void write_book_to_file(fstream &iofile, book &b) {
        iofile.write((char *)&b.id, sizeof(int));
        short len = strlen(b.title);
        iofile.write((char *)&len, sizeof(short));
        iofile.write(b.title, len);
        len = strlen(b.author);
        iofile.write((char *)&len, sizeof(short));
        iofile.write(b.author, len);
    }

    void read_book_from_file(fstream &iofile, book &b) {
        iofile.read((char *)&b.id, sizeof(int));
        short len;
        iofile.read((char *)&len, sizeof(short));
        iofile.read(b.title, len);
        b.title[len] = '\0';
        iofile.read((char *)&len, sizeof(short));
        iofile.read(b.author, len);
        b.author[len] = '\0';
    }
};

//Implementations
void book::addbook(fstream &iofile, const book &b) {
    book_file_manager fm;
    int newSize = b.calclength();
    int index = -1;
    for (int i = 0; i < (int)avail_list_book.size(); i++) {
        if (avail_list_book[i].size >= newSize) {
            index = i;
            break;
        }
    }
    primaryindex_book pib;

    if (index != -1) {
        int offset = avail_list_book[index].offset;
        iofile.seekp(offset, ios::beg);
        pib.id = b.id;
        pib.offset = offset;
        fm.write_book_to_file(iofile, (book&)b);
        int padding = avail_list_book[index].size - newSize;
        while (padding--) iofile.put('#');
        avail_list_book.erase(avail_list_book.begin() + index);
    }
    else {
        iofile.seekp(0, ios::end);
        pib.id = b.id;
        pib.offset = iofile.tellp();
        fm.write_book_to_file(iofile, (book&)b);
    }

    addtoprimaryindex_book(pib);
    addtosecondaryindex_book((char*)b.author, b.id);
    cout << "Book added successfully.\n";
}

void book::searchbook_byid(fstream &iofile, const int &id) {
    book_file_manager fm;
    book b;
    int offset = searchinprimaryindex_book(id);
    if (offset == -1) cout << "Book not found.\n";
    else {
        iofile.seekg(offset, ios::beg);
        fm.read_book_from_file(iofile, b);
        b.display();
        cout << "====================\n";
    }
}

void book::searchbook_byauthor(fstream &iofile, char* auth) {
    bool found = false;
    book_file_manager fm;
    book b;
    for (int i = 0; i < (int)sec_idx_book.size(); i++) {
        if (strcmp(sec_idx_book[i].author, auth) == 0) {
            int offset = searchinprimaryindex_book(sec_idx_book[i].id);
            if (offset != -1) {
                iofile.seekg(offset, ios::beg);
                fm.read_book_from_file(iofile, b);
                b.display();
                found = true;
            }
        }
    }
    if (!found) cout << "No books found for this author.\n";
}

void book::deletebook(fstream &iofile, const int &id) {
    book_file_manager fm;
    book b;
    int offset = searchinprimaryindex_book(id);
    if (offset == -1) {
        cout << "Book not found.\n";
        return;
    }
    iofile.seekg(offset, ios::beg);
    fm.read_book_from_file(iofile, b);
    int size = b.calclength();

    BookFreeSlot fs;
    fs.offset = offset;
    fs.size = size;
    avail_list_book.push_back(fs);

    iofile.seekp(offset + sizeof(int) + sizeof(short), ios::beg);
    iofile.put('*');

    deletefromsecondaryindex_book(b.author, id);
    deletefromprimaryindex_book(id);
    cout << "Book deleted successfully.\n";
}

void book::updatebook(fstream &iofile, const int &id) {
    book_file_manager fm;
    book oldB, newB;

    int offset = searchinprimaryindex_book(id);
    if (offset == -1) {
        cout << "Book not found.\n";
        return;
    }

    // Read current data
    iofile.seekg(offset, ios::beg);
    fm.read_book_from_file(iofile, oldB);
    int oldLen = oldB.calclength();

    cout << "Current Data::\n";
    oldB.display();
    cout << "\n--------------------------\n";

    // Read new data from user
    cout << "Edit Data::\n";
    newB.read_book_data_from_user(true); // true means keep ID
    newB.id = id;
    int newLen = newB.calclength();

    if (oldLen >= newLen) {
        //write in the same place
        iofile.seekp(offset, ios::beg);
        fm.write_book_to_file(iofile, newB);

        int padding = oldLen - newLen;
        while (padding--) iofile.put('#');

        // Update secondary index
        deletefromsecondaryindex_book(oldB.author, id);
        addtosecondaryindex_book(newB.author, id);

        cout << "Book updated successfully .\n";
    }
    else {
        //Delete old record 
        deletebook(iofile, id);
        //Add new record
        addbook(iofile, newB);

        cout << "Book updated successfully (Relocated).\n";
    }
}

void book::deletebook_byauthor(fstream &iofile, char* auth) {
    vector<int> foundIds;
    book_file_manager fm;
    book b;

    cout << "\nBooks found for author [" << auth << "]:\n";
    for (int i = 0; i < (int)sec_idx_book.size(); i++) {
        if (strcmp(sec_idx_book[i].author, auth) == 0) {
            int offset = searchinprimaryindex_book(sec_idx_book[i].id);
            if (offset != -1) {
                iofile.seekg(offset, ios::beg);
                fm.read_book_from_file(iofile, b);
                cout << "-> ID: " << b.id << " | Title: " << b.title << endl;
                foundIds.push_back(b.id);
            }
        }
    }

    if (foundIds.empty()) {
        cout << "No books found for this author.\n";
        return;
    }

    int selectedId;
    bool valid = false;
    while (!valid) {
        cout << "\nEnter specific ID to DELETE: ";
        cin >> selectedId;
        for (int id_val : foundIds) {
            if (id_val == selectedId) {
                valid = true;
                break;
            }
        }
        if (!valid) cout << "Invalid ID! Choose from the list above.";
    }

    deletebook(iofile, selectedId);
}

void book::updatebook_byauthor(fstream &iofile, char* auth) {
    vector<int> foundIds;
    book_file_manager fm;
    book b;

    cout << "\nBooks found for author [" << auth << "]:\n";
    for (int i = 0; i < (int)sec_idx_book.size(); i++) {
        if (strcmp(sec_idx_book[i].author, auth) == 0) {
            int offset = searchinprimaryindex_book(sec_idx_book[i].id);
            if (offset != -1) {
                iofile.seekg(offset, ios::beg);
                fm.read_book_from_file(iofile, b);
                cout << "-> ID: " << b.id << " | Title: " << b.title << endl;
                foundIds.push_back(b.id);
            }
        }
    }

    if (foundIds.empty()) {
        cout << "No books found for this author.\n";
        return;
    }

    int selectedId;
    bool valid = false;
    while (!valid) {
        cout << "\nEnter specific ID to UPDATE: ";
        cin >> selectedId;
        for (int id_val : foundIds) {
            if (id_val == selectedId) {
                valid = true;
                break;
            }
        }
        if (!valid) cout << "Invalid ID! Choose from the list above.";
    }

    updatebook(iofile, selectedId);
}

void book::displaybooks(fstream &iofile) {
    book_file_manager fm;
    book b;
    if(pri_book.empty()) cout << "No books to display.\n";
    for (int i = 0; i < (int)pri_book.size(); i++) {
        int offset = pri_book[i].offset;
        iofile.seekg(offset, ios::beg);
        fm.read_book_from_file(iofile, b);
        b.display();
        cout << "====================\n";
    }
}

void book::displayTOP5Books(fstream& file) {
    book b;
    book_file_manager fm;

    if (pri_book.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "\n===== TOP 5 BOOKS =====\n";
    int count = 0;
    for (int i = 0; i < (int)pri_book.size() && count < 5; i++) {
        file.seekg(pri_book[i].offset);
        fm.read_book_from_file(file, b);
        cout << "\nBook " << (count + 1) << ":\n";
        b.display();
        cout << "-----------------\n";
        count++;
    }
}
#endif