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

}

void FrequencyForm::on_buttonBox_rejected()
{
    close();
}
