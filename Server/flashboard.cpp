#include "flashboard.h"

FlashBoard::FlashBoard()
{
}

//Get Methods
QString FlashBoard::getName(){ return name;}
QList<FlashSegment> FlashBoard::getSegments(){ return segments;}
bool FlashBoard::isFiltered(){ return filtered;}
int FlashBoard::getFlashboardID(){return flashboard_id;}

//Set Methods
void FlashBoard::setName(QString a_name){
    name = a_name;
}
void FlashBoard::addSegment(FlashSegment a_segment){
    segments.append(a_segment);
}

void FlashBoard::setFiltered(bool a_filtered){
    filtered = a_filtered;
}
void FlashBoard::setFlashBoardID(int flashboardid){
    flashboard_id = flashboardid;
}
