#include "frequencyform.h"

FrequencyForm::FrequencyForm(QWidget *parent) : QDialog(parent){

    setupUi(this);
    setModal(true);
    init();

    connect(mainChoice,SIGNAL(currentIndexChanged(int)),this,SLOT(onMainChoiceChanged(int)));

}

void FrequencyForm::init(){
    daysOfWeek->hide();
    monthsOfYear->hide();
    prepLabel->hide();
    numberInput->hide();
    secondaryTypeLabel->hide();
}

void FrequencyForm::on_buttonBox_accepted() {

    switch(mainChoice->currentIndex()){

    case  0  :
        postData = "* * * * *";
        break;

    case 1 :
        postData = numberInput->text()+" * * * *";
        break;

    case 2 :
        postData = "0 " +numberInput->text()+" * * *";
        break;

    case 3 :
        postData = "0 12 * * " +QString::number(daysOfWeek->currentIndex());
        break;

    case 4 :
        postData = "0 12 " +numberInput->text()+" * *";
        break;

    case 5 :
        int monthChoice = (monthsOfYear->currentIndex()  + 1);
        postData = "0 12 1 " + QString::number(monthChoice)+" *";
        break;
    }

    emit frequencySelected(postData);
    close();
}

void FrequencyForm::on_buttonBox_rejected()
{
    close();
}

void FrequencyForm::minuteChoiceLayout(){
    init();
    prepLabel->show();
    numberInput->show();
    secondaryTypeLabel->show();
}

void FrequencyForm::hourChoiceLayout(){
    init();
    prepLabel->show();
    numberInput->show();
    secondaryTypeLabel->show();
    prepLabel->setText("à");
    secondaryTypeLabel->setText("minute(s)");
    numberInput->setMaximum(59);
    numberInput->setMinimum(0);
}

void FrequencyForm::dayChoiceLayout(){
    init();
    prepLabel->show();
    numberInput->show();
    secondaryTypeLabel->show();
    prepLabel->setText("à");
    secondaryTypeLabel->setText("heure(s)");
    numberInput->setMaximum(23);
    numberInput->setMinimum(0);
}

void FrequencyForm::weekChoiceLayout(){
    init();
    daysOfWeek->show();
    daysOfWeek->raise();
}

void FrequencyForm::monthChoiceLayout(){
    init();
    prepLabel->show();
    numberInput->show();
    secondaryTypeLabel->show();
    prepLabel->setText("le");
    secondaryTypeLabel->setText("e jour");
    numberInput->setMaximum(31);
    numberInput->setMinimum(1);
}

void FrequencyForm::yearChoiceLayout(){
    init();
    monthsOfYear->show();
    monthsOfYear->raise();
}

void FrequencyForm::onMainChoiceChanged(int choiceIndex){
    switch(choiceIndex){

    case  0  :
        minuteChoiceLayout();
        break;

    case 1 :
        hourChoiceLayout();
        break;

    case 2 :
        dayChoiceLayout();
        break;

    case 3 :
        weekChoiceLayout();
        break;

    case 4 :
        monthChoiceLayout();
        break;

    case 5 :
        yearChoiceLayout();
        break;

    default:
        minuteChoiceLayout();
        break;
    }
}
