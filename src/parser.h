#ifndef __PARSER_H_
#define __PARSER_H_

#include <string>
#include <vector>
#include <initializer_list>
#include "data_frame.h"

using namespace std;

namespace sd
{

class cvs_helper
{
public:
    cvs_helper();
    cvs_helper(string);
    cvs_helper(cvs_helper&);
    virtual ~cvs_helper();

    cvs_helper& splitBy(const char);
    cvs_helper& withDefaultHeaders();
    cvs_helper& withHeaders(initializer_list<string>);
    DataFrame createDF();

    bool useDefaultHeaders;
    string content;
    char split;

private:
    vector<string> customizedHeaders;
    bool headerSetting = false;
    bool splitSetting = false;
};

class Parser
{
public:
    Parser();
    virtual ~Parser();

    cvs_helper readCVS(const char* filePath);
};

} // namespace sd

#endif
