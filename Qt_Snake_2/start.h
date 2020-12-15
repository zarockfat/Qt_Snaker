#ifndef START_H
#define START_H

#include <QWidget>
#include <widget.h>

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = 0);
    ~start();

private slots:
    void on_pushButton_clicked();
    //游戏界面关闭时，回到开始界面
    void onGameOver();

private:
    Ui::start *ui;
    //游戏主界面
    Widget *gameWind;
};

#endif // START_H
