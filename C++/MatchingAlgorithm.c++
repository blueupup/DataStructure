#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include "LinkedListNodes.C++"
using namespace std;

class MatchingAlgorithm {
public:

    void tolower(char *str){
        for (int i = 0; str[i]; i ++){
            if (str[i] >= 'A' && str[i] <= 'Z'){
                str[i] = str[i] + 32;
            }
        }
    };

    



    
};