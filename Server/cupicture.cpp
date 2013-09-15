#include "cupicture.h"

CUPicture::CUPicture()
{
}


QString CUPicture::getFormat(){return format;}
const QImage& CUPicture::getPicture()const{return picture;}

void CUPicture::setFormat(QString a_format){
    format = a_format;
}

void CUPicture::setPicture(QImage a_picture){
    picture = a_picture;
}

QByteArray CUPicture::toBytes(){
    QByteArray ba;
    QBuffer buffer(&ba);
    if(format == "JPG" || format == "jpg")
    picture.save(&buffer, "JPG");
    if(format == "PNG" || format == "png")
    picture.save(&buffer, "PNG");
    if(format == "GIF" || format == "gif")
    picture.save(&buffer, "GIF");

    ////qDebug() << ba.size();
    ////qDebug() << ba;
    return ba.toBase64();
}
