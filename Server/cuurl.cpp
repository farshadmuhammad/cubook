#include "cuurl.h"

CUUrl::CUUrl()
{
}

//Get Methods
QUrl CUUrl::getLink(){return link;}
QString CUUrl::getPageName(){return pagename;}

//Set Methods
void CUUrl::setLink(QUrl a_link){
    link = a_link;
}

void CUUrl::setPageName(QString a_pagename){
    pagename = a_pagename;
}
