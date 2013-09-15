#include "flashfeedwindowhandler.h"

FlashFeedWindowHandler::FlashFeedWindowHandler(QObject *parent) :
    QObject(parent)
{
    connect(mWindow.ui->homeButton,SIGNAL(clicked()),this, SLOT(goHome()));
    connect(mWindow.ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(mWindow.ui->menuComboBox,SIGNAL(currentIndexChanged(int)),this, SLOT(menu(int)));
    connect(mWindow.ui->firstPostTextBrowser_3, SIGNAL(selectionChanged()), this, SLOT(postOneSelect()));
    connect(mWindow.ui->secondPostTextBrowser_3, SIGNAL(selectionChanged()), this, SLOT(postTwoSelect()));
    connect(mWindow.ui->thirdPostTextBrowser_3, SIGNAL(selectionChanged()), this, SLOT(postThreeSelect()));
    connect(mWindow.ui->fourthPostTextBrowser_3, SIGNAL(selectionChanged()), this, SLOT(postFourSelect()));
    connect(mWindow.ui->fifthPostTextBrowser_3, SIGNAL(selectionChanged()), this, SLOT(postFiveSelect()));
    connect(mWindow.ui->firstPostDeleteToolButton_3, SIGNAL(clicked()), this, SLOT(postOneDeleteButton()));
    connect(mWindow.ui->secondPostDeleteToolButton_3, SIGNAL(clicked()), this, SLOT(postTwoDeleteButton()));
    connect(mWindow.ui->thirdPostDeleteToolButton_3, SIGNAL(clicked()), this, SLOT(postThreeDeleteButton()));
    connect(mWindow.ui->fourthPostDeleteToolButton_3, SIGNAL(clicked()), this, SLOT(postFourDeleteButton()));
    connect(mWindow.ui->fifthPostDeleteToolButton_3, SIGNAL(clicked()), this, SLOT(postFiveDeleteButton()));
    connect(mWindow.ui->previousPostsButton_3, SIGNAL(clicked()), this, SLOT(previous()));
    connect(mWindow.ui->nextPostsButton_3, SIGNAL(clicked()), this, SLOT(next()));
    connect(mWindow.ui->attachComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(attachmentMenu(int)));
    connect(mWindow.ui->sendButton, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));
    connect(mWindow.ui->viewProfileButton, SIGNAL(clicked()), this, SLOT(viewUserButton()));

}

void FlashFeedWindowHandler::run(clientCache *cache){
    mCache = cache;
    connect(mCache->getCommManager(),SIGNAL(logoutSignal(bool)),this,SLOT(logoutReply(bool)));
    connect(mCache->getCommManager(), SIGNAL(updateProfileUpdateSignal(bool)),this,SLOT(updateProfileUpdate(bool)));
    connect(mCache->getCommManager(), SIGNAL(newNewsFlashSignal(bool)),this,SLOT(newPostReply(bool)));
    if(mCache->isStudent()){ //If we are a student
	mWindow.ui->viewProfileButton->hide();
	mWindow.ui->firstPostDeleteToolButton_3->hide();
	mWindow.ui->secondPostDeleteToolButton_3->hide();
	mWindow.ui->thirdPostDeleteToolButton_3->hide();
	mWindow.ui->fourthPostDeleteToolButton_3->hide();
	mWindow.ui->fifthPostDeleteToolButton_3->hide();
    }

    //Flash Board
    if(mCache->getFlashFeedType() == 0){
	foreach(FlashBoard mCourse, mCache->getCourseList()){
	    if(mCourse.isFiltered())
		mWindow.ui->courseComboBox->addItem(mCourse.getName());
	}
	mWindow.ui->profInfoTextBrowser->hide();
    }

    //Flash Segment
    else if(mCache->getFlashFeedType() == 1){
	mWindow.ui->courseComboBox->hide();
	mWindow.ui->profInfoTextBrowser->hide();
    }

    //Student's Personal
    else if(mCache->getFlashFeedType() == 2){
       mWindow.ui->newPostTextEdit->hide();
       mWindow.ui->attachComboBox->hide();
       mWindow.ui->courseComboBox->hide();
       mWindow.ui->sendButton->hide();
       QString userinfo;
       foreach(UserProfile tProfile, mCache->getProfileList()){
	   if(tProfile.getRealName() == mCache->getCurrentFlashFeedName()){
	       userinfo.append(tProfile.getRealName() + "\n");
	       if(tProfile.getUserType() == "true"){
		   userinfo.append(tProfile.getNickname() + "\n");
	       }
	       userinfo.append(tProfile.getUserID());
	   }
       }
    }

    mWindow.ui->segmentNameLabel->setText(mCache->getCurrentFlashFeedName()); //Set the label of what we are currently viewing

    //Set the icon to the user's profile photo
    mWindow.ui->homeButton->setIcon(QIcon(QPixmap::fromImage(mCache->getPhoto().getPicture())));


    loadPosts();
    mCache->setPosition(0);

    mWindow.exec();
}



void FlashFeedWindowHandler::displayPosts(bool success){
    qDebug()<<"Success";
    if (success){


    }
    else{
        qDebug() << "Something failed in Display Posts";
        WindowControl::changeWindow();
    }
}

//Slots
void FlashFeedWindowHandler::goHome(){
    mCache->setFlashFeedType(0);
    mCache->setCurrentFlashFeedName("Flash Feed");
    mWindow.hide();
    WindowControl::changeWindow(2, mCache);
}

void FlashFeedWindowHandler::logout(){
    mCache->getCommManager()->logout();
}

void FlashFeedWindowHandler::logoutReply(bool success){
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


void FlashFeedWindowHandler::menu(int index){
    if (index == 1)
    {
        mWindow.hide();
	WindowControl::changeWindow(WindowControl::PROFILE_PAGE,mCache);
    }
    else if (index == 2){
        mWindow.hide();
	WindowControl::changeWindow(WindowControl::FILTER_PAGE, mCache);
    }
    else if (index == 3){
        mWindow.hide();
	WindowControl::changeWindow(WindowControl::FLASHSEGMENT_PAGE, mCache);
    }
}
void FlashFeedWindowHandler::postOneSelect(){
    readPost(mCache->getPost(0));
}

void FlashFeedWindowHandler::postTwoSelect(){
    readPost(mCache->getPost(1));

}

void FlashFeedWindowHandler::postThreeSelect(){
    readPost(mCache->getPost(2));

}

void FlashFeedWindowHandler::postFourSelect(){
    readPost(mCache->getPost(3));

}

void FlashFeedWindowHandler::postFiveSelect(){
    readPost(mCache->getPost(4));

}
void FlashFeedWindowHandler::postOneDeleteButton(){
    mCache->getCommManager()->newsFlashDeleted(QString::number(mCache->getPost(0).getNewsFlashID()));
}

void FlashFeedWindowHandler::postTwoDeleteButton(){
    mCache->getCommManager()->newsFlashDeleted(QString::number(mCache->getPost(1).getNewsFlashID()));

}

void FlashFeedWindowHandler::postThreeDeleteButton(){
    mCache->getCommManager()->newsFlashDeleted(QString::number(mCache->getPost(2).getNewsFlashID()));

}

void FlashFeedWindowHandler::postFourDeleteButton(){
    mCache->getCommManager()->newsFlashDeleted(QString::number(mCache->getPost(3).getNewsFlashID()));

}

void FlashFeedWindowHandler::postFiveDeleteButton(){
    mCache->getCommManager()->newsFlashDeleted(QString::number(mCache->getPost(4).getNewsFlashID()));

}

void FlashFeedWindowHandler::previous(){
    if(mCache->getPosition() == 0){
	QMessageBox errBox;
	errBox.setWindowTitle("Error");
	errBox.setText("You are already at the newest news flashes");
	errBox.exec();
    }
    else if(mCache->getPosition() == 1){
	mCache->setPosition(0);
	loadPosts();
    }
    else if(mCache->getPosition() == 2){
	mCache->setPosition(1);
	loadPosts();
    }
}
void FlashFeedWindowHandler::next(){
    if(mCache->getPosition() == 0){
	mCache->setPosition(1);
	loadPosts();
    }
    else if(mCache->getPosition() == 1){
	mCache->setPosition(2);
	loadPosts();
    }
    else if(mCache->getPosition() == 2){
	QMessageBox errBox;
	errBox.setWindowTitle("Error");
	errBox.setText("You are already at the oldest news flashes");
	errBox.exec();
    }
}

void FlashFeedWindowHandler::attachmentMenu(int index){
    if (index == 1)
    {
	QString fileName = QFileDialog::getOpenFileName(&mWindow,
             tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.gif)"));

        QFile t(fileName);
        QFileInfo k(t);

        QString ext = k.completeSuffix();
        QImage uploaded_photo;
        uploaded_photo.load(fileName);

        CUPicture temp;
        temp.setPicture(uploaded_photo);
        temp.setFormat(ext);
	tPictures.append(temp);
	mWindow.ui->attachedFilesLabel->setText(QString::number(tPictures.size() + tUrls.size()) +" File(s) Attached");
	mWindow.ui->attachComboBox->setCurrentIndex(0);
    }

    if (index == 2)
    {
	bool ok;
	QString text = QInputDialog::getText(&mWindow, tr("Attach Link"), tr("Enter the link:"),
					     QLineEdit::Normal,  tr(""),  &ok );

	CUUrl temp;
	QUrl url;
	url.setUrl(text);
	temp.setLink(url);
	tUrls.append(temp);
	mWindow.ui->attachedFilesLabel->setText(QString::number(tPictures.size() + tUrls.size()) +" File(s) Attached");
	mWindow.ui->attachComboBox->setCurrentIndex(0);
    }
}

void FlashFeedWindowHandler::newPostReply(bool success){
    if(success){
        tPictures.clear();
        tUrls.clear();
        mWindow.ui->newPostTextEdit->setPlainText("");
        mWindow.ui->courseComboBox->setCurrentIndex(0);
        loadPosts();
    }
    else{
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("News Flash could not be saved");
        errBox.exec();
    }
}

void FlashFeedWindowHandler::sendButtonClicked(){
    if(mWindow.ui->courseComboBox->currentIndex() == 0){
	QMessageBox errBox;
	errBox.setWindowTitle("Error");
	errBox.setText("You have not selected a course");
	errBox.exec();
    }
    else{
	NewsFlash temp;
	temp.setText(mWindow.ui->newPostTextEdit->toPlainText());
	foreach(CUPicture mPic, tPictures){
	    temp.addPicture(mPic);
	}
	foreach(CUUrl mUrl, tUrls){
	    temp.addURL(mUrl);
	}
	if(mCache->getFlashFeedType() == 0){
	    foreach(FlashBoard mCourse, mCache->getCourseList()){
		if(mCourse.getName() == mWindow.ui->courseComboBox->currentText())
		    temp.setFlashBoardID(mCourse.getFlashboardID());
	    }
	}
	else if(mCache->getFlashFeedType() == 1){
	    foreach(FlashBoard mCourse, mCache->getCourseList()){
		foreach(FlashSegment mSegment, mCourse.getSegments()){
		    if(mSegment.getName() == mCache->getCurrentFlashFeedName()){
			temp.setSegmentID(mSegment.getSegmentID());
			temp.setFlashBoardID(mCourse.getFlashboardID());
		    }
		}
	    }
	}
	temp.setAuthorID(mCache->getUserId());
	mCache->getCommManager()->newNewsFlash(temp);
    }
}
void FlashFeedWindowHandler::viewUserButton(){
    QString text = mWindow.ui->postBrowser->toPlainText();
    NewsFlash temp;

    mCache->setFlashFeedType(2);
    if(text == formatText(mCache->getPost(0), true)){
        temp = mCache->getPost(0);
    }
    else if(text == formatText(mCache->getPost(1), true)){
        temp = mCache->getPost(1);
    }
    else if(text == formatText(mCache->getPost(2), true)){
        temp = mCache->getPost(2);
    }
    else if(text == formatText(mCache->getPost(3), true)){
        temp = mCache->getPost(3);
    }
    else if(text == formatText(mCache->getPost(4), true)){
        temp = mCache->getPost(4);
    }
    else{
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("You have not selected a news flash");
        errBox.exec();
        return;
    }
    foreach(UserProfile mProfile, mCache->getProfileList()){
        if(temp.getAuthorID() == mProfile.getUserID()){
            mCache->setCurrentFlashFeedName(mProfile.getRealName());
            //mCache->getCommManager()->getNewsFlashIDs(mProfile.getUserID());
        }
    }


    mWindow.hide();
    WindowControl::changeWindow(2, mCache);

}

void FlashFeedWindowHandler::updateProfileUpdate(bool success){
    mWindow.ui->homeButton->setIcon(QIcon(QPixmap::fromImage(mCache->getPhoto().getPicture())));
    loadPosts();
}




//Functions used by this class

QString FlashFeedWindowHandler::formatText(NewsFlash newsflash, bool full_version){
    QString temp;
    if(!full_version){
	if (newsflash.getPictures().size()+newsflash.getURLs().size() > 0)
	    temp.append("(attach)");
    }
    foreach(UserProfile mProfile, mCache->getProfileList()){
        if(mProfile.getUserID() == newsflash.getAuthorID()){
            if(mProfile.getUserType() == "student")
                temp.append(mProfile.getNickname());
            else
                temp.append(mProfile.getRealName());

        }
    }


    temp.append(" says: ");
    //int i = temp.length();
    temp.append(newsflash.getText());
    if(!full_version && temp.length() > 80){
        temp.resize(80);
	temp.append("...");
    }
    return temp;
}
void FlashFeedWindowHandler::loadPosts(){
    //Get 5 posts

    mWindow.ui->firstPostTextBrowser_3->setText(formatText(mCache->getPost(0), false));
    mWindow.ui->secondPostTextBrowser_3->setText(formatText(mCache->getPost(1), false));
    mWindow.ui->thirdPostTextBrowser_3->setText(formatText(mCache->getPost(2), false));
    mWindow.ui->fourthPostTextBrowser_3->setText(formatText(mCache->getPost(3), false));
    mWindow.ui->fifthPostTextBrowser_3->setText(formatText(mCache->getPost(4), false));
}
void FlashFeedWindowHandler::readPost(NewsFlash selected_post){
    //sets the text to be seen
    mWindow.ui->postBrowser->setText(formatText(selected_post, true));



    //sets the  picture attachments to be seen

    scene = new QGraphicsScene;

    QSize size = mWindow.ui->attachedGraphicsView->size();
    scene->setSceneRect(0,0,20 ,2000);

    int j = 0;
    int x = 0;

    for(int i = 0; i < selected_post.getPictures().size(); i++){
	if (j % 2 == 0){
	    j = 0;
	    x++;
        }
        qDebug() << "Problem?";
	QPixmap fPic = QPixmap::fromImage(selected_post.getPictures()[i].getPicture());
        QGraphicsPixmapItem *mItem = scene->addPixmap(fPic.scaled(50,50));
	mItem->setPos(5 + (j*50) ,-45 + (x*50));
        j++;
    }

    scene->setSceneRect(0,0,size.width(),(scene->sceneRect().height() - 150));
    mWindow.ui->attachedGraphicsView->setScene(scene);

     //sets the  url attachments to be seen
    mWindow.ui->urlBrowser->clear();
    for(int i = 0; i < selected_post.getURLs().size(); i++){
	if(i == 0){
	    mWindow.ui->urlBrowser->setPlainText(selected_post.getURLs()[i].getLink().toString());
	}
	else{
	    mWindow.ui->urlBrowser->setPlainText(mWindow.ui->urlBrowser->toPlainText().append("\n" + selected_post.getURLs()[i].getLink().toString()));
	}
    }

}
