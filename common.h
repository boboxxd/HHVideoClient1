#ifndef COMMON_H
#define COMMON_H
#include <QObject>
#include <QString>

struct Camera
{
    int id;
    QString ip;
    int port;
    QString username;
    QString password;
    QString brief;
};
Q_DECLARE_METATYPE(Camera)

struct AlarmInfo
{
    int id;
    int cameraid;
    QString time;
    QString type;
    QString image;
};
Q_DECLARE_METATYPE(AlarmInfo)

#endif // COMMON_H
