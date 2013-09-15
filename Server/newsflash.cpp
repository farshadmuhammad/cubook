#include "newsflash.h"

NewsFlash::NewsFlash(){
    newsflash_id = 0;
    author_id = 0;
    flashboard_id = 0;
    segment_id = 0;
    text = "";

}

NewsFlash::NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id){
    newsflash_id = a_newsflash_id;
    author_id = a_author_id;
    flashboard_id = a_flashboard_id;
    segment_id = a_segment_id;

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
void NewsFlash::setText(QString s_text){
    text = s_text;
}
