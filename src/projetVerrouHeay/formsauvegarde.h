#ifndef FORMSAUVEGARDE_H
#define FORMSAUVEGARDE_H

#include <QDialog>

namespace Ui {
class FormSauvegarde;
}

class FormSauvegarde : public QDialog
{
    Q_OBJECT

public:
    explicit FormSauvegarde(QWidget *parent = 0);
    ~FormSauvegarde();

private:
    Ui::FormSauvegarde *ui;
};

#endif // FORMSAUVEGARDE_H
