#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
using namespace std;


class JobLinkedList {
private:
    struct JobNode {
        char id[20];
        char description[1000];
        JobNode* next;
        
        JobNode(const char* jid, const char* desc) : next(nullptr) {
            strcpy(id, jid);
            strcpy(description, desc);
        }
    };
    
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
    
    void addJob(const char* id, const char* description) {
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
    
    const char* getJobId(int index) const {
        JobNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        return (current != nullptr) ? current->id : nullptr;
    }
    
    const char* getJobDescription(int index) const {
        JobNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        return (current != nullptr) ? current->description : nullptr;
    }
    
    // Bubble sort for linked list
    void sortById() {
        if (head == nullptr || head->next == nullptr) return;
        
        bool swapped;
        do {
            swapped = false;
            JobNode* current = head;
            while (current->next != nullptr) {
                if (strcmp(current->id, current->next->id) > 0) {
                    // Swap data
                    char tempId[20], tempDesc[1000];
                    strcpy(tempId, current->id);
                    strcpy(tempDesc, current->description);
                    
                    strcpy(current->id, current->next->id);
                    strcpy(current->description, current->next->description);
                    
                    strcpy(current->next->id, tempId);
                    strcpy(current->next->description, tempDesc);
                    
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
    
    // Display all jobs
    void displayJobs() const {
        JobNode* current = head;
        int index = 0;
        while (current != nullptr) {
            cout << "Job " << index + 1 << ":\n";
            cout << "  ID: " << current->id << endl;
            cout << "  Description: " << current->description << endl;
            cout << endl;
            current = current->next;
            index++;
        }
    }
    
    // Search for job by ID (Linear Search)
    JobNode* searchById(const char* searchId) const {
        JobNode* current = head;
        while (current != nullptr) {
            if (strcmp(current->id, searchId) == 0) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

class ResumeLinkedList {
private:
    struct ResumeNode {
        char id[20];
        char description[1000];
        ResumeNode* next;
        
        ResumeNode(const char* rid, const char* desc) : next(nullptr) {
            strcpy(id, rid);
            strcpy(description, desc);
        }
    };
    
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
    
    void addResume(const char* id, const char* description) {
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
    
    const char* getResumeId(int index) const {
        ResumeNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        return (current != nullptr) ? current->id : nullptr;
    }
    
    const char* getResumeDescription(int index) const {
        ResumeNode* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        return (current != nullptr) ? current->description : nullptr;
    }
    
    // Display all resumes
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
    
    // Search for resume by ID (Linear Search)
    ResumeNode* searchById(const char* searchId) const {
        ResumeNode* current = head;
        while (current != nullptr) {
            if (strcmp(current->id, searchId) == 0) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

// ============== JOB MATCHING ALGORITHM ==============

class JobMatcher {
private:
    // Convert string to lowercase for case-insensitive matching
    void toLower(char* str) {
        for (int i = 0; str[i]; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str[i] = str[i] + 32;
            }
        }
    }
    
    // Count keyword matches between resume and job description
    int countKeywordMatches(const char* resume, const char* job) {
        char resumeCopy[1000], jobCopy[1000];
        strcpy(resumeCopy, resume);
        strcpy(jobCopy, job);
        
        toLower(resumeCopy);
        toLower(jobCopy);
        
        // Common keywords to search for
        const char* keywords[] = {
            "python", "java", "c++", "javascript", "sql",
            "leadership", "team", "management", "communication",
            "developer", "engineer", "analyst", "manager",
            "experience", "project", "design", "data",
            "react", "node", "database", "frontend", "backend"
        };
        
        int matchCount = 0;
        int keywordSize = 21;
        
        for (int i = 0; i < keywordSize; i++) {
            if (strstr(resumeCopy, keywords[i]) != nullptr && 
                strstr(jobCopy, keywords[i]) != nullptr) {
                matchCount++;
            }
        }
        
        return matchCount;
    }
    
public:
    // Match jobs to resumes using Linked List
    void matchJobsLinkedList(JobLinkedList& jobs, ResumeLinkedList& resumes) {
        cout << "\n========== JOB MATCHING RESULTS (Linked List) ==========\n";
        
        clock_t start = clock();
        
        for (int i = 0; i < resumes.getSize(); i++) {
            cout << "\n----------------------------------------\n";
            cout << "Resume ID: " << resumes.getResumeId(i) << endl;
            cout << "Resume Description: " << resumes.getResumeDescription(i) << endl;
            cout << "\nTop Job Matches:\n";
            
            int maxMatches = 0;
            int bestJobIndex = -1;
            
            // Linear search through all jobs to find best match
            for (int j = 0; j < jobs.getSize(); j++) {
                int matches = countKeywordMatches(
                    resumes.getResumeDescription(i),
                    jobs.getJobDescription(j)
                );
                
                if (matches > maxMatches) {
                    maxMatches = matches;
                    bestJobIndex = j;
                }
            }
            
            if (bestJobIndex != -1 && maxMatches > 0) {
                cout << "  Best Match - Job ID: " << jobs.getJobId(bestJobIndex) << endl;
                cout << "  Job Description: " << jobs.getJobDescription(bestJobIndex) << endl;
                cout << "  Match Score: " << maxMatches << " keywords matched\n";
            } else {
                cout << "  No suitable match found (0 keyword matches).\n";
            }
        }
        
        clock_t end = clock();
        double timeTaken = double(end - start) / CLOCKS_PER_SEC;
        cout << "\n========================================\n";
        cout << "Time taken for matching: " << timeTaken << " seconds\n";
        cout << "========================================\n";
    }
};

// ============== FILE LOADING FUNCTIONS ==============

bool loadJobsToLinkedList(const char* filename, JobLinkedList& jobs) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        cerr << "Make sure the file exists in the same directory as the program.\n";
        return false;
    }
    
    string line;
    getline(file, line); // Skip header
    
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string id, description;
        
        getline(ss, id, ',');
        getline(ss, description);
        
        if (!id.empty() && !description.empty()) {
            jobs.addJob(id.c_str(), description.c_str());
            count++;
        }
    }
    
    file.close();
    cout << "Successfully loaded " << count << " jobs from " << filename << endl;
    return true;
}

bool loadResumesToLinkedList(const char* filename, ResumeLinkedList& resumes) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        cerr << "Make sure the file exists in the same directory as the program.\n";
        return false;
    }
    
    string line;
    getline(file, line); // Skip header
    
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string id, description;
        
        getline(ss, id, ',');
        getline(ss, description);
        
        if (!id.empty() && !description.empty()) {
            resumes.addResume(id.c_str(), description.c_str());
            count++;
        }
    }
    
    file.close();
    cout << "Successfully loaded " << count << " resumes from " << filename << endl;
    return true;
}

// ============== MAIN DRIVER ==============

int main() {
    cout << "============================================" << endl;
    cout << "    JOB MATCHING SYSTEM" << endl;
    cout << "    Linked List Implementation" << endl;
    cout << "============================================\n" << endl;
    
    // Linked List-based implementation
    JobLinkedList jobs;
    ResumeLinkedList resumes;
    
    // Load data
    cout << "Loading data...\n" << endl;
    
    if (!loadJobsToLinkedList("job_description.csv", jobs)) {
        cout << "\nPress Enter to exit...";
        cin.get();
        return 1;
    }
    
    if (!loadResumesToLinkedList("resume.csv", resumes)) {
        cout << "\nPress Enter to exit...";
        cin.get();
        return 1;
    }
    
    cout << "\nTotal Jobs: " << jobs.getSize() << endl;
    cout << "Total Resumes: " << resumes.getSize() << endl;
    
    // Menu system
    int choice;
    do {
        cout << "\n\n========== MENU ==========\n";
        cout << "1. Display All Jobs\n";
        cout << "2. Display All Resumes\n";
        cout << "3. Search Job by ID\n";
        cout << "4. Search Resume by ID\n";
        cout << "5. Sort Jobs by ID\n";
        cout << "6. Perform Job Matching\n";
        cout << "0. Exit\n";
        cout << "==========================\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                cout << "\n--- All Jobs ---\n";
                jobs.displayJobs();
                break;
                
            case 2:
                cout << "\n--- All Resumes ---\n";
                resumes.displayResumes();
                break;
                
            case 3: {
                char searchId[20];
                cout << "Enter Job ID to search: ";
                cin.getline(searchId, 20);
                
                clock_t start = clock();
                auto result = jobs.searchById(searchId);
                clock_t end = clock();
                
                if (result != nullptr) {
                    cout << "\nJob Found!\n";
                    cout << "ID: " << searchId << endl;
                    cout << "Description: " << result->description << endl;
                } else {
                    cout << "\nJob not found.\n";
                }
                cout << "Search time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
                break;
            }
                
            case 4: {
                char searchId[20];
                cout << "Enter Resume ID to search: ";
                cin.getline(searchId, 20);
                
                clock_t start = clock();
                auto result = resumes.searchById(searchId);
                clock_t end = clock();
                
                if (result != nullptr) {
                    cout << "\nResume Found!\n";
                    cout << "ID: " << searchId << endl;
                    cout << "Description: " << result->description << endl;
                } else {
                    cout << "\nResume not found.\n";
                }
                cout << "Search time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
                break;
            }
                
            case 5: {
                cout << "\nSorting jobs by ID...\n";
                clock_t start = clock();
                jobs.sortById();
                clock_t end = clock();
                cout << "Jobs sorted successfully!\n";
                cout << "Sort time: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
                break;
            }
                
            case 6: {
                JobMatcher matcher;
                matcher.matchJobsLinkedList(jobs, resumes);
                break;
            }
                
            case 0:
                cout << "\nExiting program. Goodbye!\n";
                break;
                
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
        
    } while (choice != 0);
    
    cout << "\n============================================" << endl;
    cout << "    PERFORMANCE NOTES" << endl;
    cout << "============================================" << endl;
    cout << "Linked List Implementation:\n";
    cout << "  - Dynamic memory allocation (no resize needed)\n";
    cout << "  - Sequential access O(n) for search operations\n";
    cout << "  - Memory overhead for storing pointers\n";
    cout << "  - Efficient insertions at head/tail\n";
    cout << "  - Bubble sort used: O(n^2) time complexity\n";
    cout << "  - Linear search used: O(n) time complexity\n";
    cout << "============================================\n";
    
    return 0;
}