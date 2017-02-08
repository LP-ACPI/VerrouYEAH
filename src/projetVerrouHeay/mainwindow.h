#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formsauvegarde.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
private slots:
    void FenetrePlanification();
private:
    Ui::MainWindow *ui;
    FormSauvegarde *formSauvegarde;
};

#endif // MAINWINDOW_H
