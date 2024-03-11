#include "playscene.h"
#include "ui_playscene.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <cstdlib>
#include <ctime>
#include <sitedisplaydata.h>
#include <QTimer>
#include "playchara.h"
#include "charaspeakcontent.h"
#include <QFontMetrics>
#include <QFont>
#include <QPainter>
#include <QPropertyAnimation>
#include "punishcontent.h"
#include <QScrollArea>

PlayScene::PlayScene(int mapChoice, int modeChoice, QStringList charas, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayScene)
{
    ui->setupUi(this);

    //设置游戏模式
    this->modeChoice = modeChoice;

    //设置固定大小
    this->setFixedSize(720, 1140);

    //设置背景框样式和大小
    ui->widget->setFixedSize(this->width() - 80, 1000);
    ui->widget->move(40, 40);
    ui->widget->setStyleSheet("background-color: rgba(255, 255, 255, 64);");

    //设置显示区域的样式和大小
    ui->displayWindow->setFixedHeight(180);
    //ui->displayWindow->setStyleSheet("background-color: rgba(255, 255, 255, 128);");

    //设置主区域的样式和大小
    ui->mainWindow->setFixedSize(614, 614);
    ui->mainWindow->setStyleSheet("background-color: rgba(255, 255, 255, 128);border: 4px solid white;");
    qDebug() << ui->mainWindow->width();

    //设置操作区域的样式和大小
    ui->operateWindow->setFixedHeight(150);
    ui->operateWindow->setStyleSheet("background-color: rgba(180, 180, 180, 128);border: 1px solid black;");

    //设置图标
    this->setWindowIcon(QIcon(":/cover/cover/Pikachu.png"));

    //设置标题
    this->setWindowTitle("游戏场景");

    //设置状态显示栏
    QLabel *profileLabel = new QLabel(ui->talkArea);
    QLabel *infoLabel = new QLabel(ui->talkArea);
    //设置头像标签的大小和位置
    profileLabel->setFixedSize(132, 124);
    profileLabel->move(0, 0);
    profileLabel->setStyleSheet("background-color: rgba(100, 100, 100, 255);");
    //设置信息显示标签的大小和位置
    infoLabel->setFixedSize(315, 124);
    infoLabel->move(132, 0);
    infoLabel->setStyleSheet("background-color: rgba(255, 255, 255, 200);");
    infoLabel->setAlignment(Qt::AlignTop);
    infoLabel->setWordWrap(true);

    //设置主区域
    QLabel *mainLabel = new QLabel(ui->mainWindow);
    SiteDisplayData *siteData = new SiteDisplayData;
    //加载图片并调整大小
    QPixmap map;
    QString mapStr = QString(":/play/play/PlaySite%1.png").arg(mapChoice + 1);
    qDebug() << mapStr;
    qDebug() << map.load(mapStr);
    map = map.scaled(614, 614);
    //显示地图
    mainLabel->setPixmap(map);
    mainLabel->setFixedSize(614, 614);
    mainLabel->move(0, 0);
    //显示地图上的火堆
    QTimer *fireTimer = new QTimer(this);
    fireTimer->start(30);
    QLabel *fireLabel = new QLabel(ui->mainWindow);
    fireLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);border: 0px;");
    qDebug() << mapChoice;
    fireLabel->move(siteData->mapCenterData[mapChoice + 1][0] * (ui->mainWindow->height() - 70), siteData->mapCenterData[mapChoice + 1][1] * (ui->mainWindow->height() - 80));
    fireLabel->setPixmap(QPixmap(":/play/play/woods.png"));
    fireLabel->setFixedSize(70, 80);
    connect(fireTimer, &QTimer::timeout, [=](){
        QPixmap firesPix;
        QString str = QString(":/play/play/flame%1.png").arg(this->fireCount++);
        firesPix.load(str);
        firesPix = firesPix.scaled(70, 80);
        fireLabel->setPixmap(firesPix);
        //判断是否到达最大，循环
        if (this->fireCount > 5) {
            this->fireCount = 1;
        }
    });
    //显示围在火堆旁的角色
    //获取实际的选中角色
    QStringList trueCharas;
    for (int i = 0; i < charas.count(); i++) {
        if (charas[i] == "true") {
            trueCharas << charas[i - 2] << charas[i - 1];
        }
    }
    qDebug() << "实际添加的角色有" << trueCharas;
    //放置角色
    int charaCount = 0;//计数已经放置的角色个数
    PlayChara *playCharas[16];
    int charaXs[16];
    int charaYs[16];//维护放置角色用的数组
    for (int i = 0; i < 16; i++) {
        if (siteData->charaLocData[trueCharas.count() / 2][siteData->visitOrder[i][0]][siteData->visitOrder[i][1]] == 1) {
            int charaX = siteData->mapCenterData[mapChoice + 1][0] * (ui->mainWindow->height() - fireLabel->height());
            int charaY = 50 + siteData->mapCenterData[mapChoice + 1][1] * (ui->mainWindow->height() - fireLabel->width());
            if (siteData->visitOrder[i][0] == 0) {
                int charaNo = trueCharas[charaCount * 2].toInt();
                charaCount++;
                PlayChara *playChara = new PlayChara(charaNo, 1);
                playChara->name = trueCharas[charaCount * 2 - 1];
                playCharas[charaCount - 1] = playChara;
                playChara->setParent(ui->mainWindow);//创建角色并设置父亲
                charaY = charaY - 140;
                charaX = charaX + siteData->visitOrder[i][1] * 50 - 110;
                playChara->move(charaX, charaY);
                charaXs[charaCount - 1] = charaX;
                charaYs[charaCount - 1] = charaY;
                playChara->setStyleSheet("background-color: rgba(255, 255, 255, 0);border:0px");//设置位置和风格
            }
            else if (siteData->visitOrder[i][0] == 5) {
                int charaNo = trueCharas[charaCount * 2].toInt();
                charaCount++;
                PlayChara *playChara = new PlayChara(charaNo, 3);
                playChara->name = trueCharas[charaCount * 2 - 1];
                playCharas[charaCount - 1] = playChara;
                playChara->setParent(ui->mainWindow);
                charaY = charaY + 80;
                charaX = charaX + siteData->visitOrder[i][1] * 50 - 110;
                playChara->move(charaX, charaY);
                charaXs[charaCount - 1] = charaX;
                charaYs[charaCount - 1] = charaY;
                playChara->setStyleSheet("background-color: rgba(255, 255, 255, 0);border:0px");
            }
            else if (siteData->visitOrder[i][1] == 0) {
                int charaNo = trueCharas[charaCount * 2].toInt();
                charaCount++;
                PlayChara *playChara = new PlayChara(charaNo, 4);
                playChara->name = trueCharas[charaCount * 2 - 1];
                playCharas[charaCount - 1] = playChara;
                playChara->setParent(ui->mainWindow);
                charaY = charaY + siteData->visitOrder[i][0] * 50 - 155;
                charaX = charaX - 110;
                playChara->move(charaX, charaY);
                charaXs[charaCount - 1] = charaX;
                charaYs[charaCount - 1] = charaY;
                playChara->setStyleSheet("background-color: rgba(255, 255, 255, 0);border:0px");
            }
            else {
                int charaNo = trueCharas[charaCount * 2].toInt();
                charaCount++;
                PlayChara *playChara = new PlayChara(charaNo, 2);
                playChara->name = trueCharas[charaCount * 2 - 1];
                playCharas[charaCount - 1] = playChara;
                playChara->setParent(ui->mainWindow);
                charaY = charaY + siteData->visitOrder[i][0] * 50 - 155;
                charaX = charaX + 140;
                playChara->move(charaX, charaY);
                charaXs[charaCount - 1] = charaX;
                charaYs[charaCount - 1] = charaY;
                playChara->setStyleSheet("background-color: rgba(255, 255, 255, 0);border:0px");
            }
        }
    }

    //设置状态显示栏的初始状态
    QPixmap profilePix;
    QString profileStr = QString(":/chara/chara/chara%1-1-1.png").arg(playCharas[this->charaOperateNo - 1]->charaNo);
    profilePix.load(profileStr);
    profilePix = profilePix.scaled(profileLabel->width(), profileLabel->height());
    profileLabel->setPixmap(profilePix);//显示初始图片
    QFont infoFont;
    infoFont.setFamily("宋体");
    infoFont.setPointSize(10);
    infoFont.setBold(true);
    infoLabel->setFont(infoFont);
    QString infoStr = QString("轮到%1投掷骰子").arg(playCharas[this->charaOperateNo - 1]->name);
    infoLabel->setText(infoStr);

    //设置骰子区域
    this->circleTimer = new QTimer(this);
    ui->diceArea->setFixedWidth(132);
    QPushButton *diceBtn = new QPushButton(ui->diceArea);//设置骰子按钮的属性
    diceBtn->setFixedSize(ui->diceArea->width(), ui->diceArea->width());
    //设置骰子标签图片
    QLabel *diceLabel = new QLabel(ui->diceArea);
    diceLabel->setPixmap(QPixmap(":/play/play/dice.png"));
    diceLabel->setAlignment(Qt::AlignCenter);
    diceLabel->setFixedSize(ui->diceArea->width(), ui->diceArea->width());
    diceLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    //实现点击骰子的功能
    connect(diceBtn, &QPushButton::clicked, [=](){
        QString infoStr = QString("%1投出了骰子！").arg(playCharas[this->charaOperateNo - 1]->name);
        infoLabel->setText(infoStr);
        //初始化随机数种子
        std::srand(std::time(nullptr));
        //生成一个随机整数在1到6之间
        int diceNumber = std::rand() % 6 + 1;
        this->diceNumder = diceNumber;
        QString diceStr = QString(":/play/play/dice%1.gif").arg(diceNumber);
        //播放gif
        QMovie *diceMovie = new QMovie(diceStr);
        diceLabel->setMovie(diceMovie);
        diceMovie->start();
        diceBtn->setEnabled(false);

        //当前角色跳一下
        QTimer::singleShot(1900, this, [=](){
            QString infoStr = QString("%1投出了%2点！").arg(playCharas[this->charaOperateNo - 1]->name).arg(diceNumber);
            infoLabel->setText(infoStr);
            playCharas[this->charaOperateNo - 1]->jump1();
            playCharas[this->charaOperateNo - 1]->jump2();
        });

        //开始绕圈
        QTimer::singleShot(1600, this, [=](){
            this->circleTimer->start(1200);
        });
    });

    //初始化真心话大冒险惩罚条
    this->punishContent = new PunishContent(this);//获取惩罚词条信息
    this->punishs = new QLabel(ui->displayWindow);
    this->punishs->setFixedSize(632, 2700);
    this->punishs->setStyleSheet("background-color: rgba(255, 255, 255, 255);border:0px");
    this->punishs->move(0, 0);
    this->generatePunishs(1);
    //设置抽取惩罚卡片按钮
    QPushButton *punishBtn = new QPushButton;
    punishBtn->setParent(ui->displayWindow);
    QFont punishFont;
    punishFont.setFamily("宋体");
    punishFont.setBold(true);
    punishBtn->setFont(punishFont);
    punishBtn->setText("抽取卡片");
    punishBtn->move(430, 120);
    punishBtn->raise();
    punishBtn->setEnabled(false);
    //设置抽取卡片点击效果
    QPropertyAnimation *punishAnimation = new QPropertyAnimation(this->punishs, "geometry");
    //设置事件间隔
    punishAnimation->setDuration(2000);
    connect(punishBtn, &QPushButton::clicked, [=](){
        if (punishBtn->text() == "抽取卡片") {//执行动画
            QString infoStr = QString("%1抽取了卡片！").arg(playCharas[this->charaOperateNo - 1]->name);
            infoLabel->setText(infoStr);
            //设置开始位置
            punishAnimation->setStartValue(QRect(this->punishs->x(), this->punishs->y(), this->punishs->width(), this->punishs->height()));
            //设置结束位置
            punishAnimation->setEndValue(QRect(this->punishs->x(), this->punishs->y() - 2520, this->punishs->width(), this->punishs->height()));
            //设置缓和曲线
            punishAnimation->setEasingCurve(QEasingCurve::OutBounce);
            //执行动画
            punishAnimation->start();
            punishBtn->setEnabled(false);
            //切换按钮字样
            QTimer::singleShot(2500, this, [=](){
                punishBtn->setText("确定");
                punishBtn->setEnabled(true);
            });
        }
        else {
            int final = this->finalPunish;
            delete this->punishs;
            this->punishs = new QLabel(ui->displayWindow);
            this->punishs->setFixedSize(632, 2700);
            this->punishs->setStyleSheet("background-color: rgba(255, 255, 255, 255);border:0px");
            this->punishs->move(0, 0);
            this->generatePunishs(final);
            this->punishs->lower();
            this->punishs->setVisible(true);
            punishBtn->setText("抽取卡片");
            punishAnimation->setTargetObject(this->punishs);

            punishBtn->setEnabled(false);//设置按钮不生效

            //角色消失
            playCharas[this->charaOperateNo - 1]->disappear();
            QTimer::singleShot(1010, this, [=](){
                //判断本局是否结束
                QString infoStr = QString("%1在接受了惩罚后被淘汰掉了！").arg(playCharas[this->charaOperateNo - 1]->name);
                infoLabel->setText(infoStr);
                this->result << QString::number(playCharas[this->charaOperateNo - 1]->charaNo) << playCharas[this->charaOperateNo - 1]->name;
                int falseCount = 0;
                for (int i = 0; i < trueCharas.count() / 2; i++) {
                    if (playCharas[i]->isFailed == false) {
                        falseCount++;
                    }
                }
                //跳到下一个操作角色
                QTimer::singleShot(1500, this, [=](){
                    if (this->charaOperateNo >= trueCharas.count() / 2) {
                        this->charaOperateNo = 1;
                    }
                    else {
                        this->charaOperateNo++;
                    }
                    while(playCharas[this->charaOperateNo - 1]->isFailed == true) {
                        if (this->charaOperateNo >= trueCharas.count() / 2) {
                            this->charaOperateNo = 1;
                        }
                        else {
                            this->charaOperateNo++;
                        }
                    }
                    QPixmap profilePix;
                    QString profileStr = QString(":/chara/chara/chara%1-1-1.png").arg(playCharas[this->charaOperateNo - 1]->charaNo);
                    profilePix.load(profileStr);
                    profilePix = profilePix.scaled(profileLabel->width(), profileLabel->height());
                    profileLabel->setPixmap(profilePix);
                    if (falseCount == 1) {
                        QString infoStr = QString("%1留存到了下来，是最后的赢家！！！").arg(playCharas[this->charaOperateNo - 1]->name);
                        infoLabel->setText(infoStr);
                        this->result << QString::number(playCharas[this->charaOperateNo - 1]->charaNo) << playCharas[this->charaOperateNo - 1]->name;
                        qDebug() << "游戏结束";

                        //显示结果
                        resultWidget = new QWidget(ui->mainWindow);
                        resultWidget->setFixedSize(300, 530);
                        resultWidget->move(160, 50);
                        resultWidget->setStyleSheet("background-color: rgba(255, 255, 255, 64);border:0px");
                        resultWidget->setVisible(true);//设置显示窗口
                        // 创建一个包含多个按钮的小部件（窗口内容）
                        QWidget *contentWidget = new QWidget(resultWidget);
                        contentWidget->setStyleSheet("background-color: rgba(255, 255, 255, 0);border:0px");
                        QVBoxLayout contentLayout(contentWidget);
                        QFont resultFont;
                        resultFont.setFamily("宋体");
                        resultFont.setBold(true);
                        resultFont.setPointSize(10);
                        for (int i = 1; i <= this->result.count() / 2; ++i) {
                            QPushButton *button = new QPushButton(QString("第%1名：%2").arg(i).arg(this->result[this->result.count() - 2 * i + 1]), contentWidget);
                            button->setStyleSheet("background-color: rgba(255, 255, 255, 200);border:1px;text-align: left");
                            button->setFont(resultFont);
                            button->setFixedWidth(270);
                            contentLayout.addWidget(button);
                            button->setVisible(true);
                        }
                        contentWidget->setVisible(true);
                        //设置返回按钮
                        QPushButton *backBtn = new QPushButton("返回主菜单", this);
                        backBtn->move(400, 820);
                        backBtn->setVisible(true);
                        backBtn->setFont(punishFont);
                        //设置返回主菜单功能
                        connect(backBtn, &QPushButton::clicked, [=](){
                            emit this->returnStart();
                        });
                    }
                    else {
                        QString infoStr = QString("现在轮到%1投掷骰子").arg(playCharas[this->charaOperateNo - 1]->name);
                        infoLabel->setText(infoStr);
                        diceBtn->setEnabled(true);
                    }
                });
            });
        }
    });

    //实现绕圈效果
    connect(this->circleTimer, &QTimer::timeout, [=](){
        //当前操作角色报数
        bool side;
        if (playCharas[this->charaOperateNo - 1]->direction == 1 || playCharas[this->charaOperateNo - 1]->direction == 4) {
            side = true;
        }
        else {
            side = false;
        }
        playCharas[this->charaOperateNo - 1]->speak(QString::number(this->countNumber), charaXs[this->charaOperateNo - 1], charaYs[this->charaOperateNo - 1], side);

        //数到骰子点数后停止并结算
        if (this->countNumber == this->diceNumder) {
            this->circleTimer->stop();
            this->countNumber = 1;
            //结算
            QTimer::singleShot(1000, this, [=](){
                QString infoStr = QString("点数落到了%1头上！").arg(playCharas[this->charaOperateNo - 1]->name);
                infoLabel->setText(infoStr);
                QPixmap profilePix;
                QString profileStr = QString(":/chara/chara/chara%1-1-1.png").arg(playCharas[this->charaOperateNo - 1]->charaNo);
                profilePix.load(profileStr);
                profilePix = profilePix.scaled(profileLabel->width(), profileLabel->height());
                profileLabel->setPixmap(profilePix);
            });//改变头像和文字

            playCharas[this->charaOperateNo - 1]->isFailed = true;
            QTimer::singleShot(2200, this, [=](){
                playCharas[this->charaOperateNo - 1]->backStep();
                QTimer::singleShot(1210, this, [=](){
                    QString infoStr = QString("轮到%1接受惩罚，进行真心话和大冒险的抽卡！").arg(playCharas[this->charaOperateNo - 1]->name);
                    infoLabel->setText(infoStr);

                    //启用惩罚按钮
                    punishBtn->setEnabled(true);
                });
            });
        }
        else {
            //报数加一
            this->countNumber++;

            //跳到下一个操作角色
            if (this->charaOperateNo >= trueCharas.count() / 2) {
                this->charaOperateNo = 1;
            }
            else {
                this->charaOperateNo++;
            }
            while(playCharas[this->charaOperateNo - 1]->isFailed == true) {
                if (this->charaOperateNo >= trueCharas.count() / 2) {
                    this->charaOperateNo = 1;
                }
                else {
                    this->charaOperateNo++;
                }
            }
        }
    });


    //实现退出功能
    connect(ui->actionexit, &QAction::triggered, [=](){
        this->close();
    });

    //实现返回主菜单功能
    connect(ui->actionreturn, &QAction::triggered, [=](){
        emit this->returnStart();
    });
}

void PlayScene::paintEvent(QPaintEvent *pev) {
    QPainter painter(this);
    QPixmap createPix;
    createPix.load(":/create/create/CreateBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), createPix);
}

void PlayScene::generatePunishs(int initPunish) {
    //初始化随机数种子
    std::srand(std::time(nullptr));
    //创建总Pix
    QPixmap longPix(632, 2700);
    longPix.fill(Qt::white);
    //初始化画家
    QPainter painter(&longPix);
    //加载初始惩罚图片
    QString punishStr = QString(":/play/play/header%1").arg(initPunish);
    QPixmap punishPix;
    punishPix.load(punishStr);
    punishPix = punishPix.scaled(610, 180);
    painter.drawPixmap(0, 0, punishPix);
    for (int i = 0; i < 14; ++i) {
        //生成一个随机整数在1到6之间
        int randNumber = std::rand() % 6 + 1;
        //加载对应惩罚图片
        QString punishStr = QString(":/play/play/header%1").arg(randNumber);
        QPixmap punishPix;
        punishPix.load(punishStr);
        punishPix = punishPix.scaled(610, 180);
        painter.drawPixmap(0, i * 180 + 180, punishPix);
        //绘制对应惩罚
        int punishNumber = std::rand() % 40;
        QString punishText;
        if (this->modeChoice == 0) {
            punishText = this->punishContent->normalPunishs[punishNumber];
        }
        else if (this->modeChoice == 1) {
            punishText = this->punishContent->malePunishs[punishNumber];
        }
        else if (this->modeChoice == 2) {
            punishText = this->punishContent->femalePunishs[punishNumber];
        }
        else {
            punishText = this->punishContent->dangerPunishs[punishNumber];
        }
        if (i == 13) {
            this->finalPunish = randNumber;
        }
        QRect textRect(190, i * 180 + 230, 350, 150);//设置文本绘制区域
        QFont punishFont("宋体", 10);
        punishFont.setBold(true);
        painter.setFont(punishFont);
        painter.drawText(textRect, punishText);
    }
    qDebug() << this->finalPunish;
    this->punishs->setPixmap(longPix);
}

PlayScene::~PlayScene()
{
    delete ui;
}
