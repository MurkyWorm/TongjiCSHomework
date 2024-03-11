#ifndef SITECHOOSEWINDOW_H
#define SITECHOOSEWINDOW_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>

class SiteChooseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SiteChooseWindow(QWidget *parent = nullptr);

    //设置图片列表
    void setImgList(QStringList imgList);

    //初始化图片切换按钮
    void initChangeImgBtn();
    //开始显示
    void startPlay();
    //重写绘图事件
    void paintEvent(QPaintEvent *pev);

    //图片列表
    QStringList imgList;
    //当前显示图片的序号
    int currentImgIndex = 0;
    //切换前后两张图片
    QPixmap currentPix;
    QPixmap nextPix;
    //图片切换动画
    QPropertyAnimation* opacityAnimation;
    //按钮列表
    QList<QPushButton*> btnList;

    //是否选择了场景
    bool isChoose = 0;

    //燃烧动画计时器对象
    QTimer *flameTimer;

    //燃烧图片计数
    int flameCount = 1;

signals:
    void hasChosen();//选择信号
    void cancelChosen();//取消选择信号
public slots:
    //在点击按钮时切换图片
    void imgChange(int btnId);
};

#endif // SITECHOOSEWINDOW_H
