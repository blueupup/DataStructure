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
    cout << "    Linked List Implementation" << endl;
    cout << "============================================\n" << endl;
    
    JobLinkedList jobs;
    ResumeLinkedList resumes;
    
    // Load data
    if (!loadJobsFromCSV("job_description.csv", jobs)) {
        cout << "\nPress Enter to exit...";
        cin.get();
        return 1;
    }
    
    if (!loadResumesFromCSV("resume.csv", resumes)) {
        cout << "\nPress Enter to exit...";
        cin.get();
        return 1;
    }
    
    cout << "\nTotal Jobs: " << jobs.getSize() << endl;
    cout << "Total Resumes: " << resumes.getSize() << endl;
    
    // Menu
    // int choice;
    // do {
    //     cout << "\n\n========== MENU ==========\n";
    //     cout << "1. Display All Jobs\n";
    //     cout << "2. Display All Resumes\n";
    //     cout << "3. Perform Job Matching\n";
    //     cout << "0. Exit\n";
    //     cout << "==========================\n";
    //     cout << "Enter choice: ";
    //     cin >> choice;
    //     cin.ignore();
        
    //     switch(choice) {
    //         case 1:
    //             cout << "\n--- All Jobs ---\n";
    //             jobs.displayJobs();
    //             break;
                
    //         case 2:
    //             cout << "\n--- All Resumes ---\n";
    //             resumes.displayResumes();
    //             break;
                
    //         case 3:
    //             performJobMatching(jobs, resumes);
    //             break;
                
    //         case 0:
    //             cout << "\nExiting program. Goodbye!\n";
    //             break;
                
    //         default:
    //             cout << "\nInvalid choice. Please try again.\n";
    //     }
        
    // } while (choice != 0);
    
    // return 0;
}