#include "diskfsinfo.h"

DiskFSInfo::DiskFSInfo()
{

}

void DiskFSInfo::loadFSInfo(QStringList recordList){
    setFsName(recordList[0]);
    setTotalVolume(recordList[1]);
    setUsedVolume(recordList[2]);
    setAvailVolume(recordList[3]);
    setUsedRate(recordList[4]);
    setMountPoint(recordList[5]);
}

QString DiskFSInfo::fsName() const
{
    return m_fsName;
}

void DiskFSInfo::setFsName(const QString &fsName)
{
    m_fsName = fsName;
}

QString DiskFSInfo::totalVolume() const
{
    return m_totalVolume;
}

void DiskFSInfo::setTotalVolume(const QString &totalVolume)
{
    m_totalVolume = totalVolume;
}

QString DiskFSInfo::usedVolume() const
{
    return m_usedVolume;
}

void DiskFSInfo::setUsedVolume(const QString &usedVolume)
{
    m_usedVolume = usedVolume;
}

QString DiskFSInfo::usedRate() const
{
    return m_usedRate;
}

void DiskFSInfo::setUsedRate(const QString &usedRate)
{
    m_usedRate = usedRate;
}

QString DiskFSInfo::availVolume() const
{
    return m_availVolume;
}

void DiskFSInfo::setAvailVolume(const QString &availVolume)
{
    m_availVolume = availVolume;
}

QString DiskFSInfo::mountPoint() const
{
    return m_mountPoint;
}

void DiskFSInfo::setMountPoint(const QString &mountPoint)
{
    m_mountPoint = mountPoint;
}
