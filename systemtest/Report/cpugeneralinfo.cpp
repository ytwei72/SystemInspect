#include "cpugeneralinfo.h"

#include <QJsonArray>
#include <QProcess>

#include "Utils/transformutil.h"

CpuGeneralInfo::CpuGeneralInfo()
{
    initCpuInfoKeyList();
}

bool CpuGeneralInfo::fetchInfo() {
    QProcess proc;

    // 查询CPU信息
    QString cmd = "lscpu";
    QStringList paramsList;
    // JSON格式输出
    paramsList << "-J";

    // 启动命令
    proc.start(cmd, paramsList);

    // 等待命令完成，并读取返回的CPU信息
    proc.waitForFinished();
    QString cpuInfo = proc.readAllStandardOutput();

    // 转换命令的输出字符串为JSON对象
    QJsonObject jsonData = TransformUtil::stringToJson(cpuInfo);
    if (jsonData.isEmpty())
        return false;

    if (!jsonData.contains("lscpu")) {
        return false;
    }
    QJsonValue jsonValue = jsonData.value("lscpu");
    QJsonArray jsonArray = jsonData.value("lscpu").toArray();
    m_jsonCpuInfo = jsonArrayToObject(jsonArray);
//    QString lscpuData = jsonData.value("lscpu").toString();
//    lscpuData = jsonData.value("lscpu").toString();
//    QJsonObject jsonCpuInfo = TransformUtil::stringToJson(lscpuData);
    if (m_jsonCpuInfo.isEmpty())
        return false;

    return true;
}

QJsonObject CpuGeneralInfo::jsonArrayToObject(QJsonArray jsonArray) {
    QJsonObject jsonResult;
//    foreach ()
    for (int i=0; i<jsonArray.size(); i++) {
        QJsonObject jsonObject = jsonArray[i].toObject();
        QString key = jsonObject.value("field").toString();
        QString value = jsonObject.value("data").toString();
        jsonResult.insert(key, value);
    }

    return jsonResult;

}

void CpuGeneralInfo::initCpuInfoKeyList() {
    m_cpuInfoKeyList << "Architecture:" << "CPU op-mode(s):" << "Byte Order:" << "CPU(s):"
                     << "Thread(s) per core:" << "Core(s) per socket:" << "Socket(s):"
                     << "Vendor ID:" << "CPU family:" << "Model name:" << "Stepping:"
                     << "CPU MHz:" << "BogoMIPS:" << "L1d cache:" << "L1i cache:"
                     << "L2 cache:" << "L3 cache:";

    m_cpuInfoKeyNameList << "架构" << "运行模式" << "字节序" << "CPU核数量"
                     << "每核线程数" << "每插槽核数量" << "插槽数"
                     << "厂商" << "CPU族" << "型号" << "步进"
                     << "主频(MHz)" << "性能(MIPS)" << "一级数据缓存" << "一级指令缓存"
                     << "二级缓存" << "三级缓存";
}

QString CpuGeneralInfo::getValueByIndex(int index) {
    if (index >= getCpuInfoCount())
        return "";

    QString key = getKeyByIndex(index);
    if (key.isEmpty())
        return "";

    return m_jsonCpuInfo.value(key).toString();
}
