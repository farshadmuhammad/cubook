#include "newsflash.h"


NewsFlash::NewsFlash(){
    this->newsflash_id = 0;
    this->author_id = 0;
    this->flashboard_id = 0;
    this->segment_id = 0;
}

NewsFlash::NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id){
    this->newsflash_id = a_newsflash_id;
    this->author_id = a_author_id;
    this->flashboard_id = a_flashboard_id;
    this->segment_id = a_segment_id;
}
NewsFlash::NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text){
    this->newsflash_id = a_newsflash_id;
    this->author_id = a_author_id;
    this->flashboard_id = a_flashboard_id;
    this->segment_id = a_segment_id;
    text = post_text;
}

NewsFlash::NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text, QList<CUPicture> pics){
    this->newsflash_id = a_newsflash_id;
    this->author_id = a_author_id;
    this->flashboard_id = a_flashboard_id;
    this->segment_id = a_segment_id;
    text = post_text;
    pictures = pics;
}
NewsFlash::NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text, QList<CUUrl> links){
    this->newsflash_id = a_newsflash_id;
    this->author_id = a_author_id;
    this->flashboard_id = a_flashboard_id;
    this->segment_id = a_segment_id;
    text = post_text;
    urls = links;
}
NewsFlash::NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text, QList<CUPicture> pics, QList<CUUrl> links){
    this->newsflash_id = a_newsflash_id;
    this->author_id = a_author_id;
    this->flashboard_id = a_flashboard_id;
    this->segment_id = a_segment_id;
    text = post_text;
    pictures = pics;
    urls = links;
}


int NewsFlash::getNewsFlashID(){ return newsflash_id;}
int NewsFlash::getAuthorID(){ return author_id;}
int NewsFlash::getFlashBoardID(){ return flashboard_id;}
int NewsFlash::getSegmentID(){ return segment_id;}
QList<CUPicture> NewsFlash::getPictures(){ return pictures;}
QList<CUUrl> NewsFlash::getURLs(){ return urls;}
QString NewsFlash::getText(){return text;}

void NewsFlash::setNewsFlashID(int a_newsflashid){
    newsflash_id = a_newsflashid;
}
void NewsFlash::setAuthorID(int an_authorid){
    author_id = an_authorid;
}
void NewsFlash::setFlashBoardID(int a_flashboardid){
    flashboard_id = a_flashboardid;
}
void NewsFlash::setSegmentID(int a_segmentid){
    segment_id = a_segmentid;
}
void NewsFlash::addPicture(CUPicture a_picture){
    pictures.append(a_picture);
}
void NewsFlash::addURL(CUUrl a_url){
    urls.append(a_url);
}


void NewsFlash::setText(QString a_text){
    text = a_text;
}
