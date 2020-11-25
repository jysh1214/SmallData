#include "parser.h"
#include <fstream>
#include <streambuf>
#include <iostream>

using namespace sd;

cvs_helper::cvs_helper()
{

}

cvs_helper::cvs_helper(std::string str): content(str)
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

cvs_helper& cvs_helper::withHeaders(std::initializer_list<std::string> list)
{
    for (std::string header: list) {
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
    }
    int current_point = 0;
    std::vector<std::string> row;
    for (std::string::size_type i = 0; i <= this->content.size(); ++i) {
        if (content[i] == this->split || content[i] == '\n' || i == content.size() - 1) {
            std::string item = content.substr(current_point, i - current_point);
            current_point = i + 1;
            if (!item.empty()) {
                row.push_back(item);
            }
        }
        // get headers in first line
        if (this->useDefaultHeaders && content[i] == '\n') {
            df.addHeaders(row);
            row.clear();
            this->useDefaultHeaders = false;
        }
        if (content[i] == '\n' || i == content.size()) {
            if (row.size() > 0) {
                df.addRow(row);
                row.clear();
            }
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
    std::string fileName(filePath);
    if (fileName.substr(fileName.size() - 4, 4) != ".csv") {
        std::cerr << "Warning: ";
        std::cerr << filePath;
        std::cerr << " is not a cvs file.\n";
    }
    std::ifstream cvsFile(filePath);
    std::string content((std::istreambuf_iterator<char>(cvsFile)),
        std::istreambuf_iterator<char>());
    cvsFile.close();

    return cvs_helper(content);
}
