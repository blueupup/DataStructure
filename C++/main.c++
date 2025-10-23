#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <algorithm>
#include "LinkedListNodes.hpp"
#include "MatchingAlgorithm.hpp"

using namespace std;

int main() {
    cout << "============================================" << endl;
    cout << "    JOB MATCHING SYSTEM" << endl;
    cout << "============================================\n" << endl;
    
    JobLinkedList jobs;
    ResumeLinkedList resumes;
    
    // Load data
    if (!loadJobsFromCSV("job_description.csv", jobs)) {
        return 1;
    }
    
    if (!loadResumesFromCSV("resume.csv", resumes)) {
        return 1;
    }
    
    cout << "\nTotal Jobs: " << jobs.getSize() << endl;
    cout << "Total Resumes: " << resumes.getSize() << endl;
    
    KeywordAlgorithm keywordAlg;
    WeightedAlgorithm weightedAlg;
    
    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Perform Keyword Matching\n";
        cout << "2. Perform Weighted Matching\n";
        cout << "3. Display Top 10 Jobs by Average Match Score\n";
        cout << "4. Search Job By ID\n";
        cout << "5. Search Resume By ID\n";

        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                keywordAlg.performMatching(resumes, jobs);
                break;
            case 2:
                weightedAlg.performWeightedMatching(resumes, jobs);
                break;
            case 3:
                cout << "Please select sorting criteria:\n";
                cout << "1. By Average Match Score\n";
                cout << "2. By Total Matches\n";
                int sortChoice;
                cin >> sortChoice;
                if (sortChoice == 1) {
                    jobs.displayTop10ByScore();
                } else if (sortChoice == 2) {
                    jobs.displayTop10ByMatches();
                } else {
                    cout << "Invalid sorting choice." << endl;
                }
                break;
            case 4: {
                string jobId;
                cout << "Enter Job ID to search: ";
                cin >> jobId;
                jobs.searchById(jobId);
                cout << "Total Matches for Job " << jobId << ": " << endl;
                cout << "Average Match Score: " << endl;
                break;
            }
            case 5: {
                string resumeId;
                cout << "Enter Resume ID to search: ";
                cin >> resumeId;
                ResumeNode* res = resumes.searchById(resumeId);
                if (res) {
                    cout << "\n*** RESUME FOUND ***" << endl;
                    cout << "Resume ID: " << res->id << endl;
                    cout << "\nFull Text:\n" << res->description << endl;
                    cout << "Best Matched Job ID: " << res->bestJobId << endl;
                    cout << "Best Matched Job Description: " << res->bestJobDesc << endl;
                } else {
                    cout << "\n*** RESUME NOT FOUND ***" << endl;
                }
                break;
            }
            case 6:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
    } while (choice != 6);
    
    return 0;
}