#include "clientcache.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>


//CONSTRUCTOR
/************************************************************************/
clientCache::clientCache()
{

    mComm = new CommManager();
    mComm->setClientCache(this);
    flashFeedType = 0;
    position = 0;
    currentFlashFeedName = "Flash Feed";

  //  mComm->login("1234");
}
//DESTRUCTOR
/************************************************************************/
clientCache::~clientCache(){}


//TO BE REMOVED
/************************************************************************/
void clientCache::setup(){



}





//GET METHODS
/************************************************************************/
bool clientCache::isStudent(){return student;}
int clientCache::getUserId(){return userID;}
int clientCache::getFlashFeedType(){return flashFeedType;}
QString clientCache::getCurrentFlashFeedName(){return currentFlashFeedName;}
QString clientCache::getName(){return name;}
QString clientCache::getAvatar(){return avatar;}
QList<FlashBoard> clientCache::getCourseList(){return flashBoards;}
QList<UserProfile> clientCache::getProfileList(){return author_list;}
NewsFlash clientCache::getPost(int in){return posts.at(in + position*5);}
UserProfile clientCache::getTempProfile(){return tempprofile;}
QList<FlashSegment> clientCache::getSegmentList(QString course_id){
    QList<FlashSegment> temp;

    foreach(FlashBoard mCourse, flashBoards){
        if(QString::number(mCourse.getFlashboardID()) == course_id){
            temp = mCourse.getSegments();
        }
    }
    return temp;
}
CUPicture clientCache::getPhoto(){return profilePicture;}
int clientCache::getPosition(){return position;}




CommManager* clientCache::getCommManager(){return mComm;}



QString clientCache::getCourseID(QString course_name){
    foreach(FlashBoard mCourse, flashBoards){
        if(mCourse.getName() == course_name){
            return QString::number(mCourse.getFlashboardID());
        }
    }
    return "";
}
QList<QString> clientCache::getPostIDs(int j, int k){
    QList<QString> temp;

    if (j > k){
        //qDebug() << "Range is improper, J > K";
        return post_ids;
    }
    if (j > post_ids.size() || k > post_ids.size() || k < 0 || j < 0){
        //qDebug() << "Out of bounds in getting post ids";
        return post_ids;
    }
    if (j == k && j == 0)
        return post_ids;
    for (int i = j; j < k; i++){
        temp.append(post_ids[i]);
    }
    return temp;
}
QList<FlashBoard> clientCache::getTempFilter(){return tempfilter;}

//SET METHODS
/************************************************************************/
void clientCache::setUserType(QString a_user_type){
    if(a_user_type == "student")
        student = true;
    else
        student = false;
}
void clientCache::setUserId(QString a_user_id){userID = a_user_id.toInt();}
void clientCache::setCurrentFlashFeedName(QString flash_feed_name){currentFlashFeedName = flash_feed_name;}
void clientCache::setFlashFeedType(int type){flashFeedType = type;}
void clientCache::setAvatar(QString an_avatar){avatar = an_avatar;}
void clientCache::setName(QString mName){name = mName;}
void clientCache::addNewPost(NewsFlash post){post = post;}
void clientCache::setCourseList(QList<FlashBoard> mFlashBoards){
    flashBoards.clear();
    for (int i=0; i<mFlashBoards.size();i++){
        flashBoards.append(mFlashBoards[i]);

    }
    return;
}
void clientCache::setPosts(QList<NewsFlash> postlist){
    posts = postlist;
}
void clientCache::addMorePosts(QList<NewsFlash> postlist, bool top){
    if (top){
        postlist = postlist;
    //    posts = postlist.append(posts);
    }
    else{
   //     posts.append(postlist);
    }
}

void clientCache::setPosition(int pos){position = pos;}
void clientCache::setPhoto(CUPicture in){profilePicture = in;}
bool clientCache::isEmpty(){
    if(!userID == 0){
        return false;
    }
    return true;
}

void clientCache::setFilter(QList<FlashBoard> course_list ){
    for(int i = 0; i < flashBoards.size(); i++){
        flashBoards[i].setFiltered(false);

        for(int j = 0; j < course_list.size(); j++){
            if (flashBoards.value(i).getName() == course_list.value(j).getName()){
                flashBoards[i].setFiltered(true);
            }
        }
    }
}
void clientCache::setProfile(UserProfile a_profile){
        setUserType(a_profile.getUserType());
        setName(a_profile.getRealName());
        setAvatar(a_profile.getNickname());
        setPhoto(a_profile.getPicture());

}
void clientCache::setAuthorIDs(QList<UserProfile> authorlist){
    author_list = authorlist;
}
void clientCache::setTempProfile(UserProfile a_profile){
    tempprofile = a_profile;
}
void clientCache::setTempFilter(QList<FlashBoard> a_filter){
    tempfilter = a_filter;
}

//SEGMENTS AND NEWS FLASHES
/************************************************************************/
void clientCache::removePost(int position){
    posts.removeAt(position);
}

bool clientCache::addSegment(QString course, FlashSegment segmentName){
   /* FlashSegment temp;
    temp.setName(segmentName.getName());

    foreach(FlashBoard mCourse, flashBoards){
        if(mCourse.getName() == course){
            mCourse.addSegment(temp);
        }
    }*/
    course = course;
    segmentName = segmentName;

    return true;
}

void clientCache::addPostID(QString post_id){
    post_ids.append(post_id);
}

void clientCache::removeSegment(QString course, QString segmentName){


    foreach(FlashBoard mCourse, flashBoards){
        if(mCourse.getName() == course){
            foreach(FlashSegment mSegment, mCourse.getSegments()){
                if(mSegment.getName() == segmentName)
                    mCourse.removeSegment(mSegment);
            }
        }
    }
}


void clientCache::clearPostIDs(){
    post_ids.clear();
}
