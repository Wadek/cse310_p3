#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;
fstream commands, dates, edges;
void getDateList(vector<int> *datesV, int startYear, int endYear, fstream &dates);
void printGraph();
int limit;
//int outDegreeTotal = 0;
int vertices = 0;
int inRange = 0;
int numEdges = 0;
int largestDegree = 0;

// single linked list
struct adjList {
    int val;
    adjList* next;
};

adjList** adjListArrPointer(NULL);

void getDateList(vector<int> *datesV, int startYear, int endYear, fstream &dates) {
    int patent,year;
    //vector<int> temp;
    while(true) {
        dates >> patent;
        if(dates.eof()) {
            break;
        }
        dates >> year;

        if(year <= endYear && year >= startYear) {
            datesV->push_back(patent);
        }
    }
}

void endGraph( adjList* adjListArrPointer[] ) {
    for(int i = 0; i < inRange; i++) {
        adjList* it = adjListArrPointer[i];
        adjList* temp = NULL;

        while(it){
            temp = it;
            int temp1 = it->val;
            it = it->next;
            free(temp);
            temp = NULL;
        }
    }

    //free(adjListArrPointer[inRange]);
}

void graph(vector<int> *datesV, fstream& edges) {
    int pi = 0;

    limit = datesV->back(); // last element in vector
    vertices = datesV->size();
    adjList **adjListArr = new adjList*[datesV->size()];
    adjListArrPointer = adjListArr;

    for(int i = 0; i < datesV->size(); i++) {
        adjListArr[i] = new adjList();
        adjListArr[i]->val = (*datesV)[i];
        adjListArr[i]->next = NULL;
    }

    while(true) {
        int counter = 0;
        edges >> pi;
        if(edges.eof()) {
            break;
        }
        int pj;
        edges >> pj;
        for(int i=0; i < datesV->size(); i++) {
            if(pi == adjListArr[i]->val && pj <= limit) {
                numEdges++;
                adjList* pointer = adjListArr[i];
                int numOfDegrees = 0;

                while(pointer->next != NULL) {
                    pointer = pointer->next;
                    numOfDegrees++;
                }

                // create new adjList and put pj into val
                adjList* newAdjList = new adjList;
                newAdjList ->val = pj;
                // have the last pointer in the list point to the newly allocated adjList element
                pointer->next = newAdjList;

                // check if current head has largest number of edges, if true, become new largestDegree
                if(numOfDegrees >= largestDegree) {
                    largestDegree = numOfDegrees+3;
                }
                break;
            }
        }
    }

    printGraph();

    cout<<"number of vertices n: "<<vertices<<endl;
    cout<<"number of edges m: "<<numEdges<<endl;
}

void printGraph() {
    for(int i = 0; i < vertices; i++) {
        adjList *ptr = adjListArrPointer[i];

        cout<<ptr->val<<" ->";
        ptr = ptr->next;
        while(ptr != NULL) {
            cout<<ptr->val<<" ->";
            ptr = ptr->next;
        }
        cout<<endl;
    }
}

void printOutDegree(unsigned int outDegree) {
    unsigned int count = 0;

    for(int i = 0; i < vertices; i++) {
        unsigned int degrees = 0;
        adjList *ptr = adjListArrPointer[i];
        ptr = ptr->next;
        while(ptr != NULL) {
            ptr = ptr->next;
            degrees++;
        }
        if (degrees == outDegree) {
            count++;
        }
    }
    cout<<"Out-Degree " << outDegree << " count: "<< count <<endl;
}

void printVector(vector<int> *v) {
    for (vector<int>::iterator it = v->begin(); it != v->end(); ++it) {
        cout << *it << endl;
    }
}

/*
void shortestPath(int s, int t) {
    vector<int> queue, prev, dist, container;

    //populate initial vectors
    for(int i = 0; i < vertices; i++) {
        adjList *ptr = adjListArrPointer[i];
        queue.push_back(ptr->val);
        container.push_back(ptr->val);
        prev.push_back(0);
        prev.push_back(-1);
    }


    int u = s;
    adjList *current = adjListArrPointer[0];
    while(!queue.empty()) {
        //find first current value
        for(int i = 0; i < vertices; i++) {
            if(u == adjListArrPointer[i]->val) {
                current = adjListArrPointer[i];
            }
        }

        //find all neighbors of current update distance by adding 1
        while(current != NULL) {
            current = current->next;
            for(int i = 0; i < vertices; i++) {
                if(current->val == container[i]) {
                    dist[i] = dist[i]+1;
                }
            }
        }
    }
}
*/


int  main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: ./a.out edges1.txt dates1.txt commands1.txt" << endl;
        return 0;
    }
    edges.open(argv[1], fstream::in);
    dates.open(argv[2], fstream::in);
    commands.open(argv[3], fstream::in);
    int startYear,endYear;
    char token [25];

    while(true) {
        commands >> token;
        if(commands.eof()) {
            break;
        }
        else if(strcmp(token, "graph") == 0) {
            commands >> startYear;
            commands >> endYear;
            vector<int> datesV;

            getDateList(&datesV, startYear, endYear, dates);
            inRange = datesV.size();
            graph(&datesV, edges);
            cout<<endl;
        }
        else if(strcmp(token, "out-degree") == 0) {
            for(int i = 0; i <= largestDegree; i++) {
                printOutDegree(i);
            }

            int averageOut = numEdges/vertices;
            cout<<"the average out degree: "<<averageOut<<endl;
        }
        else if(strcmp(token, "shortest-path") == 0) {
            int s, t;
            commands >> s;
            commands >> t;
            shortestPath(s, t);

        }
        else if(strcmp(token, "diameter") == 0) {
            cout<<"diameter"<<endl;
        }
        else if(strcmp(token, "scc") == 0) {
            cout<<"scc"<<endl;
        }
        else if(strcmp(token, "end-graph") == 0) {
            //endGraph(adjListArr);
            cout<<"hereEnd"<<endl;
        }
    }
    return 0;
}


