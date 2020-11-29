#ifndef __DATA_FRAME_H
#define __DATA_FRAME_H

#include "row.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace sd
{

class DataFrame
{
public:
    DataFrame();
    DataFrame(const DataFrame*);
    DataFrame(const DataFrame&);
    virtual ~DataFrame();

    void addHeaders(vector<string>&);
    void addRow(vector<string>&);
    void addRow(Row&);
    size_t getRowSize();
    size_t getColSize();
    vector<string>& getHeaders();
    size_t getHeaderValue(const string);
    vector<Row>& dfIterator();
    Row& getRow(size_t i);
    template <typename T>
    void sortBy(const string, const char);
    template <typename T>
    T getMax(string);
    template <typename T>
    T getMin(string);
    template <typename T>
    T getAvg(string);
    void addCol(const string);
    void removeCol(const string);
    DataFrame selectCol(const initializer_list<string>&);
    void show();
    void show(size_t size);
    void resetHeadersMap();

private:
    map<string, size_t> headersMap;
    vector<string> headersVec;
    vector<Row> rowVec;
};

} // namespace sd

#endif
