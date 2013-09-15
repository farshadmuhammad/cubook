#include "cutask.h"

CUTask::CUTask(QByteArray *a_message, QByteArray *an_update, int a_user_id)
{
    update = *an_update;
    message = *a_message;
    user_id = a_user_id;
}

void CUTask::run(){
    QByteArray ba;
    if (user_id == 0){
        ba = translator.checkXML(message, update, &user_id);
        emit userID(user_id);
    }
    else{
     ba = translator.checkXML(message, update, &user_id);
    }
    if(!update.isEmpty())
        emit(newUpdate(update));
    ba.append('\0');

    emit result(ba);
}
