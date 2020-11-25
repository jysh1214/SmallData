#ifndef __ROW_H_
#define __ROW_H_

#include <vector>
#include <string>

namespace sd
{

struct Row: public std::vector<std::string>
{
public:
    Row(std::vector<std::string>&);
    Row(std::vector<std::string>&&);
    std::string& operator[](size_t);
    size_t size();
    void push_back(std::string);
    void print(size_t);
    void erase(size_t);

private:
    std::vector<std::string> db_row;
};

} // namespace sd

#endif
