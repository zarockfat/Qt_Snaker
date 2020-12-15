#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QLayout>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QCloseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(int _currentPoints, QWidget *parent = 0);
    ~Widget();
    enum direction {UP, DOWN, LEFT, RIGHT};
    //复写绘画事件
    void paintEvent(QPaintEvent *event);
    //复写按键操作函数
    void keyPressEvent(QKeyEvent *event);
    //判断蛇头坐标是否碰墙
    void judgeArriveEdge(QPoint pos);
    //判断蛇头是否撞到蛇身
    void judgeEatSelf(QPoint pos);
    //设置当前关卡
    void setCurrentPoints(int a){currentPoints = a;}
    //复写窗口关闭函数
    void closeEvent(QCloseEvent *event);


signals:
    //窗口关闭时发送的信号
    void abc();

private slots:
    //计时器
    void onTimeOut();

private:
    Ui::Widget *ui;
    int length;		//蛇身长度
    QPoint posHead; //蛇头坐标
    QPoint nodePos; // 蛇身节点坐标
    QPoint posFood; //随机生成食物坐标
    bool initFood;  //初始化蛇食物的标志位

    QList<QPoint> list; //存放蛇身节点坐标

    direction currentDirection;//蛇当前移动方向

    QPen pen;           //定义画笔
    QBrush brush;       //定义画刷
    QTimer timer;       //定义定时器更新绘画事件

    int socker;         //分数，所吃的方块数
    int currentSpeed;   //当前速度
    int currentPoints;  //当前关卡

};

#endif // WIDGET_H
