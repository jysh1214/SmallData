#include "parser.h"
#include <fstream>
#include <streambuf>
#include <iostream>

using namespace sd;
using namespace std;

size_t COL_SIZE = 0;

cvs_helper::cvs_helper()
{

}

cvs_helper::cvs_helper(string str): content(str)
{

}

cvs_helper::cvs_helper(cvs_helper& helper)
{
    this->content = helper.content;
}

cvs_helper::~cvs_helper()
{

}

cvs_helper& cvs_helper::splitBy(const char split)
{
    this->split = split;
    this->splitSetting = true;

    return *this;
}

cvs_helper& cvs_helper::withDefaultHeaders()
{
    this->useDefaultHeaders = true;
    this->headerSetting = true;

    return *this;
}

cvs_helper& cvs_helper::withHeaders(initializer_list<string> list)
{
    for (string header: list) {
        this->customizedHeaders.push_back(header);
    }
    this->useDefaultHeaders = false;
    this->headerSetting = true;

    return *this;
}

DataFrame cvs_helper::createDF()
{
    if (!this->splitSetting) {
        std::cerr << "Error: Split char is not setted.\n";
        exit(0);
    }
    if (!this->headerSetting) {
        std::cerr << "Error: DataFrame header is not setted.\n";
        exit(0);
    }

    DataFrame df;
    // customized headers
    if (!this->useDefaultHeaders) {
        df.addHeaders(this->customizedHeaders);
        COL_SIZE = this->customizedHeaders.size();
    }
    int current_point = 0;
    vector<string> row;
    string::size_type it = 0;
    string item;
    for (; it <= this->content.size(); ++it) {
        if (content[it] == this->split || it == content.size() - 1) {
            item = content.substr(current_point, it - current_point);
            current_point = it + 1;
            row.push_back(item);
        }
        else if (content[it] == '\n' && COL_SIZE > 0) {
            if (row.size() == COL_SIZE - 1) {
                item = content.substr(current_point, it - current_point);
                current_point = it + 1;
                row.push_back(item);
            }
        }
        // get headers in first line
        if (this->useDefaultHeaders && content[it] == '\n') {
            item = content.substr(current_point, it - current_point);
            current_point = it + 1;
            row.push_back(item);

            df.addHeaders(row);
            COL_SIZE = row.size();
            row.clear();
            this->useDefaultHeaders = false;
        }
        if ((content[it] == '\n' && row.size() == COL_SIZE) || it == content.size()) {
            df.addRow(row);
            row.clear();
        }
    } // read whole cvs file

    return df;
}

Parser::Parser()
{

}

Parser::~Parser()
{

}

cvs_helper Parser::readCVS(const char* filePath)
{
    string fileName(filePath);
    if (fileName.substr(fileName.size() - 4, 4) != ".csv") {
        std::cerr << "Warning: ";
        std::cerr << filePath;
        std::cerr << " is not a cvs file.\n";
    }
    ifstream cvsFile(filePath);
    string content((istreambuf_iterator<char>(cvsFile)), istreambuf_iterator<char>());
    cvsFile.close();

    return cvs_helper(content);
}
