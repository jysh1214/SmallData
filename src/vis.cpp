#include "vis.h"
#include <iostream>

using namespace sd;
using namespace std;

inline void drawSplitLine(size_t col, int* colMaxSize)
{
    for (size_t i = 0; i < col; ++i) {
        cout << "+";
        for (int len = 0; len < colMaxSize[i]; ++len) {
            cout << "-";
        }
    }
    cout << "+\n";
}

Vis::Vis(vector<string>& headersVector, vector<Row>& rowVector, size_t showNum)
{
    this->headersPtr = &headersVector;
    this->rowPtr = &rowVector;
    this->showNum = showNum;
}

Vis::~Vis()
{

}

void Vis::showTable()
{
    // record col max length
    size_t col = headersPtr->size();
    int* colMaxSize = (int*) new int[col];

    int count = 0;
    vector<string>::iterator it1 = headersPtr->begin();
    for (; it1 != headersPtr->end(); ++it1) {
        colMaxSize[count] = ((*it1).size() > MAX_SIZE)? MAX_SIZE: (*it1).size();
        ++count;
    }

    size_t showTimes = 0;
    vector<Row>::iterator it2 = rowPtr->begin();
    for (; it2 != rowPtr->end(); ++it2) {
        for (size_t i = 0; i < col; ++i) {
            if ((int)(*it2)[i].size() > colMaxSize[i]) {
                colMaxSize[i] = ((*it2)[i].size() > MAX_SIZE)? MAX_SIZE: (*it2)[i].size();
            }
        } //for each row item
        ++showTimes;
        if (showTimes == showNum) break;
    }

    drawSplitLine(col, colMaxSize);

    // headers
    std::vector<string>::iterator it3 = headersPtr->begin();
    for (size_t i = 0; i < col; ++i) {
        cout << "|";
        if ((*it3).size() > MAX_SIZE) {
            cout << (*it3).substr(0, 7) + "...";
        }
        else {
            cout << (*it3);
            // fill space
            for (int j = 0; i < (colMaxSize[i] - (int)(*it3).size()); ++j)
                cout << " ";
        }
        ++it3;
    }
    cout << "|\n";

    drawSplitLine(col, colMaxSize);

    // table
    showTimes = 0;
    std::vector<Row>::iterator it4 = rowPtr->begin();
    for (; it4 != rowPtr->end(); ++it4) {
        for (size_t i = 0; i < col; ++i) {
            cout << "|";
            if ((*it4).size() > MAX_SIZE) {
                cout << (*it4)[i].substr(0, 7) + "...";
            }
            else {
                cout << (*it4)[i];
                // fill space
                for (int j = 0; i < (colMaxSize[i] - (int)(*it4).size()); ++j)
                    cout << " ";
            }
        }
        cout << "|\n";
        ++showTimes;
        if (showTimes == showNum) break;
    }

    drawSplitLine(col, colMaxSize);

    if ((this->rowPtr)->size() < this->showNum) {
        cout << "Just show top " << this->showNum << " row.\n";
    }

    delete colMaxSize;
}
