#ifndef CUURL_H
#define CUURL_H

#include <QUrl>

class CUUrl
{
public:
    CUUrl();

    //Get Methods
    QUrl getLink();
    QString getPageName();

    //Set Methods
    void setLink(QUrl a_link);
    void setPageName(QString a_pagename);

private:
    QUrl link;
    QString pagename;
};

#endif // CUURL_H
