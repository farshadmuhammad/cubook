#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QDialog>

namespace Ui {
    class ProfileWindow;
}

class ProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileWindow(QWidget *parent = 0);
    ~ProfileWindow();
    Ui::ProfileWindow *ui;

private:

};

#endif // PROFILEWINDOW_H
