#ifndef CUPICTURE_H
#define CUPICTURE_H
#include <QImageWriter>
#include <QImage>
#include <QBuffer>
#include <QDebug>
#include <QDataStream>
class CUPicture
{
public:
    CUPicture();
    QString getFormat();
    const QImage& getPicture()const;

    void setFormat(QString a_format);
    void setPicture(QImage a_picture);

    QByteArray toBytes();
private:
    QString format;
    QImage picture;
};

#endif // CUPICTURE_H
