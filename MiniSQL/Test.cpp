#include "Interpreter.h"
#include <iostream>
#include <regex>
#include <string>
#include <iomanip>

using namespace std;


int main() {

    Interpreter interpreter;
    
    cout << "*************************************************" << endl;
    cout << "*                                               *" << endl;
    cout << "*         Welcome to miniSQL System!            *" << endl;
    cout << "* Authors: SONG, Chen XU, Zhikui CHEN, Chienyu  *" << endl;
    cout << "* Verison: 1.0 (Last modified on June 20, 2016) *" << endl;
    cout << "*                                               *" << endl;
    cout << "*************************************************" << endl << endl;
    while (true) {
        try {
            string statement;
            char temp;
            cout << "miniSQL> ";
            cin.clear();
            do {
                temp = cin.get();
                statement.push_back(temp);
                if ('\n' == temp || '\r' == temp) {
                    cout << "      -> ";
                }
            } while (';' != temp);
            if (interpreter.executeStatement(statement)) {
                interpreter.printResults();
            } else {
                cout << "Query has been executed successfully!" << endl << endl;
            }
        } catch (MyException ex) {
            cout << ex.getMessage() << endl;
        }
        
        while (cin.rdbuf()->in_avail() > 0) {
            char temp = cin.peek();
            if (regex_match(string(&temp, 1), regex("\\s"))) {
                cin.seekg(1, ios::cur); /* move the cursor forward */
            } else {
                break;
            }
        }
    }


    return 0;
}