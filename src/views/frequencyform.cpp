#include "frequencyform.h"

FrequencyForm::FrequencyForm(QWidget *parent) : QDialog(parent){
    init();

}

void FrequencyForm::init(){
    setupUi(this);
    setModal(true);
}

void FrequencyForm::on_buttonBox_accepted() {

    QString postInfo  =   minutes->text().remove( QRegExp("^[0]*") )+' '+
                                            hours->text().remove( QRegExp("^[0]*") ) +' '+
                                            daysOfMonth->text() +' '+
                                            QString::number(monthsOfYear->currentIndex() +1)+' '+
                                             QString::number(daysOfWeek->currentIndex());
    emit frequencySelected(postInfo);
    close();
}

void FrequencyForm::on_buttonBox_rejected()
{
    close();
}
