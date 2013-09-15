#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QDialog {
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    Ui::LoginWindow *ui;

protected:


private:

};

#endif // LOGINWINDOW_H
