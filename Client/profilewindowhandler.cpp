#include "profilewindowhandler.h"
#include "QFileDialog"
#include "QMessageBox"
#include "userprofile.h"

ProfileWindowHandler::ProfileWindowHandler(QObject *parent) :
    QObject(parent)
{
    connect(mWindow.ui->homeButton,SIGNAL(clicked()),this, SLOT(goHome()));
    connect(mWindow.ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(mWindow.ui->uploadButton,SIGNAL(clicked()), this, SLOT(upload()));
    connect(mWindow.ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(mWindow.ui->saveButton, SIGNAL(clicked()), this, SLOT(save()));


}
void ProfileWindowHandler::run(clientCache *cache){
    mCache = cache;
    connect(mCache->getCommManager(), SIGNAL(logoutSignal(bool)), this, SLOT(logoutReply(bool)));
    connect(mCache->getCommManager(), SIGNAL(updateProfileUpdateSignal(bool)),this, SLOT(change(bool)));
    connect(mCache->getCommManager(), SIGNAL(updateProfileReplySignal(bool)), this, SLOT(updateReply(bool)));
    QImage mPic;
    mPic.load(":/pics/default.jpeg"); //Load the default image
    if(mCache->getPhoto().getPicture().isNull()){
	//If there is no picture loaded in from client's profile load defualt
	mWindow.ui->homeButton->setIcon(QIcon(QPixmap::fromImage(mPic)));
    }
    else{
	//load their picture
	mWindow.ui->homeButton->setIcon(QIcon(QPixmap::fromImage(mCache->getPhoto().getPicture())));
    }
    if(mCache->isStudent()){
	//If its a student
	mWindow.ui->iDLabel->setText("Student ID");
	mWindow.ui->editTextField->setText(mCache->getAvatar());

    }
    else{
	//It's a professor
	mWindow.ui->iDLabel->setText("Instructor ID:");
	mWindow.ui->editLabel->hide(); //Label that says avatar
	mWindow.ui->editTextField->hide(); //Text Field that says you can edit your avatar
    }
    QString id;
    id.setNum(mCache->getUserId());
    mWindow.ui->iDTextField->setText(id);
    mWindow.ui->nameTextField->setText(mCache->getName());//Real Name
    mWindow.exec();
}
bool ProfileWindowHandler::firstTimeSaved(){
    if((mCache->getAvatar().isEmpty() && mCache->isStudent())){
	errorBox();
	return false;
    }
    return true;
}
void ProfileWindowHandler::errorBox(){
    QMessageBox errBox;
    errBox.setWindowTitle("Error");
    errBox.setText("Please fill in your Avatar name");
    errBox.exec();
}
void ProfileWindowHandler::goHome(){
    if(firstTimeSaved()){
	mCache->setFlashFeedType(0);
	mCache->setCurrentFlashFeedName("Flash Feed");
	mWindow.hide();
	WindowControl::changeWindow(WindowControl::FLASHFEED_PAGE, mCache);
    }
}
void ProfileWindowHandler::logout(){
    mCache->getCommManager()->logout();
   //
}

void ProfileWindowHandler::logoutReply(bool success){
    if(success){
        mWindow.hide();
        WindowControl::changeWindow();
    }
    else{
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("Logout Failed for some reason.");
        errBox.exec();
    }
}

void ProfileWindowHandler::upload(){
    QString fileName = QFileDialog::getOpenFileName(&mWindow,
         tr("Open Image"), tr("/home"), tr("Image Files (*.png *.jpg *.gif)"));
    QFile t(fileName);
    QFileInfo k(t);

    ext = k.completeSuffix();
    uploaded_photo.load(fileName);
    mWindow.ui->homeButton->setIcon(QIcon(QPixmap::fromImage(uploaded_photo)));
}
void ProfileWindowHandler::cancel(){
    if(firstTimeSaved()){
	mWindow.hide();
	WindowControl::changeWindow(WindowControl::FLASHFEED_PAGE, mCache);
    }
}
void ProfileWindowHandler::save(){
    if(!(mWindow.ui->editTextField->text().isEmpty()) || !mCache->isStudent()){
	UserProfile profile;
	if(mCache->isStudent()){
	    if(mCache->getAvatar() != mWindow.ui->editTextField->text()){

		profile.setNickname(mWindow.ui->editTextField->text());
	    }
	}
	CUPicture temp;
        if(!uploaded_photo.isNull())
            temp.setPicture(uploaded_photo);


        temp.setFormat(ext);
        profile.setPicture(temp);

        if(!profile.getPicture().getPicture().isNull() || !profile.getNickname().isEmpty())
            mCache->getCommManager()->updateProfile(profile);
        else{
            change(true);
        }
    }
    else{
	errorBox();
    }
}
void ProfileWindowHandler::change(bool recieved){
    if(recieved){
	mWindow.hide();
	WindowControl::changeWindow(WindowControl::FLASHFEED_PAGE, mCache);
    }
}

void ProfileWindowHandler::updateReply(bool success){
    if (!success){
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("Data not saved please try again");
        errBox.exec();
    }
}
