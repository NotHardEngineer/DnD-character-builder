#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    characterImageSet(ui->raceChoose->currentIndex(), ui->raceChoose->currentIndex());


}
Widget::~Widget()
{
    delete ui;
}





void Widget::characterImageSet(int raseIndex, int classIndex){
    switch(classIndex){
    case 0: //воин
        switch (raseIndex) {
        case 0:     //человек
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/warriorHuman.jpg"));
            break;
        case 1:     //эльф
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/warriorElf.jpg"));
            break;
        case 2:     //гном
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/warriorDwarf.jpg"));
            break;
        }
        break;
    case 1: //разбойник
        switch (raseIndex) {
        case 0:     //человек
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/rogueHuman.png"));
            break;
        case 1:     //эльф
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/rogueElf.jpg"));
            break;
        case 2:     //гном
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/rogueDwarf.jpg"));
            break;
        }
        break;
    case 2: //маг
        switch (raseIndex) {
        case 0:     //человек
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/mageHuman.png"));
            break;
        case 1:     //эльф
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/mageElf.png"));
            break;
        case 2:     //гном
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/mageDwarf.jpg"));
            break;
        }
        break;
    case 3: //жрец
        switch (raseIndex) {
        case 0:     //человек
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/priestHuman.png"));
            break;
        case 1:     //эльф
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/priestElf.png"));
            break;
        case 2:     //гном
            ui->characterImagePlace->setPixmap(QPixmap(":/characters/resources/images/characters/priestDwarf.jpg"));
            break;
        }
        break;
    }
}

void Widget::skillCounter(){
    bool constitutionOK = 0, streightOK = 0, dexterityOK = 0, wisdomOK = 0, intelligenceOK = 0, charismaOK = 0;
    int constitutionPoints =  ui->constitutionCount->text().toInt(&constitutionOK);
    int streightPoints =  ui->streightCount->text().toInt(&streightOK);
    int dexterityPoints =  ui->dexterityCount->text().toInt(&dexterityOK);
    int wisdomPoints =  ui->wisdomCount->text().toInt(&wisdomOK);
    int intelligencePoints =  ui->intelligenceCount->text().toInt(&intelligenceOK);
    int charismaPoints =  ui->charismaCount->text().toInt(&charismaOK);
    bool allOK = constitutionOK && streightOK && dexterityOK && wisdomOK && intelligenceOK && charismaOK;

    if(allOK){
        ui->debuggingLabel->setText("all read ok");
        int usedPointsSum = (constitutionPoints + streightPoints + dexterityPoints + wisdomPoints + intelligencePoints + charismaPoints) - 48;
        int skillLeft = 25 - usedPointsSum;
        ui->skillpointCount->setText(QString::number(skillLeft));

        if(skillLeft < 0){
            //подсветкой указать на излишнее использование очков
        }
        else{
            if (constitutionPoints < 8){
                //подсветить поле
                ui->debuggingLabel->setText("Характеристика не может быть меньше 8");
            }
            if (streightPoints < 8){
                //подсветить поле
                ui->debuggingLabel->setText("Характеристика не может быть меньше 8");
            }
            if (dexterityPoints < 8){
                //подсветить поле
                ui->debuggingLabel->setText("Характеристика не может быть меньше 8");
            }
            if (wisdomPoints < 8){
                //подсветить поле
                ui->debuggingLabel->setText("Характеристика не может быть меньше 8");
            }
            if (intelligencePoints < 8){
                //подсветить поле
                ui->debuggingLabel->setText("Характеристика не может быть меньше 8");
            }
            if (charismaPoints < 8){
                //подсветить поле
                ui->debuggingLabel->setText("Характеристика не может быть меньше 8");
            }
        }

    }
    else{
        //не забыть обработать случай, когда пользователь еще не успел ввести данные
        ui->debuggingLabel->setText("somthing wrong, i can feel it");
    }
}


//Вызов смены картинок
void Widget::on_raceChoose_currentIndexChanged(int index)
{
    characterImageSet(index, ui->classChoose->currentIndex());
}
void Widget::on_classChoose_currentIndexChanged(int index)
{
    characterImageSet(ui->raceChoose->currentIndex(), index);
}

//Вызов счетчика скилов
/*void Widget::on_constitutionCount_editingFinished()
{
    skillCounter();
}
void Widget::on_streightCount_editingFinished()
{
    skillCounter();
}
void Widget::on_dexterityCount_editingFinished()
{
    skillCounter();
}
void Widget::on_wisdomCount_editingFinished()
{
    skillCounter();
}
void Widget::on_intelligenceCount_editingFinished()
{
    skillCounter();
}
void Widget::on_charismaCount_editingFinished()
{
    skillCounter();
}
*/
void Widget::on_skillButton_clicked()
{
    skillCounter();
}

