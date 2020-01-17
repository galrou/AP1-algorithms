#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <thread>
#include "State.h"
#include "Matrix.h"
#include "BestFirstSearch.h"
#include "AStar.h"
#include "DepthFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "CacheManager.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "MyParallelServer.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"


vector<double> getValuesVector(string str) {

    string copyStr = "";
    vector<string> ansVec;
    size_t start = 0;

    //  Copying to string type
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        copyStr += str[i];
    }

    // Split by ',' and push back into the ansVec
    while ((start = copyStr.find(",")) != std::string::npos) {

        // Get the current subString
        string currentStr = copyStr.substr(0, start);

        // Push back the current subString into the ansVec
        ansVec.push_back(currentStr);

        // Remove the current subString out of the string
        copyStr.erase(0, start + 1);
    }
    ansVec.push_back(copyStr);

    string newAnsVecT = "";
    for (unsigned int t = 0; t < ansVec.size(); t++) {

        for (unsigned int j = 0; j < ansVec[t].length(); j++) {
            if (ansVec[t][j] != ' ' && ansVec[t][j] != '\n') {
                newAnsVecT += ansVec[t][j];
            }
        }

        istringstream os(newAnsVecT);
        double d;
        os >> d;
        string answerVecElem = std::to_string(d);
        ansVec[t] = answerVecElem;
        newAnsVecT = "";
    }

    vector<double> doublesAnsVec;
    unsigned int ansVecSize = ansVec.size();

    for (unsigned int elem = 0; elem < ansVecSize; elem++) {

        doublesAnsVec.push_back(atof(ansVec[elem].c_str()));
    }

    return doublesAnsVec;
}


Matrix getMatrixObject(string fileName) {


    string line; // The current line
    //******Counting the number of lines in the file (almost)******
    int numberOfRows = 0;
    int numberOfColumns = 0;
    ifstream readFileCounter(fileName); // The stream
    // If the file is not open
    if (!readFileCounter) {
        cout<<"error: ClientHandler.cpp->getMatrixObject->openFile"<<endl;
        exit(0);
    }

    while(!readFileCounter.eof()) {
        getline(readFileCounter, line);

        if (line.compare("end") == 0)
            break;

        if (numberOfRows == 0) {
            vector<double> colsVec = getValuesVector(line);
            numberOfColumns = colsVec.size();
        }

        numberOfRows++;
    }

    readFileCounter.close();
    //****************************************
    numberOfRows -= 2;

    double** ansMatrix = (double**) malloc(numberOfRows * sizeof(double*));

    for (unsigned int k = 0; k < numberOfRows; k++) {
        ansMatrix[k] = (double*) malloc(numberOfColumns * sizeof(double));
    }

    ifstream readFile(fileName); // The stream

    // If the file is not open
    if (!readFile) {
        cout<<"error: ClientHandler.cpp->getMatrixObject->openFile"<<endl;
        exit(0);
    }

    // Add any line to the vector
   for (int i = 0; i < numberOfRows; i++) {
        // Put the current line into the string 'line'
        getline(readFile, line);

        vector<double> splittedLine = getValuesVector(line);

        for (unsigned int j = 0; j < splittedLine.size(); j++) {
            ansMatrix[i][j] = splittedLine[j];
        }
    }

    getline(readFile, line);
    vector<double> splittedLine = getValuesVector(line);
    string stateInit = to_string((int)splittedLine[0]) + "," + to_string((int)splittedLine[1]);
   State* initialState = new State(stateInit);
    initialState->setCost(ansMatrix[(int)splittedLine[0]][(int)splittedLine[1]]);
    initialState->setOriginalCost(ansMatrix[(int)splittedLine[0]][(int)splittedLine[1]]);

    getline(readFile, line);
    splittedLine = getValuesVector(line);
    string stateGoal = to_string((int)splittedLine[0]) + "," + to_string((int)splittedLine[1]);
    State* goalState = new State(stateGoal);
    goalState->setCost(ansMatrix[(int)splittedLine[0]][(int)splittedLine[1]]);
    goalState->setOriginalCost(ansMatrix[(int)splittedLine[0]][(int)splittedLine[1]]);

   Matrix ansMatrixObject = Matrix(numberOfRows, numberOfColumns, ansMatrix, initialState, goalState);

    readFile.close();

    return ansMatrixObject;
}


using namespace std;
int main() {

    Matrix mat = getMatrixObject("Matrix16x16.txt");

//    for (int i = 0; i < mat.getRow(); i++) {
//        for (int j = 0; j < mat.getCol(); j++) {
//
//            cout<<mat.getMatrix()[i][j];
//            cout<< " ";
//        }
//        cout<<""<<endl;
//    }

//    double** vec = (double**) malloc(3 * sizeof(double*));
//
//    for (int i = 0; i < 3; i++) {
//        vec[i] = (double *) malloc(3 * sizeof(double));
//    }
//
//    vec[0][0]=6;
//    vec[0][1]=1;
//    vec[0][2]=4;
//    vec[1][0]=11;
//    vec[1][1]=9;
//    vec[1][2]=2;
//    vec[2][0]=5;
//    vec[2][1]=8;
//    vec[2][2]=2;
//
//    State initState1 = State("0,0");
//    initState1.setCost(vec[0][0]);
//    initState1.setOriginalCost(vec[0][0]);
//
//    State goalState1 = State("2,2");
//    goalState1.setCost(vec[2][2]);
//    goalState1.setOriginalCost(vec[2][2]);
//
//    Matrix matrix = Matrix(3, 3, vec, &initState1, &goalState1);
//

/**
 * לשנות את הטיפוס פשוט לפי שם ההאלגוריתם ואז יודפס המשקל הכולל של המסלול הקצר ביותר
 */
    BreadthFirstSearch algorithm;
    cout<<"BFS:"<<endl;
    vector<State*> ansVector= algorithm.search(&mat);
    cout<<"Shortest path weight:"<<endl;
    cout<<ansVector[ansVector.size()-1]->getCost()<<endl;
    cout<<"Number of evaluated nodes:"<<endl;
    cout<<algorithm.getNumberOfNodesEvaluated()<<endl;
    //cout<<p<<endl;
    CacheManager<string, string> *cacheManager = new  FileCacheManager<string>(3);
    StringReverser *sr=new StringReverser();
    MyParallelServer mss{};
    MyTestClientHandler *ch=new MyTestClientHandler(cacheManager,sr);
    mss.open(8081,ch);

//    DepthFirstSearch algorithm1;
//    cout<<"\nDFS:"<<endl;
//    vector<State*> ansVector1= algorithm1.search(&mat);
//    cout<<"Shortest path weight:"<<endl;
//    cout<<ansVector1[ansVector1.size()-1]->getCost()<<endl;
//    cout<<"Number of evaluated nodes:"<<endl;
//    cout<<algorithm1.getNumberOfNodesEvaluated()<<endl;
//
//    BestFirstSearch algorithm2;
//    cout<<"\nBestFS:"<<endl;
//    vector<State*> ansVector2= algorithm2.search(&mat);
//    cout<<"Shortest path weight:"<<endl;
//    cout<<ansVector2[ansVector2.size()-1]->getCost()<<endl;
//    cout<<"Number of evaluated nodes:"<<endl;
//    cout<<algorithm2.getNumberOfNodesEvaluated()<<endl;
//
//
//    AStar algorithm3;
//    cout<<"\nAStar:"<<endl;
//    vector<State*> ansVector3= algorithm3.search(&mat);
//    cout<<"Shortest path weight:"<<endl;
//    cout<<ansVector3[ansVector3.size()-1]->getCost()<<endl;
//    cout<<"Number of evaluated nodes:"<<endl;
//    cout<<algorithm3.getNumberOfNodesEvaluated()<<endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(120000000));


    return 0;
}