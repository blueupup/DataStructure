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
        cout << "4. Exit\n";
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
                jobs.displayTop10ByScore();
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
    } while (choice != 4);
    
    return 0;
}