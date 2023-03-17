
#pragma once 

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

class dbg {
    public:
        std::ofstream file;
        double curtime;
        clock_t start_t, end_t;

        void out(std::string x);
        dbg(std::string y = "home/lvuser/debug.txt");
        bool end();
        int iterations;
        ~dbg();
};
