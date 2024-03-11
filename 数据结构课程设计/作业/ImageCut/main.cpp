#include "mainwindow.h"

#include <QApplication>
#include <QImage>
#include <QRect>
#include <QDebug>

int main(int argc, char *argv[])
{
    for (int i = 1; i < 31; i++) {
        QString path = QString("D:/shujvjiegoukeshe/ImageCut/chara/chara%1.png").arg(i);
        QImage img;

        //加载原图
        img.load(path);

        //修正高度
        int correct;
        if (img.height() == 192) {
            correct = 0;
        }
        else {
            correct = 16;
        }

        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                //裁剪
                QRect cutRect(k * img.width() / 4, j * img.height() / 4 +  + correct, 48, 48);
                QImage imgCut = img.copy(cutRect);
                //保存
                int col;
                if (j == 2) {
                    col = 4;
                }
                else if (j == 3) {
                    col = 3;
                }
                else {
                    col = j + 1;
                }
                QString savePath = QString("D:/shujvjiegoukeshe/ImageCut/chara/%1/chara%2-%3-%4.png").arg(i).arg(i).arg(col).arg(k + 1);
                qDebug() << savePath;
                qDebug() << imgCut.save(savePath);
            }
        }
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
