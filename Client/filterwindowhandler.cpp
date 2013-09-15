#include "filterwindowhandler.h"

FilterWindowHandler::FilterWindowHandler(QObject *parent) :
    QObject(parent)
{
    connect(mWindow.ui->allButton, SIGNAL(clicked()), this, SLOT(allButtonClicked()));
    connect(mWindow.ui->addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(mWindow.ui->removeButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));
    connect(mWindow.ui->noneButton, SIGNAL(clicked()), this, SLOT(noneButtonClicked()));
    connect(mWindow.ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(mWindow.ui->saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));

}
void FilterWindowHandler::run(clientCache *cache){
    mCache = cache;

    connect(mCache->getCommManager(), SIGNAL(updateFilterSignal(bool)), this, SLOT(updatedFilter(bool)));
    QList<FlashBoard> mFilteredCourse;
    QList<FlashBoard> mUnfilter;


    foreach(FlashBoard mCourse, mCache->getCourseList()){
	if(!mCourse.isFiltered())
	    mUnfilter.append(mCourse);
        else{
	    mFilteredCourse.append(mCourse);
            mFilter.append(mCourse);
        }
    }


    foreach(FlashBoard mCourse, mUnfilter){
	new QListWidgetItem(mCourse.getName(), mWindow.ui->unfilteredList);
    }
    mWindow.ui->unfilteredList->setCurrentRow(0);
    foreach(FlashBoard mCourse, mFilteredCourse){
	new QListWidgetItem(mCourse.getName(), mWindow.ui->filteredList);
    }
    mWindow.ui->filteredList->setCurrentRow(0);
    mWindow.exec();
}
void FilterWindowHandler::allButtonClicked(){

    mWindow.ui->unfilteredList->clear();
    mWindow.ui->filteredList->clear();
    foreach(FlashBoard mCourse, mCache->getCourseList()){
	new QListWidgetItem(mCourse.getName(), mWindow.ui->filteredList);
    }
    mWindow.ui->filteredList->setCurrentRow(0);
    mFilter = mCache->getCourseList();
    
}
void FilterWindowHandler::addButtonClicked(){
    if(mWindow.ui->unfilteredList->count() != 0){

	QListWidgetItem *item = mWindow.ui->unfilteredList->takeItem(mWindow.ui->unfilteredList->currentRow());
	mWindow.ui->filteredList->addItem(item);

	mWindow.ui->filteredList->setCurrentRow(0);

	foreach(FlashBoard mFlashBoard, mCache->getCourseList()){
	    if(mFlashBoard.getName() == item->text())
		mFilter.append(mFlashBoard);
	}
    }
}
void FilterWindowHandler::removeButtonClicked(){

    if(mWindow.ui->filteredList->count() != 0){

	QListWidgetItem *item = mWindow.ui->filteredList->takeItem(mWindow.ui->filteredList->currentRow());
	mWindow.ui->unfilteredList->addItem(item);

	mWindow.ui->unfilteredList->setCurrentRow(0);


	for(int i = 0; i < mFilter.size(); i++){
	    if(mFilter.value(i).getName() == item->text()) {
		mFilter.removeAt(i);
	    }
	}
    }
}
void FilterWindowHandler::noneButtonClicked(){
    mWindow.ui->unfilteredList->clear();
    mWindow.ui->filteredList->clear();
    foreach(FlashBoard mCourse, mCache->getCourseList()){
	new QListWidgetItem(mCourse.getName(), mWindow.ui->unfilteredList);
    }
    mWindow.ui->unfilteredList->setCurrentRow(0);
    mFilter.clear();
}
void FilterWindowHandler::cancelButtonClicked(){
    change();
}
void FilterWindowHandler::saveButtonClicked(){
    if(mWindow.ui->filteredList->count() != 0){


	mCache->getCommManager()->updateFilter(mFilter);
    }
    else{
	QMessageBox errBox;
	errBox.setWindowTitle("Error");
	errBox.setText("You cannot have an empty filter");
	errBox.exec();
    }
}
void FilterWindowHandler::updatedFilter(bool updated){
    if(updated){
	mCache->setFlashFeedType(0);
	mCache->setCurrentFlashFeedName("Flash Feed");

	change();
    }
    else{
	QMessageBox errBox;
	errBox.setWindowTitle("Error");
	errBox.setText("Data not saved please try again");
	errBox.exec();
    }
}

void FilterWindowHandler::change(){
    mWindow.hide();
    WindowControl::changeWindow(WindowControl::FLASHFEED_PAGE, mCache);
}
