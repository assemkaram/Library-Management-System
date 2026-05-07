#include <iostream>
#include <fstream>
#include "member.h"
#include "book.h"

using namespace std;

void loadAllData() {
    readprimaryindex_member();
    readsecondaryindex_member();
    readavail_list_member();

    readprimaryindex_book();
    readsecondaryindex_book();
    readavail_list_book();
}

void saveAllData() {
    writeprimaryindex_member();
    writesecondaryindex_member();
    writeavail_list_member();

    writeprimaryindex_book();
    writesecondaryindex_book();
    writeavail_list_book();
}

int main() {
    loadAllData();

    fstream memberFile("members_data.txt", ios::in | ios::out | ios::binary | ios::app);
    if (!memberFile) memberFile.open("members_data.txt", ios::out | ios::binary);
    memberFile.close();
    memberFile.open("members_data.txt", ios::in | ios::out | ios::binary);

    fstream bookFile("books_data.txt", ios::in | ios::out | ios::binary | ios::app);
    if (!bookFile) bookFile.open("books_data.txt", ios::out | ios::binary);
    bookFile.close();
    bookFile.open("books_data.txt", ios::in | ios::out | ios::binary);

    member m_manager;
    book b_manager;
    int mainChoice;

    do {
        cout << "\n================================";
        cout << "\n   LIBRARY MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Member Management";
        cout << "\n2. Book Management";
        cout << "\n0. Exit & Save";
        cout << "\nEnter choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            int subChoice;
            do {
                cout << "\n--- Member Management ---";
                cout << "\n1. Add Member";
                cout << "\n2. Search by ID";
                cout << "\n3. Search by Name";
                cout << "\n4. Update Member by ID";
                cout << "\n5. Update Member by Name";
                cout << "\n6. Delete Member by ID";
                cout << "\n7. Delete Member by Name";
                cout << "\n8. Display All Members";
                cout << "\n9. Display TOP 5 Members";
                cout << "\n0. Back to Main Menu";
                cout << "\nEnter choice: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    member newM;
                    newM.read_member_data_from_user();
                    m_manager.addmember(memberFile, newM);
                } else if (subChoice == 2) {
                    int id; cout << "Enter ID: "; cin >> id;
                    m_manager.searchmember_byid(memberFile, id);
                } else if (subChoice == 3) {
                    char name[100]; cout << "Enter Name: ";
                    m_manager.solve_getLineProblem();
                    cin.getline(name, 100);
                    m_manager.searchmember_byname(memberFile, name);
                } else if (subChoice == 4) {
                    int id; cout << "Enter ID to update: "; cin >> id;
                    m_manager.updatemember(memberFile, id);
                } else if (subChoice == 5) {
                    char name[100]; cout << "Enter Name to update: ";
                    m_manager.solve_getLineProblem();
                    cin.getline(name, 100);
                    m_manager.updatemember_byname(memberFile, name);
                } else if (subChoice == 6) {
                    int id; cout << "Enter ID to delete: "; cin >> id;
                    m_manager.deletemember(memberFile, id);
                } else if (subChoice == 7) {
                    char name[100]; cout << "Enter Name to delete: ";
                    m_manager.solve_getLineProblem();
                    cin.getline(name, 100);
                    m_manager.deletemember_byname(memberFile, name);
                } else if (subChoice == 8) {
                    m_manager.displaymembers(memberFile);
                } else if (subChoice == 9) {
                    m_manager.displayTOP5Members(memberFile);
                }
            } while (subChoice != 0);

        } else if (mainChoice == 2) {
            int subChoice;
            do {
                cout << "\n--- Book Management ---";
                cout << "\n1. Add Book";
                cout << "\n2. Search by ID";
                cout << "\n3. Search by Author";
                cout << "\n4. Update Book by ID";
                cout << "\n5. Update Book by Author";
                cout << "\n6. Delete Book by ID";
                cout << "\n7. Delete Book by Author";
                cout << "\n8. Display All Books";
                cout << "\n9. Display TOP 5 Books";
                cout << "\n0. Back to Main Menu";
                cout << "\nEnter choice: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    book newB;
                    newB.read_book_data_from_user();
                    b_manager.addbook(bookFile, newB);
                } else if (subChoice == 2) {
                    int id; cout << "Enter ID: "; cin >> id;
                    b_manager.searchbook_byid(bookFile, id);
                } else if (subChoice == 3) {
                    char author[100]; cout << "Enter Author Name: ";
                    b_manager.solve_getLineProblem();
                    cin.getline(author, 100);
                    b_manager.searchbook_byauthor(bookFile, author);
                } else if (subChoice == 4) {
                    int id; cout << "Enter ID to update: "; cin >> id;
                    b_manager.updatebook(bookFile, id);
                } else if (subChoice == 5) {
                    char author[100]; cout << "Enter Author Name to update: ";
                    b_manager.solve_getLineProblem();
                    cin.getline(author, 100);
                    b_manager.updatebook_byauthor(bookFile, author);
                } else if (subChoice == 6) {
                    int id; cout << "Enter ID to delete: "; cin >> id;
                    b_manager.deletebook(bookFile, id);
                } else if (subChoice == 7) {
                    char author[100]; cout << "Enter Author Name to delete: ";
                    b_manager.solve_getLineProblem();
                    cin.getline(author, 100);
                    b_manager.deletebook_byauthor(bookFile, author);
                } else if (subChoice == 8) {
                    b_manager.displaybooks(bookFile);
                } else if (subChoice == 9) {
                    b_manager.displayTOP5Books(bookFile);
                }
            } while (subChoice != 0);
        }

    } while (mainChoice != 0);

    saveAllData();
    memberFile.close();
    bookFile.close();

    cout << "\nAll changes saved. Program exited.\n";
    return 0;
}