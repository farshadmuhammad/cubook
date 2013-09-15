#ifndef FLASHSEGMENTWINDOW_H
#define FLASHSEGMENTWINDOW_H

#include <QDialog>

namespace Ui {
    class FlashSegmentWindow;
}

class FlashSegmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FlashSegmentWindow(QWidget *parent = 0);
    ~FlashSegmentWindow();
    Ui::FlashSegmentWindow *ui;

private:

};

#endif // FLASHSEGMENTWINDOW_H
