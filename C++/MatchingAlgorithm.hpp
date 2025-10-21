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

// Skill lookup structure for O(1) checks
struct SkillSet {
    static const int MAX_SKILLS = 40;
    const char* skills[MAX_SKILLS];
    int count;
    
    SkillSet(const char* arr[], int n) : count(n) {
        for (int i = 0; i < n; i++) {
            skills[i] = arr[i];
        }
    }
};

class KeywordAlgorithm {
private:
    static const int NUM_SKILLS = 35;
    const char* skillsList[NUM_SKILLS] = {
        "python", "java", "javascript", "c++", "sql", "excel", "power bi", 
        "tableau", "pandas", "machine learning", "deep learning", "nlp", 
        "statistics", "data cleaning", "reporting", "tensorflow", "keras", 
        "mlops", "computer vision", "spring boot", "rest apis", "docker", 
        "git", "system design", "agile", "data analyst", "data scientist", 
        "software engineer", "ml engineer", "developer", "engineer",
        "experience", "professional", "skilled"
    };

    void calculateJobStats(JobLinkedList& jobs, const ResumeLinkedList& resumes) {
        for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
            job->totalMatches = 0;
            job->totalScore = 0.0;
        }

        for (ResumeNode* res = resumes.getHead(); res != nullptr; res = res->next) {
            if (!res->bestJobId.empty()) {
                for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
                    if (job->id == res->bestJobId) {
                        job->totalMatches++;
                        job->totalScore += res->bestMatchScore;
                        break;
                    }
                }
            }
        }

        for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
            job->averageScore = (job->totalMatches > 0) ? 
                (job->totalScore / job->totalMatches) : 0.0;
        }
    }

    // Optimized string search using simple character comparison
    bool findSubstring(const char* text, int textLen, const char* pattern, int patternLen) const {
        if (patternLen > textLen) return false;
        
        for (int i = 0; i <= textLen - patternLen; i++) {
            bool match = true;
            for (int j = 0; j < patternLen; j++) {
                char c1 = text[i + j];
                char c2 = pattern[j];
                // Case-insensitive comparison
                if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
                if (c1 != c2) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }

public:
    int KeywordMatching(const string& resumeDesc, const string& jobsDesc) {
        const char* resume = resumeDesc.c_str();
        const char* job = jobsDesc.c_str();
        int resumeLen = resumeDesc.length();
        int jobLen = jobsDesc.length();

        int score = 0;
        for (int i = 0; i < NUM_SKILLS; i++) {
            int skillLen = strlen(skillsList[i]);
            if (findSubstring(resume, resumeLen, skillsList[i], skillLen) &&
                findSubstring(job, jobLen, skillsList[i], skillLen)) {
                score++;
            }
        }

        return score;
    }

    void performMatching(ResumeLinkedList& resumes, JobLinkedList& jobs) {
        clock_t start = clock();

        for (ResumeNode* resume = resumes.getHead(); resume != nullptr; resume = resume->next) {
            int maxScore = 0;
            JobNode* bestJob = nullptr;

            for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
                int score = KeywordMatching(resume->skillsOnly, job->skillsOnly);

                if (score > maxScore) {
                    maxScore = score;
                    bestJob = job;
                }
            }

            if (bestJob != nullptr) {
                resume->bestJobId = bestJob->id;
                resume->bestJobDesc = bestJob->description;
                resume->bestMatchScore = maxScore;
            }
        }
        
        calculateJobStats(jobs, resumes);

        clock_t end = clock();
        double timeTaken = double(end - start) / CLOCKS_PER_SEC;
        cout << "Matching completed in " << timeTaken << " seconds.\n";
    }
};

class WeightedAlgorithm {
private:
    static const int NUM_CRITICAL = 6;
    static const int NUM_CORE = 10;
    static const int NUM_SOFT = 7;

    const char* criticalSkills[NUM_CRITICAL] = {
        "machine learning", "deep learning", "computer vision", 
        "mlops", "tensorflow", "keras"
    };
    
    const char* coreSkills[NUM_CORE] = {
        "python", "java", "sql", "nlp", "spring boot",
        "docker", "system design", "rest apis", "javascript", "c++"
    };
    
    const char* softSkills[NUM_SOFT] = {
        "pandas", "excel", "power bi", "tableau", 
        "git", "agile", "statistics"
    };

    void calculateJobStats(JobLinkedList& jobs, const ResumeLinkedList& resumes) {
        for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
            job->totalMatches = 0;
            job->totalScore = 0.0;
        }

        for (ResumeNode* res = resumes.getHead(); res != nullptr; res = res->next) {
            if (!res->bestJobId.empty()) {
                for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
                    if (job->id == res->bestJobId) {
                        job->totalMatches++;
                        job->totalScore += res->bestMatchScore;
                        break;
                    }
                }
            }
        }

        for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
            job->averageScore = (job->totalMatches > 0) ? 
                (job->totalScore / job->totalMatches) : 0.0;
        }
    }

    bool findSubstring(const char* text, int textLen, const char* pattern, int patternLen) const {
        if (patternLen > textLen) return false;
        
        for (int i = 0; i <= textLen - patternLen; i++) {
            bool match = true;
            for (int j = 0; j < patternLen; j++) {
                char c1 = text[i + j];
                char c2 = pattern[j];
                if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
                if (c1 != c2) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }

public:
    int WeightedMatching(const string& resumedsc, const string& jobsdsc) {
        const char* resume = resumedsc.c_str();
        const char* job = jobsdsc.c_str();
        int resumeLen = resumedsc.length();
        int jobLen = jobsdsc.length();

        int critical = 0, core = 0, soft = 0;

        for (int i = 0; i < NUM_CRITICAL; i++) {
            int len = strlen(criticalSkills[i]);
            if (findSubstring(resume, resumeLen, criticalSkills[i], len) &&
                findSubstring(job, jobLen, criticalSkills[i], len)) {
                critical++;
            }
        }

        for (int i = 0; i < NUM_CORE; i++) {
            int len = strlen(coreSkills[i]);
            if (findSubstring(resume, resumeLen, coreSkills[i], len) &&
                findSubstring(job, jobLen, coreSkills[i], len)) {
                core++;
            }
        }

        for (int i = 0; i < NUM_SOFT; i++) {
            int len = strlen(softSkills[i]);
            if (findSubstring(resume, resumeLen, softSkills[i], len) &&
                findSubstring(job, jobLen, softSkills[i], len)) {
                soft++;
            }
        }

        return (critical * 3) + (core * 2) + soft;
    }

    void performWeightedMatching(ResumeLinkedList& resumes, JobLinkedList& jobs) {
        clock_t start = clock();

        for (ResumeNode* resume = resumes.getHead(); resume != nullptr; resume = resume->next) {
            int maxScore = 0;
            JobNode* bestJob = nullptr;

            for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
                int score = WeightedMatching(resume->skillsOnly, job->skillsOnly);

                if (score > maxScore) {
                    maxScore = score;
                    bestJob = job;
                }
            }

            if (bestJob != nullptr) {
                resume->bestJobId = bestJob->id;
                resume->bestJobDesc = bestJob->description;
                resume->bestMatchScore = maxScore;
            }
        }
        
        calculateJobStats(jobs, resumes);

        clock_t end = clock();
        double timeTaken = double(end - start) / CLOCKS_PER_SEC;
        cout << "Weighted Matching completed in " << timeTaken << " seconds.\n";
    }
};

#endif