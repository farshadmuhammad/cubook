#ifndef FLASHBOARD_H
#define FLASHBOARD_H

#include <QList>
#include "flashsegment.h"

class FlashBoard
{
public:
    FlashBoard();
    FlashBoard(int a_flashboard_id, QString a_name, bool a_filter);

    QString getName();
    QList<FlashSegment> getSegments();
    bool isFiltered();
    int getFlashboardID();

    void setName(QString a_name);
    void addSegment(FlashSegment a_segment);
    void removeSegment(FlashSegment a_segment);
    void setFiltered(bool a_filtered);
    void setSegments(QList<FlashSegment> a_segments);
private:
    int flashboard_id;
    QString name;
    QList<FlashSegment> segments;
    bool filtered;
};

#endif // FLASHBOARD_H
