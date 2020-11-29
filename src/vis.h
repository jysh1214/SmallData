#ifndef __VIS_H_
#define __VIS_H_

#include "row.h"
#include <vector>
#include <string>

using namespace std;

namespace sd
{

class Vis
{
public:
    Vis(vector<string>&, vector<Row>&, size_t);
    virtual ~Vis();

    void showTable();

private:
    size_t MAX_SIZE = 10;
    vector<string>* headersPtr;
    vector<Row>* rowPtr;
    size_t showNum;
};

} // namespace sd

#endif
