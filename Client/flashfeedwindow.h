#ifndef FLASHFEEDWINDOW_H
#define FLASHFEEDWINDOW_H

#include <QDialog>

namespace Ui {
    class FlashFeedWindow;
}

class FlashFeedWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FlashFeedWindow(QWidget *parent = 0);
    ~FlashFeedWindow();
    Ui::FlashFeedWindow *ui;

private:

};

#endif // FLASHFEEDWINDOW_H
