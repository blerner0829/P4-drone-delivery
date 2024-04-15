// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

enum LocationType {
    MAIN_CAMPUS,
    MEDICAL_CAMPUS,
    BORDER
};

struct Point {
    int x, y;
    LocationType location;
};

struct Prim {
    bool K = false;
    double D = numeric_limits<double>::infinity();
    size_t P; 
};

void setLocation(Point& p) {
    if (p.x < 0 && p.y < 0) p.location = LocationType::MEDICAL_CAMPUS;
    else if ((p.y == 0 && p.x <= 0) || (p.x == 0 && p.y <= 0)) p.location = LocationType::BORDER;
    else p.location = LocationType::MAIN_CAMPUS;

}
double calcDistanceRootless(const Point& p1, const Point& p2) {
    if ((p1.location == LocationType::MEDICAL_CAMPUS && p2.location == LocationType::MAIN_CAMPUS)
        || (p1.location == LocationType::MAIN_CAMPUS && p2.location == LocationType:: MEDICAL_CAMPUS)) {
            return numeric_limits<double>::infinity(); 
    }
    // Calculate Euclidean distance between two points
    double first = static_cast<double>(p2.x) - static_cast<double>(p1.x);
    double second = static_cast<double>(p2.y) - static_cast<double>(p1.y);
    return (first * first) + (second * second);
};

double calcDistanceExact(const Point& p1, const Point& p2) {
    if ((p1.location == LocationType::MEDICAL_CAMPUS && p2.location == LocationType::MAIN_CAMPUS)
        || (p1.location == LocationType::MAIN_CAMPUS && p2.location == LocationType:: MEDICAL_CAMPUS)) {
            return numeric_limits<double>::infinity(); 
    }
    // Calculate Euclidean distance between two points
    double first = static_cast<double>(p2.x) - static_cast<double>(p1.x);
    double second = static_cast<double>(p2.y) - static_cast<double>(p1.y);
    return sqrt((first * first) + (second * second));
};

class A {
private:
    double runningTotal = 0;
    vector<Prim> prim;
    vector<Point> entries;
public:   
    void solveMST() {
    // Prim's algorithm
        prim.resize(entries.size());
        prim[0].D = 0;
        // double weight running total
        for (size_t i = 0; i < entries.size(); i++) {
            // find the smallest distance in the table
            double smallest = numeric_limits<double>::infinity();
            size_t smallestIndex = 0;
            for (size_t j = 0; j < entries.size(); j++) {
                if (!prim[j].K && prim[j].D < smallest) {
                    smallest = prim[j].D;
                    smallestIndex = j;
                }
            }
            // mark that specific vertex in the MST as true
            prim[smallestIndex].K = true;
            runningTotal += sqrt(smallest);
            // update the distances
            for (size_t h = 0; h < entries.size(); h++) {
                double distance = calcDistanceRootless(entries[smallestIndex], entries[h]);
                if (!prim[h].K && (distance < prim[h].D)) {
                    prim[h].D = distance;
                    prim[h].P = smallestIndex;
                }
            }
        }
    }
    void printOutput() {
        solveMST();
        // print runningTotal - 2 decimal precision dealt with in main
        cout << runningTotal << endl;
        // print each node
        for (size_t i = 1; i < entries.size(); i++) {
            cout << min(i, prim[i].P)  << " " << max(i , prim[i].P) << "\n";
        }
    }
    A(vector<Point> e)
        : entries(e)
    {}
};