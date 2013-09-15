#ifndef GETWRAPPER_H
#define GETWRAPPER_H
#include <QtSql>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QtCore>
#include "filter.h"
class getWrapper
{
public:
    getWrapper();

    QList<QList<QString> > getFlashFeed( Filter*);
    QList<QList<QString> > getNewsFlashFive(Filter*, int );
    QList<QList<QString> > getFlashFeedSegment(int );
    QList<QList<QString> > getNewsFlashFiveSegment(int , int );
    QList<QList<QString> > getFlashFeedUser(int );
    QList<QList<QString> > getNewsFlashFiveUser(int , int );
    QList<QString> getNewsFlash(int);
    QList<QString> getFlashBoard(int);
    QList<QString> getSegmentIDs(int);
    QList<QString> getAttachments(int);
    QList<QString> getProfile(int);
    QList<QString> getCourseList(int);
    QList<QString> getNewsFlashIDList(Filter*, int);
    QList<QString> getNewsFlashIDList(Filter*, int, int);
    QList<QString> getNewsFlashIDList(Filter*, int, int, int);
    QList<QString> getNewsFlashIDList(int,int);
    QList<QString> getNewsFlashIDList(int,int, int);
    QList<QString> getNewsFlashIDList(int,int, int, int);
    QList<QString> getNewsFlashIDList(int,int,int,QString);
    QList<QString> getNewsFlashIDList(int,int,int,int,QString);
    QList<QString> getNewsFlashIDList(int,int,int,int,int,QString);
    QList<QString> getLinks(int PostID);
    QList<QString> getSegment(int segmentID);
    QList<QString> getSegmentsIDs(int flashBoard);
    QList<QString> getFilter(int);
    QString getUserProfPic(int userID);
    int getAttachmentPointer();
    bool openDatabase();
    void closeDatabase();
    QSqlDatabase *db;
    int getNewsFlashID(int);
    Filter *holder;
};

#endif // GETWRAPPER_H
