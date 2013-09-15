#include "messagetranslator.h"
//this translator receives and parses XML files from the server and forms a
//reply that the client will be able to decipher.

//constructor for the translator, this inititalizes an API, which accesses database wrapers for queries.
MessageTranslator::MessageTranslator()
    {
        api = new SQLApi;
        userID = 0;
    }


//This function checks the type of XML received and sends the xml file to its respective translator to be processed.
//All the translator functions return a byte array holding the reply to be sent to the client
QByteArray MessageTranslator:: checkXML(QByteArray message, QByteArray& update, int * a_user_id){
    QDomDocument doc;
    doc.setContent(message);
    QString type = getMessageType(doc);


    //qDebug()<<type;
    if(type == "request"){

        QString rootAtt = getRootMessageAttribute(doc,"type");
        //qDebug()<<rootAtt;


          if(rootAtt == "Authenticate"){
            return processAuthReq(message, a_user_id);
          }

          if(rootAtt == "CreateNewsFlash"){
             return processNewsFlashCreation(message, update, *a_user_id);
          }

          if(rootAtt == "DeleteSegment"){
             return processDelFlashSegm(message, update);
          }

          if(rootAtt == "DeleteNewsflash"){
              return processDelNewsFlash(message, update);
          }
          if(rootAtt == "CreateSegment"){
              return processCreateSegment(message, update);
          }

          if(rootAtt == "GetNewsflashIDs"){
              return processGetNewsFlashIDs(message);
          }

          if(rootAtt == "GetProfiles"){
              return processGetProfileReq(message);
          }

          if(rootAtt == "GetNewsflashes"){
              return processGetNewsFlash(message);
          }

          if(rootAtt == "GetBoardList"){

              return processGetBoardList(*a_user_id);
          }

          if(rootAtt == "UpdateProfile"){

             return processUpdateProfile(message,*a_user_id,update);
          }

          if(rootAtt == "Unauthenticate"){

             return processUnauthenticate(message, *a_user_id);
          }
          if(rootAtt == "FilterBoard"){
              return processUpdateFilter(message, *a_user_id);
          }
    }
    return message;
    }

// Processes a request for authentication, (Log in)
QByteArray MessageTranslator:: processAuthReq(QByteArray message, int *a_user_id){

    //Put the message received into a QDomDocument then uses the QDomDocument functionality to parse the XML byte array
      QDomDocument doc;
      doc.setContent(message);


      QList<QString> profile;
      int ID = getMessageAttribute(doc, "loginid", "username").toInt();

      //SQL query to check is the client exists in database.
      profile = api->get->getProfile(ID);

     UserProfile user;

     //creates a intermediate user profile to be sent back to the server if client exists.
     if(profile.size()>0){
         user.setUserID(profile.at(0).toInt());
         userID = user.getUserID();
         *a_user_id = userID;
         user.setNickname(profile.at(1));
         user.setRealname(profile.at(2));
         user.setUserType(profile.at(3));
         QString fp = QDir::currentPath();
          fp.append(profile[4]);
         QFile file (fp);
         QFileInfo fil(file);
         QString ext = fil.completeSuffix();
         //qDebug()<<ext;
         QImage pic(fp);
         //qDebug()<<pic.size();

         CUPicture pichold;
         pichold.setPicture(pic);
         pichold.setFormat(ext);
             QByteArray userP = MessageProtocol::createAuthenticateReply(user);
             return userP;
         }
     //returns an error message if user was not found in the database
    return MessageProtocol::createRequestFailedReply(MessageProtocol::UNAVAILABLE);
}

//processes a request for getting profiles from the client and creates an appropriate reply to be sent back to the client
QByteArray MessageTranslator:: processGetProfileReq(QByteArray message){

    //Put the message received into a QDomDocument then uses the QDomDocument functionality to parse the XML byte array
    QDomDocument doc;
    doc.setContent(message);

     //declares lists for holding information.
     QList<UserProfile> usero;
     QList<QString> profile;
     QList<QString> profileids;
     profileids = getMessageElementList(doc,"user","user_id");

     //loops through the XML information parsed, makes queries and creates a list of User Profile to be sent back to the client
    for(int i = 0; i<profileids.size(); i++){

        //SQL query for getting profiles
        profile = api->get->getProfile(profileids[i].toInt());

            //setting information into a User Profile object
            UserProfile user;
            user.setUserID(profile.at(0).toInt());
            user.setNickname(profile.at(1));
            user.setRealname(profile.at(2));
            if(profile.at(3)=="1")
                user.setUserType("instructor");
            else
                user.setUserType("student");

                //Setting file path and getting the profile image from database and flat file.
                QDir dir = QDir::currentPath();
                QString fp = dir.path();
                fp.append(profile[4]);

                QImageReader reader;
                reader.setFileName(fp);
                QFileInfo fil(fp);
                QString ext = fil.completeSuffix();
                QImage picture(fp);
                //qDebug()<<picture.size();

    //putting image into a CUpicture object, setting the CUpicture object into the user.
    CUPicture newPic;
    newPic.setPicture(picture);
    newPic.setFormat(ext);
    user.setPicture(newPic);

    //inserting the created user into a list of users.
    usero.append(user);


                }

        if(!usero.isEmpty()){
            //creates a reply according to the message protocol to be sent to client of the user profiles found
            QByteArray reply = MessageProtocol::createGetProfilesReply(usero);

            return reply;

        }

    //returns an error message if user was not found
    return MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
}

//processes creation of newsflashes and returns the appropriate XML reply to be sent to client
QByteArray MessageTranslator::processNewsFlashCreation(QByteArray message, QByteArray &update, int user_id){
    //qDebug()<<"OMGGGGGGGGGGGGGGGGGGGG";
    //Put the message received into a QDomDocument then uses the QDomDocument functionality to parse the XML byte array
    QDomDocument doc;
    doc.setContent(message);

    //inserts all information obtained from the XML request into lists.
    int FlashBoardID = getMessageAttribute(doc,"newsflash","flashboard_id").toInt();
    int FlashSegmentID = getMessageAttribute(doc,"newsflash","segment_id").toInt();
    QString text = getMessageElement(doc,"text");
    QList<QByteArray> pictures = getMessageNodeElementList(doc,"binarydata");
    int Attach;

    if(pictures.size() > 0)
        Attach = 1;
    else
        Attach = 0;

    QString Date = QDateTime::currentDateTime().toString();

    //creates a temp Post to be parsed as an XML reply for client
    NewsFlash Post;
    Post.setAuthorID(user_id);
    Post.setFlashBoardID(FlashBoardID);
    Post.setSegmentID(FlashSegmentID);
    QList<QString> exts = getMessageElementList(doc,"picture","format");
    QList<QString> Links = getMessageNodeElementListStrings(doc,"url");

    //qDebug()<<"WALAKOLAAAAAAAAAAAAAAAAAAAAAA";
    //adds the News flash to the database and sets all information about the addes News flash to the
    //object before parsing it into an XML reply or update
    if(api->add->addNewsFlashPost(text,FlashBoardID,user_id,FlashSegmentID,Attach,Date)){


        Post.setNewsFlashID(api->get->getNewsFlashID(user_id));
        Post.setAuthorID(user_id);
        Post.setFlashBoardID(FlashBoardID);
        Post.setSegmentID(FlashSegmentID);
        Post.setText(text);
        for(int i = 0; i < exts.size(); i++){
            QImage img;
            QDir dir = QDir::currentPath();
            QString path = dir.path();
            path.append("/picture/CUBook");
            QString dbPath = ("/picture/CUBook");

            int pointer = api->get->getAttachmentPointer();
            pointer++;

             dbPath.append(QString::number(pointer));
            path.append(QString::number(pointer));

                if(exts[i] == "JPG"){
                    path.append(".jpg");
                    dbPath.append(".jpg");
                    img.loadFromData(QByteArray::fromBase64(pictures.at(i)), "JPG");
                    img.save(path,"JPG");
                }
                if(exts[i] == "PNG"){
                    path.append(".png");
                    dbPath.append(".png");
                    img.loadFromData(QByteArray::fromBase64(pictures.at(i)), "PNG");

                    img.save(path,"PNG");
                }
                if(exts[i] == "GIF"){
                    path.append(".gif");
                    dbPath.append(".gif");
                    img.loadFromData(QByteArray::fromBase64(pictures.at(i)), "GIF");
                    img.save(path,"GIF");
                }
               api->add->addAttachments(pointer,Post.getNewsFlashID(), dbPath);

                    }
                    for(int i =0; i< Links.size(); i++){
                         api->add->addLinks(Post.getNewsFlashID(),Links[i]);
                    }

        //creates a reply and update for the client to receive
        QByteArray newsFlash = MessageProtocol::createRequestSucceededReply(Post.getNewsFlashID());
        //qDebug()<<newsFlash;
        update = MessageProtocol::createNewNewsflashUpdate(Post);
        //qDebug()<<update;
        return newsFlash;
    }

    //creates an error message reply if addition of newsflash into database fails
    return MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
}

//Process for deleting FlashSegments from the database according to the XML received
QByteArray MessageTranslator::processDelFlashSegm(QByteArray message, QByteArray &update){

    QDomDocument doc;
    doc.setContent(message);
    int FlashSegmentID = getMessageAttribute(doc,"segment","segment_id").toInt();

    //SQL qeury for database removal
    if(api->remove->removeFlashSegment(FlashSegmentID)){
        //if successful returns an appropriate reply to client
        QByteArray reply = MessageProtocol::createRequestSucceededReply(FlashSegmentID);
        update = MessageProtocol::createSegmentDeletedUpdate(FlashSegmentID);
        return reply;
    }
    //returns an error reply if removal is not successful
    return MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
}

//Process for deleting a NewsFlash from the database according to the XML received
QByteArray MessageTranslator::processDelNewsFlash(QByteArray message, QByteArray &update){

        QDomDocument doc;
        doc.setContent(message);

        int NewsFlashID = getMessageAttribute(doc,"newsflash","newsflash_id").toInt();

        //SQL query to remove the Newsflash from the database
        if(api->remove->removeNewsFlashPost(NewsFlashID)){
            QByteArray reply = MessageProtocol::createRequestSucceededReply(NewsFlashID);
            update = MessageProtocol::createNewsflashDeletedUpdate(NewsFlashID);
            return reply;
        }

        //returns an error message if newsflash deletion failed
        return MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
    }

//proccess creation of segments and send back a valid reply to the client
QByteArray MessageTranslator::processCreateSegment(QByteArray message, QByteArray &update){

    QDomDocument doc;
    doc.setContent(message);

    //getting information from the XML received.
    int FlashBoardID = getMessageAttribute(doc,"segment","flashboard_id").toInt();
    int FlashSegmentID = getMessageAttribute(doc,"segment","segment_id").toInt();
    QString name = getMessageAttribute(doc,"segment","name");

    //creating a placeholder Flashsegment object to be parsed and sent to the client
        FlashSegment seg;
        seg.setFlashboardID(FlashBoardID);
        seg.setName(name);


            //Query for creation of segments into the database
            if(api->add->addFlashSegment(0,seg.getName(),seg.getFlashboardID())){
                QList<QString> hold = api->get->getSegmentsIDs(seg.getFlashboardID());
                seg.setSegmentID(hold.last().toInt());
                //creates a valid xml reply and update on success and returns it
                QByteArray reply = MessageProtocol::createRequestSucceededReply(seg.getSegmentID());
                update = MessageProtocol::createNewSegmentUpdate(seg);
                if(!update.isEmpty()){
                return reply;
                }
            }

      //returns an error message if FlashSegment wasnt happened
      return MessageProtocol::createRequestFailedReply(MessageProtocol::UNRECOGNIZED);
}



//proccess for getting newsflash ids and returning a valid XML reply
QByteArray MessageTranslator::processGetNewsFlashIDs(QByteArray message){


    QDomDocument doc;
    doc.setContent(message);


    int max = 0;
    QList<QString> flashboard_ids;
    int segment_ID = 0;
    int user_id = 0;
    int range_lte = 0;
    int range_gte = 0;
    int flashboard_id = 0;
    QList<QString> newsflash_ids;


    //gets information from the XML received
    max = getMessageAttribute(doc,"maxnumber","number").toInt();
    flashboard_ids =  getMessageElementList(doc, "flashboard","flashboard_id");
    segment_ID = getMessageAttribute(doc, "segment", "segment_id").toInt();
    user_id = getMessageAttribute(doc,"user", "user_id").toInt();
    range_lte = getMessageAttribute(doc,"lte","newsflash_id").toInt();
    range_gte = getMessageAttribute(doc,"gte", "newsflash_id").toInt();
    flashboard_id = getMessageAttribute(doc,"segment", "flashboard_id").toInt();
    //qDebug()<<"HOIUAHDHAFHSHDASHFSHAFSAHFHASFHASF"<<segment_ID;
    if(flashboard_ids.isEmpty() && segment_ID == 0 && user_id == 0){

        QByteArray Reply;
        Reply = MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
        return Reply;
    }
    //sets a constraint of 5 courses and checks how many courses were sent over.
    if(segment_ID == 0 && user_id ==0){
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int c4 = 0;
    int c5 = 0;
        if(flashboard_ids.size() == 1){
           c1 = flashboard_ids.at(0).toInt();
          }
        else if(flashboard_ids.size() == 2){
           c1 = flashboard_ids.at(0).toInt();
           c2 = flashboard_ids.at(1).toInt();
        }
        else if(flashboard_ids.size() == 3){
            c1 = flashboard_ids.at(0).toInt();
            c2 = flashboard_ids.at(1).toInt();
            c3 = flashboard_ids.at(2).toInt();
        }
        else if(flashboard_ids.size() < 5){
            c1 = flashboard_ids.at(0).toInt();
            c2 = flashboard_ids.at(1).toInt();
            c3 = flashboard_ids.at(2).toInt();
            c4 = flashboard_ids.at(3).toInt();
        }
        if(flashboard_ids.size() >= 5){
            c1 = flashboard_ids.at(0).toInt();
            c2 = flashboard_ids.at(1).toInt();
            c3 = flashboard_ids.at(2).toInt();
            c4 = flashboard_ids.at(3).toInt();
            c5 = flashboard_ids.at(4).toInt();
        }

        //sets a temp filter object for the database
        api->get->holder->setFilter(c1,c2,c3,c4,c5);
       }
        QByteArray reply;

    //gets IDs if a max number and range arent entered or their is a max number by flashfeeds
    if(flashboard_ids.size()>0 && range_lte == 0 && segment_ID == 0){
        newsflash_ids = api->get->getNewsFlashIDList(api->get->holder, max);
        reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }

    //gets IDs for a range with no max number for flashfeeds
    if(flashboard_ids.size()>0 && range_lte != 0 && max == 0 && segment_ID == 0){
        newsflash_ids = api->get->getNewsFlashIDList(api->get->holder, range_lte, range_gte );
        reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);

    }

    //gets IDs for a max number and range for flashfeed
    if(flashboard_ids.size()>0 && range_lte != 0 && max != 0 && segment_ID == 0){
        newsflash_ids = api->get->getNewsFlashIDList(api->get->holder, range_lte, range_gte, max);
        reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }

    //gets IDs if a max number and range arent entered or their is a max number by users
    if(user_id != 0 && max != 0 && range_lte == 0){
        newsflash_ids = api->get->getNewsFlashIDList(user_id,max);
        reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }

    //gets IDs if a range is enteres with no max number by Users
    if(user_id != 0 && max == 0 && range_lte != 0){

        newsflash_ids = api->get->getNewsFlashIDList(user_id,range_lte,range_gte);
        reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }

    //gets IDs for a max number and range by Users
    if(user_id != 0 && max != 0 && range_lte != 0){
        newsflash_ids = api->get->getNewsFlashIDList(user_id,range_lte,range_gte, max);
        reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }


    //gets IDs if a max number and range arent entered or their is a max number by Segments
    if(segment_ID != 0 && flashboard_id != 0 && range_lte == 0 ){
       QString a = "l";
       newsflash_ids = api->get->getNewsFlashIDList(segment_ID,flashboard_id,max,a);
       reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }

    //gets IDs if a range is enteres with no max number by Segments
    if(segment_ID != 0 && flashboard_id != 0 && max == 0 && range_lte != 0 ){
       QString a = "l";
       newsflash_ids = api->get->getNewsFlashIDList(segment_ID,flashboard_id,range_lte,range_gte,a);
       reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }

    //gets IDs for a max number and range by Segments
    if(segment_ID != 0 && flashboard_id != 0 && max != 0 && range_lte != 0){
        QString a = "l";
        newsflash_ids = api->get->getNewsFlashIDList(segment_ID,flashboard_id,range_lte,range_gte,max,a);
        reply = MessageProtocol::createGetNewsflashIDsReply(newsflash_ids);
    }
    if(reply.isEmpty()){
        reply = MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
    }
    return reply;
}

//process for getting Newsflashes and returning a valid XML reply to client.
QByteArray MessageTranslator::processGetNewsFlash(QByteArray message){
    QDomDocument doc;
    doc.setContent(message);

    //Declaring lists to hold information from XML and database
    int max;
    QList<NewsFlash>newsflashing;
    QList<QString> newsflash;
    QList<QString> newsflash_ids;
    QList<QString> Filepaths;
    QList<QString> Links;

    //extracting newsflash ids from XML
    newsflash_ids = getMessageElementList(doc,"newsflash", "newsflash_id");

    //loops through newsflash ids and gets newsflashes from the database
    for(int i =0; i<newsflash_ids.size();i++){

        //sql queries to get information pertaining to newsflashes and all its attachments and links from the database
        newsflash=api->get->getNewsFlash(newsflash_ids.at(i).toInt());
        Filepaths = api->get->getAttachments(newsflash_ids.at(i).toInt());
        Links = api->get->getLinks(newsflash_ids.at(i).toInt());

            //declares and initializes a temp Newsflash object to be parsed into XML reply
            NewsFlash a;
            a .setNewsFlashID(newsflash.at(0).toInt());
            a .setText(newsflash.at(1));
            a .setFlashBoardID(newsflash.at(2).toInt());
            a .setAuthorID(newsflash.at(3).toInt());
            a .setSegmentID(newsflash.at(4).toInt());


            //loop to get pictures for each post and places the list of attachments
            for(int j = 0; j<Filepaths.size(); j++){

               QDir dir = QDir::currentPath();
               QString path = dir.path();
               path.append(Filepaths[j]);
               CUPicture picture;
               QFile file(path);
               QFileInfo fil(file);
               QString ext = fil.completeSuffix();
               //sets the CUpicture to the NewsFlash
               picture.setFormat(ext);
               QImage picdata(path);
               picture.setPicture(picdata);
               a.addPicture(picture);

            }

            //loops through the links for the Newsflash and inserts them into the Newsflash object
            for(int k = 0; k <Links.size(); k++){
                CUUrl url;
                url.setLink(Links[k]);
                a.addURL(url);
            }

            //adds the newsflash to a list of newsflashes to be parsed
            newsflashing.append(a);
     }

    //parses the list of newsflashes into a valid XML reply and returns it.
    QByteArray reply = MessageProtocol::createGetNewsflashesReply(newsflashing);
    return reply;
 }

//gets a list of non text items in between nodes in the XML file
QList<QByteArray> MessageTranslator:: getMessageNodeElementList(QDomDocument doc, QString ele){
    QList<QByteArray> elements;
    QDomElement root = doc.firstChildElement();
     QDomNodeList items = root.elementsByTagName(ele);
     for(int i = 0; i<items.size(); i++){
     QDomNode textData = items.at(i).firstChild();
     QByteArray temp;
     temp.append(textData.nodeValue());

     elements.append(temp);
     }

     return elements;
}


//gets a list of text items in between XML nodes
QList<QString> MessageTranslator:: getMessageNodeElementListStrings(QDomDocument doc, QString ele){
    QList<QString> elements;
    QDomElement root = doc.firstChildElement();
     QDomNodeList items = root.elementsByTagName(ele);
     for(int i = 0; i<items.size(); i++){
     QDomNode textData = items.at(i).firstChild();
     QByteArray temp;
     temp.append(textData.nodeValue());

     elements.append(temp);
     }
     return elements;
}

//proccesses getting a list of flashboards
QByteArray MessageTranslator:: processGetBoardList(int user_ID){

    //gets information from the database (namely flashboards and filters from the database)
    QList<QString> filter = api->get->getCourseList(user_ID);
    QList<FlashBoard> flashboard;
    QList<QString> filters = api->get->getFilter(user_ID);

    //loops through the list of flashboards and their filtered state
    for(int i =0; i<filter.size(); i++){
        //temp object to hold flashboards
        FlashBoard holder;
            if(filters[i]=="true"){
                holder.setFiltered(true);
            }
            else{
                holder.setFiltered(false);
            }
                //gets segment IDs from the database
                QList<QString> segIDs = api->get->getSegmentsIDs(filter[i].toInt());
               for(int j = 0; j<segIDs.size();j++){
                   //uses those segment IDs to get segments for each flashboard.
                   QList<QString> segInfo = api->get->getSegment(segIDs[j].toInt());
                  FlashSegment temp;
                   //inserts all data into a temp FlashSegment list to be added to the flashboard
                   temp.setSegmentID(segInfo[0].toInt());
                   temp.setName(segInfo[1]);
                   temp.setFlashboardID(segInfo[2].toInt());
                   holder.addSegment(temp);

                    }
               //gets all the required information about the flashboards to be parsed
               QList<QString> fbInfo = api->get->getFlashBoard(filter[i].toInt());

               //sets this information into a temp holder
               holder.setName(fbInfo[1]);
               holder.setFlashBoardID(fbInfo[0].toInt());
               flashboard.append(holder);

    }

    if(!flashboard.isEmpty()){

        //if successful parses all the flashboards and its segments into a valid XML reply and returns it
        QByteArray Reply = MessageProtocol::createGetBoardListReply(flashboard);
        return Reply;
            }

    //returns an error if
    QByteArray Reply = MessageProtocol::createRequestFailedReply(MessageProtocol::UNAUTHORIZED);
   return Reply;

    }

//proccesses the update requests for profiles and returns a valid XML reply and update
QByteArray MessageTranslator::processUpdateProfile(QByteArray message, int user_ID, QByteArray &update){

    QDomDocument doc;
    bool changed = false;
    doc.setContent(message);

    //extracts information from the XML received
    QString Picture = getMessageElement(doc,"binarydata");
    QString Avatar = getMessageElement(doc,"nickname");
    QString ext = getMessageAttribute(doc,"picture","format");

    //creates a temporary user profile to hold information and sets it
            UserProfile prof;

            //gets profiles from the database
            QList<QString> profile = api->get->getProfile(user_ID);
            prof.setUserID(user_ID);
            prof.setRealname(profile[2]);
            if(profile[3] == "1")

            //sets the profile type
            prof.setUserType("instructor");
            else
            prof.setUserType("student");
                    if(!Picture.isEmpty()){
                //parses the profile picture and sets it into the profile
                QByteArray pic;
                pic.append(Picture);
                QDir dir = QDir::currentPath();
                QString path = dir.path();
                path.append(api->get->getUserProfPic(user_ID));
                QFile::remove(path);
                CUPicture profpic;
                QImage img;

                //checks the type of the picture
                if(ext == "JPG"){
                    //qDebug() << "Got a JPG";
                    img.loadFromData(QByteArray::fromBase64(pic), "JPG");
                    profpic.setFormat(ext);
                    profpic.setPicture(img);



                    img.save(path,"JPG");
                    path.append("/picture/");
                    path.append(QString::number(user_ID));
                    path.append(".jpg");
                    path.clear();
                    path.append("/picture/");
                    path.append(QString::number(user_ID));
                    path.append(".jpg");
                    api->update->changePhoto(user_ID,path);
                    prof.setPicture(profpic);
                                        }
                else if(ext == "PNG"){
                    //qDebug() << "Got a PNG";
                    img.loadFromData(QByteArray::fromBase64(pic), "PNG");
                    profpic.setFormat(ext);
                    profpic.setPicture(img);
                    img.save(path,"PNG");
                    path.clear();
                    path.append("/picture/");
                    path.append(QString::number(user_ID));
                     path.append(".png");
                    img.save(path,"PNG");
                    api->update->changePhoto(user_ID,path);
                    prof.setPicture(profpic);
                }
                else if(ext == "GIF"){
                    //qDebug() << "Got a GIF";
                    img.loadFromData(QByteArray::fromBase64(pic), "GIF");
                    profpic.setFormat(ext);
                    profpic.setPicture(img);
                    img.save(path,"GIF");
                    path.clear();
                    path.append("/picture/");
                    path.append(QString::number(user_ID));
                    path.append(".gif");
                    img.save(path,"GIF");
                    api->update->changePhoto(user_ID,path);
                    prof.setPicture(profpic);
                }
                else
                    //qDebug() << "Got nothing";

                    changed = true;
                }


                    if(!Avatar.isEmpty()){
                    //updates the avatar name
                    api->update->changeAvatar(user_ID,Avatar);
                    prof.setNickname(Avatar);
                    changed = true;
                }
                if(changed){
               //returns a valid XML update and reply if successful
               update = MessageProtocol::createProfileUpdateUpdate(prof);
               QByteArray Reply = MessageProtocol::createRequestSucceededReply(user_ID);
               return Reply;
                }
              //returns an error message if not successful
              QByteArray Reply = MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
              return Reply;
            }

//proccesses the update filter request from the client and returns a Valid XML reply
QByteArray MessageTranslator:: processUpdateFilter(QByteArray message, int user_id){
    QByteArray reply;
    QDomDocument doc;
    bool checker = false;
    doc.setContent(message);

    //extracts information from the XML bytearray received
    QList<QString> flashboard_ids = getMessageElementList(doc,"flashboard", "flashboard_id");
    QList<QString> visible = getMessageElementList(doc,"flashboard","visible");
    //qDebug()<<flashboard_ids.size();

    api->update->changeFilter(user_id);

    for(int i = 0; i < flashboard_ids.size(); i++){
        //sends each flashboard and updates its filter state on the database

        if(visible[i] == "1"){
         visible[i] = "true";
        }

        if(api->update->changeFilter(flashboard_ids[i].toInt(),visible[i],user_id))
           checker = true;
    }


    if(checker){

       //if successful returns a valid XML reply
       reply = MessageProtocol::createRequestSucceededReply(-1);

       return reply;
   }

  //returns an error message if not successful
  reply = MessageProtocol::createRequestFailedReply(MessageProtocol::CONTENTS);
  return reply;

}

//gets the tag name of the root of the XML received
QString MessageTranslator::getMessageType(QDomDocument doc){
    return doc.firstChildElement().tagName();


}

//gets an attribute from the root of the XML document
QString MessageTranslator::getRootMessageAttribute(QDomDocument doc, QString att){
    return doc.firstChildElement().attribute(att);
}

//gets an attribute from a specified tag in the XML
QString MessageTranslator::getMessageAttribute(QDomDocument a, QString element, QString attribute){
    QDomElement root = a.firstChildElement();
    QDomNodeList items = root.elementsByTagName(QString("%1").arg(element));
    QDomNode itemnode = items.at(0);
    QDomElement itemele = itemnode.toElement();
   return itemele.attribute(QString("%2").arg(attribute));


}

//gets an element in between nodes in the document
QString MessageTranslator::getMessageElement(QDomDocument doc, QString ele){

    QDomElement root = doc.firstChildElement();
     QDomNodeList items = root.elementsByTagName(ele);
     QDomNode textData = items.at(0).firstChild();
     //qDebug()<<textData.nodeValue();

     return textData.nodeValue();

}

//gets a specified list of attributes from the XML file
QList<QString> MessageTranslator::getMessageElementList(QDomDocument doc, QString element, QString attribute){
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

//checks if the XML received is valid
bool MessageTranslator::isValidXML(QDomDocument doc){
    QDomNode xml = doc.firstChild();
    QString xml_name = xml.nodeName();
    QString xml_info = xml.nodeValue();
    if (QString::compare("xml", xml_name, Qt::CaseInsensitive) == 0 &&
        xml_info.contains("version", Qt::CaseInsensitive) && xml_info.contains("1.0",  Qt::CaseInsensitive) &&
        xml_info.contains("encoding",  Qt::CaseInsensitive) && xml_info.contains("UTF-8", Qt::CaseInsensitive)){
            return true;
    }
    else
            return false;
}

//proccesses the unauthentication process and sends a valid XML reply
QByteArray MessageTranslator:: processUnauthenticate(QByteArray message, int user_id){

    //returns a successful unauthenticate reply
    QByteArray Reply;
    Reply = MessageProtocol::createRequestSucceededReply(-1);

    return Reply;
}
