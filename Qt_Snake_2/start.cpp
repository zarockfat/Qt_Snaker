#include "start.h"
#include "ui_start.h"
#include <QPalette>
#include <QApplication>
#include <QDebug>
start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    //设置窗口全局坐标
    this->setGeometry(500, 200, 280, 260);
   // ui->label->setAlignment(Qt::AlignHCenter);
    //填充开始界面图片背景
    QPalette picture;
    picture.setBrush(QPalette::Window, QBrush(QPixmap("snake.png")));
    this->setPalette(picture);
    //关联游戏退出时回到开始界面信号与槽
    connect(gameWind, SIGNAL(abc()), this, SLOT(onGameOver()));

}

start::~start()
{
    delete ui;
}

//点击开始游戏，弹出游戏界面，隐藏该界面
void start::on_pushButton_clicked()
{
   gameWind = new Widget(ui->comboBox->currentIndex() + 1);
   gameWind->show();
   this->hide();
}

void start::onGameOver()
{
   this->show();
}
