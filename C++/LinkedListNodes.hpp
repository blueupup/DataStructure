#ifndef LINKEDLISTNODES_HPP
#define LINKEDLISTNODES_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

class JobNode {
public:
    string id;
    string description;
    JobNode* next;

    JobNode(const string& jid, const string& desc)
    {
        id = jid;
        description = desc;
        next = nullptr;
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


    void addJobAtFront(const string& id, const string& description) {
        JobNode* newNode = new JobNode(id, description);
        newNode->next = head;
        head = newNode;
        size++;
    }


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
    string id;
    string description;
    ResumeNode* next;

    string bestJobId;
    string bestJobDesc;
    int bestMatchScore;

    ResumeNode(const string& rid, const string& desc)
    {
        id = rid;
        description = desc;
        bestJobDesc = "";
        bestJobId = "";
        bestMatchScore = 0;
        next = nullptr;
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

    ResumeNode* getHead() const { return head; }

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


//Load Data

inline string trim(const string& str) {
    if (str.empty()) return "";
    size_t start = 0;
    size_t end = str.size();

    while (start < end && isspace(static_cast<unsigned char>(str[start]))) start++;
    while (end > start && isspace(static_cast<unsigned char>(str[end - 1]))) end--;

    if (start >= end) return "";
    return str.substr(start, end - start);
}

inline string extract_skills(const string& text) {
    try {
        if (text.empty()) return "";

        string start_marker = "in ";
        char end_marker = '.';

        string lower_text = text;
        transform(lower_text.begin(), lower_text.end(), lower_text.begin(), ::tolower);

        size_t start_pos = lower_text.find(start_marker);
        if (start_pos == string::npos) return "";

        size_t end_pos = lower_text.find(end_marker, start_pos + start_marker.size());
        if (end_pos == string::npos || end_pos <= start_pos) return "";

        start_pos += start_marker.length();

        // Sanity checks
        if (start_pos >= text.size()) return "";
        size_t length = min(end_pos - start_pos, text.size() - start_pos);

        return text.substr(start_pos, length);
    }
    catch (const exception& e) {
        cerr << "extract_skills() failed: " << e.what()
             << " | text: " << text.substr(0, min((size_t)100, text.size())) << "...\n";
        return "";
    }
}



inline bool loadJobsFromCSV(const string& filename, JobLinkedList& jobs) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return false;
    }
    
    string line;
    getline(file, line);
    
    int jobCounter = 1;
    int count = 0;
    
    cout << "\n--- Loading Jobs ---\n";
    
    while (getline(file, line)) {
        string trimmedLine = trim(line);
        
        if (trimmedLine.empty()) {
            continue;
        }

        string skills = extract_skills(trimmedLine);

        if (skills.empty()) {
            cout << "  Warning: No skills found in job description. Skipping line.\n";
            continue;
        }


        // Auto-generate ID
        string generatedID = "J";
        int numDigits = to_string(jobCounter).length();
        if (numDigits < 3) {
            generatedID += string(3 - numDigits, '0');  // Only pad if needed
        }
        generatedID += to_string(jobCounter);

        
        jobs.addJobAtEnd(generatedID, trimmedLine);

        count++;
        jobCounter++;
    }
    
    file.close();
    
    cout << "\n✓ Successfully loaded " << count << " jobs\n";
    cout << "-------------------\n";
    
    return count > 0;
}


inline bool loadResumesFromCSV(const string& filename, ResumeLinkedList& resumes) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return false;
    }
    
    string line;
    getline(file, line);
    
    int resumeCounter = 1;
    int count = 0;
    
    cout << "\n--- Loading Resumes ---\n";
    
    while (getline(file, line)) {
        string trimmedLine = trim(line);
        
        if (trimmedLine.empty()) {
            continue; // Skip empty lines
        }

        string skills = extract_skills(trimmedLine);
        
        if (skills.empty()) {
            cout << "  Warning: No skills found in resume description. Skipping line.\n";
            continue;
        }


        // Auto-generate ID
        string generatedID = "J";
        int numDigits = to_string(resumeCounter).length();
        if (numDigits < 3) {
            generatedID += string(3 - numDigits, '0');  // Only pad if needed
        }
        generatedID += to_string(resumeCounter);
        
        resumes.addResume(generatedID, trimmedLine);
        
        count++;
        resumeCounter++;
    }
    
    file.close();
    
    cout << "\n✓ Successfully loaded " << count << " resumes\n";
    cout << "-------------------\n";
    
    return count > 0;
}

#endif