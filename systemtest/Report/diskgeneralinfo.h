#ifndef DISKGENERALINFO_H
#define DISKGENERALINFO_H

#include <QJsonArray>

#include "Report/diskfsinfo.h"



class DiskGeneralInfo
{
public:
    DiskGeneralInfo();

    bool fetchInfo();

    bool fetchFDiskInfo();

    bool fetchDiskFSInfo();
    int getDiskCount() { return m_diskInfoList.count(); }
    QString getFSName(int index);
    QJsonObject getFSInfo(int index);

private:
    QList<DiskFSInfo>          m_diskInfoList;
};

#endif // DISKGENERALINFO_H
