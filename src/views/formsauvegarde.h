#ifndef FORMSAUVEGARDE_H
#define FORMSAUVEGARDE_H

#include "ui_formsauvegarde.h"
#include <QDialog>

class FormSauvegarde : public QDialog, private Ui::FormSauvegarde
{
    Q_OBJECT

public:
    explicit FormSauvegarde(QWidget *parent = 0);
    ~FormSauvegarde();

private:
    Ui::FormSauvegarde *ui;
};

#endif // FORMSAUVEGARDE_H
