#ifndef CPUUSAGEINFO_H
#define CPUUSAGEINFO_H

#include "taskrunninginfo.h"

#include <QList>



class CpuUsageInfo
{
public:
    CpuUsageInfo();

    bool fetchInfo();
    int getUsageInfoCount();

    int getTasksCount() const;
    void setTasksCount(int tasksCount);

    int getRunningTasksCount() const;
    void setRunningTasksCount(int runningTasksCount);

    int getSleepingTasksCount() const;
    void setSleepingTasksCount(int sleepingTasksCount);

    int getStoppedTasksCount() const;
    void setStoppedTasksCount(int stoppedTasksCount);

    int getZombieTasksCount() const;
    void setZombieTasksCount(int zombieTasksCount);

    float getUserRate() const;
    void setUserRate(float userRate);

    float getKernelRate() const;
    void setKernelRate(float kernelRate);

    float getIdleRate() const;
    void setIdleRate(float idleRate);

    float getIoRate() const;
    void setIoRate(float ioRate);

    float getHardIntRate() const;
    void setHardIntRate(float hardIntRate);

    float getSoftIntRate() const;
    void setSoftIntRate(float softIntRate);

    void parseCpuRankData(QString rankData);
    int getCpuRankDataCount() { return m_cpuRankingList.count(); }
    TaskRunningInfo getCpuRankData(int index) { return m_cpuRankingList[index]; }

private:
    //! Task信息
    // 总任务数
    int         m_tasksCount;
    // 运行任务数
    int         m_runningTasksCount;
    // 休眠任务数
    int         m_sleepingTasksCount;
    // 中止任务数
    int         m_stoppedTasksCount;
    // 僵尸任务数
    int         m_zombieTasksCount;

    //! CPU运行信息
    // 用户任务占用率
    float       m_userRate;
    // 内核任务占用率
    float       m_kernelRate;
    // 空闲百分比
    float       m_idleRate;
    // IO等待占用率
    float       m_ioRate;
    // 硬中断占用率
    float       m_hardIntRate;
    // 软中断占用率
    float       m_softIntRate;

    //! CPU任务排行
    int         m_maxTaskCount;
    QList<TaskRunningInfo>  m_cpuRankingList;


};

#endif // CPUUSAGEINFO_H
