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
#include "mode.h"
using namespace std;

enum Mode {
    NONE,
    MST,
    FASTTSP,
    OPTTSP,
};
struct Options {
    Mode m = Mode::NONE;
};

vector<Point> readInput(Options& opt) {
    size_t numVertices = 0;
    cin >> numVertices;

    vector<Point> points(numVertices);
    for (size_t i = 0; i < numVertices; ++i) {
        cin >> points[i].x >> points[i].y;
        if (opt.m == MST) setLocation(points[i]);
    }

    return points;
};

void printHelp(char *argv[]) {
    cout << "Usage: " << argv[0] << " [-m MST|FASTTSP|OPTTSP] | -h\n";
    cout << "< inputFile\n";
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
                    opt.m = Mode::MST;
                else if (modeStr == "FASTTSP")
                    opt.m = Mode::FASTTSP;
                else if (modeStr == "OPTTSP")
                    opt.m = Mode::OPTTSP;
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
    if (opt.m == Mode::NONE) {
        cerr << "Error: No mode specified" << endl;
        exit(1);
    }
} // getMode()

// This function is already done.
int main(int argc, char *argv[])
{
    cout << setprecision(2); // Always show 2 decimal places
    cout << fixed; // Disable scientific notation for large numbers

    Options opt;
    getMode(argc, argv, opt);
    switch (opt.m)
    {
    case Mode::MST:
        {
        A m(readInput(opt));
        m.printOutput();
        break;
        }
    case Mode::FASTTSP:
        {
        // cout << "C RAN\n"; // for testing
        B m(readInput(opt));
        m.printOutput(); 
        break;
        }
    case Mode::OPTTSP:
        {
        C m(readInput(opt));
        m.printOutput(); 
        break;
        }
    default:
        break;
    }
    return 0;

} // main()
