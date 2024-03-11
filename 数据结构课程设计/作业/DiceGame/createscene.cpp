#include "createscene.h"
#include "ui_createscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <sitechoosewindow.h>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "modetoolbutton.h"
#include "charalabel.h"
#include <QPropertyAnimation>

#define pageNum 3

CreateScene::CreateScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateScene)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(720, 1140);

    //设置图标
    this->setWindowIcon(QIcon(":/cover/cover/Pikachu.png"));

    //设置标题
    this->setWindowTitle("创建游戏场景");

    //创建游戏按钮
    MyPushButton * createBtn = new MyPushButton(":/cover/cover/CoverButton.png", "", 1, 1.6);
    createBtn->setParent(this);
    createBtn->move(70, 650);

    //回退按钮
    MyPushButton * backBtn = new MyPushButton(":/create/create/back.png");
    backBtn->setParent(this);
    backBtn->move(10, this->height() - backBtn->height() - 30);

    //触发返回信号
    connect(backBtn, &MyPushButton::clicked, [=](){
        //弹跳动画
        backBtn->zoom1();
        backBtn->zoom2();

        //停止选择动画的时钟
        this->charaChooseTimer->stop();
        delete this->charaChooseTimer;

        //延时触发
        QTimer::singleShot(400, this, [=](){
            emit this->createSceneBack();
        });
    });

    //设置场景选择窗口
    SiteChooseWindow *siteChooseWindow = new SiteChooseWindow();
    siteChooseWindow->setParent(this);
    //设置大小位置
    siteChooseWindow->setFixedSize(this->width() - 80, (this->width() - 80) * 0.5);
    siteChooseWindow->move(40, 80);

    //设置图片列表
    QStringList imgList;
    imgList << ":/create/create/PlaySite1.png" << ":/create/create/PlaySite2.png" << ":/create/create/PlaySite3.png";
    siteChooseWindow->setImgList(imgList);
    siteChooseWindow->startPlay();

    siteChooseWindow->show();

    //设置场景选择边框的大小和位置
    ui->siteFrame->setFixedSize(this->width() - 64, (this->width() - 80) * 0.5 + 16);
    ui->siteFrame->move(32, 42);
    ui->siteFrame->setAttribute(Qt::WA_TransparentForMouseEvents);

    //设置模式选择容器的大小和位置
    ui->modeFrame->setFixedSize(250, 200);
    ui->modeFrame->move(32, 400);

    //设置模式选择容器的背景透明度
    ui->modeContainer->setStyleSheet("background-color: rgba(255, 255, 255, 64);");

    //设置字体
    QFont font;
    font.setFamily("宋体");
    font.setBold(true);

    //设置模式选择容器标题
    QLabel *modelTitle = new QLabel;
    modelTitle->setParent(ui->modeContainer);
    modelTitle->setText("模式选择");
    modelTitle->setFont(font);

    //设置模式选择容器的布局管理器
    QVBoxLayout *modeLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    QVBoxLayout *modeLayout2 = new QVBoxLayout(ui->modeFrame);

    modeLayout2->addWidget(modelTitle);
    modeLayout2->addWidget(ui->modeContainer);

    //在设置模式选择容器中添加按钮
    ModeToolButton *normalBtn = new ModeToolButton(":/create/create/normal.png", ":/create/create/normal1.png", "  普通模式");
    modeLayout->addWidget(normalBtn);//普通模式
    ModeToolButton *maleBtn = new ModeToolButton(":/create/create/male.png", ":/create/create/male1.png", "  只有男生");
    modeLayout->addWidget(maleBtn);//只有男生
    ModeToolButton *femaleBtn = new ModeToolButton(":/create/create/female.png", ":/create/create/female1.png", "  只有女生");
    modeLayout->addWidget(femaleBtn);//只有女生
    ModeToolButton *dangerBtn = new ModeToolButton(":/create/create/danger.png", ":/create/create/danger1.png", "  危险模式");
    modeLayout->addWidget(dangerBtn);//危险模式

    //实现点击模式选择按钮的效果
    connect(normalBtn, &ModeToolButton::clicked, [=](){//普通模式
        //所有按钮停止抖动
        normalBtn->stopShake();
        maleBtn->stopShake();
        femaleBtn->stopShake();
        dangerBtn->stopShake();
        //判断接下来是抖动还是停止
        if (this->modeChoice == 0) {
            this->modeChoice = -1;
        }
        else {
            normalBtn->shake();
            this->modeChoice = 0;
        }
    });
    connect(maleBtn, &ModeToolButton::clicked, [=](){//只有男生
        //所有按钮停止抖动
        normalBtn->stopShake();
        maleBtn->stopShake();
        femaleBtn->stopShake();
        dangerBtn->stopShake();
        //判断接下来是抖动还是停止
        if (this->modeChoice == 1) {
            this->modeChoice = -1;
        }
        else {
            maleBtn->shake();
            this->modeChoice = 1;
        }
    });
    connect(femaleBtn, &ModeToolButton::clicked, [=](){//只有女生
        //所有按钮停止抖动
        normalBtn->stopShake();
        maleBtn->stopShake();
        femaleBtn->stopShake();
        dangerBtn->stopShake();
        //判断接下来是抖动还是停止
        if (this->modeChoice == 2) {
            this->modeChoice = -1;
        }
        else {
            femaleBtn->shake();
            this->modeChoice = 2;
        }
    });
    connect(dangerBtn, &ModeToolButton::clicked, [=](){//危险模式
        //所有按钮停止抖动
        normalBtn->stopShake();
        maleBtn->stopShake();
        femaleBtn->stopShake();
        dangerBtn->stopShake();
        //判断接下来是抖动还是停止
        if (this->modeChoice == 3) {
            this->modeChoice = -1;
        }
        else {
            dangerBtn->shake();
            this->modeChoice = 3;
        }
    });
    //设置模式选择的布局管理器
    ui->modeFrame->setLayout(modeLayout2);
    ui->scrollAreaWidgetContents->setLayout(modeLayout);

    //设置角色添加容器的大小和位置
    ui->charaFrame->setFixedSize(376, 300);
    ui->charaFrame->move(312, 400);

    //设置角色添加容器的背景透明度
    ui->charaContainer->setStyleSheet("background-color: rgba(255, 255, 255, 64);");

    //设置角色添加容器标题
    QLabel *charaTitle = new QLabel;
    charaTitle->setParent(ui->charaContainer);
    charaTitle->setText("角色添加");
    charaTitle->setFont(font);

    //设置角色添加容器的布局管理器
    QHBoxLayout *charaLayout = new QHBoxLayout(ui->scrollAreaWidgetContents_3);
    QVBoxLayout *charaLayout2 = new QVBoxLayout(ui->charaFrame);

    //设置左对齐
    charaLayout->setAlignment(Qt::AlignLeft);

    charaLayout2->addWidget(charaTitle);
    charaLayout2->addWidget(ui->charaContainer);

    //添加角色添加按钮
    QPushButton *addCharaBtn = new QPushButton;
    addCharaBtn->setStyleSheet("background-color: rgba(255, 255, 255, 200);");
    addCharaBtn->setFont(font);
    addCharaBtn->setText("添加角色");
    charaLayout2->addWidget(addCharaBtn);

    //点击角色添加窗口的角色添加按钮，角色选择框弹出
    QPropertyAnimation *charaChooseshow = new QPropertyAnimation(ui->charaChooseContainer, "geometry");
    //设置动画时间
    charaChooseshow->setDuration(300);
    //设置缓和曲线
    charaChooseshow->setEasingCurve(QEasingCurve::Linear);
    connect(addCharaBtn, &QPushButton::clicked, [=](){
        if (this->isAdd == false) {
            //设置开始位置
            charaChooseshow->setStartValue(QRect(ui->charaChooseContainer->x(), ui->charaChooseContainer->y(), ui->charaChooseContainer->width(), ui->charaChooseContainer->height()));
            //设置结束位置
            charaChooseshow->setEndValue(QRect(ui->charaChooseContainer->x() - 700, ui->charaChooseContainer->y(), ui->charaChooseContainer->width(), ui->charaChooseContainer->height()));
            //改变按钮文字
            addCharaBtn->setText("添加完成");
            this->isAdd = true;
        }
        else {
            //设置开始位置
            charaChooseshow->setStartValue(QRect(ui->charaChooseContainer->x(), ui->charaChooseContainer->y(), ui->charaChooseContainer->width(), ui->charaChooseContainer->height()));
            //设置结束位置
            charaChooseshow->setEndValue(QRect(ui->charaChooseContainer->x() + 700, ui->charaChooseContainer->y(), ui->charaChooseContainer->width(), ui->charaChooseContainer->height()));
            //改变按钮文字
            addCharaBtn->setText("添加角色");
            this->isAdd = false;
        }
        //执行动画
        charaChooseshow->start();
    });

    //设置角色添加的布局管理器
    ui->charaFrame->setLayout(charaLayout2);
    ui->scrollAreaWidgetContents_3->setLayout(charaLayout);

    //设置角色选择界面容器的大小和位置
    ui->charaChooseContainer->setFixedSize(this->width() - 64, 290);
    //ui->charaChooseContainer->move(32, 720);这是显示的位置
    ui->charaChooseContainer->move(732, 720);//这是隐藏的位置
    ui->lineEdit->setPlaceholderText("请输入角色名字");

    //设置角色选择页面的大小和位置
    ui->charaChooseContainer->setStyleSheet("background-color: rgba(255, 255, 255, 128);");

    //设置角色选择页面的行数和列数
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(10);

    //设置表格中每个框内的内容并维护这些按钮
    QPushButton *chooseButtons[30];
    this->charaChooseTimer = new QTimer;//初始化角色选择动画时钟
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            //设置按钮
            QPushButton *btn = new QPushButton;
            chooseButtons[i * 10 + j] = btn;
            btn->setFixedSize(48, 48);
            QString iconPath = QString(":/chara/chara/chara%1-1-1.png").arg(i * 10 + j + 1);
            btn->setIcon(QIcon(iconPath));
            btn->setIconSize(QSize(48, 48));
            //进行布局
            QVBoxLayout *layout = new QVBoxLayout;
            layout->addWidget(btn);
            layout->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            QWidget *container = new QWidget;
            container->setLayout(layout);
            //放入单元格中
            ui->tableWidget->setCellWidget(i, j, container);
        }
    }
    for (int i = 0; i < 30; i++) {
        //设置按钮点击效果
        connect(chooseButtons[i], &QPushButton::clicked, [=](){
            if (i + 1 == this->currentCharaIndex) {//若点击到选中按钮，则停止
                this->charaChooseTimer->stop();
                this->currentCharaIndex = -1;
                chooseButtons[i]->setIcon(QIcon(QString(":/chara/chara/chara%1-1-1.png").arg(i + 1)));
            }
            else {//若点击到未选中按钮，则停止其它按钮，启动该按钮动画
                if (this->currentCharaIndex != -1) {//如果已选中其它按钮，则停止
                    this->charaChooseTimer->stop();
                    chooseButtons[this->currentCharaIndex - 1]->setIcon(QIcon(QString(":/chara/chara/chara%1-1-1.png").arg(this->currentCharaIndex)));
                }
                this->currentCharaIndex = i + 1;
                this->charaChooseTimer->start(300);
            }
        });
    }
    //实现选择动画时钟启动时当前选中按钮开始执行动画
    connect(this->charaChooseTimer, &QTimer::timeout, [=](){  
        QString charaChooseStr = QString(":/chara/chara/chara%1-%2-1.png").arg(this->currentCharaIndex).arg(this->imgIndex++);
        chooseButtons[this->currentCharaIndex - 1]->setIcon(QIcon(charaChooseStr));

        //循环
        if (this->imgIndex > 4) {
            this->imgIndex = 1;
        }
    });

    //获取输入框内容
    connect(ui->lineEdit, &QLineEdit::textChanged, [=](){
        this->currentLineText = ui->lineEdit->text();
    });

    //设置角色选择页面的添加按钮字体
    ui->pushButton->setFont(font);

    //实现角色选择页面的添加角色功能
    connect(ui->pushButton, &QPushButton::clicked, [=]() {
        //判断是否符合创建要求
        if (this->currentCharaIndex == -1) {
            QPixmap waringPix;
            waringPix.load(":/create/create/FailCreate.png");
            waringPix = waringPix.scaled(100, 100);
            QMessageBox *warningMessage = new QMessageBox(QMessageBox::Warning, "提示", "未选择角色");
            warningMessage->setWindowIcon(QIcon(":/create/create/FailCreate.png"));
            warningMessage->setIconPixmap(waringPix);
            warningMessage->setAttribute(Qt::WA_DeleteOnClose);
            warningMessage->move(this->x() + (this->width() - warningMessage->width()) * 0.5 + 135, this->y() + (this->height() - warningMessage->height()) * 0.5);
            warningMessage->exec();
        }
        else if (this->currentLineText == "") {
            QPixmap waringPix;
            waringPix.load(":/create/create/FailCreate.png");
            waringPix = waringPix.scaled(100, 100);
            QMessageBox *warningMessage = new QMessageBox(QMessageBox::Warning, "提示", "未输入角色名称");
            warningMessage->setWindowIcon(QIcon(":/create/create/FailCreate.png"));
            warningMessage->setIconPixmap(waringPix);
            warningMessage->setAttribute(Qt::WA_DeleteOnClose);
            warningMessage->move(this->x() + (this->width() - warningMessage->width()) * 0.5 + 135, this->y() + (this->height() - warningMessage->height()) * 0.5);
            warningMessage->exec();
        }
        else if (this->currentLineText == "true" || this->currentLineText == "false") {
            QPixmap waringPix;
            waringPix.load(":/create/create/FailCreate.png");
            waringPix = waringPix.scaled(100, 100);
            QMessageBox *warningMessage = new QMessageBox(QMessageBox::Warning, "提示", "不可以使用数字true或false作为名字哦");
            warningMessage->setWindowIcon(QIcon(":/create/create/FailCreate.png"));
            warningMessage->setIconPixmap(waringPix);
            warningMessage->setAttribute(Qt::WA_DeleteOnClose);
            warningMessage->move(this->x() + (this->width() - warningMessage->width()) * 0.5 + 135, this->y() + (this->height() - warningMessage->height()) * 0.5);
            warningMessage->exec();
        }
        else {
            //创建角色
            CharaLabel *newChara = new CharaLabel(this->currentCharaIndex, this->currentLineText);
            charaLayout->addWidget(newChara);
            newChara->no = this->charas.count() / 3;
            this->charaNum++;
            qDebug() << "添加后当前角色数"  << this->charaNum;
            qDebug() << "添加的角色编号"  << newChara->no;

            //添加入创建信息
            this->charas << QString::number(this->currentCharaIndex) << this->currentLineText <<"true";
            //清空当前信息
            ui->lineEdit->setText("");

            qDebug() << "当前角色列表" << this->charas;

            //返回时停止添加的角色的动画时钟
            connect(backBtn, &MyPushButton::clicked, [=](){
                newChara->animationTimer->stop();
                delete newChara->animationTimer;
                delete newChara;
            });
            //创建时停止添加的角色的动画时钟
            connect(createBtn, &QPushButton::clicked, [=](){
                if (this->mapChoice != -1 && this->modeChoice != -1 && this->charaNum >=2 && this->charaNum <=16) {
                    if (newChara != NULL) {
                        newChara->animationTimer->stop();
                        delete newChara->animationTimer;
                        delete newChara;
                    }
                }
            });
            //删除该角色标签
            connect(newChara, &CharaLabel::deleteLabel, [=](){
                qDebug() << "删除的角色编号"  << newChara->no;
                newChara->animationTimer->stop();
                newChara->close();
    //            delete newChara->animationTimer;
    //            delete newChara;//不能重复删除
                this->charas[newChara->no * 3 + 2] = "0";
                this->charaNum--;
                qDebug() << "删除后当前角色数"  << this->charaNum;
                qDebug() << "当前角色列表" << this->charas;
            });
        }
    });

    //设置字体
    font.setPointSize(14);

    //选择标签
    QLabel * createLabel = new QLabel;
    createLabel->setParent(this);
    createLabel->setFixedSize(createBtn->width(), createBtn->height());
    createLabel->setFont(font);
    createLabel->setText("创建游戏");
    createLabel->setStyleSheet("color:white");
    createLabel->move(70, 650);
    //设置label上的文字对齐方式
    createLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //设置让鼠标进行穿透
    createLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    //接收场景选择信号并处理
    connect(siteChooseWindow, &SiteChooseWindow::hasChosen, [=](){
        this->mapChoice = siteChooseWindow->currentImgIndex;
    });
    //接收场景取消信号并处理
    connect(siteChooseWindow, &SiteChooseWindow::cancelChosen, [=](){
        this->mapChoice = -1;
    });

    //设置创建游戏按钮功能
    connect(createBtn, &MyPushButton::clicked, [=](){
        createBtn->zoom1();
        createBtn->zoom2();

        //检查创建是否合规
        QTimer::singleShot(400, this, [=](){
            qDebug() << "点击了创建按钮啦";

            if (this->mapChoice == -1) {
                QPixmap waringPix;
                waringPix.load(":/create/create/FailCreate.png");
                waringPix = waringPix.scaled(100, 100);
                QMessageBox *warningMessage = new QMessageBox(QMessageBox::Warning, "提示", "创建未成功，因为未选择场景");
                warningMessage->setWindowIcon(QIcon(":/create/create/FailCreate.png"));
                warningMessage->setIconPixmap(waringPix);
                warningMessage->setAttribute(Qt::WA_DeleteOnClose);
                warningMessage->move(this->x() + (this->width() - warningMessage->width()) * 0.5 + 135, this->y() + (this->height() - warningMessage->height()) * 0.5);
                warningMessage->exec();
            }
            else if (this->modeChoice == -1) {
                QPixmap waringPix;
                waringPix.load(":/create/create/FailCreate.png");
                waringPix = waringPix.scaled(100, 100);
                QMessageBox *warningMessage = new QMessageBox(QMessageBox::Warning, "提示", "创建未成功，因为未选择模式");
                warningMessage->setWindowIcon(QIcon(":/create/create/FailCreate.png"));
                warningMessage->setIconPixmap(waringPix);
                warningMessage->setAttribute(Qt::WA_DeleteOnClose);
                warningMessage->move(this->x() + (this->width() - warningMessage->width()) * 0.5 + 135, this->y() + (this->height() - warningMessage->height()) * 0.5);
                warningMessage->exec();
            }
            else if (this->charaNum < 2 || this->charaNum > 16) {
                QPixmap waringPix;
                waringPix.load(":/create/create/FailCreate.png");
                waringPix = waringPix.scaled(100, 100);
                QMessageBox *warningMessage;
                if (this->charaNum < 2) {
                    warningMessage = new QMessageBox(QMessageBox::Warning, "提示", "创建未成功，因为未添加足够的角色");
                }
                else {
                    warningMessage = new QMessageBox(QMessageBox::Warning, "提示", "创建未成功，因为添加了过多的角色");
                }
                warningMessage->setWindowIcon(QIcon(":/create/create/FailCreate.png"));
                warningMessage->setIconPixmap(waringPix);
                warningMessage->setAttribute(Qt::WA_DeleteOnClose);
                warningMessage->move(this->x() + (this->width() - warningMessage->width()) * 0.5 + 135, this->y() + (this->height() - warningMessage->height()) * 0.5);
                warningMessage->exec();
            }
            else {
                qDebug() << "开始创建游玩场景啦";

                //停止选择动画的时钟
                this->charaChooseTimer->stop();
                delete this->charaChooseTimer;

                qDebug() << "成功停止时钟啦";

                //打开游玩场景
                this->playscene = new PlayScene(this->mapChoice, this->modeChoice, this->charas);
                this->close();
                playscene->setGeometry(this->geometry());
                playscene->show();

                qDebug() << "成功显示游玩场景啦";

                //处理游玩场景的返回开始界面信号
                connect(playscene, &PlayScene::returnStart, [=](){
                    this->setGeometry(playscene->geometry());
                    delete this->playscene;
                    emit this->createSceneBack();
                });
            }
        });
    });

    //退出功能实现
    connect(ui->actionexit, &QAction::triggered, [=](){
        this->close();
    });
}

void CreateScene::paintEvent(QPaintEvent *pev) {
    QPainter painter(this);
    QPixmap createPix;
    createPix.load(":/create/create/CreateBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), createPix);
}

CreateScene::~CreateScene()
{
    delete ui;
}
