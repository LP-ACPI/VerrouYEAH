#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList listPlanification;

    listPlanification.push_front("Salut");
    ui->ListPlanifications->addItems(listPlanification);


    QObject::connect(ui->ButtonNouvellePlan,SIGNAL(clicked(bool)), this, SLOT(FenetrePlanification()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FenetrePlanification(){
    formSauvegarde = new FormSauvegarde(this);
    formSauvegarde->setModal(true);
    formSauvegarde->show();
}
