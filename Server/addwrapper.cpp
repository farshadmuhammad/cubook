#include "addwrapper.h"



addWrapper::addWrapper()
{

    //db->open();

}
bool addWrapper::openDatabase(){
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE","addconnect"));
    db->setDatabaseName("CUBook");
    return db->open();
}
void addWrapper::closeDatabase(){
    db->close();
    delete db;
    QSqlDatabase::removeDatabase("addconnect");
}

bool addWrapper::addUser(int userID, QString avaName, QString name, int accType, QString Photo){
    openDatabase();
    bool check = false;
     QSqlQuery newQ(*db);
    if(db->isOpen()){

        ////qDebug()<<"Database is open for writing";
        check = newQ.exec(QString("insert into Users values(%1,'%2','%3',%4,'%5')")
                          .arg(userID).arg(avaName).arg(name).arg(accType).arg(Photo));
        closeDatabase();
        return check;
    }
    closeDatabase();
    return check;
}
bool addWrapper::addNewsFlashPost(QString newsFlash, int FlashBoard, int userID,
                          int flashSegmentID, int Attachment, QString date){
    int postID;
    openDatabase();
    bool check = false;
     QSqlQuery newQ(*db);
    if(db->isOpen()){
        newQ.exec("SELECT * from NewsFlashPost");
        newQ.last();
        if(newQ.isValid()){
            postID = newQ.value(0).toInt();
            postID++;

        }
        else{
            postID = 1;
        }
        //qDebug()<<"Database is open for writing";
        check = newQ.exec(QString("insert into NewsFlashPost values(%1,'%2',%3,%4,%5,%6,'%7')")
                          .arg(postID).arg(newsFlash)
                          .arg(FlashBoard).arg(userID).arg(flashSegmentID)
                          .arg(Attachment).arg(date));
        //qDebug()<<postID;
        //qDebug()<<check;
        closeDatabase();
        return check;
    }
    closeDatabase();
    return check;
}

bool addWrapper::addFlashBoard(int flashBoardID, QString flashBoardName){
    bool check = false;
    openDatabase();
    QSqlQuery newQ(*db);
    if(db->isOpen()){

        //qDebug()<<"Database is open for writing";
        check = newQ.exec(QString("insert into FlashBoard values(%1, '%2')")
                          .arg(flashBoardID).arg(flashBoardName));
        closeDatabase();
        return check;
    }
    closeDatabase();
    return check;
}

bool addWrapper::addFilter(int filterID, int userID, int flashBoardID1,
                           int flashBoardID2, int flashBoardID3,
                           int flashBoardID4, int flashBoardID5){
    openDatabase();
    bool check = false;
     QSqlQuery newQ(*db);
    if(db->isOpen()){

        //qDebug()<<"Database is open for writing";
        check = newQ.exec(QString("insert into Filter values(%1, %2,%3,%4,%5,%6,%7)")
                          .arg(filterID).arg(userID).arg(flashBoardID1)
                          .arg(flashBoardID2).arg(flashBoardID3).arg(flashBoardID4)
                          .arg(flashBoardID5));
        closeDatabase();
        return check;
    }
    closeDatabase();
    return check;
}

bool addWrapper::addFlashSegment(int flashSegmentID, QString flashSegmentName,
                                  int flashBoardID){
    int segID;
    openDatabase();
    bool check = false;
     QSqlQuery newQ(*db);
    if(db->isOpen()){
      newQ.exec(QString("SELECT * from FlashSegment"));
      newQ.last();
      if(newQ.isValid()){
        segID =  newQ.value(0).toInt();
        segID++;
        //qDebug()<<"Database is open for writing";
        check = newQ.exec(QString("insert into FlashSegment values(%1,'%2',%3)")
                          .arg(segID).arg(flashSegmentName)
                          .arg(flashBoardID));

    }}
    closeDatabase();
    return check;
}

bool addWrapper::addAttachments(int attachmentID, int newsFlashPostID, QString fileP){
    openDatabase();
    bool check = false;
     QSqlQuery newQ(*db);
    if(db->isOpen()){

        //qDebug()<<"Database is open for writing";
        check = newQ.exec(QString("insert into Attachments values(%1,%2,'%3')")
                          .arg(attachmentID).arg(newsFlashPostID)
                          .arg(fileP));
        closeDatabase();
        return check;
        }
    closeDatabase();
    return check;
}
bool addWrapper::addLinks(int newsFlashPostID, QString Link){
    openDatabase();
    bool check = false;
     QSqlQuery newQ(*db);
     int Linkp;
    if(db->isOpen()){

        //qDebug()<<"Database is open for writing";
        newQ.exec(QString("Select * from Links"));
        newQ.last();
        if(newQ.isValid()){
            Linkp = newQ.value(0).toInt();
            Linkp++;
        }
        else{
            Linkp = 1;
        }
        check = newQ.exec(QString("insert into Links values(%1,%2,'%3')")
                          .arg(Linkp).arg(newsFlashPostID)
                          .arg(Link));

        }
    closeDatabase();
    return check;
}
