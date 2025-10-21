#ifndef MATCHING_ALGORITHM_HPP
#define MATCHING_ALGORITHM_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <algorithm>
#include "LinkedListNodes.hpp"
using namespace std;

class KeywordAlgorithm{
public:
    string toLowerString(const string& str) {
        string lower = str;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }


    int KeywordMatching(const string&resumeDesc, const string&jobsDesc){

        string resumeLower = toLowerString(resumeDesc);
        string jobsLower = toLowerString(jobsDesc);


        string skills[] = {"python", "java", "javascript", "c++","sql", "excel", "power bi", "tableau", "pandas","machine learning", "deep learning", "nlp", "statistics", "data cleaning", "reporting","tensorflow", "keras", "mlops", "computer vision","spring boot", "rest apis", "docker", "git","system design", "agile","data analyst", "data scientist", "software engineer","ml engineer", "developer", "engineer","experience", "professional", "skilled"};

        int score = 0;
        for (const string& skill : skills) {
            if (resumeLower.find(skill) != string::npos &&
                jobsLower.find(skill) != string::npos) {
                score++;
            }
        }

        return score;

    }

    void performMatching(const ResumeLinkedList& resumes, const JobLinkedList& jobs){
        clock_t start = clock();

        ResumeNode* Resumecurrent = resumes.getHead();

        while(Resumecurrent != nullptr){
            int maxScore = 0;
            string bestJobDesc1 = "";
            string bestJobId1 = "";

            string resumeDesc = Resumecurrent ->description;
            JobNode* currentJob = jobs.getHead();

            while(currentJob != nullptr){
                string jobDesc = currentJob ->description;

                int score = KeywordMatching(resumeDesc, jobDesc);

                if(score >maxScore){
                    maxScore = score;
                    bestJobDesc1 = currentJob ->description;
                    bestJobId1 = currentJob -> id;
                }

                currentJob = currentJob ->next;
            }

            Resumecurrent->bestJobDesc = bestJobDesc1;
            Resumecurrent->bestJobId = bestJobId1;
            Resumecurrent -> bestMatchScore = maxScore;

            Resumecurrent = Resumecurrent->next;
        }

        clock_t end = clock();
        double timeTaken = double(end - start) / CLOCKS_PER_SEC;
        cout << "Matching completed in " << timeTaken << " seconds.\n";
    }

};

class WeightedAlgorithm {
public:

    string toLowerString(const string& str) {
        string lower = str;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

    
    int WeightedMatching(const string&resumedsc, const string&jobsdsc){
        //In-Demand ML skills
        string CriticalSkills[] = {"machine learning", "deep learning", "computer vision", "mlops","tensorflow", "keras"};
        //Basic Skills
        string CoreSkills [] = {"python","java","sql","nlp","spring boot","docker","system design","rest apis","javascript","c++"}; 
        //Soft Skills
        string SoftSkills[] = {"pandas","excel","power bi","tableau","git","agile","statistics"};

        int score = 0;
        int critical = 0;
        int core = 0;
        int soft = 0;

        string resumeLower = toLowerString(resumedsc);
        string jobsLower = toLowerString(jobsdsc);
        for (const string& skill : CriticalSkills) {
            if (resumeLower.find(skill) != string::npos &&
                jobsLower.find(skill) != string::npos) {
                critical++;
            }
        }

        for (const string& skill : CoreSkills) {
            if (resumeLower.find(skill) != string::npos &&
                jobsLower.find(skill) != string::npos) {
                core++;
            }
        }

        for (const string& skill : SoftSkills) {
            if (resumeLower.find(skill) != string::npos &&
                jobsLower.find(skill) != string::npos) {
                soft++;
            }
        }

        score = (critical * 3) + (core * 2) + (soft * 1);
        return score;
    }

    void performWeightedMatching(const ResumeLinkedList& resumes, const JobLinkedList& jobs){
        clock_t start = clock();

        ResumeNode* Resumecurrent = resumes.getHead();

        while(Resumecurrent != nullptr){
            int maxScore = 0;
            string bestJobDesc1 = "";
            string bestJobId1 = "";

            string resumeDesc = Resumecurrent ->description;
            JobNode* currentJob = jobs.getHead();

            while(currentJob != nullptr){
                string jobDesc = currentJob ->description;

                int score = WeightedMatching(resumeDesc, jobDesc);

                if(score >maxScore){
                    maxScore = score;
                    bestJobDesc1 = currentJob ->description;
                    bestJobId1 = currentJob -> id;
                }

                currentJob = currentJob ->next;
            }

            Resumecurrent->bestJobDesc = bestJobDesc1;
            Resumecurrent->bestJobId = bestJobId1;
            Resumecurrent -> bestMatchScore = maxScore;

            Resumecurrent = Resumecurrent->next;
        }

        clock_t end = clock();
        double timeTaken = double(end - start) / CLOCKS_PER_SEC;
        cout << "Weighted Matching completed in " << timeTaken << " seconds.\n";
    }


    
};

#endif