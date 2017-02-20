#ifndef FREQUENCYFORM_H
#define FREQUENCYFORM_H

#include <QDialog>
#include "ui_frequencydialog.h"


class FrequencyForm : public QDialog, private Ui::FrequencyDialog
{
    Q_OBJECT
    void init();
public:
    explicit FrequencyForm(QWidget *parent = 0);

signals:
    void frequencySelected(QString);

protected slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


};

#endif // FREQUENCYFORM_H
