#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

class JobNode {
public:
    // --- Changed char[] to string ---
    string id;
    string description;
    JobNode* next;

    JobNode(const string& jid, const string& desc)
        : id(jid), description(desc), next(nullptr) {
    }
};

class JobLinkedList {
private:
    JobNode* head;
    int size;

public:
    JobLinkedList() : head(nullptr), size(0) {}

    ~JobLinkedList() {
        while (head != nullptr) {
            JobNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // --- Updated parameters to const string& ---
    void addJobAtFront(const string& id, const string& description) {
        JobNode* newNode = new JobNode(id, description);
        newNode->next = head; // Point new node to the old head
        head = newNode;
        size++;
    }

    // --- Updated parameters to const string& ---
    void addJobAtEnd(const string& id, const string& description) {
        JobNode* newNode = new JobNode(id, description);
        if (head == nullptr) {
            head = newNode;
        } else {
            JobNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    int getSize() const { return size; }

    JobNode* getHead() const { return head; }

    // --- Updated return type from const char* to string ---
    string getJobId(int index) const {
        JobNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        // Return ID or an empty string if not found
        return (current != nullptr) ? current->id : "";
    }

    // --- Updated return type from const char* to string ---
    string getJobDescription(int index) const {
        JobNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        // Return description or an empty string if not found
        return (current != nullptr) ? current->description : "";
    }
};

class ResumeNode {
public:
    // --- Changed char[] to string ---
    string id;
    string description;
    ResumeNode* next;

    ResumeNode(const string& rid, const string& desc)
        : id(rid), description(desc), next(nullptr) {

    }
};

class ResumeLinkedList {
private:
    ResumeNode* head;
    int size;

public:
    ResumeLinkedList() : head(nullptr), size(0) {}

    ~ResumeLinkedList() {
        while (head != nullptr) {
            ResumeNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addResume(const string& id, const string& description) {
        ResumeNode* newNode = new ResumeNode(id, description);
        if (head == nullptr) {
            head = newNode;
        } else {
            ResumeNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    int getSize() const { return size; }

    string getResumeId(int index) const {
        ResumeNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        return (current != nullptr) ? current->id : "";
    }

    string getResumeDescription(int index) const {
        ResumeNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        return (current != nullptr) ? current->description : "";
    }


    void displayResumes() const {
        ResumeNode* current = head;
        int index = 0;
        while (current != nullptr) {
            cout << "Resume " << index + 1 << ":\n";
            cout << "  ID: " << current->id << endl;
            cout << "  Description: " << current->description << endl;
            cout << endl;
            current = current->next;
            index++;
        }
    }

    ResumeNode* searchById(const string& searchId) const {
        ResumeNode* current = head;
        while (current != nullptr) {
            if (current->id == searchId) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};