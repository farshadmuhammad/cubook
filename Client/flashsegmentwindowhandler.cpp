#include "flashsegmentwindowhandler.h"

FlashSegmentWindowHandler::FlashSegmentWindowHandler(QObject *parent) :
    QObject(parent)
{
    connect(mWindow.ui->classList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(itemChanged(QListWidgetItem*, QListWidgetItem*)));
    connect(mWindow.ui->okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mWindow.ui->addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(mWindow.ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    connect(mWindow.ui->viewButton, SIGNAL(clicked()), this, SLOT(viewButtonClicked()));
}
void FlashSegmentWindowHandler::run(clientCache *cache){
    mCache = cache;


    //connect(mCache->getCommManager(), SIGNAL(segmentDeletedReplySignal(bool)), this, SLOT(deleteSegmentReturn(bool)));
    connect(mCache->getCommManager(), SIGNAL(newSegmentSignal(bool)), this, SLOT(addSegmentUpdate(bool)));
    connect(mCache->getCommManager(), SIGNAL(segmentDeletedSignal(bool)),this, SLOT(deleteSegmentUpdate(bool)));
    connect(mCache->getCommManager(), SIGNAL(getPostsSegmentSignal(bool)),this,SLOT(changeReply(bool)));

    if(mCache->isStudent()){
	mWindow.ui->deleteButton->hide();
    }
    QList<FlashBoard> mCourseList = mCache->getCourseList();
    foreach(FlashBoard mCourse, mCourseList){
	new QListWidgetItem(mCourse.getName(), mWindow.ui->classList);
    }
    mWindow.ui->classList->setCurrentRow(0);

    mWindow.exec();
}
void FlashSegmentWindowHandler::itemChanged(QListWidgetItem *current, QListWidgetItem *old){
    old = old;
    mWindow.ui->segmentList->clear();
    qDebug()<< current->text();
    QList<FlashSegment> mSegmentList = mCache->getSegmentList(mCache->getCourseID(current->text()));
    foreach(FlashSegment mSegment, mSegmentList){
	new QListWidgetItem(mSegment.getName(), mWindow.ui->segmentList);
    }
    mWindow.ui->segmentList->setCurrentRow(0);
}
void FlashSegmentWindowHandler::okButtonClicked(){
    change();
}
void FlashSegmentWindowHandler::addButtonClicked(){
    bool ok;
    QString text = QInputDialog::getText(&mWindow, tr("Flash Segment"), tr("Enter a flash segment name:"),
					 QLineEdit::Normal,  tr(""),  &ok );

    if( ok && !text.isEmpty() )
    {
	if(segmentExsists(text)){
	    QMessageBox errBox;
	    errBox.setWindowTitle("Error");
	    errBox.setText("Segment name already exists");
	    errBox.exec();
	}
	else{
	    FlashSegment mSegment;
	    mSegment.setName(text);
            foreach(FlashBoard mCourse, mCache->getCourseList()){
                if(mCourse.getName() == mWindow.ui->classList->currentItem()->text())
                    mSegment.setFlashboardID(mCourse.getFlashboardID());
            }
	    mCache->getCommManager()->newSegment(mSegment);
	}
    }
}

void FlashSegmentWindowHandler::addSegmentUpdate(bool success){
    if(!success){
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("Addition unsuccessful");
        errBox.exec();
    }
    else{
        mWindow.ui->segmentList->clear();
        QList<FlashSegment> mSegmentList = mCache->getSegmentList(mCache->getCourseID(mWindow.ui->classList->currentItem()->text()));
        foreach(FlashSegment mSegment, mSegmentList){
            new QListWidgetItem(mSegment.getName(), mWindow.ui->segmentList);
        }
        mWindow.ui->segmentList->setCurrentRow(0);
    }
}

bool FlashSegmentWindowHandler::segmentExsists(QString segment_name){
    foreach(FlashBoard mCourse, mCache->getCourseList()){
	if(mCourse.getName() == mWindow.ui->classList->currentItem()->text()){
	    foreach(FlashSegment mSegment, mCourse.getSegments()){
		if(mSegment.getName() == segment_name)
		    return true;
	    }
	}
    }
    return false;
}

void FlashSegmentWindowHandler::deleteButtonClicked(){
    if(mWindow.ui->segmentList->count() != 0){
	foreach(FlashBoard mCourse, mCache->getCourseList()){
	    foreach(FlashSegment mSegment, mCache->getSegmentList(QString::number(mCourse.getFlashboardID()))){
		if(mSegment.getName() == mWindow.ui->segmentList->currentItem()->text())
                    mCache->getCommManager()->segmentDeleted(QString::number(mSegment.getSegmentID()));
	    }
	}
    }
}

void FlashSegmentWindowHandler::deleteSegmentUpdate(bool success){
    if (success){
        mWindow.ui->segmentList->clear();

        QList<FlashSegment> mSegmentList = mCache->getSegmentList(mCache->getCourseID(mWindow.ui->classList->currentItem()->text()));
        foreach(FlashSegment mSegment, mSegmentList){
            new QListWidgetItem(mSegment.getName(), mWindow.ui->segmentList);
        }
        mWindow.ui->segmentList->setCurrentRow(0);
    }
    else{
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("Deletion unsuccessful");
        errBox.exec();
    }
}

void FlashSegmentWindowHandler::viewButtonClicked(){
    if(mWindow.ui->segmentList->count() != 0){

        foreach(FlashBoard mFlashboard, mCache->getCourseList()){
            foreach(FlashSegment mSegment, mFlashboard.getSegments()){
                if (mSegment.getName() == mWindow.ui->segmentList->currentItem()->text())
                    //mCache->getCommManager()->getNewsFlashIDs(mSegment);
                    changeReply(true);
            }
        }
    }
    else{
	QMessageBox errBox;
	errBox.setWindowTitle("Error");
	errBox.setText("No segment selected to view");
	errBox.exec();
    }
}

void FlashSegmentWindowHandler::changeReply(bool success){
    if(success){
        mCache->setCurrentFlashFeedName(mWindow.ui->segmentList->currentItem()->text());
        mCache->setFlashFeedType(1);
        change();
    }
    else{
        QMessageBox errBox;
        errBox.setWindowTitle("Error");
        errBox.setText("Segment is error");
        errBox.exec();
    }
}

void FlashSegmentWindowHandler::change(){
    mWindow.hide();
    WindowControl::changeWindow(WindowControl::FLASHFEED_PAGE, mCache);
}
