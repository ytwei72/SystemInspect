#ifndef CPUGENERALINFO_H
#define CPUGENERALINFO_H

#include <QJsonObject>
#include <QString>
#include <QStringList>



class CpuGeneralInfo
{
public:
    CpuGeneralInfo();

    bool fetchInfo();
    int getCpuInfoCount() { return m_cpuInfoKeyList.count(); }
    QString getKeyByIndex(int index) { return m_cpuInfoKeyList[index]; }
    QString getKeyNameByIndex(int index) { return m_cpuInfoKeyNameList[index]; }
    QString getValueByIndex(int index);

private:
//    QString     architecture;
//    QString     vendorID;
    QJsonObject     m_jsonCpuInfo;
    QStringList     m_cpuInfoKeyList;
    QStringList     m_cpuInfoKeyNameList;

    QJsonObject jsonArrayToObject(QJsonArray);
    void initCpuInfoKeyList();
};

#endif // CPUGENERALINFO_H
