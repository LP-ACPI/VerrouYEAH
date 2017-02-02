#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
//#include <QtGui/QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setAcceptDrops(true);
    QImage image("ark-open.png");
    ui->label_4->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
        ui->textEdit->setText(event->mimeData()->text());
    }
}
