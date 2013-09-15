#include "flashsegmentwindow.h"
#include "ui_flashsegmentwindow.h"

FlashSegmentWindow::FlashSegmentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlashSegmentWindow)
{
    ui->setupUi(this);
}

FlashSegmentWindow::~FlashSegmentWindow()
{
    delete ui;
}
