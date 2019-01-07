#ifndef MEMGENERALINFO_H
#define MEMGENERALINFO_H

#include <QJsonObject>
#include <QStringList>



class MemGeneralInfo
{
public:
    MemGeneralInfo();

    bool fetchInfo();
    bool parseMemInfo(QString memInfo);
    QString getKeyMeaning(QString key);
    QStringList getKeyList() { return m_memInfo.keys(); }
    QString getKeyValue(QString key) { return m_memInfo[key].toString(); }

private:
    QJsonObject m_memInfo;
    QStringList m_keyNameList;
    QStringList m_keyMeaningList;

//    // MemTotal: 内存总量（单位：KB）
//    long        m_memTotal;
//    // MemFree: 空闲内存（单位：KB）
//    long        m_memFree;
//    // MemAvailable: 可用内存（单位：KB）
//    long        m_memAvail;
//    // 内存占用率（%）
//    float       m_memUsedRate;
//    // Cached: 缓存区大小（cache, CPU与内存间）（单位：KB）
//    long        m_cacheAmount;
//    // Buffers: 缓冲区大小（buffer，内存与磁盘间）（单位：KB）
//    long        m_bufferAmount;
//    // SwapTotal: 交换区总量（单位：KB）
//    long        m_swapTotal;
//    // SwapFree: 空闲交换区（单位：KB）
//    long        m_swapFree;
//    // Active: 活跃内存总量（单位：KB）
//    long        m_activeAmount;
//    // Inactive: 不活跃内存总量（单位：KB）
//    long        m_inactiveAmount;
//    // Shmem: 共享内存（单位：KB）
//    long        m_shareMem;
//    // Mapped: 已映射（单位：KB）
//    long        m_mappedMem;
//    // Slab: 内核Slab（单位：KB）
//    long        m_slab;
//    // VmallocTotal: 虚拟内存总量（单位：KB）
//    long        m_vmTotal;
//    // VmallocUsed: 已用虚拟内存（单位：KB）
//    long        m_vmUsed;
//    // 可用虚拟内存（单位：KB）
//    long        m_vmAvail;

};

#endif // MEMGENERALINFO_H
