#ifndef PUNISHCONTENT_H
#define PUNISHCONTENT_H

#include <QObject>

class PunishContent : public QObject
{
    Q_OBJECT
public:
    explicit PunishContent(QObject *parent = nullptr);

    //普通模式
    QStringList normalPunishs;

    //只有男生
    QStringList malePunishs;

    //只有女生
    QStringList femalePunishs;

    //危险模式
    QStringList dangerPunishs;

signals:

};

#endif // PUNISHCONTENT_H
