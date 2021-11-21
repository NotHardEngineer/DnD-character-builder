#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    characterImageSet(ui->raceChoose->currentIndex(), ui->raceChoose->currentIndex());
    pointsCounter();

}
Widget::~Widget()
{
    delete ui;
}

void Widget::characterImageSet(int raceIndex, int classIndex){
    switch(classIndex){
    case 0: //воин
        switch (raceIndex) {
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
        switch (raceIndex) {
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
        switch (raceIndex) {
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
        switch (raceIndex) {
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

void Widget::oneCounter(QLineEdit *edit, bool operand){
    bool readOK1 = 0, readOK2 = 0;
    int prime = edit->text().toInt(&readOK1);
    int pointLeft = ui->skillpointCount->text().toInt(&readOK2);
    bool ok = readOK1 && readOK2;
    QPalette pal;
    if (ok && pointLeft > 0){
        if(operand == 0)// тут функция для минуса
        {
            if(prime > 8 && prime <= 13){
                edit->setText(QString::number(prime - 1));
                ui->skillpointCount->setText(QString::number(pointLeft + 1));
            }
            else if(prime > 13){
                edit->setText(QString::number(prime - 1));
                ui->skillpointCount->setText(QString::number(pointLeft + 2));
            }
            else{
                ui->debugLabel->setText("хар-ка не может быть меньше 8");
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
        ui->skillpointCount->setPalette(pal);
    }
    else if (ok && pointLeft == 0 && operand == 0){
        if(prime > 8 && prime <= 13){
            edit->setText(QString::number(prime - 1));
            ui->skillpointCount->setText(QString::number(pointLeft + 1));
        }
        else if(prime > 13){
            edit->setText(QString::number(prime - 1));
            ui->skillpointCount->setText(QString::number(pointLeft + 2));
        }
        else{
            ui->debugLabel->setText("хар-ка не может быть меньше 8");
        }
        ui->skillpointCount->setPalette(pal);
    }
    else if (ok && pointLeft == 0) {
        QPalette pal;
        pal.setColor(QPalette::Base, Qt::red);
        ui->skillpointCount->setPalette(pal);
    }
    else {
        ui->debugLabel->setText("unknow error, pls restart");
    }


}
bool Widget::getValueFromLineEdit(QLineEdit *line, int &value){
    bool ok;
    value = line->text().toInt(&ok);
    QPalette pal;
    if(!ok){
        pal.setColor(QPalette::Base, Qt::red);

    }
    line->setPalette(pal);
    return ok;
}


bool Widget::bonusShow(QLabel *bonusLabel, int bonusArg /*то, от чего зависит бонус*/, int bonusState /*какой дожен быть аргумент для бонуса*/, int bonus){
    QPalette pal = bonusLabel->palette();
    if (bonusArg == bonusState){
        if(bonus > 0){
            pal.setColor(bonusLabel->foregroundRole(), QColor(64, 179, 97));
            bonusLabel->setText("+" + QString::number(bonus));
        }
        else if (bonus < 0) {
            pal.setColor(bonusLabel->foregroundRole(), Qt::red);
            bonusLabel->setText(QString::number(bonus));
        }
        bonusLabel->setPalette(pal);
        return 1;
    }
    else{

        return 0;
    }
}
void Widget::noBonusShow(QLabel *bonusLabel){
    QPalette pal;
    pal.setColor(bonusLabel->foregroundRole(), Qt::gray);
    bonusLabel->setPalette(pal);
    bonusLabel->setText("0");
}
void Widget::totalShow(int base, QLabel *bonus, QLabel *total){
    total->setText(QString::number(base + bonus->text().toInt()));
}

void Widget::HPCount(){

}

void Widget::constitutionPointsCount(){
    bool ok = 1;
    int raceIndex = ui->raceChoose->currentIndex(), classIndex = ui->classChoose->currentIndex();
    int constitutionPoints, strengthPoints;
    ok = getValueFromLineEdit(ui->constitutionCount, constitutionPoints) && ok;
    ok = getValueFromLineEdit(ui->strengthCount, strengthPoints) && ok;
    if(ok){
        //подсчет телосложения
        if(!bonusShow(ui->constitutionBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->constitutionBonus, raceIndex, 2, 3)){
                noBonusShow(ui->constitutionBonus);
            }
        }
        totalShow(constitutionPoints, ui->constitutionBonus, ui->constitutionTotal);

        //подсчет силы
        if(!bonusShow(ui->strengthBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->strengthBonus, raceIndex, 2, 2)){
                noBonusShow(ui->strengthBonus);
            }
        }
        totalShow(strengthPoints, ui->strengthBonus, ui->strengthTotal);
        //подсчет атлетики
        if(!bonusShow(ui->athleticsBonus, classIndex, 0, 1)){
            noBonusShow(ui->athleticsBonus);
        }
        totalShow(ui->strengthTotal->text().toInt(), ui->athleticsBonus, ui->athleticsTotal);
    }
    else{
        ui->debugLabel->setText("unknow error");
    }
    if(constitutionPoints % 2 == 0){
        ui->healthPoints->setText(QString::number(constitutionPoints/2 + 3));
    }
    else{
        ui->healthPoints->setText(QString::number((constitutionPoints - 1)/2 + 3));
    }
}
void Widget::dexterityPointsCount(){
    bool ok = 1;
    int raceIndex = ui->raceChoose->currentIndex(), classIndex = ui->classChoose->currentIndex();
    int dexterityPoints;
    ok = getValueFromLineEdit(ui->dexterityCount, dexterityPoints) && ok;
    if (ok){
        //подсчет ловкости
        if(!bonusShow(ui->dexterityBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->dexterityBonus, raceIndex, 1, 2)){
                noBonusShow(ui->dexterityBonus);
            }
        }
        totalShow(dexterityPoints, ui->dexterityBonus, ui->dexterityTotal);
        //подсчет акробатики
        if(!bonusShow(ui->acrobaticsBonus, classIndex, 1, 2)){
            noBonusShow(ui->acrobaticsBonus);
        }
        totalShow(ui->dexterityTotal->text().toInt(), ui->acrobaticsBonus, ui->acrobaticsTotal);
        //подсчет ловкости рук
        if(!bonusShow(ui->sleightofhandBonus, classIndex, 1, 1)){
            noBonusShow(ui->sleightofhandBonus);
        }
        totalShow(ui->dexterityTotal->text().toInt(), ui->sleightofhandBonus, ui->sleightofhandTotal);
        //подсчет скрытности
        noBonusShow(ui->stealthBonus);
        totalShow(ui->dexterityTotal->text().toInt(), ui->stealthBonus, ui->stealthTotal);
        ui->speedPoints->setText(QString::number(dexterityPoints * 2));
    }

    else{
        ui->debugLabel->setText("unknow error");
    }
}
void Widget::wisdomPointsCount(){
    bool ok = 1;
    int raceIndex = ui->raceChoose->currentIndex(), classIndex = ui->classChoose->currentIndex(), storyIndex =ui->storyChoose->currentIndex();
    int wisdomPoints;
    ok = getValueFromLineEdit(ui->wisdomCount, wisdomPoints) && ok;
    if(ok){
        //подсчет бонуса мудрости
        if(!bonusShow(ui->wisdomBonus, raceIndex, 1, 2)){
            if(!bonusShow(ui->wisdomBonus, raceIndex, 2, 1))
                noBonusShow(ui->wisdomBonus);
        }
        totalShow(wisdomPoints, ui->wisdomBonus, ui->wisdomTotal);
        //подсчет бонуса внимательности
        if(!bonusShow(ui->perceptionBonus, classIndex, 0, 1)){
            noBonusShow(ui->perceptionBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->perceptionBonus, ui->perceptionTotal);
        //подсчет бонуса выживания
        if(!bonusShow(ui->survivalBonus, storyIndex, 3, 1)){
            noBonusShow(ui->survivalBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->survivalBonus, ui->survivalTotal);
        //подсчет бонуса медицины
        if(!bonusShow(ui->medicineBonus, classIndex, 3, 2)){
            noBonusShow(ui->medicineBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->medicineBonus, ui->medicineTotal);
        //подсчет бонуса проницательности
        if(!bonusShow(ui->insightBonus, storyIndex, 2, 1)){
            noBonusShow(ui->insightBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->insightBonus, ui->insightTotal);
        //подсчет бонуса ухода за животными
        if(!bonusShow(ui->animalhandlingBonus, storyIndex, 3, 2)){
            noBonusShow(ui->animalhandlingBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->animalhandlingBonus, ui->animalhandlingTotal);
    }
    else{
        ui->debugLabel->setText("unknow error");
    }
}
void Widget::intelligencePointsCount(){
    bool ok = 1;
    int raceIndex = ui->raceChoose->currentIndex(), classIndex = ui->classChoose->currentIndex();
    int intelligencePoints;
    ok = getValueFromLineEdit(ui->intelligenceCount, intelligencePoints) && ok;
    if(ok){
        //подсчет бонуса интеллекта
        if(!bonusShow(ui->intelligenceBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->intelligenceBonus, raceIndex, 1, 2)){
                noBonusShow(ui->intelligenceBonus);
            }
        }
        totalShow(intelligencePoints, ui->intelligenceBonus, ui->intelligenceTotal);
        //подсчет бонуса анализа
        if(!bonusShow(ui->investigationBonus, classIndex, 2, 2)){
            noBonusShow(ui->investigationBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->investigationBonus, ui->investigationTotal);
        //подсчет бонуса истории
        if(!bonusShow(ui->historyBonus, classIndex, 2, 1)){
            noBonusShow(ui->historyBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->historyBonus, ui->historyTotal);
        //подсчет бонуса магии
        if(!bonusShow(ui->arcaneBonus, classIndex, 2, 3)){
            noBonusShow(ui->arcaneBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->arcaneBonus, ui->arcaneTotal);
        //подсчет бонуса природы
        noBonusShow(ui->natureBonus);
        totalShow(ui->intelligenceTotal->text().toInt(), ui->natureBonus, ui->natureTotal);
        //подсчет бонуса религии
        if(!bonusShow(ui->religionBonus, classIndex, 2, 3)){
            noBonusShow(ui->religionBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->religionBonus, ui->religionTotal);

    }
    else{
        ui->debugLabel->setText("unknow error");
    }

}
void Widget::charismaPointsCount(){
    bool ok = 1;
    int raceIndex = ui->raceChoose->currentIndex(), classIndex = ui->classChoose->currentIndex(), storyIndex =ui->storyChoose->currentIndex();
    int charismaPoints;
    ok = getValueFromLineEdit(ui->charismaCount, charismaPoints) && ok;
    if(ok){
        //подсчет харизмы
        if(!bonusShow(ui->charismaBonus, raceIndex, 0, 1)){
            noBonusShow(ui->charismaBonus);
        }
        totalShow(charismaPoints, ui->charismaBonus, ui->charismaTotal);
        //подсчет выступления
        if(!bonusShow(ui->performanceBonus, storyIndex, 2, 2)){
            noBonusShow(ui->performanceBonus);
        }
        totalShow(ui->charismaTotal->text().toInt(), ui->performanceBonus, ui->performanceTotal);
        //подсчет запугивания
        if(!bonusShow(ui->intimitationBonus, classIndex, 0, 2)){
            noBonusShow(ui->intimitationBonus);
        }
        totalShow(ui->charismaTotal->text().toInt(), ui->intimitationBonus, ui->intimitationTotal);
        //подсчет обмана
        if(!bonusShow(ui->deceptionBonus, classIndex, 1, 1)){
            noBonusShow(ui->deceptionBonus);
        }
        totalShow(ui->charismaTotal->text().toInt(), ui->deceptionBonus, ui->deceptionTotal);
        //подсчет убеждения
        noBonusShow(ui->persuationBonus);
        totalShow(ui->charismaTotal->text().toInt(), ui->persuationBonus, ui->persuationTotal);

    }
    else{
        ui->debugLabel->setText("unknow error");
    }
}
void Widget::pointsCounter(){
    bool ok = 1;
    int raceIndex = ui->raceChoose->currentIndex(), classIndex = ui->classChoose->currentIndex(), storyIndex =ui->storyChoose->currentIndex();
    int constitutionPoints, strengthPoints, dexterityPoints, wisdomPoints, intelligencePoints, charismaPoints;
    ok = getValueFromLineEdit(ui->constitutionCount, constitutionPoints) && ok;
    ok = getValueFromLineEdit(ui->strengthCount, strengthPoints) && ok;
    ok = getValueFromLineEdit(ui->dexterityCount, dexterityPoints) && ok;
    ok = getValueFromLineEdit(ui->wisdomCount, wisdomPoints) && ok;
    ok = getValueFromLineEdit(ui->intelligenceCount, intelligencePoints) && ok;
    ok = getValueFromLineEdit(ui->charismaCount, charismaPoints) && ok;


    if(ok){
        //подсчет телосложения
        if(!bonusShow(ui->constitutionBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->constitutionBonus, raceIndex, 2, 3)){
                noBonusShow(ui->constitutionBonus);
            }
        }
        totalShow(constitutionPoints, ui->constitutionBonus, ui->constitutionTotal);

        //подсчет силы
        if(!bonusShow(ui->strengthBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->strengthBonus, raceIndex, 2, 2)){
                noBonusShow(ui->strengthBonus);
            }
        }
        totalShow(strengthPoints, ui->strengthBonus, ui->strengthTotal);
        //подсчет атлетики
        if(!bonusShow(ui->athleticsBonus, classIndex, 0, 1)){
            noBonusShow(ui->athleticsBonus);
        }
        totalShow(ui->strengthTotal->text().toInt(), ui->athleticsBonus, ui->athleticsTotal);

        if(constitutionPoints % 2 == 0){
            ui->healthPoints->setText(QString::number(constitutionPoints/2 + 3));
        }
        else{
            ui->healthPoints->setText(QString::number((constitutionPoints - 1)/2 + 3));
        }

        //подсчет ловкости
        if(!bonusShow(ui->dexterityBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->dexterityBonus, raceIndex, 1, 2)){
                noBonusShow(ui->dexterityBonus);
            }
        }
        totalShow(dexterityPoints, ui->dexterityBonus, ui->dexterityTotal);
        //подсчет акробатики
        if(!bonusShow(ui->acrobaticsBonus, classIndex, 1, 2)){
            noBonusShow(ui->acrobaticsBonus);
        }
        totalShow(ui->dexterityTotal->text().toInt(), ui->acrobaticsBonus, ui->acrobaticsTotal);
        //подсчет ловкости рук
        if(!bonusShow(ui->sleightofhandBonus, classIndex, 1, 1)){
            noBonusShow(ui->sleightofhandBonus);
        }
        totalShow(ui->dexterityTotal->text().toInt(), ui->sleightofhandBonus, ui->sleightofhandTotal);
        //подсчет бонуса скрытности
        noBonusShow(ui->stealthBonus);
        totalShow(ui->dexterityTotal->text().toInt(), ui->stealthBonus, ui->stealthTotal);

        ui->speedPoints->setText(QString::number(dexterityPoints * 2));

        //подсчет бонуса мудрости
        if(!bonusShow(ui->wisdomBonus, raceIndex, 1, 2)){
            if(!bonusShow(ui->wisdomBonus, raceIndex, 2, 1))
                noBonusShow(ui->wisdomBonus);
        }
        totalShow(wisdomPoints, ui->wisdomBonus, ui->wisdomTotal);
        //подсчет бонуса внимательности
        if(!bonusShow(ui->perceptionBonus, classIndex, 0, 1)){
            noBonusShow(ui->perceptionBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->perceptionBonus, ui->perceptionTotal);
        //подсчет бонуса выживания
        if(!bonusShow(ui->survivalBonus, storyIndex, 3, 1)){
            noBonusShow(ui->survivalBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->survivalBonus, ui->survivalTotal);
        //подсчет бонуса медицины
        if(!bonusShow(ui->medicineBonus, classIndex, 3, 2)){
            noBonusShow(ui->medicineBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->medicineBonus, ui->medicineTotal);
        //подсчет бонуса проницательности
        if(!bonusShow(ui->insightBonus, storyIndex, 2, 1)){
            noBonusShow(ui->insightBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->insightBonus, ui->insightTotal);
        //подсчет бонуса ухода за животными
        if(!bonusShow(ui->animalhandlingBonus, storyIndex, 3, 2)){
            noBonusShow(ui->animalhandlingBonus);
        }
        totalShow(ui->wisdomTotal->text().toInt(), ui->animalhandlingBonus, ui->animalhandlingTotal);

        //подсчет бонуса интеллекта
        if(!bonusShow(ui->intelligenceBonus, raceIndex, 0, 1)){
            if(!bonusShow(ui->intelligenceBonus, raceIndex, 1, 2)){
                noBonusShow(ui->intelligenceBonus);
            }
        }
        totalShow(intelligencePoints, ui->intelligenceBonus, ui->intelligenceTotal);
        //подсчет бонуса анализа
        if(!bonusShow(ui->investigationBonus, classIndex, 2, 2)){
            noBonusShow(ui->investigationBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->investigationBonus, ui->investigationTotal);
        //подсчет бонуса истории
        if(!bonusShow(ui->historyBonus, classIndex, 2, 1)){
            noBonusShow(ui->historyBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->historyBonus, ui->historyTotal);
        //подсчет бонуса магии
        if(!bonusShow(ui->arcaneBonus, classIndex, 2, 3)){
            noBonusShow(ui->arcaneBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->arcaneBonus, ui->arcaneTotal);
        //подсчет бонуса природы
        noBonusShow(ui->natureBonus);
        totalShow(ui->intelligenceTotal->text().toInt(), ui->natureBonus, ui->natureTotal);
        //подсчет бонуса религии
        if(!bonusShow(ui->religionBonus, classIndex, 2, 3)){
            noBonusShow(ui->religionBonus);
        }
        totalShow(ui->intelligenceTotal->text().toInt(), ui->religionBonus, ui->religionTotal);


        //подсчет харизмы
        if(!bonusShow(ui->charismaBonus, raceIndex, 0, 1)){
            noBonusShow(ui->charismaBonus);
        }
        totalShow(charismaPoints, ui->charismaBonus, ui->charismaTotal);
        //подсчет выступления
        if(!bonusShow(ui->performanceBonus, storyIndex, 2, 2)){
            noBonusShow(ui->performanceBonus);
        }
        totalShow(ui->charismaTotal->text().toInt(), ui->performanceBonus, ui->performanceTotal);
        //подсчет запугивания
        if(!bonusShow(ui->intimitationBonus, classIndex, 0, 2)){
            noBonusShow(ui->intimitationBonus);
        }
        totalShow(ui->charismaTotal->text().toInt(), ui->intimitationBonus, ui->intimitationTotal);
        //подсчет обмана
        if(!bonusShow(ui->deceptionBonus, classIndex, 1, 1)){
            noBonusShow(ui->deceptionBonus);
        }
        totalShow(ui->charismaTotal->text().toInt(), ui->deceptionBonus, ui->deceptionTotal);
        //подсчет убеждения
        noBonusShow(ui->persuationBonus);
        totalShow(ui->charismaTotal->text().toInt(), ui->persuationBonus, ui->persuationTotal);

    }
    else{
        ui->debugLabel->setText("unknow error");
    }
}


//Вызов смены картинок
void Widget::on_raceChoose_currentIndexChanged(int index)
{
    characterImageSet(index, ui->classChoose->currentIndex());
    pointsCounter();
}
void Widget::on_classChoose_currentIndexChanged(int index)
{
    characterImageSet(ui->raceChoose->currentIndex(), index);
    pointsCounter();
}
void Widget::on_storyChoose_currentIndexChanged(int index)
{
    pointsCounter();
}



void Widget::on_constitutionPlusButton_clicked()
{
    oneCounter(ui->constitutionCount, 1);
    constitutionPointsCount();
}
void Widget::on_strengthPlusButton_clicked()
{
    oneCounter(ui->strengthCount, 1);
    constitutionPointsCount();
}
void Widget::on_dexterityPlusButton_clicked()
{
    oneCounter(ui->dexterityCount, 1);
    dexterityPointsCount();
}
void Widget::on_wisdomPlusButton_clicked()
{
    oneCounter(ui->wisdomCount, 1);
    wisdomPointsCount();
}
void Widget::on_intelligencePlusButton_clicked()
{
    oneCounter(ui->intelligenceCount, 1);
    intelligencePointsCount();
}
void Widget::on_charismaPlusButton_clicked()
{
    oneCounter(ui->charismaCount, 1);
    charismaPointsCount();
}


void Widget::on_constitutionMinusButton_clicked()
{
    oneCounter(ui->constitutionCount, 0);
    constitutionPointsCount();
}
void Widget::on_strengthMinusButton_clicked()
{
    oneCounter(ui->strengthCount, 0);
    constitutionPointsCount();
}
void Widget::on_dexterityMinusLabel_clicked()
{
    oneCounter(ui->dexterityCount, 0);
    dexterityPointsCount();
}
void Widget::on_wisdomMinusButton_clicked()
{
    oneCounter(ui->wisdomCount, 0);
    wisdomPointsCount();
}
void Widget::on_intelligenceMinusButton_clicked()
{
    oneCounter(ui->intelligenceCount, 0);
    intelligencePointsCount();
}
void Widget::on_charismaMinusButton_clicked()
{
    oneCounter(ui->charismaCount, 0);
    charismaPointsCount();
}
