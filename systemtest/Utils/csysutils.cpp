#include "csysutils.h"

#include <QDateTime>

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
