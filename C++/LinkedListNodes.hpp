#ifndef LINKEDLISTNODES_HPP
#define LINKEDLISTNODES_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

inline string trim(const string& str) {
    if (str.empty()) return "";
    size_t start = 0;
    size_t end = str.size();

    while (start < end && isspace(static_cast<unsigned char>(str[start]))) start++;
    while (end > start && isspace(static_cast<unsigned char>(str[end - 1]))) end--;

    return (start >= end) ? "" : str.substr(start, end - start);
}

inline string extract_skills(const string& text) {
    if (text.empty()) return "";

    const char* start_marker = "in ";
    const size_t marker_len = 3;
    const char end_marker = '.';

    size_t start_pos = string::npos;
    for (size_t i = 0; i <= text.size() - marker_len; i++) {
        if ((text[i] == 'i' || text[i] == 'I') && 
            (text[i+1] == 'n' || text[i+1] == 'N') && 
            text[i+2] == ' ') {
            start_pos = i;
            break;
        }
    }
    
    if (start_pos == string::npos) return "";

    size_t content_start = start_pos + marker_len;
    size_t end_pos = text.find(end_marker, content_start);
    
    if (end_pos == string::npos || end_pos <= content_start) return "";
    if (content_start >= text.size()) return "";
    
    size_t length = end_pos - content_start;
    if (length > text.size() - content_start) {
        length = text.size() - content_start;
    }

    return text.substr(content_start, length);
}

// Node classes
class JobNode {
public:
    string id;
    string description;
    int skills[33];
    int criticalSkills[6];
    int coreSkills[10];
    int softSkills[7];
    JobNode* next;

    int totalMatches;
    double totalScore;
    double averageScore;
    
    JobNode(const string& jid, const string& desc, const string& skills)
        : id(jid), description(desc), next(nullptr),
          totalMatches(0), totalScore(0.0), averageScore(0.0) {}
};

class JobLinkedList {
private:
    JobNode* head;
    JobNode* tail;
    int size;

public:
    JobLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~JobLinkedList() {
        while (head != nullptr) {
            JobNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addJobAtFront(const string& id, const string& description) {
        string skills = extract_skills(description);
        JobNode* newNode = new JobNode(id, description, skills);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) tail = newNode;
        size++;
    }

    void addJobAtEnd(const string& id, const string& description) {
        string skills = extract_skills(description);
        JobNode* newNode = new JobNode(id, description, skills);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    int getSize() const { return size; }
    JobNode* getHead() const { return head; }

    string getJobId(int index) const {
        JobNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return (current != nullptr) ? current->id : "";
    }

    string getJobDescription(int index) const {
        JobNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return (current != nullptr) ? current->description : "";
    }

    void displayTop10ByScore() const {
        if (size == 0) return;
        
        // Use dynamic allocation based on actual size
        JobNode** jobArray = new JobNode*[size];
        int count = 0;

        for (JobNode* job = head; job != nullptr; job = job->next)
            jobArray[count++] = job;

        // Selection Sort by averageScore (descending)
        for (int i = 0; i < count - 1; i++) {
            int maxIdx = i;
            for (int j = i + 1; j < count; j++) {
                if (jobArray[j]->averageScore > jobArray[maxIdx]->averageScore)
                    maxIdx = j;
            }
            if (maxIdx != i) {
                JobNode* temp = jobArray[i];
                jobArray[i] = jobArray[maxIdx];
                jobArray[maxIdx] = temp;
            }
        }

        cout << "\nTop 10 Jobs by Average Match Score\n";
        cout << "--------------------------------------------\n";
        int limit = (count < 10) ? count : 10;
        for (int i = 0; i < limit; i++) {
            cout << i + 1 << ". " << jobArray[i]->id
                 << " | Avg Score: " << jobArray[i]->averageScore
                 << " | Matches: " << jobArray[i]->totalMatches << "\n";
        }
        cout << "--------------------------------------------\n";
        
        delete[] jobArray;
    }
};

class ResumeNode {
public:
    string id;
    string description;
    int skills[33];
    int criticalSkills[6];
    int coreSkills[10];
    int softSkills[7];
    ResumeNode* next;

    string bestJobId;
    string bestJobDesc;
    int bestMatchScore;

    ResumeNode(const string& rid, const string& desc, const string& skills)
        : id(rid), description(desc), next(nullptr),
          bestJobId(""), bestJobDesc(""), bestMatchScore(0) {}
};

class ResumeLinkedList {
private:
    ResumeNode* head;
    ResumeNode* tail;
    int size;

public:
    ResumeLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~ResumeLinkedList() {
        while (head != nullptr) {
            ResumeNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addResume(const string& id, const string& description) {
        string skills = extract_skills(description);
        ResumeNode* newNode = new ResumeNode(id, description, skills);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    int getSize() const { return size; }
    ResumeNode* getHead() const { return head; }

    string getResumeId(int index) const {
        ResumeNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return (current != nullptr) ? current->id : "";
    }

    string getResumeDescription(int index) const {
        ResumeNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
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
        for (ResumeNode* current = head; current != nullptr; current = current->next) {
            if (current->id == searchId) return current;
        }
        return nullptr;
    }
};

// Load Data Functions
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
        if (trimmedLine.empty()) continue;

        string skills = extract_skills(trimmedLine);
        if (skills.empty()) {
            cout << "  Warning: No skills found in job description. Skipping line.\n";
            continue;
        }

        // Generate ID
        string generatedID = "J";
        if (jobCounter < 10) generatedID += "00";
        else if (jobCounter < 100) generatedID += "0";
        generatedID += to_string(jobCounter);
        
        jobs.addJobAtEnd(generatedID, trimmedLine);

        count++;
        jobCounter++;
    }
    
    file.close();
    
    cout << "Successfully loaded " << count << " jobs\n";
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
        if (trimmedLine.empty()) continue;

        string skills = extract_skills(trimmedLine);
        if (skills.empty()) {
            cout << "  Warning: No skills found in resume description. Skipping line.\n";
            continue;
        }

        // Generate ID
        string generatedID = "R";
        if (resumeCounter < 10) generatedID += "00";
        else if (resumeCounter < 100) generatedID += "0";
        generatedID += to_string(resumeCounter);
        
        resumes.addResume(generatedID, trimmedLine);
        
        count++;
        resumeCounter++;
    }
    
    file.close();
    
    cout << "Successfully loaded " << count << " resumes\n";
    cout << "-------------------\n";
    
    return count > 0;
}

#endif