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
void getDateList(vector<int> datesV, int startYear, int endYear, fstream &dates);
int limit;
int outDegreeTotal = 0;
int edgesLines = 0;
int vertices = 0;
int numEdges = 0;
int inRange = 0;
int largestDegree = 0;
int pointerIndex = 0;
vector<int> keyV;
//int keyArray[0];

// single linked list
struct adjList {
    int val;
    adjList* next;
};

adjList* adjListArrPointer = new adjList;

void getDateList(vector<int> datesV, int startYear, int endYear, fstream &dates) {
    int patent,year;
    //vector<int> temp;
    while(true) {
        dates >> patent;
        if(dates.eof()) {
            break;
        }
        dates >> year;

        if(year <= endYear && year >= startYear) {
            datesV.push_back(patent);
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

void graph(vector<int> datesV, fstream& edges, adjList* adjListArr[]) {
    cout<<"here"<<endl;
    int vertex;

    limit = datesV.back(); // last element in vector
    inRange = datesV.size(); // number of elements in vector
    adjListArr[inRange];
    adjList* adjListArrPointer = new adjList;
    cout<<"here1"<<endl;


    for(int i = 0; i < datesV.size(); i++) {
        // create a new adjList
        // put something in it yo
        // point it to another adjList or have it be pointed to
        //adjListArr = new adjList;
        //adjListArr[i] = new adjList; // you gotta lose the array idea
        adjListArr[i]->val = datesV[i];
        adjListArr[i]->next = NULL;
        vertices++;
    }

    while(true) {
        int counter = 0;
        edges >> vertex;
        if(edges.eof()) {
            break;
        }
        int node;
        edges >> node;
        for(int i=0; i < datesV.size(); i++) {
            if(vertex == adjListArr[i]->val && node <= limit) {
                numEdges++;
                //keyArray[i] = keyArray[i] + 1;
                //keyV[i] = keyV[i] + 1;
                adjList* pointer = adjListArr[i];
                pointerIndex = 0;

                while(pointer->next != NULL) {
                    pointer = pointer->next;
                    pointerIndex++;
                }


                //add to adj list
                adjList* adjListArrPointer = new adjList;
                pointer->next = adjListArrPointer;
                adjListArrPointer->val = node;

                if(pointerIndex > largestDegree) {
                    largestDegree = pointerIndex+3;

                }
                break;
            }
        }
        edgesLines++;
    }


    for(int i = 0; i < datesV.size(); i++) {
        cout<<adjListArr[i]->val<<" ->";
        adjListArrPointer = adjListArr[i]->next;
        while(adjListArrPointer != NULL) {
            cout<<adjListArrPointer->val<<" ->";
            adjListArrPointer = adjListArrPointer->next;
        }
        cout<<endl;
    }

    cout<<"number of vertices n: "<<vertices<<endl; // this is the size of the pointer array
    // can we figure this out right at the beginning?
    // did she say that it must be a pointer array or it can be a vector of pointers?
    cout<<"number of edges m: "<<numEdges<<endl;
}

int  main(int argc, char *argv[]) {
    edges.open(argv[1], fstream::in);
    dates.open(argv[2], fstream::in);
    commands.open(argv[3], fstream::in);
    int startYear,endYear;
    char token [25];
    adjList* adjListArr[15];
    vector<int> datesV;

    while(true) {
        commands >> token;
        if(commands.eof()) {
            break;
        }
        else if(strcmp(token, "graph") == 0) {
            commands >> startYear;
            commands >> endYear;
            // creating new vector here initialized with getDateList(startYear, endYear, dates)
            getDateList(datesV, startYear, endYear, dates);
            //keyArray[datesV.size()]; // wtf? accessing the element of keyArray which is at position size of datesV
            //adjListArr[datesV.size()]; // wtf? same as above. not doing anything with them though.
            graph(datesV, edges, adjListArr);
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
            endGraph(adjListArr);
            cout<<"hereEnd"<<endl;
        }
    }
}


