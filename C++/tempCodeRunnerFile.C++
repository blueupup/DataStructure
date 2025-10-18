#include <iostream>
#include <string>
using namespace std;


void cleanup(string str){
    string result;

    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == ',') {
            result += ' ';
        } else if (str[i] == '.') {
            result += '.';
            // Skip any spaces after the period
            while (i + 1 < str.length() && str[i + 1] == ' ') {
                ++i;
            }
        } else {
            result += str[i];
        }
    }


    str = result;


};

int main(){
    string str = "Experienced professional skilled in SQL, Power BI, well, try, Excel, Tableau.";
    cleanup(str);
    cout << "'" << str << "'" << endl;
    return 0;
}