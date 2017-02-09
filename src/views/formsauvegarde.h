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
    void setSourceText(QString);

private:
};

#endif // FORMSAUVEGARDE_H
