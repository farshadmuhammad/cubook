#include "database.h"

Database::Database()
{

}


bool Database::createDatabase(){
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("CUBook");
    return db->open();
}


void Database:: closeDatabase(){

    db->close();
    delete db;
    QSqlDatabase::removeDatabase("CUBook");
}

bool Database::createUserTable(){
    QSqlQuery newQ;
    bool check = false;
    if(db->isOpen()){
        //qDebug()<<"database opened";
    check = newQ.exec("create table Users "
                       "(UserId integer primary key, "
                       "Avatar text, "
                       "Name text, "
                       "AccType integer, "
                       "Photo text)");
    return check;
}
  return check;
}

bool Database::createNewsFlashPostTable(){
    QSqlQuery newQ;
    bool check = false;
    if(db->isOpen()){
        //qDebug()<<"database opened";
    check = newQ.exec("create table NewsFlashPost "
                       "(newsFlashID integer primary key, "
                       "newsFlash text, "
                       "FlashBoard integer, "
                       "UserID integer, "
                       "FlashSegment integer, "
                       "Attachment integer, "
                       "Date text)");
    return check;
}
  return check;
}

bool Database::createFilterTable(){
    QSqlQuery newQ;
    bool check = false;
    if(db->isOpen()){
        //qDebug()<<"database opened";
    check = newQ.exec("create table Filter "
                       "(FilterID integer primary key, "
                       "UserID integer, "
                       "FlashBoardID1 integer, "
                       "Filtered1 text, "
                       "FlashBoardID2 integer, "
                       "Filtered2 text, "
                       "FlashBoardID3 integer, "
                       "Filtered3 text, "
                       "FlashBoardID4 integer, "
                       "Filtered4 text, "
                       "FlashBoardID5 integer, "
                       "Filtered5 text)");
    return check;
}
  return check;
}
bool Database::createAttachmentTable(){
    QSqlQuery newQ;
    bool check = false;
    if(db->isOpen()){
        //qDebug()<<"database opened";
    check = newQ.exec("create table Attachments "
                       "(AttachmentID integer primary key, "
                       "NewsFlashPostID integer, "
                       "FilePath text)");
    return check;
}
  return check;
}
bool Database::createFlashBoardTable(){
    QSqlQuery newQ;
    bool check = false;
    if(db->isOpen()){
        //qDebug()<<"database opened";
    check = newQ.exec("create table FlashBoard "
                       "(FlashBoardID integer primary key, "
                       "FlashBoard text)");
    return check;
}
  return check;
}
bool Database::createFlashSegmentTable(){
    QSqlQuery newQ;
    bool check = false;
    if(db->isOpen()){
        //qDebug()<<"database opened";
    check = newQ.exec("create table FlashSegment "
                       "(FlashSegmentID integer primary key, "
                       "Name text, "
                       "FlashBoardID integer)");
    return check;
}
  return check;
}

