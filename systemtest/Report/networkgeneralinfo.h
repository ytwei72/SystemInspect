#ifndef NETWORKGENERALINFO_H
#define NETWORKGENERALINFO_H

#include <QJsonObject>



class NetworkGeneralInfo
{
public:
    NetworkGeneralInfo();

    bool fetchInfo();
    QJsonObject getInfo() { return m_ethInfo; }

private:
    void matchAndSaveInfo(QString buff, QString matchName, QString keyName, QJsonObject * jsonObj);

private:
    QJsonObject         m_ethInfo;
    QJsonObject         m_wlanInfo;
};

#endif // NETWORKGENERALINFO_H
