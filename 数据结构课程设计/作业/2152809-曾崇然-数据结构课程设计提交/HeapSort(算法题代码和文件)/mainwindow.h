#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //所要排序的数组的大小
    int heapSize;

    //要排序的数组
    QVector<double>array;

    //更新图片的函数
    void drawRefresh();

    //和排序相关的函数
    //交换两个数
    void swap(int i, int j);
    //调整为大顶堆
    void heapify(int index);
    //变为大顶堆
    void heapInsert(int index);
    //排序
    void heapSort();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
