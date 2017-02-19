#include "../views/frequencyform.h"

FrequencyForm::FrequencyForm(QWidget *parent) : QDialog(parent){
    init();

}

void FrequencyForm::init(){
    setupUi(this);
    setModal(true);

}

void FrequencyForm::on_buttonBox_accepted()
{
    emit frequencySelected(dateEdit->text() + timeEdit->text());
    close();
}

void FrequencyForm::on_buttonBox_rejected()
{
    close();
}
