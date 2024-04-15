// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
#include <getopt.h>
#include <string>
#include <limits>
#include <algorithm>
#include <deque>
#include <queue>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "mode.h"
using namespace std;

enum mode {
    NONE,
    MST,
    FASTTSP,
    OPTTSP,
};
struct Options {
    mode m = mode::NONE;
};

vector<Point> readInput() {
    size_t numVertices = 0;
    cin >> numVertices;

    vector<Point> points(numVertices);
    for (size_t i = 0; i < numVertices; ++i) {
        cin >> points[i].x >> points[i].y;
        setLocation(points[i]);
    }

    return points;
};

void printHelp(char *argv[]) {
    cout << "Usage: " << argv[0] << " [-m resize|reserve|nosize] | -h\n";
    cout << "This program is to help you learn command-line processing,\n";
    cout << "reading data into a vector, the difference between resize and\n";
    cout << "reserve and how to properly read until end-of-file." << endl;
} // printHelp()

void getMode(int argc, char *argv[], Options &opt)
{
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        {"help", no_argument, nullptr, 'h'},
        {"mode", required_argument, nullptr, 'm'},
        
    }; // long_options[]

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "hm:", long_options, &index)) != -1)
    {
        switch (choice)
        {
        case 'h':
            printHelp(argv);
            exit(0);
        case 'm':
            // Handle mode option
            if (optarg) {
                std::string modeStr(optarg);
                if (modeStr == "MST")
                    opt.m = mode::MST;
                else if (modeStr == "FASTTSP")
                    opt.m = mode::FASTTSP;
                else if (modeStr == "OPTTSP")
                    opt.m = mode::OPTTSP;
                else {
                    cerr << "Error: Invalid mode" << endl;
                    cout << "MODE: " << modeStr << endl;
                    exit(1);
                }
            } else {
                cerr << "Mode option requires an argument." << endl;
                exit(1);
            }
            break;

        default:
            // Handle invalid options
            // e.g., handleInvalidOption();
            cerr << "Error: Invalid command line option" << endl;
            exit(1);
        }
    }
    // Check if mode option is provided
    if (opt.m == mode::NONE) {
        cerr << "Error: No mode specified" << endl;
        exit(1);
    }
} // getMode()

// This function is already done.
int main(int argc, char *argv[])
{
    Options opt;
    getMode(argc, argv, opt);
    A m;
    m.entries = readInput();
    m.printOutput();
    return 0;

} // main()
