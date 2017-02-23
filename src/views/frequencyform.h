#ifndef FREQUENCYFORM_H
#define FREQUENCYFORM_H

#include <QDialog>
#include "ui_frequencydialog.h"


class FrequencyForm : public QDialog, private Ui::FrequencyDialog
{
    Q_OBJECT
    QString postData;

    void init();
    void minuteChoiceLayout();
    void hourChoiceLayout();
    void dayChoiceLayout();
    void weekChoiceLayout();
    void monthChoiceLayout();
    void yearChoiceLayout();
public:
    explicit FrequencyForm(QWidget *parent = 0);

signals:
    void frequencySelected(QString);

protected slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void onMainChoiceChanged(int);
};

#endif // FREQUENCYFORM_H
