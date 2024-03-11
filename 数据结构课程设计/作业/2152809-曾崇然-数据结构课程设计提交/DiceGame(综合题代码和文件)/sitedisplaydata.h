#ifndef SITEDISPLAYDATA_H
#define SITEDISPLAYDATA_H

#include <QObject>
#include <QMap>
#include <QVector>

class SiteDisplayData : public QObject
{
    Q_OBJECT
public:
    explicit SiteDisplayData(QObject *parent = nullptr);

    //角色位置数据
    QMap<int, QVector<QVector<int>>>charaLocData;

    //角色访问顺序
    QVector<QVector<int>>visitOrder;

    //地图中心数据
    QMap<int, QVector<double>>mapCenterData;

signals:

};

#endif // SITEDISPLAYDATA_H
