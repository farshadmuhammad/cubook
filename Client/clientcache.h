#ifndef CLIENTCACHE_H
#define CLIENTCACHE_H

#include <QImage>
#include <QList>
#include <QMap>
#include <QPicture>
#include <QPixmap>

#include "newsflash.h"
#include "flashboard.h"
#include "flashsegment.h"
#include "commmanager.h"


class clientCache
{
public:
    clientCache();
    ~clientCache();
    //General Functions
    void setup();//to be gotten rid of

    //Get Methods
    int getUserId();
    int getFlashFeedType();
    int getPosition();
    bool isStudent();
    bool isEmpty();
    QString getCurrentFlashFeedName();
    QString getName();
    QString getAvatar();
    QString getCourseID(QString course_name);
    NewsFlash getPost(int);
    CUPicture getPhoto();
    QList<FlashBoard> getCourseList();
    QList<FlashSegment> getSegmentList(QString segment_id);
    QList<QString> getPostIDs(int j, int k);
    QList<UserProfile> getProfileList();
    CommManager* getCommManager();
    UserProfile getTempProfile();
    QList<FlashBoard> getTempFilter();


    //Set Methods
    void setUserType(QString a_user_type);
    void setUserId(QString a_user_id);
    void setCurrentFlashFeedName(QString flash_feed_name);
    void setName(QString mName);
    void setAvatar(QString an_avatar);
    void setFlashFeedType(int type);
    void setPosition(int position);
    void addNewPost(NewsFlash post);
    void setFilter(QList<FlashBoard> course_list);
    void setCourseList(QList<FlashBoard> mFlashBoards);
    void setPhoto(CUPicture);
    void setProfile(UserProfile profile);
    void setPosts(QList<NewsFlash> postlist);
    void addMorePosts(QList<NewsFlash> postlist, bool top);
    void setAuthorIDs(QList<UserProfile> authorlist);
    void setTempProfile(UserProfile a_profile);
    void setTempFilter(QList<FlashBoard> a_filter);

    //Other Methods
    bool addSegment(QString course_id, FlashSegment);
    void addPostID(QString post_id);
    void removePost(int position);
    void removeSegment(QString course_id, QString segment_id );
    void clearPostIDs();










private:
    int userID;
    bool student; //keeps track of the type of user that this client is
    int flashFeedType; // keeps track of type of flash feed (0 = filter, 1 = segment, 2 = student)
    int position; // keeps track of where in the list of 15 post we are displaying (0-4 = 0, 5-9 = 1, 10-14 = 2)
    QString currentFlashFeedName;
    CUPicture profilePicture; //stores the profile picture
    UserProfile tempprofile;
    QList<FlashBoard> tempfilter;
    QString name;
    QString avatar;
    QList<UserProfile> author_list;
    QList<NewsFlash> posts; // 15 posts
    QList<QString> post_ids;
    QList<FlashBoard> flashBoards;
    CommManager *mComm;

};
#endif // CLIENTCACHE_H
