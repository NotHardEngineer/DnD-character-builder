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



void Widget::oneCounter(QLineEdit *edit, bool operand){
    bool readOK1 = 0, readOK2 = 0;
    int prime = edit->text().toInt(&readOK1);
    int pointLeft = ui->skillpointCount->text().toInt(&readOK2);
    if (readOK1 && readOK2 && pointLeft > 0){
        if(operand == 0)// тут функция для минуса
        {
            if(prime > 1 && prime <= 13){
                edit->setText(QString::number(prime - 1));
                ui->skillpointCount->setText(QString::number(pointLeft + 1));
            }
            else if(prime > 13){
                edit->setText(QString::number(prime - 1));
                ui->skillpointCount->setText(QString::number(pointLeft + 2));
            }
            else{
                ui->debugLabel->setText("хар-ка не может быть меньше 1");
            }

        }
        else if(operand == 1)//тут для плюса
        {
            if (prime < 13){
                edit->setText(QString::number(prime + 1));
                ui->skillpointCount->setText(QString::number(pointLeft - 1));
            }
            else if (prime >= 13 && prime < 15){
                edit->setText(QString::number(prime + 1));
                ui->skillpointCount->setText(QString::number(pointLeft - 2));
            }
            else{
                ui->debugLabel->setText("хар-ка не может быть больше 15");
            }
        }
    }
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
    int streightPoints =  ui->strengthCount->text().toInt(&streightOK);
    int dexterityPoints =  ui->dexterityCount->text().toInt(&dexterityOK);
    int wisdomPoints =  ui->wisdomCount->text().toInt(&wisdomOK);
    int intelligencePoints =  ui->intelligenceCount->text().toInt(&intelligenceOK);
    int charismaPoints =  ui->charismaCount->text().toInt(&charismaOK);
    bool allOK = constitutionOK && streightOK && dexterityOK && wisdomOK && intelligenceOK && charismaOK;

    if(allOK){
        ui->debugLabel->setText("all read ok");
        int usedPointsSum = (constitutionPoints + streightPoints + dexterityPoints + wisdomPoints + intelligencePoints + charismaPoints) - 48;
        int skillLeft = 25 - usedPointsSum;
        ui->skillpointCount->setText(QString::number(skillLeft));

        if(skillLeft < 0){
            //подсветкой указать на излишнее использование очков
        }
        else{

        }

    }
    else{
        //не забыть обработать случай, когда пользователь еще не успел ввести данные
        ui->debugLabel->setText("somthing wrong, i can feel it");
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


void Widget::on_skillButton_clicked()
{
    skillCounter();
}


void Widget::on_constitutionPlusButton_clicked()
{
    oneCounter(ui->constitutionCount, 1);
}
void Widget::on_strengthPlusButton_clicked()
{
    oneCounter(ui->strengthCount, 1);
}
void Widget::on_dexterityPlusButton_clicked()
{
    oneCounter(ui->dexterityCount, 1);
}
void Widget::on_wisdomPlusButton_clicked()
{
    oneCounter(ui->wisdomCount, 1);
}
void Widget::on_intelligencePlusButton_clicked()
{
    oneCounter(ui->intelligenceCount, 1);
}
void Widget::on_charismaPlusButton_clicked()
{
    oneCounter(ui->charismaCount, 1);
}


void Widget::on_constitutionMinusButton_clicked()
{
    oneCounter(ui->constitutionCount, 0);
}
void Widget::on_strengthMinusButton_clicked()
{
    oneCounter(ui->strengthCount, 0);
}
void Widget::on_dexterityMinusLabel_clicked()
{
    oneCounter(ui->dexterityCount, 0);
}
void Widget::on_wisdomMinusButton_clicked()
{
    oneCounter(ui->wisdomCount, 0);
}
void Widget::on_intelligenceMinusButton_clicked()
{
    oneCounter(ui->intelligenceCount, 0);
}
void Widget::on_charismaMinusButton_clicked()
{
    oneCounter(ui->charismaCount, 0);
}

