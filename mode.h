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
double calcDistanceRootless(const Point& p1, const Point& p2, bool isA) {
    if ((isA) && ((p1.location == LocationType::MEDICAL_CAMPUS && p2.location == LocationType::MAIN_CAMPUS)
        || (p1.location == LocationType::MAIN_CAMPUS && p2.location == LocationType:: MEDICAL_CAMPUS))) {
            return numeric_limits<double>::infinity(); 
    }
    // Calculate Euclidean distance between two points
    double first = static_cast<double>(p2.x) - static_cast<double>(p1.x);
    double second = static_cast<double>(p2.y) - static_cast<double>(p1.y);
    return (first * first) + (second * second);
};

double calcDistanceExact(const Point& p1, const Point& p2) {
    // if ((type == 'A') && ((p1.location == LocationType::MEDICAL_CAMPUS && p2.location == LocationType::MAIN_CAMPUS)
    //     || (p1.location == LocationType::MAIN_CAMPUS && p2.location == LocationType:: MEDICAL_CAMPUS))) {
    //         return numeric_limits<double>::infinity(); 
    // }
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
    // constructor
    A(vector<Point> e) : entries(e) {}
    // Prim's algorithm
    void solvePrim() {
        size_t n = entries.size();
        prim.resize(n);
        prim[0].D = 0;
        // double weight running total
        for (size_t i = 0; i < n; i++) {
            // find the smallest distance in the table
            double smallest = numeric_limits<double>::infinity();
            size_t smallestIndex = 0;
            for (size_t j = 0; j < n; j++) {
                if (!prim[j].K && prim[j].D < smallest) {
                    smallest = prim[j].D;
                    smallestIndex = j;
                }
            }
            // mark that specific vertex in the MST as true
            prim[smallestIndex].K = true;
            runningTotal += sqrt(smallest);
            // update the distances
            for (size_t h = 0; h < n; h++) {
                double distance = calcDistanceRootless(entries[smallestIndex], entries[h], true);
                if (!prim[h].K && (distance < prim[h].D)) {
                    prim[h].D = distance;
                    prim[h].P = smallestIndex;
                }
            }
        }
    }
    void printOutput() {
        solvePrim();
        // print runningTotal - 2 decimal precision dealt with in main
        cout << runningTotal << endl;
        // print each node
        for (size_t i = 1; i < entries.size(); i++) {
            cout << min(i, prim[i].P)  << " " << max(i , prim[i].P) << "\n";
        }
    }
    double mstEstimater(size_t permLength, vector<size_t> path) {
        size_t n = path.size() - permLength;
        prim.resize(n);
        prim[0].D = 0;
        // double weight running total
        for (size_t i = 0; i < n; i++) {
            // find the smallest distance in the table
            double smallest = numeric_limits<double>::infinity();
            size_t smallestIndex = 0;
            for (size_t j = 0; j < n; j++) {
                if (!prim[j].K && prim[j].D < smallest) {
                    smallest = prim[j].D;
                    smallestIndex = j;
                }
            }
            // mark that specific vertex in the MST as true
            prim[smallestIndex].K = true;
            runningTotal += sqrt(smallest);
            // update the distances
            for (size_t h = 0; h < n; h++) {
                double distance = calcDistanceRootless(entries[path[smallestIndex + permLength]], entries[path[h + permLength]], true);
                if (!prim[h].K && (distance < prim[h].D)) {
                    prim[h].D = distance;
                    prim[h].P = smallestIndex;
                }
            }
        }
        return runningTotal;
    }
};

// arbitrary insertion
class B {
private:
    vector<Point> entries;
    vector<size_t> route;
    double totalLength;

public:
    // Nearest Neighbor Algorithm to solve the TSP
    B(vector<Point> e) : entries(e) {}

    size_t findInsertionIndex(const Point& newPoint, const vector<size_t>& currentRoute) {
        size_t bestIndex = 0;
        double minDistance = numeric_limits<double>::infinity();

        for (size_t i = 0; i < currentRoute.size() - 1; ++i) {
            double distance = calcDistanceRootless(entries[currentRoute[i]], newPoint, false) +
                              calcDistanceRootless(newPoint, entries[currentRoute[i + 1]], false) -
                              calcDistanceRootless(entries[currentRoute[i]], entries[currentRoute[i + 1]], false);
            if (distance < minDistance) {
                minDistance = distance;
                bestIndex = i + 1; // Insert after current index
            }
        }

        return bestIndex;
    }
    // Function to solve TSP using arbitrary insertion
    void solveArbitraryInsertion() {
        route.clear();
        totalLength = 0.0;

        // Start with the first point
        route.push_back(0);

        // Iterate over remaining points and insert them into route
        for (size_t i = 1; i < entries.size(); ++i) {
            size_t insertionIndex = findInsertionIndex(entries[i], route);
            route.insert(route.begin() + static_cast<ptrdiff_t>(insertionIndex), i);
        }

        // Ensure that the resulting route starts with zero
        if (route[0] != 0) {
            // Find the index of zero in the route
            auto zeroIter = find(route.begin(), route.end(), 0);
            // Rotate the route so that zero becomes the first element
            rotate(route.begin(), zeroIter, route.end());
        }

        // Calculate total length of the route
        for (size_t i = 0; i < route.size() - 1; ++i) {
            totalLength += calcDistanceExact(entries[route[i]], entries[route[i + 1]]);
        }
        // Add distance from last vertex back to the starting vertex
        totalLength += calcDistanceExact(entries[route.back()], entries[route[0]]);
    }

    void printOutput() {
        // call arbitrary insertion function here
        solveArbitraryInsertion();
        // print total length
        cout << totalLength << endl;

        // print the route
        for (size_t i = 0; i < route.size(); i++) {
            cout << route[i] << " ";
        }

    }
};

// most optimal solution
class C {
private:
    vector<Point> entries;
    vector<size_t> path;
    vector<size_t> bestPath;
    double curLength = 0;
    // starts out equal to infinity
    double minDistance = numeric_limits<double>::infinity();
public:
    // constructor
    C(vector<Point> e) : entries(e) {}

    // permLength tells you how much of the path is fixed
    void genPerms(size_t permLength) { // permLength = "locked-in vertices"
        // base case
        if (permLength == path.size()) {
            // Do something with the path
            double tempDistance = calcDistanceExact(entries[path[path.size() - 1]], entries[path[0]]);
            // add closing edge
            curLength += tempDistance;
            // check and update the best so far
            if (curLength < minDistance) {
                minDistance = curLength;
                bestPath = path;
            }
            // subtract that closing edge
            curLength -= tempDistance;
            return;
        }  // if ..complete path

        if (!promising(permLength)) {
            return;
        }  // if ..not promising

        // goes through every other permutation
        for (size_t i = permLength; i < path.size(); ++i) {
            swap(path[permLength], path[i]);
            double tempDistance = calcDistanceExact(entries[path[permLength-1]], entries[path[permLength]]);
            curLength += tempDistance;

            // never start a path at any vertex other than zero
            genPerms(permLength + 1);
            curLength -= tempDistance;
            swap(path[permLength], path[i]);

        }  // for ..unpermuted elements
    }  // genPerms()

      // Function to check if adding more vertices to the current path can lead to an optimal solution
      // estimates if the path has the potential to be better than the 
    bool promising(size_t permLength) {
        A pathRest(entries);
        // prims
        double remainder = pathRest.mstEstimater(permLength, path);
        // Check if the partial tour distance plus the lower bound estimate is less than the current best distance
        return (curLength + remainder) < minDistance;
    }

     void printOutput() {
        path.resize(entries.size());
        for (size_t i = 0; i < entries.size(); i++) {
            path[i] = i;
        }
        genPerms(1);
        // print total length
        cout << minDistance << endl;

        // print the route
        for (size_t i = 0; i < bestPath.size(); i++) {
            cout << bestPath[i] << " ";
        }

    }

};