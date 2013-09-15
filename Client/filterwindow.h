#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QDialog>

namespace Ui {
    class FilterWindow;
}

class FilterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = 0);
    ~FilterWindow();
    Ui::FilterWindow *ui;

private:

};

#endif // FILTERWINDOW_H
