#include "flashfeedwindow.h"
#include "ui_flashfeedwindow.h"

FlashFeedWindow::FlashFeedWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlashFeedWindow)
{
    ui->setupUi(this);
}

FlashFeedWindow::~FlashFeedWindow()
{
    delete ui;
}
