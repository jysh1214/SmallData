#ifndef __DATA_FRAME_H
#define __DATA_FRAME_H

#include "row.h"
#include <string>
#include <vector>
#include <map>

namespace sd
{

class DataFrame
{
public:
    DataFrame();
    DataFrame(const DataFrame*);
    DataFrame(const DataFrame&);
    virtual ~DataFrame();

    void addHeaders(std::vector<std::string>&);
    void addRow(std::vector<std::string>&);
    void addRow(Row&);
    size_t getRowSize();
    size_t getColSize();
    std::vector<std::string>& getHeaders();
    size_t getHeaderValue(const std::string);
    std::vector<Row>& dfIterator();
    Row& getRow(size_t i);
    template <typename T>
    void sortBy(const std::string, const char);
    template <typename T>
    T getMax(std::string);
    template <typename T>
    T getMin(std::string);
    template <typename T>
    T getAvg(std::string);
    void addCol(const std::string);
    void removeCol(const std::string);
    DataFrame selectCol(const std::initializer_list<std::string>&);


private:
    std::map<std::string, size_t> headersMap;
    std::vector<std::string> headersVec;
    std::vector<Row> rowVec;
};

} // namespace sd

#endif
