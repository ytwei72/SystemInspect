#include "diskgeneralinfo.h"

#include <QProcess>

#include "Utils/transformutil.h"

DiskGeneralInfo::DiskGeneralInfo()
{

}

bool DiskGeneralInfo::fetchInfo() {
//    if (!fetchFDiskInfo())
//        return false;

    if (!fetchDiskFSInfo())
        return false;

    return true;
}

/**
    Disk /dev/sda: 80 GiB, 85899345920 bytes, 167772160 sectors
    Units: sectors of 1 * 512 = 512 bytes
    Sector size (logical/physical): 512 bytes / 512 bytes
    I/O size (minimum/optimal): 512 bytes / 512 bytes
    Disklabel type: dos
    Disk identifier: 0x011f6e81

    Device     Boot     Start       End   Sectors Size Id Type
    /dev/sda1  *         2048 163579903 163577856  78G 83 Linux
    /dev/sda2       163581950 167770111   4188162   2G  5 Extended
    /dev/sda5       163581952 167770111   4188160   2G 82 Linux swap / Solaris
*/
bool DiskGeneralInfo::fetchFDiskInfo() {
    QProcess procFDisk;

    QString cmd = "fdisk";
    QStringList paramsList;
    paramsList << "-l";

    // 执行 fdisk 命令
    procFDisk.start(cmd, paramsList);
    procFDisk.waitForFinished();

    // 检查是否有错误，没有错误则读取执行输出结果
    QString errorInfo = procFDisk.readAllStandardError();
    if (!errorInfo.isEmpty())
        return false;
    QString fDiskResult = procFDisk.readAllStandardOutput();
    if (fDiskResult.isEmpty())
        return false;

    return true;
}

/**
    文件系统        容量  已用  可用 已用% 挂载点
    udev            3.9G     0  3.9G    0% /dev
    tmpfs           798M  9.6M  788M    2% /run
    /dev/sda1        77G   26G   47G   36% /
    tmpfs           3.9G   16M  3.9G    1% /dev/shm
    tmpfs           5.0M     0  5.0M    0% /run/lock
    tmpfs           3.9G     0  3.9G    0% /sys/fs/cgroup
    tmpfs           798M   12K  798M    1% /run/user/133
    tmpfs           798M   24K  798M    1% /run/user/0
*/
bool DiskGeneralInfo::fetchDiskFSInfo() {
    QProcess procDF;

    QString cmd = "df";
    QStringList paramsList;
    paramsList << "-h";

    // 执行 df 命令
    procDF.start(cmd, paramsList);
    procDF.waitForFinished();

    // 检查是否有错误，没有错误则读取执行输出结果
    QString errorInfo = procDF.readAllStandardError();
    if (!errorInfo.isEmpty())
        return false;
    QString dfResult = procDF.readAllStandardOutput();

    m_diskInfoList.clear();

    // 用换行符分割
    QStringList rowList = dfResult.split("\n");
    if (rowList.count() <= 1)
        return false;

    for (int i=1; i<rowList.count(); i++) {
        // 第一行是标题，跳过
        QString row = rowList[i];
        QStringList itemList = TransformUtil::trimSpace(row).split(" ");
        if ((itemList.count() == 6) && (!itemList[0].isEmpty())) {
            // 保存磁盘信息
            DiskFSInfo fsInfo;
            fsInfo.loadFSInfo(itemList);
            m_diskInfoList.append(fsInfo);
        }
    }

    return true;
}

QString DiskGeneralInfo::getFSName(int index) {
    if (m_diskInfoList.count() <= index)
        return "";

    return m_diskInfoList[index].fsName();
}

QJsonObject DiskGeneralInfo::getFSInfo(int index) {
    QJsonObject jsonObj;
    if (m_diskInfoList.count() <= index)
        return jsonObj;

    DiskFSInfo fsInfo = m_diskInfoList[index];
    jsonObj.insert("1: 容量", fsInfo.totalVolume());
    jsonObj.insert("2: 已用", fsInfo.usedVolume());
    jsonObj.insert("3: 可用", fsInfo.availVolume());
    jsonObj.insert("4: 已用%", fsInfo.usedRate());
    jsonObj.insert("5: 挂载点", fsInfo.mountPoint());

    return jsonObj;
}

