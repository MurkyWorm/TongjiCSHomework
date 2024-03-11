#include "sitechoosewindow.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <mypushbutton.h>

SiteChooseWindow::SiteChooseWindow(QWidget *parent) : QWidget(parent)
{
    this->setProperty("imgOpacity", 1.0);

    //初始化动画切换类
    this->opacityAnimation = new QPropertyAnimation(this, "imgOpacity");
    //设置动画时间
    this->opacityAnimation->setDuration(600);

    //设置透明度变化范围
    this->opacityAnimation->setStartValue(1.0);
    this->opacityAnimation->setEndValue(0.0);

    //透明度变化时更新显示
    connect(this->opacityAnimation, &QPropertyAnimation::valueChanged, this, [=](){
        this->update();
    });

    //显示标题
    QLabel *titleLabel = new QLabel;
    titleLabel->setParent(this);
    titleLabel->setFixedSize(100, 50);
    //设置字体
    QFont font;
    font.setFamily("宋体");
    font.setBold(true);
    //设置位置与对齐
    titleLabel->move(10, 10);
    titleLabel->setFont(font);
    titleLabel->setText("场景选择");
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //设置选择按钮
    MyPushButton * chooseBtn = new MyPushButton(":/cover/cover/CoverButton.png", "", 0.62, 0.78);
    chooseBtn->setParent(this);
    chooseBtn->move(this->width() - chooseBtn->width() - 15, this->height() * 0.58);

    //选择标签
    QLabel * newLabel = new QLabel;
    newLabel->setParent(this);
    newLabel->setFixedSize(chooseBtn->width(), chooseBtn->height());
    newLabel->setFont(font);
    newLabel->setText("选择");
    newLabel->setStyleSheet("color:white");
    newLabel->move(this->width() - chooseBtn->width() - 15, this->height() * 0.58);
    //设置label上的文字对齐方式
    newLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //设置让鼠标进行穿透
    newLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    //设置木柴图标
    QLabel *fireLabel = new QLabel(this);
    QPixmap firePix;
    firePix.load(":/play/play/woods.png");
    firePix = firePix.scaled(70, 80);
    fireLabel->setFixedSize(firePix.width(), firePix.height());
    fireLabel->setPixmap(firePix);
    fireLabel->move(0.5 * (this->width() - fireLabel->width()), 0.35 * this->height());

    //初始化动画计时器对象
    this->flameTimer = new QTimer(this);

    //设置点击按钮效果
    connect(chooseBtn, &MyPushButton::clicked, [=](){
        //设置弹跳效果
        chooseBtn->zoom1();
        chooseBtn->zoom2();
        //改变文字
        if (this->isChoose == false) {
            newLabel->setText("取消选择");
            this->isChoose = true;

            //开始燃烧
            flameTimer->start(30);
            qDebug() << "开始燃烧啦";

            //发出选中信号
            emit hasChosen();
        }
        else {
            newLabel->setText("选择");
            this->isChoose = false;

            flameTimer->stop();
            fireLabel->setPixmap(firePix);

            //发出取消信号
            emit cancelChosen();
        }
    });

    //燃烧动画实现
    connect(flameTimer, &QTimer::timeout, [=](){
        QPixmap firesPix;
        QString str = QString(":/play/play/flame%1.png").arg(this->flameCount++);
        firesPix.load(str);
        firesPix = firesPix.scaled(70, 80);
        fireLabel->setPixmap(firesPix);
        //判断是否到达最大，循环
        if (this->flameCount > 5) {
            this->flameCount = 1;
        }
    });
}

void SiteChooseWindow::initChangeImgBtn() {
    QButtonGroup* changeBtnGroup = new QButtonGroup;

    //水平容器
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();

    for (int i = 0; i < this->imgList.count(); i++) {
        //创建按钮
        QPushButton* btn = new QPushButton;
        btn->setFixedSize(QSize(25, 25));
        btn->setCheckable(true);
        btn->setStyleSheet("QPushButton{border-image:url(:/create/create/UncheckedButton.png);}\
                            QPushButton:checked{border-image:url(:/create/create/CheckedButton.png);}");
        //将按钮添加入按钮组
        changeBtnGroup->addButton(btn, i);
        this->btnList.append(btn);
        hLayout->addWidget(btn);
    }

    //设置默认按钮
    (changeBtnGroup->button(0))->setChecked(true);

    //设置排列样式
    hLayout->addStretch();
    hLayout->setSpacing(10);
    hLayout->setMargin(0);

    //设置点击按钮切换图片
    void( QButtonGroup:: * btnClicked )(int index) = &QButtonGroup::buttonClicked;
    connect(changeBtnGroup, btnClicked, this, [=](int index){
        for (int i = 0; i < this->imgList.count(); i++) {
            changeBtnGroup->button(i)->setEnabled(false);
        }
        QTimer::singleShot(630, this, [=](){
            for (int i = 0; i < this->imgList.count(); i++) {
                changeBtnGroup->button(i)->setEnabled(true);
            }
        });
        this->imgChange(index);
    });

    //设置选中时禁用按钮
    connect(this, &SiteChooseWindow::hasChosen, [=](){
        for (int i = 0; i < this->imgList.count(); i++) {
            changeBtnGroup->button(i)->setEnabled(false);
        }
    });
    //设置取消选中时启用按钮
    connect(this, &SiteChooseWindow::cancelChosen, [=](){
        for (int i = 0; i < this->imgList.count(); i++) {
            changeBtnGroup->button(i)->setEnabled(true);
        }
    });

    //设置垂直布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(hLayout);
    mainLayout->setContentsMargins(0, 0, 0, 20);

}

void SiteChooseWindow::setImgList(QStringList imgList) {
    this->imgList = imgList;
}

//设置初始图片
void SiteChooseWindow::startPlay() {
    this->initChangeImgBtn();
    currentPix = QPixmap(this->imgList.at(this->currentImgIndex));
    nextPix = QPixmap(this->imgList.at(this->currentImgIndex));
}

void SiteChooseWindow::paintEvent(QPaintEvent *pev) {
    QPainter painter(this);
    QRect imgRect = this->rect();

    //准备下一张图片
    painter.setOpacity(1);
    painter.drawPixmap(imgRect, this->nextPix.scaled(imgRect.size()));

    //画标题
    QPixmap titlePix;
    titlePix.load(":/create/create/Title.png");
    titlePix = titlePix.scaled(100, 50);
    painter.drawPixmap(10, 10, titlePix);

    //画出当前图片
    float imageOpacity = this->property("imgOpacity").toFloat();
    painter.setOpacity(imageOpacity);
    painter.drawPixmap(imgRect, this->currentPix.scaled(imgRect.size()));

    painter.drawPixmap(10, 10, titlePix);
}

void SiteChooseWindow::imgChange(int btnId) {
    this->nextPix = QPixmap(this->imgList.at(btnId));
    this->opacityAnimation->start();
    QTimer::singleShot(620, this, [=](){
        this->currentImgIndex = btnId;
        qDebug() << this->currentImgIndex;
        currentPix = QPixmap(this->imgList.at(this->currentImgIndex));
    });
}
