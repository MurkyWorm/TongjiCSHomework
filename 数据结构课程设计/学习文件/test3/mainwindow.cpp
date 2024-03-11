#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPushButton * btn = new QPushButton("第一个按钮", this);
    QPushButton * btn2 = new QPushButton("第二个按钮", this);
    btn->move(100, 100);
//    ui->setupUi(this);
    setFixedSize(600, 400);
    setWindowTitle("jing");
}

MainWindow::~MainWindow()
{
    delete ui;
}

