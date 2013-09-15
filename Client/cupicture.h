#ifndef CUPICTURE_H
#define CUPICTURE_H

#include <QtGui/QImage>
#include <QBuffer>
class CUPicture
{
public:
    CUPicture();
    QString getFormat();
    QImage getPicture();

    void setFormat(QString a_format);
    void setPicture(QImage a_picture);

    QByteArray toBytes();
private:
    QString format;
    QImage picture;
};

#endif // CUPICTURE_H
