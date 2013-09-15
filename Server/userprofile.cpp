#include "userprofile.h"

UserProfile::UserProfile()
{
    user_id = 0;
}


int UserProfile::getUserID(){return user_id;}
QString UserProfile::getUserType(){return user_type;}
QString UserProfile::getNickname(){return nickname;}
QString UserProfile::getRealName(){return realname;}
QString UserProfile::getLoginID(){return login_id;}
CUPicture UserProfile::getPicture(){return picture;}

void UserProfile::setUserID(int a_user_id){
    user_id = a_user_id;
}

void UserProfile::setUserType(QString a_user_type){
    user_type = a_user_type;
}

void UserProfile::setNickname(QString a_nickname){
    nickname = a_nickname;
}

void UserProfile::setRealname(QString a_realname){
    realname = a_realname;
}

void UserProfile::setLoginID(QString a_loginid){
    login_id = a_loginid;
}

void UserProfile::setPicture(CUPicture a_picture){
    picture = a_picture;
}
