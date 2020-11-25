#include "data_frame.h"
#include <iostream>

using namespace sd;

DataFrame::DataFrame()
{

}

DataFrame::DataFrame(const DataFrame* old_df)
{
    for (auto item: old_df->headersMap) {
        this->headersMap[item.first] = item.second;
    }
    for (auto item: old_df->headersVec) {
        this->headersVec.push_back(item);
    }
    for (auto item: old_df->rowVec) {
        this->rowVec.push_back(item);
    }
}

DataFrame::DataFrame(const DataFrame& old_df)
{
    for (auto item: old_df.headersMap) {
        this->headersMap[item.first] = item.second;
    }
    for (auto item: old_df.headersVec) {
        this->headersVec.push_back(item);
    }
    for (auto item: old_df.rowVec) {
        this->rowVec.push_back(item);
    }
}

DataFrame::~DataFrame()
{

}

void DataFrame::addHeaders(std::vector<std::string>& headers)
{
    try {
        size_t i = 0;
        for (auto header: headers) {
            this->headersVec.push_back(header);
            this->headersMap[header] = i;
            ++i;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void DataFrame::addRow(std::vector<std::string>& row)
{
    try {
        this->rowVec.push_back(Row(row));
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void DataFrame::addRow(Row& row)
{
    try {
        this->rowVec.push_back(row);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

size_t DataFrame::getRowSize()
{
    return this->rowVec.size();
}

size_t DataFrame::getColSize()
{
    return this->headersVec.size();
}

std::vector<std::string>& DataFrame::getHeaders()
{
    return this->headersVec;
}

size_t DataFrame::getHeaderValue(const std::string header)
{
    return this->headersMap[header];
}

std::vector<Row>& DataFrame::dfIterator()
{
    return this->rowVec;
}

Row& DataFrame::getRow(size_t i)
{
    return this->rowVec[i];
}

template <>
void DataFrame::sortBy<std::string>(const std::string header, const char op)
{
    if (op != '<' && op != '>') {
        std::cerr << "DataFrame::sortBy Error: Use '<' or '>'.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    if (op == '<')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return lrow[headerValue] < rrow[headerValue]; });
    }
    else if (op == '>')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return lrow[headerValue] > rrow[headerValue]; });
    }
}

template <>
void DataFrame::sortBy<int>(const std::string header, const char op)
{
    if (op != '<' && op != '>') {
        std::cerr << "DataFrame::sortBy Error: Use '<' or '>'.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    if (op == '<')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stoi(lrow[headerValue]) < stoi(rrow[headerValue]); });
    }
    else if (op == '>')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stoi(lrow[headerValue]) > stoi(rrow[headerValue]); });
    }
}

template <>
void DataFrame::sortBy<float>(const std::string header, const char op)
{
    if (op != '<' && op != '>') {
        std::cerr << "DataFrame::sortBy Error: Use '<' or '>'.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    if (op == '<')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stof(lrow[headerValue]) < stof(rrow[headerValue]); });
    }
    else if (op == '>')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stof(lrow[headerValue]) > stof(rrow[headerValue]); });
    }
}

template <>
void DataFrame::sortBy<double>(const std::string header, const char op)
{
    if (op != '<' && op != '>') {
        std::cerr << "DataFrame::sortBy Error: Use '<' or '>'.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    if (op == '<')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stod(lrow[headerValue]) < stod(rrow[headerValue]); });
    }
    else if (op == '>')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stod(lrow[headerValue]) > stod(rrow[headerValue]); });
    }
}

template <>
void DataFrame::sortBy<long>(const std::string header, const char op)
{
    if (op != '<' && op != '>') {
        std::cerr << "DataFrame::sortBy Error: Please use '<' or '>'.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    if (op == '<')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stol(lrow[headerValue]) < stol(rrow[headerValue]); });
    }
    else if (op == '>')
    {
        sort(this->rowVec.begin(), this->rowVec.end(),
             [=](Row &lrow, Row &rrow) { return stol(lrow[headerValue]) > stol(rrow[headerValue]); });
    }
}

inline bool exist(std::string str, std::vector<std::string>& vec)
{
    for (auto item: vec) {
        if (str == item)
            return true;
    }

    return false;
}

template <>
std::string DataFrame::getMax<std::string>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMax Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    std::string max = this->rowVec[0][headerValue];
    for (auto row : this->rowVec) {
        max = row[headerValue] >= max ? row[headerValue] : max;
    }

    return max;
}

template <>
int DataFrame::getMax<int>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMax Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    int max = stoi(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        max = stoi(row[headerValue]) >= max ? stoi(row[headerValue]) : max;
    }

    return max;
}

template <>
float DataFrame::getMax<float>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMax Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    float max = stof(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        max = stof(row[headerValue]) >= max ? stof(row[headerValue]) : max;
    }

    return max;
}

template <>
double DataFrame::getMax<double>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMax Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    double max = stod(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        max = stod(row[headerValue]) >= max ? stod(row[headerValue]) : max;
    }

    return max;
}

template <>
long DataFrame::getMax<long>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMax Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    long max = stol(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        max = stol(row[headerValue]) >= max ? stol(row[headerValue]) : max;
    }

    return max;
}

template <>
std::string DataFrame::getMin<std::string>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    std::string min = this->rowVec[0][headerValue];
    for (auto row : this->rowVec) {
        min = row[headerValue] <= min ? row[headerValue] : min;
    }

    return min;
}

template <>
int DataFrame::getMin<int>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    int min = stoi(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        min = stoi(row[headerValue]) <= min ? stoi(row[headerValue]) : min;
    }

    return min;
}

template <>
float DataFrame::getMin<float>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    float min = stof(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        min = stof(row[headerValue]) <= min ? stof(row[headerValue]) : min;
    }

    return min;
}

template <>
double DataFrame::getMin<double>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    float min = stod(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        min = stod(row[headerValue]) <= min ? stod(row[headerValue]) : min;
    }

    return min;
}

template <>
long DataFrame::getMin<long>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    size_t headerValue = this->headersMap[header];
    float min = stol(this->rowVec[0][headerValue]);
    for (auto row : this->rowVec) {
        min = stol(row[headerValue]) <= min ? stol(row[headerValue]) : min;
    }

    return min;
}

template <>
int DataFrame::getAvg<int>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    if (this->rowVec.size() == 0)
        return 0;

    size_t headerValue = this->headersMap[header];
    int sum = 0;
    for (Row row : this->rowVec) {
        sum += stoi(row[headerValue]);
    }

    return int(sum / this->rowVec.size());
}

template <>
float DataFrame::getAvg<float>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    if (this->rowVec.size() == 0)
        return 0;

    size_t headerValue = this->headersMap[header];
    float sum = 0;
    for (Row row : this->rowVec) {
        sum += stof(row[headerValue]);
    }

    return float(sum / this->rowVec.size());
}

template <>
double DataFrame::getAvg<double>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "cs::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    if (this->rowVec.size() == 0)
        return 0;

    size_t headerValue = this->headersMap[header];
    double sum = 0;
    for (Row row : this->rowVec) {
        sum += stod(row[headerValue]);
    }

    return double(sum / this->rowVec.size());
}

template <>
long DataFrame::getAvg<long>(const std::string header)
{
    if (!exist(header, this->headersVec)) {
        std::cerr << "sd::DataFrame::getMin Error: Header does not exist.\n";
        exit(0);
    }

    if (this->rowVec.size() == 0)
        return 0;

    size_t headerValue = this->headersMap[header];
    long sum = 0;
    for (Row row : this->rowVec) {
        sum += stol(row[headerValue]);
    }

    return long(sum / this->rowVec.size());
}

void DataFrame::addCol(const std::string newHeader)
{
    auto check = [=]() -> bool {
        for (auto item : DataFrame::headersMap) {
            if (item.first == newHeader)
                return false;
        }
        return true;
    };

    if (!check()) {
        std::cerr << "sd::DataFrame::addCol Error: Header has been existed.\n";
        exit(0);
    }

    size_t headersMapSize = this->headersMap.size();
    size_t headersVectorSize = this->headersVec.size();
    size_t rowVectorSize = this->rowVec.size();

    this->headersMap[newHeader] = this->headersVec.size();
    this->headersVec.push_back(newHeader);

    for (Row& row : this->rowVec) {
        row.push_back(std::string(""));
    }

    assert(this->headersMap.size() == headersMapSize + 1);
    assert(this->headersVec.size() == headersVectorSize + 1);
    assert(this->rowVec.size() == rowVectorSize);
}

void DataFrame::removeCol(const std::string header)
{
    auto check = [=]() -> bool {
        for (auto item : DataFrame::headersMap) {
            if (item.first == header)
                return true;
        }
        return false;
    };

    if (!check()) {
        std::cerr << "sd::DataFrame::addCol Error: Header does not existed\n";
        exit(0);
    }

    size_t headersMapSize = this->headersMap.size();
    size_t headersVectorSize = this->headersVec.size();
    size_t rowVectorSize = this->rowVec.size();

    int index = this->headersMap[header];
    this->headersVec.erase(this->headersVec.begin() + index);

    for (auto& row : this->rowVec) {
        row.erase(index);
    }

    // reset headersMap
    this->headersMap.clear();
    size_t i = 0;
    for (auto header : this->headersVec)
    {
        this->headersMap[header] = i;
        ++i;
    }

    assert(this->headersMap.size() == headersMapSize - 1);
    assert(this->headersVec.size() == headersVectorSize - 1);
    assert(this->rowVec.size() == rowVectorSize);
}

DataFrame DataFrame::selectCol(const std::initializer_list<std::string>& list)
{
    auto check = [=]() -> bool {
        for (auto item : list) {
            if (!exist(item, this->headersVec))
                return false;
        }
        return true;
    };

    if (!check()) {
        std::cerr << "sd::DataFrame::selectCol Error: Header does not existed\n";
        exit(0);
    }

    std::vector<std::string> list_vec = list;

    DataFrame new_df(this);
    for (auto header : this->headersVec) {
        if (!exist(header, list_vec)) {
            new_df.removeCol(header);
        }
    }

    assert(new_df.getColSize() == list.size());
    assert(new_df.headersMap.size() == list.size());
    assert(new_df.getRowSize() == this->getRowSize());

    return new_df;
}
/*
void DataFrame::show()
{
    size_t size = (10 > this->rowVector.size()) ? this->rowVector.size() : 10;

    Visualization vis(this->headersVector, this->rowVector, size);
    vis.showTable();
}

void DataFrame::show(size_t size)
{
    assert((size <= this->rowVector.size()) &&
           "cs::DataFrame::show Error: Input size must <= dataframe size.\n");

    Visualization vis(this->headersVector, this->rowVector, size);
    vis.showTable();
}

void DataFrame::resetHeadersMap()
{
    this->headersMap.clear();
    size_t i = 0;
    for (auto header : this->headersVector)
    {
        this->headersMap[header] = i;
        ++i;
    }
}
*/
