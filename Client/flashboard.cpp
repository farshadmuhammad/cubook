#include "flashboard.h"

FlashBoard::FlashBoard(){

}

FlashBoard::FlashBoard(int a_flashboard_id, QString a_name, bool a_filter){
    flashboard_id = a_flashboard_id;
    name = a_name;
    filtered = a_filter;
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
void FlashBoard::removeSegment(FlashSegment a_segment){
    for(int i = 0; i < segments.size(); i++){
	if(segments.value(i).getName() == a_segment.getName()) {
	    segments.removeAt(i);
	}
    }
}

void FlashBoard::setFiltered(bool a_filtered){
    filtered = a_filtered;
}

void FlashBoard::setSegments(QList<FlashSegment> a_segments){
    segments.clear();
    for (int i=0; i<a_segments.size();i++){
        segments.append(a_segments[i]);
    }
    return;
}
