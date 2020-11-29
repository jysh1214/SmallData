#ifndef __ROW_H_
#define __ROW_H_

#include <vector>
#include <string>

using namespace std;

namespace sd
{

struct Row: public vector<string>
{
public:
    Row(vector<string>&);
    Row(vector<string>&&);
    string& operator[](size_t);
    size_t size();
    void push_back(string);
    void print(size_t);
    void erase(size_t);

private:
    vector<string> db_row;
};

} // namespace sd

#endif
