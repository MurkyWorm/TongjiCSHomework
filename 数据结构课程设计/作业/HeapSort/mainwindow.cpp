#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QPixmap>
#include <QtMath>
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //进行布局
    ui->imgDisplay->setFixedHeight(550);//设置图形界面的高度
    ui->inputData->setStyleSheet("background-color: rgba(255, 255, 255, 255);");
    ui->sortResult->setStyleSheet("background-color: rgba(255, 255, 255, 255);");//设置背景颜色

    //设置字体
    QFont font;
    font.setBold(true);
    font.setFamily("宋体");

    //设置数据框内的标签
    ui->dataLabel->setFont(font);

    this->drawRefresh();//初始时刷新

    //实现添加数据功能
    connect(ui->addBtn, &QPushButton::clicked, [=](){
        bool isNum;
        ui->inputEdit->text().toDouble(&isNum);//判断是否为数字
        if (isNum) {//若是，则添加数据
            ui->dataLabel->setText(ui->dataLabel->text() + ui->inputEdit->text() + " ");
            this->array.push_back(ui->inputEdit->text().toDouble());

            ui->inputEdit->setText("");//设置输入框
        }
        else {//若不是，则警告
            QMessageBox *typeWaring = new QMessageBox(QMessageBox::Warning, "警告", "输入并非为数字");
            typeWaring->move(this->x() + (this->width() - typeWaring->contentsRect().width()) / 2 + 220, this->y() + (this->height() - typeWaring->contentsRect().height()) / 2);
            typeWaring->exec();//警告

            ui->inputEdit->setText("");//设置输入框
        }
    });

    //点击添加完成时初始化图形
    connect(ui->completeBtn, &QPushButton::clicked, [=](){
        //设置添加和完成按钮为不可用
        ui->addBtn->setEnabled(false);
        ui->completeBtn->setEnabled(false);
        this->heapSize = this->array.count();
        this->drawRefresh();
        this->heapSort();
        qDebug() << this->array;
    });

    //点击下一步时更新
    connect(ui->nextBtn, &QPushButton::clicked, [=](){

    });

    //实现退出功能
    connect(ui->actionexit, &QAction::triggered, [=](){
        this->close();
    });

    //实现刷新功能
    connect(ui->actionfresh, &QAction::triggered, [=](){
        ui->addBtn->setEnabled(true);
        ui->completeBtn->setEnabled(true);
        ui->nextBtn->setEnabled(true);
        ui->inputEdit->setText("");
        ui->orderResult->setText("");
        ui->dataLabel->setText("");
        ui->orderResult->setText("");
        this->array.clear();
        this->drawRefresh();
    });
}

void MainWindow::drawRefresh() {
    //确定画布大小
    int h = 0;
    while(true) {
        if (pow(2, h) > this->array.count()) {
            break;
        }
        else {
            h++;
        }
    }//确定高度
    int w = pow(2, h - 1);//确定宽度
    //设置最小的宽和高
    if (h <= 5) {
        h = 5;
    }
    if (w <= 7) {
        w = 7;
    }

    //创建画布
    QPixmap pix(w * 200, h * 100);
    pix.fill(Qt::white);

    //创建画家
    QPainter painter(&pix);
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QColor(255, 255, 0));
    QFont numFont("宋体", 8);
    numFont.setBold(true);
    painter.setFont(numFont);

    //画画和画数字
    for (int i = 0; i < this->array.count(); i++) {
        //确定当前元素应该在的位置
        int x = 0;
        int y = 0;
        while(true) {
            if (pow(2, y) > i + 1) {
                break;
            }
            else {
                y++;
            }
        }//确定y位置
        x = i + 2 - pow(2, y - 1);//确定x位置
        int Y = y * 100 - 50;
        int X = pix.width() / pow(2, y) * x - 0.5 * pix.width() / pow(2, y);//确定实际位置

        //连接父与子结点
        int j = (i + 1) / 2 - 1;
        if (i != 0) {
            int x_j = 0;
            int y_j = 0;
            while(true) {
                if (pow(2, y_j) > j + 1) {
                    break;
                }
                else {
                    y_j++;
                }
            }//确定y位置
            x_j = j + 2 - pow(2, y_j - 1);//确定x位置
            int Y_j = y_j * 100 - 50;
            int X_j = pix.width() / pow(2, y_j) * x_j - 0.5 * pix.width() / pow(2, y_j);//确定实际位置
            if (i < this->heapSize) {
                painter.drawLine(X_j + 22, Y_j + 22, X + 22, Y + 22);
            }
            painter.drawEllipse(X, Y, 44, 44);//画圆
            painter.drawEllipse(X_j, Y_j, 44, 44);//画父圆

            //绘制数字
            QRect textRect1(X + 5, Y + 18, 44, 22);//设置文本绘制区域
            painter.drawText(textRect1, QString::number(this->array[i]));
            QRect textRect2(X_j + 5, Y_j + 18, 44, 22);
            painter.drawText(textRect2, QString::number(this->array[j]));
        }
        else {
            painter.drawEllipse(X, Y, 44, 44);//画圆
            QRect textRect1(X + 5, Y + 18, 44, 22);
            painter.drawText(textRect1, QString::number(this->array[i]));
        }
    }

    //加载到标签上
    ui->imgLabel->setFixedSize(w * 102, h * 100);
    ui->imgLabel->setPixmap(pix);
    ui->imgLabel->setVisible(true);
}

void MainWindow::swap(int i, int j) {
    QEventLoop eventLoop;
    connect(ui->nextBtn, &QPushButton::clicked, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    int tmp = this->array[i];
    this->array[i] = this->array[j];
    this->array[j] = tmp;
    this->drawRefresh();
}

void MainWindow::heapify(int index) {
    int left = index * 2 + 1;
    while(left < this->heapSize) {
        int largest = left + 1 < heapSize && this->array[left + 1] > this->array[left] ? left + 1 : left;
        largest = this->array[largest] > this->array[index] ? largest : index;
        if (index == largest) {
            break;
        }
        this->swap(index, largest);
        index = largest;
        left = index * 2 + 1;
    }
}

void MainWindow::heapInsert(int index) {
    while(this->array[index] > this->array[(index - 1) / 2]) {
        this->swap(index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}

void MainWindow::heapSort() {
    if (this->array.count() < 2) {
        return;
    }
    for (int i = 0; i < this->array.count(); i++) {
        heapInsert(i);
    }
    this->swap(0, --this->heapSize);
    while(this->heapSize > 0) {
        this->heapify(0);
        this->swap(0, --this->heapSize);
    }
    ui->nextBtn->setEnabled(false);
    QMessageBox *typeInform = new QMessageBox(QMessageBox::Information, "提示", "排序已经完成");
    typeInform->move(this->x() + (this->width() - typeInform->contentsRect().width()) / 2 + 220, this->y() + (this->height() - typeInform->contentsRect().height()) / 2);
    typeInform->exec();//提示

    QString resultStr = "";
    for(int i = 0; i < this->array.count(); i++) {
        resultStr = resultStr + " " + QString::number(this->array[i]);
    }
    ui->orderResult->setText(resultStr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

