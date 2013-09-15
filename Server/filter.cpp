#include "filter.h"

Filter::Filter()
{
     cID1 = 0;
     cID2 = 0;
     cID3 = 0;
     cID4 = 0;
     cID5 = 0;
}
void Filter::setFilter(int cI1, int cI2, int cI3, int cI4, int cI5){
    cID1 = cI1;
    cID2 = cI2;
    cID3 = cI3;
    cID4 = cI4;
    cID5 = cI5;
}
