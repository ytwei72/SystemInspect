#include "cpuusageinfo.h"
#include "Utils/transformutil.h"

#include <QProcess>

CpuUsageInfo::CpuUsageInfo()
{
    m_maxTaskCount = 16;
}

bool CpuUsageInfo::fetchInfo() {
    QProcess proc;

    //! top命令获取系统监控信息
    // 查询系统监控信息，只获取一次
    QString cmd = "top";
    QStringList paramsList;
    // -b 参数防止命令执行的错误："TERM environment variable not set"
    paramsList << "-b" << "-o" << "%CPU" << "-n" << "1";
//    paramsList << "-n 1";

    // 启动命令
    proc.start(cmd, paramsList);

    // 读取命令返回结果
    proc.waitForFinished();
    QString usageInfo = proc.readAllStandardOutput();
    QString errorInfo = proc.readAllStandardError();
    if (!errorInfo.isEmpty())
        return false;

    //! 任务监控结果
    QRegExp regExpTask("Tasks:(.*) total, (.*) running, (.*) sleeping, (.*) stopped, (.*) zombie");
    int pos = usageInfo.indexOf(regExpTask);
    if (pos < 0)
        return false;

    // 保存任务信息
    setTasksCount(regExpTask.cap(1).toInt());
    setRunningTasksCount(regExpTask.cap(2).toInt());
    setSleepingTasksCount(regExpTask.cap(3).toInt());
    setStoppedTasksCount(regExpTask.cap(4).toInt());
    setZombieTasksCount(regExpTask.cap(5).toInt());

    //! CPU使用结果
    QRegExp regExpCpuUsage("%Cpu\\(s\\): (.*) us, (.*) sy,  (.*) ni, (.*) id,  (.*) wa,  (.*) hi,  (.*) si,  (.*) st");
    pos = usageInfo.indexOf(regExpCpuUsage);
    if (pos < 0)
        return false;

    // 保存CPU使用信息
    setUserRate(regExpCpuUsage.cap(1).toFloat());
    setKernelRate(regExpCpuUsage.cap(2).toFloat());
    setIdleRate(regExpCpuUsage.cap(4).toFloat());
    setIoRate(regExpCpuUsage.cap(5).toFloat());
    setHardIntRate(regExpCpuUsage.cap(6).toFloat());
    setSoftIntRate(regExpCpuUsage.cap(7).toFloat());

    //! CPU任务占用率排行
    QString taskRankTitle = "PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND\n";
    pos = usageInfo.indexOf(taskRankTitle);
    if (pos < 0)
        return false;

    // 解析CPU排行数据
    parseCpuRankData(usageInfo.mid(pos + taskRankTitle.length()));

    return true;
}

void CpuUsageInfo::parseCpuRankData(QString rankData){
    QStringList rankList = rankData.split("\n");

    QStringList detailsList;
    TaskRunningInfo runInfo;
    m_cpuRankingList.clear();
    foreach (QString row, rankList) {
        if (row.isEmpty())
            continue;

        // 使用一个空格替换掉连续的多余的空格，并去掉首尾的空格
        row = TransformUtil::trimSpace(row);
//        row = row.replace(QRegExp("\\s{1,}"), " ");
//        row = row.trimmed();

        detailsList = row.split(" ");
        runInfo.setPid(detailsList[0].toInt());
        runInfo.setCpuRate(detailsList[8].toFloat());
        runInfo.setMemRate(detailsList[9].toFloat());
        runInfo.setCpuTime(detailsList[10]);
        runInfo.setCmd(detailsList[11]);
        runInfo.setStatus(detailsList[7]);

        m_cpuRankingList.append(runInfo);

        if (m_cpuRankingList.count() >= m_maxTaskCount)
            break;
    }

}

int CpuUsageInfo::getTasksCount() const
{
    return m_tasksCount;
}

void CpuUsageInfo::setTasksCount(int tasksCount)
{
    m_tasksCount = tasksCount;
}

int CpuUsageInfo::getRunningTasksCount() const
{
    return m_runningTasksCount;
}

void CpuUsageInfo::setRunningTasksCount(int runningTasksCount)
{
    m_runningTasksCount = runningTasksCount;
}

int CpuUsageInfo::getSleepingTasksCount() const
{
    return m_sleepingTasksCount;
}

void CpuUsageInfo::setSleepingTasksCount(int sleepingTasksCount)
{
    m_sleepingTasksCount = sleepingTasksCount;
}

int CpuUsageInfo::getStoppedTasksCount() const
{
    return m_stoppedTasksCount;
}

void CpuUsageInfo::setStoppedTasksCount(int stoppedTasksCount)
{
    m_stoppedTasksCount = stoppedTasksCount;
}

int CpuUsageInfo::getZombieTasksCount() const
{
    return m_zombieTasksCount;
}

void CpuUsageInfo::setZombieTasksCount(int zombieTasksCount)
{
    m_zombieTasksCount = zombieTasksCount;
}

float CpuUsageInfo::getUserRate() const
{
    return m_userRate;
}

void CpuUsageInfo::setUserRate(float userRate)
{
    m_userRate = userRate;
}

float CpuUsageInfo::getKernelRate() const
{
    return m_kernelRate;
}

void CpuUsageInfo::setKernelRate(float kernelRate)
{
    m_kernelRate = kernelRate;
}

float CpuUsageInfo::getIdleRate() const
{
    return m_idleRate;
}

void CpuUsageInfo::setIdleRate(float idleRate)
{
    m_idleRate = idleRate;
}

float CpuUsageInfo::getIoRate() const
{
    return m_ioRate;
}

void CpuUsageInfo::setIoRate(float ioRate)
{
    m_ioRate = ioRate;
}

float CpuUsageInfo::getHardIntRate() const
{
    return m_hardIntRate;
}

void CpuUsageInfo::setHardIntRate(float hardIntRate)
{
    m_hardIntRate = hardIntRate;
}

float CpuUsageInfo::getSoftIntRate() const
{
    return m_softIntRate;
}

void CpuUsageInfo::setSoftIntRate(float softIntRate)
{
    m_softIntRate = softIntRate;
}


