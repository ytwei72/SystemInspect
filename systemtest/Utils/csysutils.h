#ifndef SYSUTILS_H
#define SYSUTILS_H

#include <QObject>


class CSysUtils : public QObject
{
    Q_OBJECT
public:
    explicit CSysUtils(QObject *parent = nullptr);

public:
    static qint64 getCurrentTimeStamp();
    static void resetTimerClock();
    static qint64 getElapsedMilliSeconds();

    static qint64 getClockStartTimeStamp();
    static void setClockStartTimeStamp(const qint64 &value);

    static bool isFileExist(QString fullFilePath);
    static bool isDirExist(QString fullPath);
    static bool checkDir(QString fullPath, bool bAlwaysMake = false);

    static QString execCmd(QString cmd);

public:
//    static qint64 clockStartTimeStamp;

signals:

public slots:
};

#endif // SYSUTILS_H
