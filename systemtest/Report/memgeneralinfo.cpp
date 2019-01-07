#include "memgeneralinfo.h"

#include <QProcess>

#include "Utils/transformutil.h"

MemGeneralInfo::MemGeneralInfo()
{
    m_keyNameList << "MemTotal" << "MemFree" << "MemAvailable" << "Cached"
                  << "Buffers" << "SwapTotal" << "SwapFree" << "Active"
                  << "Inactive" << "Shmem" << "Mapped" << "Slab"
                  << "VmallocTotal" << "VmallocUsed";
    m_keyMeaningList << "内存总量" << "空闲内存" << "可用内存" << "缓存区大小"
                     << "缓冲区大小" << "交换区总量" << "空闲交换区" << "活跃内存总量"
                     << "不活跃内存总量" << "共享内存" << "已映射" << "内核Slab"
                     << "虚拟内存总量" << "已用虚拟内存";
}

bool MemGeneralInfo::fetchInfo() {
    QProcess procMem;
    QString cmd = "cat";
    QStringList paramsList;
    paramsList << "/proc/meminfo";

    // 执行进程
    procMem.start(cmd, paramsList);
    procMem.waitForFinished();

    // 读取错误信息，如有错误信息，则返回失败
    QString error = procMem.readAllStandardError();
    if (!error.isEmpty())
        return false;

    // 读取内存信息结果
    QString memInfo = procMem.readAllStandardOutput();

    // 解析内存信息
    if (!parseMemInfo(memInfo)) {
        return false;
    }

    return true;
}

QString MemGeneralInfo::getKeyMeaning(QString key) {
    for (int i=0; i<m_keyNameList.count(); i++) {
        if (key == m_keyNameList[i])
            return m_keyMeaningList[i];
    }

    return "";
}

bool MemGeneralInfo::parseMemInfo(QString memInfo) {
    // 将内存信息按行来分割
    QStringList infoList = memInfo.split("\n");
    if (infoList.count() <= 0)
        return false;

    // 清空保存的内存信息，准备填入新的数据
    TransformUtil::clearJsonObject(&m_memInfo);

    for (QString item : infoList) {
        // infoItem 形如：MemTotal:        8166536 kB
        // 整理数据：空格和冒号
        item = TransformUtil::trimSpace(item);
        item.remove(":");

        // 只取关心的数据
        QStringList itemList = item.split(" ");
        QString keyMeaning = getKeyMeaning(itemList[0]);
        if (keyMeaning.isEmpty())
            continue;

        // JSON对象的键值是自定义的名称（中文或英文）
//        QJsonObject jsonObj;
//        jsonObj.insert(itemList[0], itemList[1]);
        m_memInfo.insert(keyMeaning, itemList[1]);
    }

    return true;
}
