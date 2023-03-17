#include "Debug.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


dbg::dbg(std::string y) {
    file.open(y, std::ios_base::app);
    iterations = 0;
    if(!file.is_open()) {
        std::cout << "ERROR DEBUG FILE FAILED TO OPEN";
    }
    start_t = clock();
}
void dbg::out(string x) {
    end_t = clock();
    curtime = (double)(end_t-start_t) / CLOCKS_PER_SEC;
    iterations++;
    file << "[" << curtime << "]" << x << endl;
    cout << x << endl;
}
bool dbg::end() {
    file << "[ROBOT SHUT OFF]";
    file.close();
    if(!file.is_open()) {
        return true;
    } else {
        return false;
    }
}
 dbg::~dbg() {
    this->end();
}