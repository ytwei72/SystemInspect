#include "networkgeneralinfo.h"

#include "Utils/csysutils.h"
#include "Utils/transformutil.h"

NetworkGeneralInfo::NetworkGeneralInfo()
{

}

bool NetworkGeneralInfo::fetchInfo() {

    TransformUtil::clearJsonObject(&m_ethInfo);
    TransformUtil::clearJsonObject(&m_wlanInfo);

    //! 1. 有线网卡名称
    // 读取PCI信息
    QString result = CSysUtils::execCmd("lspci");
    QStringList pciList = result.split("\n");

    // 获取有线网卡名称
    for (int i=0; i<pciList.count(); i++) {
        QString pciInfo = pciList[i];
        int pos = pciInfo.indexOf("Ethernet controller:");
        if (pos > 0) {
            QStringList ethInfoList = pciInfo.split(": ");
            if (ethInfoList.count() >= 2)
                m_ethInfo.insert("01. 网卡名称", ethInfoList[1]);
        }
    }
    //! 1. 有线网卡名称

    //! 2. 有线网卡信息
    result = CSysUtils::execCmd("ethtool eth0");
    QStringList eth0InfoList = result.split("\n");
    for (int i=0; i<eth0InfoList.count(); i++) {
        QString eth0Info = eth0InfoList[i];

        // 保存支持端口（Supported ports）
        matchAndSaveInfo(eth0Info, "Supported ports", "02. 支持端口", &m_ethInfo);

        // 保存速度（Speed）
        matchAndSaveInfo(eth0Info, "Speed", "03. 速度", &m_ethInfo);

        // 双工模式
        matchAndSaveInfo(eth0Info, "Duplex", "04. 双工模式", &m_ethInfo);

        // 连接状态
        matchAndSaveInfo(eth0Info, "Link detected", "05. 连接状态", &m_ethInfo);
    }
    //! 2. 有线网卡信息

    //! 3. 有线网卡地址、数据传输量（收发）
    result = CSysUtils::execCmd("ifconfig eth0");
    QStringList ifcfgInfoList = result.split("\n");
    for (int i=0; i<ifcfgInfoList.count(); i++) {
        QString ifcfgInfo = ifcfgInfoList[i];
        ifcfgInfo = ifcfgInfo.trimmed();
        // IP地址
        if ( ifcfgInfo.indexOf("inet ") >= 0 ) {
            QStringList ipAddrList = ifcfgInfo.split(" ");
            m_ethInfo.insert("06. IP地址", ipAddrList[1]);
            m_ethInfo.insert("07. 掩码", ipAddrList[4]);
        }
        // MAC地址
        if ( ifcfgInfo.indexOf("ether ") >= 0 ) {
            QStringList macList = ifcfgInfo.split(" ");
            m_ethInfo.insert("08. MAC地址", macList[1]);
        }
        // 收包
        if ( ifcfgInfo.indexOf("RX packets") >= 0 ) {
            QStringList rxList = ifcfgInfo.split(" ");
            m_ethInfo.insert("09. 收包数", rxList[2]);
            m_ethInfo.insert("10. 接收数据量", rxList[5] + rxList[6] + rxList[7]);
        }
        // 发包
        if ( ifcfgInfo.indexOf("TX packets") >= 0 ) {
            QStringList txList = ifcfgInfo.split(" ");
            m_ethInfo.insert("11. 发包数", txList[2]);
            m_ethInfo.insert("12. 发送数据量", txList[5] + txList[6] + txList[7]);
        }
    }
    //! 3. 有线网卡地址、数据传输量（收发）


    return true;
}

void NetworkGeneralInfo::matchAndSaveInfo(QString buff, QString matchName, QString keyName, QJsonObject * jsonObj) {
    int pos = buff.indexOf(matchName);
    if (pos > 0) {
        QStringList itemList = buff.split(": ");
        if (itemList.count() >= 2) {
            jsonObj->insert(keyName, itemList[1]);
        }
    }
}
