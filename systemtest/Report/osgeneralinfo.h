#ifndef OSGENERALINFO_H
#define OSGENERALINFO_H

#include <QJsonObject>



class OsGeneralInfo
{
public:
    OsGeneralInfo();

    bool fetchInfo();

    int getInfoCount(){ return m_osInfo.count(); }
    QJsonObject getOsInfo() { return m_osInfo; }

private:
    QJsonObject         m_osInfo;
};

#endif // OSGENERALINFO_H
