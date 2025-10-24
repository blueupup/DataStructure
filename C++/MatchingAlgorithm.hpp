#ifndef MATCHING_ALGORITHM_HPP
#define MATCHING_ALGORITHM_HPP

#include <iostream>
#include <ctime>
#include <cstring> // for memset, strstr
#include <cmath>   // for pow
#include "LinkedListNodes.hpp"
using namespace std;


class KeywordAlgorithm {
private:
    static const int SKILL_COUNT = 33;
    const char* skills[SKILL_COUNT] = {
        "python", "java", "javascript", "c++", "sql", "excel", "power bi", "tableau",
        "pandas", "machine learning", "deep learning", "nlp", "statistics", "data cleaning",
        "reporting", "tensorflow", "keras", "mlops", "computer vision", "spring boot",
        "rest apis", "docker", "git", "system design", "agile", "data analyst",
        "data scientist", "software engineer", "ml engineer", "developer",
        "engineer", "experience", "professional"};

    inline void toLowerInPlace(string& s) {
        for (size_t i = 0; i < s.size(); ++i)
            s[i] = tolower(s[i]);
    }

    inline int containsWord(const string& text, const char* word) {
        return strstr(text.c_str(), word) != nullptr;
    }

    void preprocessResumeSkills(ResumeLinkedList& resumes) {
        for (ResumeNode* r = resumes.getHead(); r != nullptr; r = r->next) {
            toLowerInPlace(r->description);
            for (int i = 0; i < SKILL_COUNT; ++i)
                r->skills[i] = containsWord(r->description, skills[i]);
        }
    }

    void preprocessJobSkills(JobLinkedList& jobs) {
        for (JobNode* j = jobs.getHead(); j != nullptr; j = j->next) {
            toLowerInPlace(j->description);
            for (int i = 0; i < SKILL_COUNT; ++i)
                j->skills[i] = containsWord(j->description, skills[i]);
        }
    }

    inline int SkillVectorMatch(const int* resumeSkills, const int* jobSkills) {
        int score = 0;
        for (int i = 0; i < SKILL_COUNT; ++i)
            score += (resumeSkills[i] & jobSkills[i]);
        return score;
    }

    void calculateJobStats(JobLinkedList& jobs, const ResumeLinkedList& resumes) {
        for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
            int totalMatches = 0;
            double totalScore = 0.0;
            for (ResumeNode* res = resumes.getHead(); res != nullptr; res = res->next) {
                if (res->bestJobId == job->id) {
                    totalMatches++;
                    totalScore += res->bestMatchScore;
                }
            }
            job->totalMatches = totalMatches;
            job->totalScore = totalScore;
            job->averageScore = (totalMatches > 0) ? (totalScore / totalMatches) : 0.0;
        }
    }

public:
    void performMatching(ResumeLinkedList& resumes, JobLinkedList& jobs) {
        clock_t start = clock();

        // --- STEP 1: Preprocess text into skill vectors ---
        preprocessResumeSkills(resumes);
        preprocessJobSkills(jobs);

        // --- STEP 2: Main matching loop ---
        for (ResumeNode* resume = resumes.getHead(); resume != nullptr; resume = resume->next) {
            int maxScore = -1;
            JobNode* bestJob = nullptr;

            for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
                int score = SkillVectorMatch(resume->skills, job->skills);
                if (score > maxScore) {
                    maxScore = score;
                    bestJob = job;
                }
            }

            if (bestJob) {
                resume->bestJobDesc = bestJob->description;
                resume->bestJobId = bestJob->id;
                resume->bestMatchScore = maxScore;
            } else {
                resume->bestJobDesc = "N/A";
                resume->bestJobId = "N/A";
                resume->bestMatchScore = 0;
            }
        }

        // --- STEP 3: Calculate aggregate job stats ---
        calculateJobStats(jobs, resumes);

        double timeTaken = double(clock() - start) / CLOCKS_PER_SEC;
        cout << "Optimized Keyword Matching completed in " << timeTaken << " seconds.\n";
    }
};

class WeightedAlgorithm {
private:
    bool strictMode = true;
    double strictThreshold = 4.0;
    static const int CRITICAL_COUNT = 6;
    static const int CORE_COUNT = 10;
    static const int SOFT_COUNT = 7;

    const char* CriticalSkills[CRITICAL_COUNT] = {
        "machine learning", "deep learning", "computer vision", "mlops", "tensorflow", "keras"
    };
    const char* CoreSkills[CORE_COUNT] = {
        "python", "java", "sql", "nlp", "spring boot", "docker", "system design", "rest apis", "javascript", "c++"
    };
    const char* SoftSkills[SOFT_COUNT] = {
        "pandas", "excel", "power bi", "tableau", "git", "agile", "statistics"
    };


    inline void toLowerInPlace(string& s) {
        for (size_t i = 0; i < s.size(); ++i)
            s[i] = tolower(s[i]);
    }

    inline int containsWord(const string& text, const char* word) {
        return strstr(text.c_str(), word) != nullptr;
    }

    void preprocessResumeSkills(ResumeLinkedList& resumes) {
        for (ResumeNode* r = resumes.getHead(); r != nullptr; r = r->next) {
            toLowerInPlace(r->description);

            for (int i = 0; i < CRITICAL_COUNT; ++i)
                r->criticalSkills[i] = containsWord(r->description, CriticalSkills[i]);
            for (int i = 0; i < CORE_COUNT; ++i)
                r->coreSkills[i] = containsWord(r->description, CoreSkills[i]);
            for (int i = 0; i < SOFT_COUNT; ++i)
                r->softSkills[i] = containsWord(r->description, SoftSkills[i]);
        }
    }

    void preprocessJobSkills(JobLinkedList& jobs) {
        for (JobNode* j = jobs.getHead(); j != nullptr; j = j->next) {
            toLowerInPlace(j->description);

            for (int i = 0; i < CRITICAL_COUNT; ++i)
                j->criticalSkills[i] = containsWord(j->description, CriticalSkills[i]);
            for (int i = 0; i < CORE_COUNT; ++i)
                j->coreSkills[i] = containsWord(j->description, CoreSkills[i]);
            for (int i = 0; i < SOFT_COUNT; ++i)
                j->softSkills[i] = containsWord(j->description, SoftSkills[i]);
        }
    }

    inline double WeightedSkillMatch(const ResumeNode* r, const JobNode* j) {
        double score = 0.0;
        double jobPossible = 0.0;

        for (int i = 0; i < CRITICAL_COUNT; ++i) {
            if (j->criticalSkills[i]) {
                jobPossible += 3;
                if (r->criticalSkills[i]) score += 3;
            }
        }

        for (int i = 0; i < CORE_COUNT; ++i) {
            if (j->coreSkills[i]) {
                jobPossible += 2;
                if (r->coreSkills[i]) score += 2;
            }
        }

        for (int i = 0; i < SOFT_COUNT; ++i) {
            if (j->softSkills[i]) {
                jobPossible += 1;
                if (r->softSkills[i]) score += 1;
            }
        }

        if (jobPossible < 5.0) return 0.0;
        
        return (score / jobPossible) * 10.0;  // Simple linear scale
    }

    void calculateJobStats(JobLinkedList& jobs, const ResumeLinkedList& resumes) {
        for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
            int totalMatches = 0;
            double totalScore = 0.0;

            for (ResumeNode* res = resumes.getHead(); res != nullptr; res = res->next) {
                if (res->bestJobId == job->id) {
                    totalMatches++;
                    totalScore += res->bestMatchScore;
                }
            }

            job->totalMatches = totalMatches;
            job->totalScore = totalScore;
            job->averageScore = (totalMatches > 0) ? (totalScore / totalMatches) : 0.0;
        }
    }

public:
    void performWeightedMatching(ResumeLinkedList& resumes, JobLinkedList& jobs) {
        clock_t start = clock();

        preprocessResumeSkills(resumes);
        preprocessJobSkills(jobs);

        // STEP 2: Resume-to-job matching
        for (ResumeNode* resume = resumes.getHead(); resume != nullptr; resume = resume->next) {
            double maxScore = -1.0;
            JobNode* bestJob = nullptr;

            for (JobNode* job = jobs.getHead(); job != nullptr; job = job->next) {
                double score = WeightedSkillMatch(resume, job);
                if (score > maxScore) {
                    maxScore = score;
                    bestJob = job;
                }
            }

                if (bestJob) {
                    if (strictMode && maxScore < strictThreshold) {
                        // Below threshold — treat as no valid match
                        resume->bestJobDesc = "No suitable match";
                        resume->bestJobId = "N/A";
                        resume->bestMatchScore = 0;
                    } else {
                        // Acceptable match
                        resume->bestJobDesc = bestJob->description;
                        resume->bestJobId = bestJob->id;
                        resume->bestMatchScore = maxScore;
                    }
                } else {
                    resume->bestJobDesc = "N/A";
                    resume->bestJobId = "N/A";
                    resume->bestMatchScore = 0;
                }

        }

        // STEP 3: Aggregate job stats
        calculateJobStats(jobs, resumes);

        double timeTaken = double(clock() - start) / CLOCKS_PER_SEC;
        cout << "Balanced Weighted Matching completed in " << timeTaken << " seconds.\n";
    }
};

#endif
