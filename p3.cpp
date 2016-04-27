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

using namespace std;
fstream commands, dates, edges;
void getDateList(vector<int> *datesV, int startYear, int endYear, fstream &dates);
int limit;
//int outDegreeTotal = 0;
int vertices = 0;
int inRange = 0;
int largestDegree = 0;
vector<int> keyV;
//int keyArray[0];

// single linked list
struct adjList {
    int val;
    adjList* next;
};

adjList* adjListArrPointer = new adjList;

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
    int numEdges = 0;
    int pi = 0;

    limit = datesV->back(); // last element in vector
    //inRange = datesV->size(); // number of elements in vector
    vertices = datesV->size();
    adjList **adjListArr = new adjList*[datesV->size()];

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
                adjList* adjListArrPointer = new adjList;
                adjListArrPointer->val = pj;
                // have the last pointer in the list point to the newly allocated adjList element
                pointer->next = adjListArrPointer;

                // check if current head has largest number of edges, if true, become new largestDegree
                if(numOfDegrees > largestDegree) {
                    largestDegree = numOfDegrees;
                }
                break;
            }
        }
    }


    for(int i = 0; i < datesV->size(); i++) {
        cout<<adjListArr[i]->val<<" ->";
        adjListArrPointer = adjListArr[i]->next;
        while(adjListArrPointer != NULL) {
            cout<<adjListArrPointer->val<<" ->";
            adjListArrPointer = adjListArrPointer->next;
        }
        cout<<endl;
    }

    cout<<"number of vertices n: "<<vertices<<endl;
    cout<<"number of edges m: "<<numEdges<<endl;
}

void printVector(vector<int> *v) {
    for (vector<int>::iterator it = v->begin(); it != v->end(); ++it) {
        cout << *it << endl;
    }
}

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
            graph(&datesV, edges);
            cout<<endl;
        }
        else if(strcmp(token, "out-degree") == 0) {

            int c1 = count(keyV.begin(),keyV.end(),1);
            int c2 = count(keyV.begin(),keyV.end(),2);
            int c3 = count(keyV.begin(),keyV.end(),3);
            int c4 = count(keyV.begin(),keyV.end(),4);
            int c5 = count(keyV.begin(),keyV.end(),5);
            int c6 = count(keyV.begin(),keyV.end(),6);
            int c7 = count(keyV.begin(),keyV.end(),7);
            int c8 = count(keyV.begin(),keyV.end(),8);
            int c9 = count(keyV.begin(),keyV.end(),9);
            int exists = 0;
            cout<<"Out-Degree 0 count: "<<(inRange+1)- vertices<<endl;
            if(c1) {
                cout<<"Out-Degree 1 count: "<<c1<<endl;
                exists++;
            }
            if(c2) {
                cout<<"Out-Degree 2 count: "<<c2<<endl;
                exists++;
            }
            if(c3) {
                cout<<"Out-Degree 3 count: "<<c3<<endl;
                exists++;
            }
            if(c4) {
                cout<<"Out-Degree 4 count: "<<c4<<endl;
                exists++;
            }
            if(c5) {
                cout<<"Out-Degree 5 count: "<<c5<<endl;
                exists++;
            }
            if(c6) {
                cout<<"Out-Degree 6 count: "<<c6<<endl;
                exists++;
            }
            if(c7) {
                cout<<"Out-Degree 7 count: "<<c7<<endl;
                exists++;
            }
            if(c8) {
                cout<<"Out-Degree 8 count: "<<c8<<endl;
                exists++;
            }
            if(c9) {
                cout<<"Out-Degree 9 count: "<<c9<<endl;
                exists++;
            }
            int averageOut = (c1+c2+c3+c4+c5+c6+c7+c8+c9)/exists;
            cout<<"the average out degree: "<<averageOut<<endl;
        }
        else if(strcmp(token, "shortest-path") == 0) {

        }
        else if(strcmp(token, "diamater") == 0) {
            cout<<"diatmeter"<<endl;
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


