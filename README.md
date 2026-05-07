# Library Management System (Indexing & File Structures)

A professional C++ implementation of a Library Management System using **Variable-Length Records** and **Advanced File Indexing** techniques. This project avoids traditional databases to demonstrate how data can be managed efficiently using raw file structures, primary/secondary indexes, and space-management algorithms.

## 🚀 Key Technical Features

* **Primary Indexing (ID):** Uses a sorted vector and binary search ($O(\log n)$) to map unique IDs to specific file offsets.
* **Secondary Indexing:** * **Members:** Searchable by **Name**.
    * **Books:** Searchable by **Author**.
* **Space Management (Availability List):** Implements a **Free List** to track deleted record slots. New records are inserted into these slots to prevent file fragmentation and minimize storage waste.
* **Dynamic Updating:**
    * **In-Place Update:** If the new data is smaller than or equal to the old record, it overwrites the existing space and uses `#` padding.
    * **Relocation:** If the record grows, it marks the old space as deleted and finds a new suitable location.
* **Binary Persistence:** All data, primary indexes, secondary indexes, and availability lists are saved in binary format to ensure fast loading and saving.

## 📂 Project Structure

| File | Role |
| :--- | :--- |
| `member.h` | Logic for Member management, indexing, and Avail List. |
| `book.h` | Logic for Book management, indexing, and Avail List. |
| `*.txt` | Binary storage files for data and index structures. |

## 🛠️ Implementation Details

### Record Format
Records are stored using a length-indicator approach:
`[ID (int)] [TitleLen (short)] [Title (char*)] [AuthorLen (short)] [Author (char*)]`

### Deletion Logic
When a record is deleted:
1.  It is removed from the **Primary Index** and **Secondary Index**.
2.  The physical spot in the file is marked with a `*`.
3.  The offset and size are stored in the `avail_list` for future reuse.

## 💻 Getting Started

### Prerequisites
* A C++ compiler supporting C++11 or higher (GCC, Clang, or MSVC).

### Usage Example
```cpp
#include "member.h"
#include "book.h"

int main() {
    fstream memberFile("members.txt", ios::in | ios::out | ios::binary);
    
    // Read existing indexes from files
    readprimaryindex_member();
    readsecondaryindex_member();
    readavail_list_member();

    member m;
    // Add a new member
    m.read_member_data_from_user();
    m.addmember(memberFile, m);

    // Save indexes before exiting
    writeprimaryindex_member();
    writesecondaryindex_member();
    writeavail_list_member();

    return 0;
}
