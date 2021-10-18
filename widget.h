#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

/*  void on_constitutionCount_editingFinished();

    void on_streightCount_editingFinished();

    void on_dexterityCount_editingFinished();

    void on_wisdomCount_editingFinished();

    void on_intelligenceCount_editingFinished();

    void on_charismaCount_editingFinished();
*/
    void on_skillButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
