#include "loginwindowhandler.h"

LoginWindowHandler::LoginWindowHandler(QObject *parent) :
    QObject(parent)
{
    mCache = new clientCache;
    connect(mWindow.ui->loginButton,SIGNAL(clicked()),this, SLOT(login()));
    connect(mCache->getCommManager(),SIGNAL(loginSignal(bool)),this, SLOT(getProfiles(bool)));
    connect(mCache->getCommManager(),SIGNAL(getProfilesSignal(bool)),this, SLOT(getBoardList(bool)));
    connect(mCache->getCommManager(),SIGNAL(getBoardListSignal(bool)),this, SLOT(getPosts(bool)));
    connect(mCache->getCommManager(), SIGNAL(getPostsLoginSignal(bool)), this, SLOT(change(bool)));
}
void LoginWindowHandler::run(){
    mWindow.exec();
}

void LoginWindowHandler::login(){
    //Function called upon clicking the login button

    //Create a new Cache for the client
    QString login_text = mWindow.ui->userIDLineEdit->text();
    qDebug() << login_text;

    //Check to make sure it is a long int
    if (login_text.toULong())
	mCache->getCommManager()->login(login_text);
    else{
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("Login Failed: Improper Login ID");
        errBox.exec();
    }

}

//Step 2, Login complete: Get Profiles is next
void LoginWindowHandler::getProfiles(bool success){
    if(!success){
        qDebug() << "Login was not in the database";
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("Login Failed: Login ID Not Found or Login ID in use.");
        errBox.exec();
        mWindow.ui->userIDLineEdit->setText("");

    }
    else{
        //Get the user's profile
        QList<QString> temp;
        temp.append(QString::number(mCache->getUserId()));

        mCache->getCommManager()->getProfiles(temp);
        //mCache->getCommManager()->getBoardList();
    }

}

//Profile receieved, get filter
void LoginWindowHandler::getBoardList(bool success){
    if(!success){
        qDebug() << "Error in reading profile";
        return;
    }
    mCache->getCommManager()->getBoardList();

}


void LoginWindowHandler::getPosts(bool success){
    if(!success){
        qDebug() << "Error in reading Course List";
        return;
    }
    QList<QString> flashboard_ids;
    foreach(FlashBoard temp, mCache->getCourseList()){
        if(temp.isFiltered())
            flashboard_ids.append(QString::number(temp.getFlashboardID()));
    }

    mCache->getCommManager()->getNewsFlashIDs(flashboard_ids);
}






void LoginWindowHandler::change(bool success){
    if(success){


        mCache->setup();///change this DO NOT KEEP THIS !!!!!!




	//If user id was returned (successful login)
        mWindow.hide();
	if(mCache->getAvatar().isEmpty() && mCache->isStudent()){
	    //If the user is a student, and has not set their avatar yet we go to the profile page
	    WindowControl::changeWindow(WindowControl::PROFILE_PAGE, mCache);
	}
	else {
	    //Otherwise user has logged in before, or is a instructor, proceed to main page
	    WindowControl::changeWindow(WindowControl::FLASHFEED_PAGE, mCache);
	}
    }

}
