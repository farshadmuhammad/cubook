#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "cupicture.h"
class UserProfile
{
public:
    UserProfile();

    int getUserID();
    QString getUserType();
    QString getNickname();
    QString getRealName();
    QString getLoginID();
    CUPicture getPicture();


    void setUserID(int a_user_id);
    void setUserType(QString a_user_type);
    void setNickname(QString a_nickname);
    void setRealname(QString a_realname);
    void setLoginID(QString a_loginid);
    void setPicture(CUPicture a_picture);


private:
    int user_id;
    QString user_type, nickname, realname, login_id;
    CUPicture picture;
};

#endif // USERPROFILE_H
