#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_raceChoose_currentIndexChanged(int index);

    void characterImageSet(int raseIndex, int classIndex);

    void on_classChoose_currentIndexChanged(int index);

    void skillCounter();

    void on_skillButton_clicked();

    void oneCounter(QLineEdit *edit, bool operand);

    void on_constitutionPlusButton_clicked();



    void on_strengthPlusButton_clicked();

    void on_dexterityPlusButton_clicked();

    void on_wisdomPlusButton_clicked();

    void on_intelligencePlusButton_clicked();

    void on_charismaPlusButton_clicked();

    void on_constitutionMinusButton_clicked();

    void on_strengthMinusButton_clicked();

    void on_dexterityMinusLabel_clicked();

    void on_wisdomMinusButton_clicked();

    void on_intelligenceMinusButton_clicked();

    void on_charismaMinusButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
