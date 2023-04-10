#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <sstream>

using namespace std;

class hm {
    private:
    int startingPoint;
    public:
    hm() {
        startingPoint = 0;
    }
    void hakariRoll(int numNodes) {
        startingPoint = (rand() % numNodes);
    }
    int getStart() {
        return startingPoint;
    }
    int findRoute(int** nodes, int numNodes) {
        vector<int> completePath;
        int pathCost;
        int counter = 0;
        unordered_map<int, bool> possibleRoutes;
        for (int i = 0; i < numNodes; i++) {
            possibleRoutes[i] = true;
        }
        while (possibleRoutes.size() != 0) {
            pathCost = 0;
            this -> hakariRoll(numNodes);
            size_t result = possibleRoutes.erase(startingPoint);
            if (result == 0) {
                // cout << startingPoint << endl;
                continue;
            }
            completePath.push_back(startingPoint + 1);
            int cur_node = startingPoint;
            // cout << "cur_node = " << cur_node << endl;
            while (completePath.size() <= numNodes) {  
                // if (counter % 1000000 == 0) {
                //     cout << counter << " counters completed" << endl;
                // }
                // counter += 1;
                int minValue = INT_MAX;
                int minIndex;
                bool noPath = false;
                for (int i = 0; i < numNodes; i++) {
                    if (nodes[cur_node][i] != 0) {
                        int oldMin = minValue;
                        // cout << node[cur_node] << endl;
                        minValue = min(minValue, nodes[cur_node][i]);
                        // cout << minValue << endl;
                        if (find(completePath.begin(), completePath.end(), (i + 1)) != completePath.end()) {
                            minValue = oldMin;
                            continue;
                        }
                        else if (oldMin != minValue) {
                            minIndex = i;
                            noPath = true;
                            // cout << "minIndex = " << minIndex << endl;
                            continue;
                        }
                    }
                    // cout << nodes[cur_node][i] << endl;
                }
                if (!noPath) {
                    // cout << "here" << endl;
                    break;
                }
                if (completePath.size() < numNodes) {
                    completePath.push_back(minIndex + 1);
                    pathCost += nodes[cur_node][minIndex];
                    // cout << "min value = "<< nodes[cur_node][minIndex] << endl;
                    cur_node = minIndex;
                    // cout << "node after change = " << cur_node << endl;
                    
                    
                }
                if (completePath.size() == numNodes && nodes[cur_node][startingPoint] != 0) {
                    pathCost += nodes[cur_node][startingPoint];
                    // cout << "pathCost = "<< pathCost << endl;
                    break;
                }
                else if (completePath.size() == numNodes && nodes[cur_node][startingPoint] == 0){
                    break;
                }
            }
            if (completePath.size() != numNodes) {
                // cout << "completePath size = " << completePath.size() << endl;
                completePath.clear();
            }
            else if (completePath.size() == numNodes) {
                // cout << "we are equal" << endl;
                break;
            }
        }
        if (completePath.size() == numNodes) {
            cout << "Path Taken: ";
            for (auto i: completePath) {
                cout << i << ' ';
            }
            cout << endl;
        }
        else {
            pathCost = 0;
        }
        if (pathCost == 0) {
            cout << "No Path Found" << endl;
        }
        return pathCost;
    }
};

int** readFile(string fileName, int &numNodes);

int main(int argc, char* argv[]) {
    srand(time(0));
    string filename = argv[1];
    int numNodes = 6;
    // int nodes[6][6] = {
    //                 {0, 2, 9, 10, 7, 8},
    //                 {2, 0, 4, 3, 1, 6},
    //                 {9, 4, 0, 8, 6, 3},
    //                 {10, 3, 8, 0, 5, 4},
    //                 {7, 1, 6, 5, 0, 2},
    //                 {8, 6, 3, 4, 2, 0}
    //                 };
    int** nodes = readFile(filename, numNodes);
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            cout << nodes[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    hm heuristic;
    int cost = heuristic.findRoute(nodes, numNodes);
    cout << "Path cost: " << cost << endl;
    return 0;
}
int** readFile(string fileName, int &numNodes) {
    ifstream myStream;
    string paper = "$";
    int** nodeList;
    myStream.open(fileName);
    if (myStream.is_open()) {
        string input;
        getline(myStream, input);
        numNodes = stoi(input);
        nodeList = new int*[numNodes];
        for (int i = 0; i < numNodes; i++) {
            int* newSection = new int[numNodes];
            for (int j = 0; j < numNodes; j++) {
                newSection[j] = 0;
            }
            nodeList[i] = newSection;
        }
        while (getline(myStream,input)) {
            stringstream tokenizer(input);
            string token;
            if (input.find(paper) != string::npos) {
                break;
            }
            int from;
            int to;
            int i = 0;
            while (getline(tokenizer, token, ' ')) {
                // cout << token << endl;
                if (i == 0) {
                    from = stoi(token) - 1;
                }
                else if (i == 1) {
                    to = stoi(token) - 1;
                }
                else if (i == 2) {
                    nodeList[from][to] = stoi(token);
                }
                i++;
            }
        }
    }
    return nodeList;
}