#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <ctime>
Widget::Widget(int _currentPoints, QWidget *parent) :
    currentPoints(_currentPoints), QWidget(parent), posHead(100, 100), initFood(true),length(5),currentDirection(RIGHT),socker(0), currentSpeed(300 - (_currentPoints-1)*50),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置窗口大小,窗口填充色
    this->resize(400, 400);
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::black, Qt::black));
    //初始化画笔跟画刷
    //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
    pen.setColor(QColor(0,0,255, 200));
    pen.setWidth(1);
    //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush.setColor(QColor(255,0,0));
    brush.setStyle(Qt::SolidPattern);
    //设置当前关卡
    qDebug() << _currentPoints;
     ui->labelP->setText(QString("%1:%2").arg("Points").arg(currentPoints));
    //ui->lineEdit_2->setText(QString("%1").arg(_currentPoints));
    //将蛇的初始化所有节点坐标存放到链表
    for(int i = 0; i < length; i++)
    {
        nodePos.setX(posHead.x() - 10*i);
        nodePos.setY(posHead.y());
        list.append(nodePos);
    }
    //产生随机数
    srand(time(NULL));
    //关联定时器信号与槽
    timer.start(currentSpeed);
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

Widget::~Widget()
{
    delete ui;
}


//绘画事件一运行就会自动执行一次，下次运行是使用update
void Widget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    //画一条横线
    //painter.drawLine(0, ui->label->y() + ui->label->height(), this->height(), ui->label->y() + ui->label->height());

    //游戏开始时先随机画一个食物
    if(initFood)
    {
        posFood.setX(rand() % (this->width()/10) * 10);
        posFood.setY((rand() % (this->height()/10)) * 10);
        painter.drawRect(posFood.x(), posFood.y(), 10, 10);
        initFood = false;
    }
    else
    {
        painter.drawRect(posFood.x(), posFood.y(), 10, 10);
    }

    //遍历链表来画出蛇
    foreach (QPoint pos, list) {
       painter.drawRect(pos.x(), pos.y(), 10, 10);
    }
}

void Widget::onTimeOut()
{
    //根据方向求出下一个将要出现点的坐标
    switch (currentDirection) {
    case UP:
        posHead.setY(posHead.y() - 10);
        break;
    case DOWN:
        posHead.setY(posHead.y() + 10);
        break;
    case LEFT:
        posHead.setX(posHead.x() - 10);
        break;
    case RIGHT:
        posHead.setX(posHead.x() + 10);
        break;
    }
    //判断头节点是否碰到墙壁，如果碰到则弹窗结束游戏
//    qDebug() << QString("x:%1").arg(posHead.x());
//    qDebug() <<  QString("y:%1").arg(posHead.y());
    judgeArriveEdge(posHead);
    //判断蛇头是否撞到蛇身
    judgeEatSelf(posHead);
    //将新节点（蛇头）添加到链表里面去
    list.insert(0, posHead);
    //将蛇尾去掉
    //如果新节点刚好与食物位置相同，则不去掉蛇尾
    if(posHead == posFood)
    {
        //设置当前分数
        socker += 1;
        ui->labelS->setText(QString("%1:%2").arg("Socker").arg(socker));
        //ui->lineEdit->setText(QString("%1").arg(socker));
        //设置当前速度
        if(currentSpeed != 100)
        {
            currentSpeed = 400 - (currentPoints-1)*50;
        }
        //每吃3个关卡加1 并且改变速度
        if(socker % 3 == 0 && currentPoints != 5)
        {
            currentPoints += 1;
            timer.stop();
            timer.start(currentSpeed);
        }
        ui->labelP->setText(QString("%1:%2").arg("Points").arg(currentPoints));
        //ui->lineEdit_2->setText(QString("%1").arg(currentPoints));
        //ui->comboBox->setCurrentIndex(socker / 5 +1);
        //产生新食物
        initFood = true;
    }
    else
    {
        list.removeLast();
    }
    //更新绘画事件
    update();
}

//改变蛇的方向
void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Up:
        if(currentDirection != DOWN)
            currentDirection = UP;
            break;
        case Qt::Key_Down:
        if(currentDirection != UP)
            currentDirection = DOWN;
            break;
        case Qt::Key_Left:
        if(currentDirection != RIGHT)
            currentDirection = LEFT;
            break;
        case Qt::Key_Right:
        if(currentDirection != LEFT)
            currentDirection = RIGHT;
            break;
        case Qt::Key_Space:
            timer.stop();
            QMessageBox::information(this, "暂停", "按空格继续");
            timer.start(currentSpeed);
    }
}

//判断是否撞墙
void Widget::judgeArriveEdge(QPoint pos)
{
    if(pos.x() > (this->width() - 10) || pos.x() < 0 || pos.y() > this->height() - 10 || pos.y() < 0)
    {
       QMessageBox::information(this, "游戏结束", "出界");
       this->close();
    }
}
//判断是否咬到自己
void Widget::judgeEatSelf(QPoint pos)
{
    foreach (QPoint point, list) {
       if(point == pos)
       {
            QMessageBox::information(this, "游戏结束", "咬到自己");
            this->close();
       }
    }
}

//复写关闭函数
void Widget::closeEvent(QCloseEvent *event)
{
   emit abc();
}
