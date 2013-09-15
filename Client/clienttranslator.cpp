#include "clienttranslator.h"

ClientTranslator::ClientTranslator()
{
}



const QString ClientTranslator::CONTENTS = "CONTENTS";
const QString ClientTranslator::UNRECOGNIZED = "UNRECOGNIZED";
const QString ClientTranslator::UNAVAILABLE = "UNAVAILABLE";
const QString ClientTranslator::UNAUTHORIZED = "UNAUTHORIZED";

//GENERAL
 QString ClientTranslator::getMessageName(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);
     return doc.firstChildElement().tagName();
 }

 QString ClientTranslator::getMessageType(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);
     return doc.firstChildElement().attribute("type");
 }

 QString ClientTranslator::getMessageCategory(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);
     return doc.firstChildElement().attribute("category");
 }



 bool ClientTranslator::isValidXML(QByteArray message){
     message = message;
    return true;
 }

//REPLIES

 QList<FlashBoard> ClientTranslator::processGetBoardListReply(QByteArray message){
    QList<FlashBoard> flashboardlist;
    QDomDocument doc;
    doc.setContent(message);
    //qDebug() << "Entering get board list reply";

    //QList<QString> flashboards = getMessageElementList(doc, "flashboard", "flashboard_id");
   // qDebug() << flashboards;
    QDomElement flashboard = doc.firstChildElement().firstChildElement(); //Skip reply, go straight to flashboard.
    while(!flashboard.isNull()){
        int flashboard_id = flashboard.attribute("flashboard_id").toInt();
        QDomElement name = flashboard.firstChildElement();
        QString namedata = name.firstChild().nodeValue();
        QDomElement segments = name.nextSiblingElement();
        QDomElement segment = segments.firstChildElement();

        FlashBoard temp(flashboard_id, namedata, true);

        while(!segment.isNull()){
            FlashSegment seg;
            seg.setSegmentID(segment.attribute("segment_id").toInt());
            seg.setName(segment.attribute("Name"));
            seg.setFlashboardID(flashboard_id);
            segment = segment.nextSiblingElement();
            temp.addSegment(seg);
        }
        QDomElement filtered = segments.nextSiblingElement();
        if (filtered.attribute("visible") == "true")
            temp.setFiltered(true);
        else
            temp.setFiltered(false);

        flashboardlist.append(temp);
        flashboard = flashboard.nextSiblingElement();
    }

    return flashboardlist;
 }
 QList<NewsFlash> ClientTranslator::processGetNewsflashesReply(QByteArray message){
    QList<NewsFlash> newsflashes;
    QDomDocument doc;
    doc.setContent(message);



    QList<QString> texts = getMessageElementNodeList(doc,"text");
    QList<QString> nfIDs = getMessageElementList(doc,"newsflash","newsflash_id");
    QList<QString> auIDs = getMessageElementList(doc,"newsflash","author_id");
    QList<QString> seIDs = getMessageElementList(doc,"newsflash","segment_id");
    QList<QString> fbIDs = getMessageElementList(doc,"newsflash","flashboard_id");


    QDomElement newsflash = doc.firstChildElement().firstChildElement().firstChildElement();
    while(!newsflash.isNull()){
        NewsFlash hold;
        hold.setAuthorID(newsflash.attribute("author_id").toInt());
        hold.setFlashBoardID(newsflash.attribute("flashboard_id").toInt());
        hold.setNewsFlashID(newsflash.attribute("newsflash_id").toInt());
        hold.setSegmentID(newsflash.attribute("segment_id").toInt());
        hold.setText(newsflash.firstChildElement().firstChild().nodeValue().append(QString::number(hold.getNewsFlashID())));

        //Get Pictures
        QDomElement pictures = newsflash.firstChildElement().nextSiblingElement();
        QDomElement picture = pictures.firstChildElement();
        while(!picture.isNull()){
            CUPicture temp;
            QImage tempimg;
            QByteArray bindata;
            temp.setFormat(picture.attribute("format"));

            if(!temp.getFormat().isEmpty()){

                bindata.append(picture.firstChildElement().firstChild().nodeValue());
                //qDebug() << QByteArray::fromBase64(bindata).size();
                if(tempimg.loadFromData(QByteArray::fromBase64(bindata), "JPEG")){
                    temp.setPicture(tempimg);
                    hold.addPicture(temp);
                }
            }
            picture = picture.nextSiblingElement();
        }
        //Get Links

        QDomElement links = pictures.nextSiblingElement();
        QDomElement link = links.firstChildElement();
        while(!link.isNull()){
            CUUrl temp;
            QDomElement url = link.firstChildElement();


            temp.setLink(url.firstChild().nodeValue());
            temp.setPageName(url.nextSibling().firstChild().nodeValue());

            hold.addURL(temp);
            link = link.nextSiblingElement();
        }
        //Advance to the next news flash
        newsflashes.append(hold);
        newsflash = newsflash.nextSiblingElement();
    }
    //qDebug() << "We can stop here";
    return newsflashes;
 }
 QList<UserProfile> ClientTranslator::processGetProfilesReply(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);
     //qDebug()<<message;
     UserProfile hold;
     QList<UserProfile> profiles;
     //QList<QString> texts = getMessageElementNodeList(doc,"text");
     QList<QString> user_ids = getMessageElementList(doc,"profile","user_id");
     QList<QString> user_types = getMessageElementList(doc,"profile","user_type");
     QList<QString> nickname = getMessageElementNodeList(doc,"nickname");
     QList<QString> realnames = getMessageElementNodeList(doc,"realname");
     QList<QString> login_ids = getMessageElementNodeList(doc,"login_id");
     QList<QString> pictures = getMessageElementNodeList(doc,"binarydata");
     QList<QString> extensions = getMessageElementList(doc,"picture","format");
  //   qDebug() << "Extensions: " << extensions.size();
   //  qDebug() << pictures.size();
     QString name = getMessageElement(doc,"binarydata");

     for(int i =0; i<user_ids.size();i++){
          hold.setLoginID(login_ids[i]);
          hold.setNickname(nickname[i]);
          hold.setRealname(realnames[i]);
          hold.setUserID(user_ids[i].toInt());
          hold.setUserType(user_types[i]);
          QByteArray bindata;
          bindata.append(pictures[i]);
          QImage img;

          img.loadFromData(QByteArray::fromBase64(bindata),"JPG");
          if (!img.isNull()){
              CUPicture temp;
              temp.setFormat(extensions[i]);
              temp.setPicture(img);
              hold.setPicture(temp);
          }
          else{
              CUPicture temp;
              temp.setPicture(QImage(":/pics/default.jpeg"));
              temp.setFormat("JPEG");
              hold.setPicture(temp);
          }

         profiles.append(hold);
     }

    return profiles;
 }
 QString ClientTranslator::processAuthenticateReply(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);
     QString user_id;
     user_id = getMessageAttribute(doc, "user","user_id");
     //TO DO

     return user_id;
 }

 QList<QString> ClientTranslator::processGetNewsflashIDsReply(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);

     QList<QString> newsflash_ids = getMessageElementList(doc,"newsflash","newsflash_id");



    return newsflash_ids;
 }

 int ClientTranslator::processRequestSucceededReply(QByteArray message){
    QDomDocument doc;
    doc.setContent(message);
     int id = 0;
      id = getRootMessageAttribute(doc,"id").toInt();

    return id;
 }
 QString ClientTranslator::processRequestFailedReply(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);
     QString exception = getRootMessageAttribute(doc,"exception");

     return exception;



 }

//UPDATES

 NewsFlash ClientTranslator::processNewNewsflashUpdate(QByteArray message){
     NewsFlash newsflash;
     QDomDocument doc;
     doc.setContent(message);
     int nfID = getMessageAttribute(doc,"newsflash","newsflash_id").toInt();
     int auID = getMessageAttribute(doc,"newsflash","author_id").toInt();
     int seID = getMessageAttribute(doc,"newsflash","segment_id").toInt();
     int fbID = getMessageAttribute(doc,"newsflash","flashboard_id").toInt();
     QString text = getMessageElement(doc,"text");
     newsflash.setAuthorID(auID);
     newsflash.setFlashBoardID(fbID);
     newsflash.setSegmentID(seID);
     newsflash.setNewsFlashID(nfID);
     newsflash.setText(text);
     //qDebug()<<newsflash.getAuthorID()<<newsflash.getNewsFlashID()<<newsflash.getText();

     return newsflash;

 }
 FlashSegment ClientTranslator::processNewSegmentUpdate(QByteArray message){
    FlashSegment segment;
    QDomDocument doc;
    doc.setContent(message);
    int seg_id = getMessageAttribute(doc,"segment", "segment_id").toInt();
    int fbID = getMessageAttribute(doc,"segment","flashboard_id").toInt();
    QString name =getMessageAttribute(doc,"segment","name");
    segment.setFlashboardID(fbID);
    segment.setName(name);
    segment.setSegmentID(seg_id);
    return segment;
 }


 UserProfile ClientTranslator::processProfileUpdateUpdate(QByteArray message){
     UserProfile profile;
     QDomDocument doc;
     doc.setContent(message);
     int userID = getMessageAttribute(doc,"profile", "user_id").toInt();
     QString name = getMessageElement(doc,"realname");
     QString nickname = getMessageElement(doc,"nickname");
     QString ext = getMessageAttribute(doc,"picture","format");
     QByteArray picture;
     picture.append( getMessageElement(doc,"binarydata"));
     QString type = getMessageAttribute(doc,"profile","user_type");
     QImage pichold;
     if(ext == "JPG"){
         pichold.loadFromData(QByteArray::fromBase64(picture), "JPG");
         //qDebug()<<pichold.size();
     }
     if(ext == "PNG"){
         pichold.loadFromData(QByteArray::fromBase64(picture), "PNG");
         //qDebug()<<pichold.size();
     }
     if(ext == "GIF"){
         pichold.loadFromData(QByteArray::fromBase64(picture), "GIF");
         //qDebug()<<pichold.size();
     }
   CUPicture profpic;
   profpic.setPicture(pichold);
   profpic.setFormat(ext);
   profile.setNickname(nickname);
   profile.setUserID(userID);
   profile.setRealname(name);
   profile.setUserType(type);
   profile.setPicture(profpic);

   return profile;
 }


 int ClientTranslator::processNewsflashDeletedUpdate(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);

     int newsflash_id = getMessageAttribute(doc,"newsflash","newsflash_id").toInt();


     return newsflash_id;
 }

 int ClientTranslator::processSegmentDeletedUpdate(QByteArray message){
     QDomDocument doc;
     doc.setContent(message);
     int segment_id = getMessageAttribute(doc,"segment","segment_id").toInt();


    return segment_id;
 }

 QString ClientTranslator::getMessageAttribute(QDomDocument a, QString element, QString attribute){
     QDomElement root = a.firstChildElement();
     QDomNodeList items = root.elementsByTagName(QString("%1").arg(element));
     QDomNode itemnode = items.at(0);
     QDomElement itemele = itemnode.toElement();
     return itemele.attribute(QString("%2").arg(attribute));


 }
 QString ClientTranslator::getMessageElement(QDomDocument doc, QString ele){

     QDomElement root = doc.firstChildElement();
      QDomNodeList items = root.elementsByTagName(ele);
      QDomNode textData = items.at(0).firstChild();
      //qDebug()<<textData.nodeValue();

      return textData.nodeValue();

 }
 QList<QString> ClientTranslator::getMessageElementList(QDomDocument doc, QString element, QString attribute){
     QList<QString> Elements;
     QDomElement root = doc.firstChildElement();
     QDomNodeList items = root.elementsByTagName(QString("%1").arg(element));
     for(int i = 0; i < items.size(); i++){
     QDomNode itemnode = items.at(i);
     QDomElement itemele = itemnode.toElement();
     Elements.append(itemele.attribute(QString("%2").arg(attribute)));
     }

    return Elements;

 }
 QList<QString> ClientTranslator::getMessageElementNodeList(QDomDocument doc, QString ele){
     QList<QString> NodeElements;
     QDomElement root = doc.firstChildElement();
      QDomNodeList items = root.elementsByTagName(ele);
      for(int i = 0; i<items.size(); i++){
      QDomNode textData = items.at(0).firstChild();
      //qDebug()<<textData.nodeValue();
      NodeElements.append(textData.nodeValue());
      }
      return NodeElements;

 }
 QString ClientTranslator::getRootMessageAttribute(QDomDocument doc, QString att){
     return doc.firstChildElement().attribute(att);
 }
