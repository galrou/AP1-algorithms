//
// Created by idanbazel on 16/01/2020.
//

#ifndef Ex4_MATRIX_H
#define Ex4_MATRIX_H

#define BLOCK -1

#include <iostream>
#include "ISearchable.h"

class Matrix : public ISearchable{

    double** matrix;
    State* initialState;
    State* goalState;
    int n;
    int m;

public:

    Matrix(int row, int col, double** mat, State* initState, State* destState) {

        this->n = row;
        this->m = col;
        this->matrix = mat;
        this->initialState = initState;
        this->goalState = destState;

    }

//    State<Cell>* getCell(int i, int j) {
//        if (i > this->n || j > this->m || i < 0 || j < 0) {
//            cout<<"Invalid values for cell in the matrix. Matrix.cpp->getCell"<<endl;
//            exit(0);
//        }
//
//        State<Cell>* ans = new State<Cell>(Cell(i, j));
//        ans->setCost(this->matrix[i][j]);
//
//        return ans;
//    }

    virtual State* getInitialState() {
        return this->initialState;
    }

    virtual State* getGoalState() {
        return this->goalState;
    }


    double** getMatrix() {
        return this->matrix;
    }

    int getRow() {
        return this->n;
    }

    int getCol() {
        return this->m;
    }

int* getIJ(string st) {

    int *splitArr = (int *) malloc(2 * sizeof(int));

    if (splitArr == nullptr) {
        cout << "Error allocated memory. Matrix.h->getIJ" << endl;
        exit(0);
    }

    string s1 = "", s2 = "";
    int i, j;

    bool flag = false;

    for (unsigned int index = 0; index < st.length(); index++) {

        if (st[index] == ',') {
            flag = true;
            continue;
        }

        if (!flag) {
            s1 += st[index];
        } else {
            s2 += st[index];
        }
    }

    i = (int)atof(s1.c_str());
    j = (int)atof(s2.c_str());

    splitArr[0] = i;
    splitArr[1] = j;

    return splitArr;
}

    virtual vector<State*> getAllPossibleStates(State* st) {

        vector<State*> adjVec; // The vector of ADJ'

        string currentState =  st->getState();
        int* arrSplit = this->getIJ(currentState);

        int i = arrSplit[0], j = arrSplit[1];

        if (i > 0 && this->matrix[i - 1][j] != BLOCK) {
            string coordinates = to_string(i - 1) + "," + to_string(j);
            State *adj = new State(coordinates);
            adj->setCost(this->matrix[i - 1][j]);
            adj->setOriginalCost(adj->getCost());

            adjVec.push_back(adj);
        }

        if (j > 0 && this->matrix[i][j - 1] != BLOCK) {
            string coordinates = to_string(i) + "," + to_string(j - 1);
            State *adj = new State(coordinates);
            adj->setCost(this->matrix[i][j - 1]);
            adj->setOriginalCost(adj->getCost());

            adjVec.push_back(adj);
        }

        if (i < (this->n - 1) && this->matrix[i + 1][j] != BLOCK) {
            string coordinates = to_string(i + 1) + "," + to_string(j);
            State *adj = new State(coordinates);
            adj->setCost(this->matrix[i + 1][j]);
            adj->setOriginalCost(adj->getCost());

            adjVec.push_back(adj);
        }

        if (j < (this->m - 1) && this->matrix[i][j + 1] != BLOCK) {
            string coordinates = to_string(i) + "," + to_string(j + 1);
            State *adj = new State(coordinates);
            adj->setCost(this->matrix[i][j + 1]);
            adj->setOriginalCost(adj->getCost());

            adjVec.push_back(adj);
        }

        return adjVec;
    }

    virtual double h(State s1) {

        int* split1 = this->getIJ(this->goalState->getState());
        int* split2 = this->getIJ(s1.getState());

        int i1 = split1[0], j1 = split1[1], i2 = split2[0], j2 = split2[1];

        double ans = abs(i1 - i2) + abs(j1 - j2);

        return ans;
    }

    virtual ~Matrix() {}

};

#endif //Ex4_MATRIX_H
