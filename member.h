#ifndef UNTITLED3_MEMBER_H
#define UNTITLED3_MEMBER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

// Primary Index ID
class primaryindex_member {
public:
    int id;
    int offset;
    bool operator<(const primaryindex_member& pim) const {
        return id < pim.id;
    }
};
vector<primaryindex_member> pri_member;

void writeprimaryindex_member() {
    ofstream outfile("primaryindex_members.txt", ios::out | ios::binary);
    for (int i = 0; i < pri_member.size(); i++) {
        outfile.write((char*)&pri_member[i], sizeof(pri_member[i]));
    }
    outfile.close();
}

void readprimaryindex_member() {
    pri_member.clear();
    primaryindex_member pim;
    ifstream infile("primaryindex_members.txt", ios::in | ios::binary);
    while (infile.read((char*)&pim, sizeof(pim))) {
        pri_member.push_back(pim);
    }
    infile.close();
}

void addtoprimaryindex_member(primaryindex_member &pim) {
    pri_member.push_back(pim);
    sort(pri_member.begin(), pri_member.end());
}

void deletefromprimaryindex_member(const int &id ) {
    int low = 0;
    int high = pri_member.size() - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(pri_member[mid].id == id) {
            pri_member.erase(pri_member.begin() + mid);
            return;
        }
        else if(pri_member[mid].id > id) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
}

int searchinprimaryindex_member(const int &id) {
    int low = 0, high = pri_member.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (pri_member[mid].id == id)
            return pri_member[mid].offset;
        else if (pri_member[mid].id > id)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

//Secondary Index Name
class secondaryindex_member_name {
public:
    char name[100];
    int id; // Linked to Primary Key
    bool operator<(const secondaryindex_member_name& sec) const {
        if (strcmp(name, sec.name) == 0) return id < sec.id;
        return strcmp(name, sec.name) < 0;
    }
};
vector<secondaryindex_member_name> sec_idx_member;

void writesecondaryindex_member() {
    ofstream outfile("secondaryindex_member_name.txt", ios::out | ios::binary);
    for (int i = 0; i < sec_idx_member.size(); i++) {
        outfile.write((char*)&sec_idx_member[i], sizeof(sec_idx_member[i]));
    }
    outfile.close();
}

void readsecondaryindex_member() {
    sec_idx_member.clear();
    secondaryindex_member_name sim;
    ifstream infile("secondaryindex_member_name.txt", ios::in | ios::binary);
    while (infile.read((char*)&sim, sizeof(sim))) {
        sec_idx_member.push_back(sim);
    }
    infile.close();
}

void addtosecondaryindex_member(char* nm, int id) {
    secondaryindex_member_name sim;
    strcpy(sim.name, nm);
    sim.id = id;
    sec_idx_member.push_back(sim);
    sort(sec_idx_member.begin(), sec_idx_member.end());
}

void deletefromsecondaryindex_member(char* nm, int id) {
    for (int i = 0; i < sec_idx_member.size(); i++) {
        if (strcmp(sec_idx_member[i].name, nm) == 0 && sec_idx_member[i].id == id) {
            sec_idx_member.erase(sec_idx_member.begin() + i);
            return;
        }
    }
}

//Available List
struct MemberFreeSlot {
    int offset;
    int size;
};
vector<MemberFreeSlot> avail_list_member;
//write available list
void writeavail_list_member() {
    ofstream outfile("avail_list_member.txt", ios::out | ios::binary);
    for (int i = 0; i < avail_list_member.size(); i++) {
        outfile.write((char*)&avail_list_member[i], sizeof(avail_list_member[i]));
    }
    outfile.close();
}
//read available list
void readavail_list_member() {
    avail_list_member.clear();
    MemberFreeSlot fs;
    ifstream infile("avail_list_member.txt", ios::in | ios::binary);
    while (infile.read((char*)&fs, sizeof(fs))) {
        avail_list_member.push_back(fs);
    }
    infile.close();
}

//Member
class member {
public:
    int id;
    char name[100];
    char phone[20];

    void solve_getLineProblem() {
        if (cin.peek() == '\n')
            cin.ignore(1000, '\n');
    }

    void read_member_data_from_user(bool isUpdate = false) {
        if (!isUpdate) {
            while (true) {
                int tempId;
                cout << "Enter ID: ";
                cin >> tempId;
                if (searchinprimaryindex_member(tempId) != -1)
                    cout << "ID already exists.\n";
                else {
                    id = tempId;
                    break;
                }
            }
        }
        cout << "Enter Name: ";
        solve_getLineProblem();
        cin.getline(name, 100);
        cout << "Enter Phone: ";
        cin.getline(phone, 20);
    }

    void display() {
        cout << "ID: " << id  << " | Name: " << name << " | Phone: " << phone << endl;
    }

    int calclength() const {
        return sizeof(int) + 2 * sizeof(short) + strlen(name) + strlen(phone);
    }

    void addmember(fstream &iofile, const member &m);
    void searchmember_byid(fstream &iofile, const int &id);
    void searchmember_byname(fstream &iofile, char* nm);
    void deletemember(fstream &iofile, const int &id);
    void updatemember(fstream &iofile, const int &id);
    void deletemember_byname(fstream &iofile, char* nm);
    void updatemember_byname(fstream &iofile, char* nm);
    void displayTOP5Members(fstream& file);
    void displaymembers(fstream &iofile);
};

//File Manager
class member_file_manager {
public:
    void write_member_to_file(fstream &iofile, member &m) {
        iofile.write((char *)&m.id, sizeof(int));
        short len = strlen(m.name);
        iofile.write((char *)&len, sizeof(short));
        iofile.write(m.name, len);
        len = strlen(m.phone);
        iofile.write((char *)&len, sizeof(short));
        iofile.write(m.phone, len);
    }

    void read_member_from_file(fstream &iofile, member &m) {
        iofile.read((char *)&m.id, sizeof(int));
        short len;
        iofile.read((char *)&len, sizeof(short));
        iofile.read(m.name, len);
        m.name[len] = '\0';
        iofile.read((char *)&len, sizeof(short));
        iofile.read(m.phone, len);
        m.phone[len] = '\0';
    }
};

//Implementations
void member::addmember(fstream &iofile, const member &m) {
    member_file_manager fm;
    int newSize = m.calclength();
    int index = -1;
    for (int i = 0; i < (int)avail_list_member.size(); i++) {
        if (avail_list_member[i].size >= newSize) {
            index = i;
            break;
        }
    }
    primaryindex_member pim;

    if (index != -1) {
        int offset = avail_list_member[index].offset;
        iofile.seekp(offset, ios::beg);
        pim.id = m.id;
        pim.offset = offset;
        fm.write_member_to_file(iofile, (member&)m);
        int padding = avail_list_member[index].size - newSize;
        while (padding--) iofile.put('#');
        avail_list_member.erase(avail_list_member.begin() + index);
    }
    else {
        iofile.seekp(0, ios::end);
        pim.id = m.id;
        pim.offset = iofile.tellp();
        fm.write_member_to_file(iofile, (member&)m);
    }

    addtoprimaryindex_member(pim);
    addtosecondaryindex_member((char*)m.name, m.id);
    cout << "Member added successfully\n";
}

void member::searchmember_byid(fstream &iofile, const int &id) {
    member_file_manager fm;
    member m;
    int offset = searchinprimaryindex_member(id);
    if (offset == -1) cout << "Member not found\n";
    else {
        iofile.seekg(offset, ios::beg);
        fm.read_member_from_file(iofile, m);
        m.display();
        cout << "====================\n";
    }
}

void member::searchmember_byname(fstream &iofile, char* nm) {
    bool found = false;
    member_file_manager fm;
    member m;
    for (int i = 0; i < sec_idx_member.size(); i++) {
        if (strcmp(sec_idx_member[i].name, nm) == 0) {
            int offset = searchinprimaryindex_member(sec_idx_member[i].id);
            if (offset != -1) {
                iofile.seekg(offset, ios::beg);
                fm.read_member_from_file(iofile, m);
                m.display();
                found = true;
            }
        }
    }
    if (!found) cout << "No members found with this name.\n";
}

void member::deletemember(fstream &iofile, const int &id) {
    member_file_manager fm;
    member m;
    int offset = searchinprimaryindex_member(id);
    if (offset == -1) {
        cout << "Member not found\n";
        return;
    }
    iofile.seekg(offset, ios::beg);
    fm.read_member_from_file(iofile, m);
    int size = m.calclength();

    MemberFreeSlot fs;
    fs.offset = offset;
    fs.size = size;
    avail_list_member.push_back(fs);

    // Mark deleted
    iofile.seekp(offset + sizeof(int) + sizeof(short), ios::beg);
    iofile.put('*');

    deletefromsecondaryindex_member(m.name, id);
    deletefromprimaryindex_member(id);
    cout << "Deleted successfully\n";
}

void member::deletemember_byname(fstream &iofile, char* nm) {
    vector<int> foundIds;
    member_file_manager fm;
    member m;

    cout << "\nMembers found with name [" << nm << "]:\n";
    for (int i = 0; i < (int)sec_idx_member.size(); i++) {
        if (strcmp(sec_idx_member[i].name, nm) == 0) {
            int offset = searchinprimaryindex_member(sec_idx_member[i].id);
            if (offset != -1) {
                iofile.seekg(offset, ios::beg);
                fm.read_member_from_file(iofile, m);
                cout << "-> ID: " << m.id << " | Phone: " << m.phone << endl;
                foundIds.push_back(m.id);
            }
        }
    }

    if (foundIds.empty()) {
        cout << "No members found with this name.\n";
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

    deletemember(iofile, selectedId);
}

void member::updatemember(fstream &iofile, const int &id) {
    member_file_manager fm;
    member oldM, newM;

    int offset = searchinprimaryindex_member(id);
    if (offset == -1) {
        cout << "Member not found\n";
        return;
    }

    // Read existing data
    iofile.seekg(offset, ios::beg);
    fm.read_member_from_file(iofile, oldM);
    int oldLen = oldM.calclength();

    cout << "Current Data::\n";
    oldM.display();
    cout << "\n--------------------------\n";

    // Get new data
    cout << "Edit Data::\n";
    newM.read_member_data_from_user(true);
    newM.id = id;
    int newLen = newM.calclength();

    if (oldLen >= newLen) {
        // t8yyr f nfs el mkan
        iofile.seekp(offset, ios::beg);
        fm.write_member_to_file(iofile, newM);

        int padding = oldLen - newLen;
        while (padding--) iofile.put('#');

        // Update secondary index
        deletefromsecondaryindex_member(oldM.name, id);
        addtosecondaryindex_member(newM.name, id);

        cout << "Member updated successfully .\n";
    }
    else {
        // add at end
        // Remove old record
        deletemember(iofile, id);
        // Add new record 
        addmember(iofile, newM);

        cout << "Member updated successfully (Relocated).\n";
    }
}

void member::updatemember_byname(fstream &iofile, char* nm) {
    vector<int> foundIds;
    member_file_manager fm;
    member m;

    cout << "\nMembers found with name [" << nm << "]:\n";
    for (int i = 0; i < (int)sec_idx_member.size(); i++) {
        if (strcmp(sec_idx_member[i].name, nm) == 0) {
            int offset = searchinprimaryindex_member(sec_idx_member[i].id);
            if (offset != -1) {
                iofile.seekg(offset, ios::beg);
                fm.read_member_from_file(iofile, m);
                cout << "-> ID: " << m.id << " | Phone: " << m.phone << endl;
                foundIds.push_back(m.id);
            }
        }
    }

    if (foundIds.empty()) {
        cout << "No members found with this name.\n";
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

    updatemember(iofile, selectedId);
}

void member::displaymembers(fstream &iofile) {
    member_file_manager fm;
    member m;
    if(pri_member.empty()) cout << "No members to display.\n";
    for (int i = 0; i < (int)pri_member.size(); i++) {
        int offset = pri_member[i].offset;
        iofile.seekg(offset, ios::beg);
        fm.read_member_from_file(iofile, m);
        m.display();
        cout << "====================\n";
    }
}

void member :: displayTOP5Members(fstream& file) {
    member m;
    member_file_manager fm;

    if (pri_member.empty()) {
        cout << "No members available.\n";
        return;
    }

    cout << "\n===== TOP 5 MEMBERS =====\n";
    int count = 0;
    for (int i = 0; i < (int)pri_member.size() && count < 5; i++) {
        file.seekg(pri_member[i].offset);
        fm.read_member_from_file(file, m);

        cout << "\nMember " << (count + 1) << ":\n";
        m.display();
        cout << "-----------------\n";
        count++;
    }
}
#endif