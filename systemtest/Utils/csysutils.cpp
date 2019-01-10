#include "csysutils.h"

#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QProcess>

static qint64 clockStartTimeStamp;

CSysUtils::CSysUtils(QObject *parent) : QObject(parent)
{
    setClockStartTimeStamp(0);

}

qint64 CSysUtils::getCurrentTimeStamp() {
    QDateTime timeNow = QDateTime::currentDateTime();

    return timeNow.currentMSecsSinceEpoch();
}

void CSysUtils::resetTimerClock() {
    setClockStartTimeStamp(getCurrentTimeStamp());
}

qint64 CSysUtils::getElapsedMilliSeconds() {
    qint64 timeStamp = getCurrentTimeStamp();

    return (timeStamp - getClockStartTimeStamp());
}

qint64 CSysUtils::getClockStartTimeStamp()
{
    return clockStartTimeStamp;
}

void CSysUtils::setClockStartTimeStamp(const qint64 &value)
{
    clockStartTimeStamp = value;
}

bool CSysUtils::isFileExist(QString fullFilePath) {
    QFileInfo fileInfo(fullFilePath);
    if(fileInfo.exists())
    {
        return true;
    }
    return false;
}

bool CSysUtils::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    return false;
}

bool CSysUtils::checkDir(QString fullPath, bool bAlwaysMake) {
    if (CSysUtils::isDirExist(fullPath)) {
        return true;
    } else if (!bAlwaysMake) {
        return false;
    } else {
        QDir dir(fullPath);
        bool bSuccess = dir.mkdir(fullPath);
        return bSuccess;
    }
}

QString CSysUtils::execCmd(QString cmd) {
    QProcess proc;
    proc.start(cmd);
    proc.waitForFinished();

    QString errorInfo = proc.readAllStandardError();
    if (!errorInfo.isEmpty())
        return "";

    QString result = proc.readAllStandardOutput();
    return result.trimmed();
}
