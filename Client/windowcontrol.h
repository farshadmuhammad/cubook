#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H
#include "clientcache.h"

/* This class is responsible for changing the page we are viewing */

class WindowControl
{
public:
    WindowControl();
    static void changeWindow();
    static void changeWindow(int, clientCache*);

    static const int PROFILE_PAGE;
    static const int FLASHFEED_PAGE;
    static const int FLASHSEGMENT_PAGE;
    static const int FILTER_PAGE;


};

#endif // WINDOWCONTROL_H
