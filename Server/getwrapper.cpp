#include "getwrapper.h"

getWrapper::getWrapper()
{
 holder = new Filter;

}
void getWrapper::closeDatabase(){
    db->close();
    db->connectOptions();
    delete db;
    QSqlDatabase::removeDatabase("getconnect");

}

bool getWrapper::openDatabase(){
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE","getconnect"));
    db->setDatabaseName("CUBook");
    return db->open();
}

QList<QList<QString> > getWrapper::getFlashFeed(Filter *courses){
    QList<QString> Post;
    QList<QList<QString> > FlashFeed;
    openDatabase();
    bool check = false;
    int i = 0;
    int point;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "FlashBoard=%1 or FlashBoard=%2 "
                                  "or FlashBoard=%3 "
                                  "or FlashBoard=%4 "
                                  "or FlashBoard=%5")
                          .arg(courses->cID1).arg(courses->cID2)
                          .arg(courses->cID3).arg(courses->cID4)
                          .arg(courses->cID5));


        newQ.last();

        while(i<15){

            if(!newQ.isValid()){
                break;
            }
            Post.append(newQ.value(0).toString());
            Post.append(newQ.value(1).toString());
            Post.append(newQ.value(2).toString());
            Post.append(newQ.value(3).toString());
            Post.append(newQ.value(4).toString());
            Post.append(newQ.value(5).toString());
            Post.append(newQ.value(6).toString());

            FlashFeed.append(Post);
            Post.clear();
            i++;

            newQ.previous();

        }
        point = newQ.at();

        }
        Post.clear();


        QString pointer = "<po>";
           pointer += QString::number(point)+="</po>";
               Post.append(pointer);
               FlashFeed.append(Post);

        closeDatabase();
        return FlashFeed;
    }



QList<QList<QString> > getWrapper::getNewsFlashFive(Filter *courses, int pointer){
    QList<QString> Post;
    QList<QList<QString> > nextFiveP;
    int point;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "FlashBoard=%1 or FlashBoard=%2 "
                                  "or FlashBoard=%3 "
                                  "or FlashBoard=%4 "
                                  "or FlashBoard=%5")
                          .arg(courses->cID1).arg(courses->cID2)
                          .arg(courses->cID3).arg(courses->cID4)
                          .arg(courses->cID5));


        newQ.seek(pointer);


        while(i<5){

            if(!newQ.isValid()){
                break;
            }
            Post.append(newQ.value(0).toString());
            Post.append(newQ.value(1).toString());
            Post.append(newQ.value(2).toString());
            Post.append(newQ.value(3).toString());
            Post.append(newQ.value(4).toString());
            Post.append(newQ.value(5).toString());
            Post.append(newQ.value(6).toString());

            nextFiveP.append(Post);
            Post.clear();
            i++;

            newQ.previous();

        }

        point = newQ.at();
        }
        Post.clear();


        QString pointee = "<po>";
           pointee += QString::number(point)+="</po>";
               Post.append(pointee);
               nextFiveP.append(Post);

        closeDatabase();
        return nextFiveP;
    }

QList<QList<QString> > getWrapper::getFlashFeedSegment(int SegmentID){
    QList<QString> Post;
    QList<QList<QString> > FlashFeed;
    openDatabase();
    bool check = false;
    int i = 0;
    int point;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "FlashSegment=%1").arg(SegmentID));

        newQ.last();

        while(i<15){

            if(!newQ.isValid()){
                break;
            }
            Post.append(newQ.value(0).toString());
            Post.append(newQ.value(1).toString());
            Post.append(newQ.value(2).toString());
            Post.append(newQ.value(3).toString());
            Post.append(newQ.value(4).toString());
            Post.append(newQ.value(5).toString());
            Post.append(newQ.value(6).toString());

            FlashFeed.append(Post);
            Post.clear();
            i++;

            newQ.previous();

        }

           point = newQ.at();
        }
        Post.clear();


        QString pointer = "<po>";
           pointer += QString::number(point)+="</po>";
               Post.append(pointer);
               FlashFeed.append(Post);

        closeDatabase();
        return FlashFeed;
    }

QList<QList<QString> > getWrapper::getNewsFlashFiveSegment(int SegmentID, int pointer){
    QList<QString> Post;
    QList<QList<QString> > nextFiveP;
    openDatabase();
    bool check = false;
    int i = 0;
    int point;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "FlashSegment=%1")
                          .arg(SegmentID));


        newQ.seek(pointer);


        while(i<5){

            if(!newQ.isValid()){
                break;
            }
            Post.append(newQ.value(0).toString());
            Post.append(newQ.value(1).toString());
            Post.append(newQ.value(2).toString());
            Post.append(newQ.value(3).toString());
            Post.append(newQ.value(4).toString());
            Post.append(newQ.value(5).toString());
            Post.append(newQ.value(6).toString());

            nextFiveP.append(Post);
            Post.clear();
            i++;

            newQ.previous();

        }

         point = newQ.at();
        }
        Post.clear();


        QString pointee = "<po>";
           pointee += QString::number(point)+="</po>";
               Post.append(pointee);
               nextFiveP.append(Post);

        closeDatabase();
        return nextFiveP;
    }

QList<QList<QString> > getWrapper::getFlashFeedUser(int UserID){
    QList<QString> Post;
    QList<QList<QString> > FlashFeed;
    openDatabase();
    bool check = false;
    int i = 0;
    int point;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "UserID=%1").arg(UserID));

        newQ.last();

        while(i<15){

            if(!newQ.isValid()){
                break;
            }
            Post.append(newQ.value(0).toString());
            Post.append(newQ.value(1).toString());
            Post.append(newQ.value(2).toString());
            Post.append(newQ.value(3).toString());
            Post.append(newQ.value(4).toString());
            Post.append(newQ.value(5).toString());
            Post.append(newQ.value(6).toString());

            FlashFeed.append(Post);
            Post.clear();
            i++;

            newQ.previous();

        }

          point = newQ.at();
        }
        Post.clear();


        QString pointer = "<po>";
           pointer += QString::number(point)+="</po>";
               Post.append(pointer);
               FlashFeed.append(Post);

        closeDatabase();
        return FlashFeed;
    }

QList<QList<QString> > getWrapper::getNewsFlashFiveUser(int UserID, int pointer){
    QList<QString> Post;
    QList<QList<QString> > nextFiveP;
    openDatabase();
    bool check = false;
    int i = 0;
    int point;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "UserID=%1")
                          .arg(UserID));


        newQ.seek(pointer);


        while(i<5){

            if(!newQ.isValid()){
                break;
            }
            Post.append(newQ.value(0).toString());
            Post.append(newQ.value(1).toString());
            Post.append(newQ.value(2).toString());
            Post.append(newQ.value(3).toString());
            Post.append(newQ.value(4).toString());
            Post.append(newQ.value(5).toString());
            Post.append(newQ.value(6).toString());

            nextFiveP.append(Post);
            Post.clear();
            i++;

            newQ.previous();

        }
         point = newQ.at();

        }
        Post.clear();


        QString pointee = "<po>";
           pointee += QString::number(point)+="</po>";
               Post.append(pointee);
               nextFiveP.append(Post);

        closeDatabase();
        return nextFiveP;
    }

QList<QString> getWrapper::getNewsFlash(int PostID){
    QList<QString> Post;
    openDatabase();
    bool check = false;



    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "newsFlashID=%1").arg(PostID));

            newQ.seek(0);

            Post.append(newQ.value(0).toString());
            Post.append(newQ.value(1).toString());
            Post.append(newQ.value(2).toString());
            Post.append(newQ.value(3).toString());
            Post.append(newQ.value(4).toString());
            Post.append(newQ.value(5).toString());
            Post.append(newQ.value(6).toString());

        }
    closeDatabase();
    return Post;
}

QList<QString> getWrapper::getFlashBoard(int flashBoard){
    QList<QString> FlashBoard;
    openDatabase();
    bool check = false;



    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from FlashBoard where "
                                  "FlashBoardID=%1").arg(flashBoard));
        newQ.next();
        FlashBoard.append(newQ.value(0).toString());
        FlashBoard.append(newQ.value(1).toString());
    }
    closeDatabase();
    return FlashBoard;

}

QList<QString>  getWrapper::getSegmentsIDs(int flashBoard){
    QList<QString> Segment;

    openDatabase();
    bool check = false;



    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from FlashSegment where "
                                  "FlashBoardID=%1").arg(flashBoard));


        newQ.next();
        while(newQ.isValid()){

        Segment.append(newQ.value(0).toString());

        newQ.next();
    }
    }
    closeDatabase();
    return Segment;

}

QList<QString> getWrapper::getAttachments(int newsFlashPostID){
    QList<QString> Attachment;
    QList<QList<QString> >AttachmentList;
    openDatabase();
    bool check = false;



    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from Attachments where "
                                  "NewsFlashPostID=%1").arg(newsFlashPostID));


        //qDebug()<<newsFlashPostID;
        newQ.next();
        while(newQ.isValid()){

        Attachment.append(newQ.value(2).toString());
        newQ.next();
    }
    }
    closeDatabase();
    return Attachment;

}

QList<QString> getWrapper::getProfile(int userID){
    QList<QString> Profile;

    bool check = false;


    openDatabase();
    if(db->isOpen()){

        QSqlQuery newQ(*db);

        check = newQ.exec(QString("SELECT * from Users where "
                                  "UserId=%1").arg(userID));

        newQ.next();
        if (newQ.isValid()){
            Profile.append(newQ.value(0).toString());
            Profile.append(newQ.value(1).toString());
            Profile.append(newQ.value(2).toString());
            Profile.append(newQ.value(3).toString());
            Profile.append(newQ.value(4).toString());
        }

    }

    closeDatabase();
    return Profile;

}

QList<QString> getWrapper::getCourseList(int userID){
    QList<QString> CourseList;
    openDatabase();
    bool check = false;



    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from Filter where "
                                  "UserID=%1").arg(userID));
        newQ.next();
        if(newQ.isValid()){
        CourseList.append(newQ.value(2).toString());
        CourseList.append(newQ.value(4).toString());
        CourseList.append(newQ.value(6).toString());
        CourseList.append(newQ.value(8).toString());
        CourseList.append(newQ.value(10).toString());
        }
    }
    closeDatabase();
    return CourseList;

}

int getWrapper:: getNewsFlashID(int userID){
    int postID = 0;
    openDatabase();

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        newQ.exec(QString("SELECT * from NewsFlashPost where "
                                          "UserID=%1").arg(userID));
        newQ.last();
        if(newQ.isValid()){
            postID = newQ.value(0).toInt();
        }
    }
    closeDatabase();
    return postID;
}

QList<QString> getWrapper::getNewsFlashIDList(Filter *courses, int max){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where "
                                  "FlashBoard=%1 or FlashBoard=%2 "
                                  "or FlashBoard=%3 "
                                  "or FlashBoard=%4 "
                                  "or FlashBoard=%5")
                          .arg(courses->cID1).arg(courses->cID2)
                          .arg(courses->cID3).arg(courses->cID4)
                          .arg(courses->cID5));
        newQ.last();
        if(max == 0){
            while(newQ.isValid()) {
                IDs.append(newQ.value(0).toString());
                newQ.previous();
            }
        }
        else{
        while(newQ.isValid() && i < max){
            IDs.append(newQ.value(0).toString());
            newQ.previous();
            i++;
        }}

    }
    closeDatabase();
    return IDs;
}

QList<QString> getWrapper::getNewsFlashIDList(Filter *courses, int range_lte, int range_gte){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where newsFlashID between %6 and %7 and "
                                  "FlashBoard=%1 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%2 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%3 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%4 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%5")
                          .arg(courses->cID1).arg(courses->cID2)
                          .arg(courses->cID3).arg(courses->cID4)
                          .arg(courses->cID5).arg(range_gte).arg(range_lte));
        newQ.last();

        while(newQ.isValid()){
          IDs.append(newQ.value(0).toString());
          newQ.previous();

        }

    }
    closeDatabase();
    return IDs;
}

QList<QString> getWrapper::getNewsFlashIDList(Filter *courses, int range_lte, int range_gte, int max){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where newsFlashID between %6 and %7 and "
                                  "FlashBoard=%1 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%2 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%3 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%4 "
                                  "or newsFlashID between %6 and %7 and FlashBoard=%5")
                          .arg(courses->cID1).arg(courses->cID2)
                          .arg(courses->cID3).arg(courses->cID4)
                          .arg(courses->cID5).arg(range_gte).arg(range_lte));
        newQ.last();

        while(newQ.isValid() && i < max){
          IDs.append(newQ.value(0).toString());
          newQ.previous();
          i++;
        }

    }
    closeDatabase();
    return IDs;
}

QList<QString> getWrapper::getNewsFlashIDList(int user_id, int max){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where UserID=%1").arg(user_id));
        newQ.last();

        if(max == 0){
            while(newQ.isValid()) {
                IDs.append(newQ.value(0).toString());
                newQ.previous();
            }
        }
        else{
        while(newQ.isValid() && i < max){
            IDs.append(newQ.value(0).toString());
            newQ.previous();
            i++;
        }}

    }
    closeDatabase();
    return IDs;
 }

QList<QString> getWrapper::getNewsFlashIDList(int user_id, int range_lte, int range_gte){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where UserID=%1 and newsFlashID between %2 and %3")
                          .arg(user_id).arg(range_gte).arg(range_lte));
        newQ.last();

        while(newQ.isValid()){
            IDs.append(newQ.value(0).toString());
            newQ.previous();

        }

    }
    closeDatabase();
    return IDs;
 }
QList<QString> getWrapper::getNewsFlashIDList(int user_id, int range_lte, int range_gte, int max){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where UserID=%1 and newsFlashID between %2 and %3")
                          .arg(user_id).arg(range_gte).arg(range_lte));
        newQ.last();

        while(newQ.isValid()&& i< max){
            IDs.append(newQ.value(0).toString());
            newQ.previous();
             i++;
        }

    }
    closeDatabase();
    return IDs;
 }

QList<QString> getWrapper::getNewsFlashIDList(int segment_id, int flashboard_id, int max, QString a){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where FlashSegment=%1 and FlashBoard=%2").arg(segment_id)
                          .arg(flashboard_id));
        newQ.last();
        if(max == 0){
            while(newQ.isValid()) {
                IDs.append(newQ.value(0).toString());
                newQ.previous();
            }
        }
        else{
        while(newQ.isValid() && i < max){
            IDs.append(newQ.value(0).toString());
            newQ.previous();
            i++;
        }}

    }
    closeDatabase();
    return IDs;
 }

QList<QString> getWrapper::getNewsFlashIDList(int segment_id, int flashboard_id, int range_lte, int range_gte, QString a){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where FlashSegment=%1 and FlashBoard=%2 and newsFlashID between %3 and %4").arg(segment_id)
                          .arg(flashboard_id).arg(range_gte).arg(range_lte));
        newQ.last();
        while(newQ.isValid()){
            IDs.append(newQ.value(0).toString());
            newQ.previous();

        }

    }
    closeDatabase();
    return IDs;
 }
QList<QString> getWrapper::getNewsFlashIDList(int segment_id, int flashboard_id, int range_lte, int range_gte, int max, QString a){
    QList<QString> IDs;
    openDatabase();
    bool check = false;
    int i = 0;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where FlashSegment=%1 and FlashBoard=%2 and newsFlashID between %3 and %4").arg(segment_id)
                          .arg(flashboard_id).arg(range_gte).arg(range_lte));
        newQ.last();
        while(newQ.isValid() && i<max){
            IDs.append(newQ.value(0).toString());
            newQ.previous();
            i++;
        }

    }
    closeDatabase();
    return IDs;
 }

int getWrapper:: getAttachmentPointer(){
    bool check = false;
    openDatabase();
    int pointerV = 1;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("Select * from Attachments"));
        newQ.last();
        if(newQ.isValid()){
            pointerV = newQ.value(0).toInt();
        }
}
 closeDatabase();
 return pointerV;
}


QList<QString>  getWrapper::getSegment(int segmentID){
    QList<QString> Segment;

    openDatabase();
    bool check = false;



    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from FlashSegment where "
                                  "FlashSegmentID=%1").arg(segmentID));


        newQ.next();
        while(newQ.isValid()){

        Segment.append(newQ.value(0).toString());
        Segment.append(newQ.value(1).toString());
        Segment.append(newQ.value(2).toString());

        newQ.next();
    }
    }
    closeDatabase();
    return Segment;

}

QString getWrapper:: getUserProfPic(int userID){
    openDatabase();
    bool check = false;
    QString fp;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from Users where "
                                  "UserId=%1").arg(userID));
        newQ.next();
        if(newQ.isValid()){
           fp = newQ.value(4).toString();
        }
        return fp;
}
}

QList<QString> getWrapper:: getFilter(int user_id){
    openDatabase();
     bool check = false;
    QList<QString> fp;


    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from Filter where "
                                  "UserId=%1").arg(user_id));
        newQ.next();
        if(newQ.isValid()){
            fp.append(newQ.value(3).toString());
            fp.append(newQ.value(5).toString());
            fp.append(newQ.value(7).toString());
            fp.append(newQ.value(9).toString());
            fp.append(newQ.value(11).toString());
        }
        return fp;
}
}

QList<QString> getWrapper:: getLinks(int PostID){
    QList<QString> Links;
    openDatabase();
    bool check = false;



    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from Links where "
                                  "NewsFlashID=%1").arg(PostID));



        newQ.next();
        while(newQ.isValid()){

        Links.append(newQ.value(2).toString());
        newQ.next();
    }
    }
    closeDatabase();
    return Links;
}
