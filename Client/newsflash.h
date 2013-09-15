#ifndef NEWSFLASH_H
#define NEWSFLASH_H

#include <QList>
#include <QtGui/QImage>
#include "cupicture.h"
#include "cuurl.h"


class NewsFlash
{
public:
    NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id);
    NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text);
    NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text, QList<CUPicture> pics);
    NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text, QList<CUUrl> links);
    NewsFlash(int a_newsflash_id, int a_author_id, int a_flashboard_id, int a_segment_id, QString post_text, QList<CUPicture> pics, QList<CUUrl> links);
    NewsFlash();

    int getNewsFlashID() ;
    int getAuthorID() ;
    int getFlashBoardID() ;
    int getSegmentID() ;
    QList<CUPicture> getPictures();
    QList<CUUrl> getURLs();
    QString getText() ;



    void setNewsFlashID(int a_newsflashid);
    void setAuthorID(int an_authorid);
    void setFlashBoardID(int a_flashboardid);
    void setSegmentID(int a_segmentid);
    void setText(QString);
    void addPicture(CUPicture a_picture);
    void addURL(CUUrl a_url);

private:
    int newsflash_id, author_id, flashboard_id, segment_id;
    QString text;
    QList<CUPicture> pictures;
    QList<CUUrl> urls;
};

#endif // NEWSFLASH_H
