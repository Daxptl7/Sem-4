#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

struct City {
  string name;
  int x;
  int y;

  City() : name(""), x(0), y(0) {}
  City(string n, int x_coord, int y_coord) : name(n), x(x_coord), y(y_coord) {}
};

// ARRAY-BASED LIST IMPLEMENTATION
class ArrayListDB {
private:
  City *db;
  int capacity;
  int size;

  void resize() {
    capacity *= 2;
    City *new_db = new City[capacity];
    for (int i = 0; i < size; ++i) {
      new_db[i] = db[i];
    }
    delete[] db;
    db = new_db;
  }

public:
  ArrayListDB(int cap = 10) : capacity(cap), size(0) {
    db = new City[capacity];
  }

  ~ArrayListDB() { delete[] db; }

  void insertRecord(string name, int x, int y) {
    if (size == capacity)
      resize();
    db[size++] = City(name, x, y);
  }

  void deleteByName(string name) {
    for (int i = 0; i < size; ++i) {
      if (db[i].name == name) {
        for (int j = i; j < size - 1; ++j) {
          db[j] = db[j + 1];
        }
        size--;
        i--;
      }
    }
  }

  void deleteByCoordinate(int x, int y) {
    for (int i = 0; i < size; ++i) {
      if (db[i].x == x && db[i].y == y) {
        for (int j = i; j < size - 1; ++j) {
          db[j] = db[j + 1];
        }
        size--;
        i--;
      }
    }
  }

  void searchByName(string name) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
      if (db[i].name == name) {
        cout << "Found: " << db[i].name << " at (" << db[i].x << ", " << db[i].y
             << ")\n";
        found = true;
      }
    }
    if (!found)
      cout << "City '" << name << "' not found.\n";
  }

  void searchByCoordinate(int x, int y) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
      if (db[i].x == x && db[i].y == y) {
        cout << "Found: " << db[i].name << " at (" << db[i].x << ", " << db[i].y
             << ")\n";
        found = true;
      }
    }
    if (!found)
      cout << "No city found at (" << x << ", " << y << ").\n";
  }

  void printWithinDistance(int px, int py, double distance) {
    cout << "Cities within distance " << distance << " from (" << px << ", "
         << py << "):\n";
    bool found = false;
    for (int i = 0; i < size; ++i) {
      double dist = sqrt(pow(db[i].x - px, 2) + pow(db[i].y - py, 2));
      if (dist <= distance) {
        cout << "- " << db[i].name << " at (" << db[i].x << ", " << db[i].y
             << ") [Distance: " << dist << "]\n";
        found = true;
      }
    }
    if (!found)
      cout << "None found.\n";
  }

  void printAll() {
    for (int i = 0; i < size; i++) {
      cout << "- " << db[i].name << " at (" << db[i].x << ", " << db[i].y
           << ")\n";
    }
  }
};

// LINKED LIST IMPLEMENTATION

struct Node {
  City data;
  Node *next;
  Node(string n, int x, int y) : data(n, x, y), next(nullptr) {}
};

class LinkedListDB {
private:
  Node *head;

public:
  LinkedListDB() : head(nullptr) {}

  ~LinkedListDB() {
    Node *curr = head;
    while (curr) {
      Node *temp = curr;
      curr = curr->next;
      delete temp;
    }
  }

  void insertRecord(string name, int x, int y) {
    Node *newNode = new Node(name, x, y);
    if (!head) {
      head = newNode;
    } else {
      Node *curr = head;
      while (curr->next) {
        curr = curr->next;
      }
      curr->next = newNode;
    }
  }

  void deleteByName(string name) {
    while (head && head->data.name == name) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }

    Node *curr = head;
    while (curr && curr->next) {
      if (curr->next->data.name == name) {
        Node *temp = curr->next;
        curr->next = temp->next;
        delete temp;
      } else {
        curr = curr->next;
      }
    }
  }

  void deleteByCoordinate(int x, int y) {
    while (head && head->data.x == x && head->data.y == y) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }

    Node *curr = head;
    while (curr && curr->next) {
      if (curr->next->data.x == x && curr->next->data.y == y) {
        Node *temp = curr->next;
        curr->next = temp->next;
        delete temp;
      } else {
        curr = curr->next;
      }
    }
  }

  void searchByName(string name) {
    Node *curr = head;
    bool found = false;
    while (curr) {
      if (curr->data.name == name) {
        cout << "Found: " << curr->data.name << " at (" << curr->data.x << ", "
             << curr->data.y << ")\n";
        found = true;
      }
      curr = curr->next;
    }
    if (!found)
      cout << "City '" << name << "' not found.\n";
  }

  void searchByCoordinate(int x, int y) {
    Node *curr = head;
    bool found = false;
    while (curr) {
      if (curr->data.x == x && curr->data.y == y) {
        cout << "Found: " << curr->data.name << " at (" << curr->data.x << ", "
             << curr->data.y << ")\n";
        found = true;
      }
      curr = curr->next;
    }
    if (!found)
      cout << "No city found at (" << x << ", " << y << ").\n";
  }

  void printWithinDistance(int px, int py, double distance) {
    cout << "Cities within distance " << distance << " from (" << px << ", "
         << py << "):\n";
    Node *curr = head;
    bool found = false;
    while (curr) {
      double dist = sqrt(pow(curr->data.x - px, 2) + pow(curr->data.y - py, 2));
      if (dist <= distance) {
        cout << "- " << curr->data.name << " at (" << curr->data.x << ", "
             << curr->data.y << ") [Distance: " << dist << "]\n";
        found = true;
      }
      curr = curr->next;
    }
    if (!found)
      cout << "None found.\n";
  }

  void printAll() {
    Node *curr = head;
    while (curr) {
      cout << "- " << curr->data.name << " at (" << curr->data.x << ", "
           << curr->data.y << ")\n";
      curr = curr->next;
    }
  }
};

int main() {
  ArrayListDB arrayDB;
  LinkedListDB linkedDB;

  while (true) {
    cout << "\n========= CITY DATABASE MENU =========\n";
    cout << "1. Insert Data\n";
    cout << "2. Print List (Array DB)\n";
    cout << "3. Print List (Linked List DB)\n";
    cout << "4. Search by Name\n";
    cout << "5. Search by Coordinate\n";
    cout << "6. Delete by Name\n";
    cout << "7. Delete by Coordinate\n";
    cout << "8. Print within Distance\n";
    cout << "9. Exit\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 9) {
      cout << "Exiting...\n";
      break;
    }

    switch (choice) {
    case 1: {
      string name;
      int x, y;
      cout << "Enter Name: ";
      cin >> name;
      cout << "Enter X: ";
      cin >> x;
      cout << "Enter Y: ";
      cin >> y;
      arrayDB.insertRecord(name, x, y);
      linkedDB.insertRecord(name, x, y);
      cout << "Data inserted into both databases.\n";
      break;
    }
    case 2:
      cout << "--- Array DB ---\n";
      arrayDB.printAll();
      break;
    case 3:
      cout << "--- Linked List DB ---\n";
      linkedDB.printAll();
      break;
    case 4: {
      string name;
      cout << "Enter name to search: ";
      cin >> name;
      cout << "Array DB: ";
      arrayDB.searchByName(name);
      cout << "Linked List DB: ";
      linkedDB.searchByName(name);
      break;
    }
    case 5: {
      int x, y;
      cout << "Enter X: ";
      cin >> x;
      cout << "Enter Y: ";
      cin >> y;
      cout << "Array DB: ";
      arrayDB.searchByCoordinate(x, y);
      cout << "Linked List DB: ";
      linkedDB.searchByCoordinate(x, y);
      break;
    }
    case 6: {
      string name;
      cout << "Enter name to delete: ";
      cin >> name;
      arrayDB.deleteByName(name);
      linkedDB.deleteByName(name);
      cout << "Deleted from both databases if it existed.\n";
      break;
    }
    case 7: {
      int x, y;
      cout << "Enter X: ";
      cin >> x;
      cout << "Enter Y: ";
      cin >> y;
      arrayDB.deleteByCoordinate(x, y);
      linkedDB.deleteByCoordinate(x, y);
      cout << "Deleted from both databases if it existed.\n";
      break;
    }
    case 8: {
      int x, y;
      double dist;
      cout << "Enter target X: ";
      cin >> x;
      cout << "Enter target Y: ";
      cin >> y;
      cout << "Enter maximum distance: ";
      cin >> dist;
      cout << "\n--- Array DB ---\n";
      arrayDB.printWithinDistance(x, y, dist);
      cout << "\n--- Linked List DB ---\n";
      linkedDB.printWithinDistance(x, y, dist);
      break;
    }
    default:
      cout << "Invalid Choice!\n";
    }
  }

  return 0;
}