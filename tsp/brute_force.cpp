#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class bfm { //Brute Force method
    private:
    int startingPoint;
    public:
    bfm() {
        startingPoint = 0;
    }
    bfm(int choosenStartPosition) {
        startingPoint = choosenStartPosition;
    }
    void setStart(int newStartPosition) {
        startingPoint = newStartPosition;
    }
    int getStart() {
        return startingPoint;
    }
    int shortestPath(int** nodes, int numNodes) {
        vector<int> travelableNodes;
        vector<int> traveledPath;
        int counter = 0;
        for (int i = 0; i < numNodes; i++) {
            if (i != startingPoint) {
                travelableNodes.push_back(i);
            }
        }
        int n = travelableNodes.size();
        int shortestPath = INT_MAX;
        while (next_permutation(travelableNodes.begin(),travelableNodes.end())) {
            // if (counter % 1000000 == 0) {
            //     cout << counter << " operations completed" << endl;
            // }
            vector<int> curPath;
            curPath.push_back(startingPoint + 1);
            int pathWeight = 0;
            int j = startingPoint;
            bool containsZero = false;
            for (int i = 0; i < n; i++) {
                if (nodes[j][travelableNodes[i]] == 0) {
                    containsZero = true;
                    break;
                }
                pathWeight += nodes[j][travelableNodes[i]];
                j = travelableNodes[i];
                curPath.push_back(j + 1);
            }
            if (containsZero) {
                continue;
            }
            pathWeight += nodes[j][startingPoint];
            int oldShortestPath = shortestPath;
            shortestPath = min(shortestPath, pathWeight);
            if (shortestPath != oldShortestPath) {
                traveledPath = curPath;
            }
            counter++;
        }
        cout << "Path Taken: ";
        for (auto i: traveledPath) {
            cout << i << ' ';
        }
        cout << endl;
        return shortestPath;
    }
};

int** readFile(string fileName, int &numNodes);

int main(int argc, char* argv[]) {
    // creating a multi-dimensional array
    int numNodes;
    string fileName = argv[1];
    int** nodes = readFile(fileName, numNodes);
    // for (int i = 0; i < num_nodes; i++) {
    //     for (int j = 0; j < num_nodes; j++) {
    //         cout << "Node ID: " << (i + 1) << " Node Edge: " << (j + 1) << " Node Edge Weight: " << nodes[i][j] << endl;
    //     }
    // }
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            cout << nodes[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    bfm bruteForce;
    int cost = bruteForce.shortestPath(nodes, numNodes);
    cout << cost << endl;
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