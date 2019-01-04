#include "taskrunninginfo.h"

TaskRunningInfo::TaskRunningInfo()
{

}

QString TaskRunningInfo::cmd() const
{
    return m_cmd;
}

void TaskRunningInfo::setCmd(const QString &cmd)
{
    m_cmd = cmd;
}

int TaskRunningInfo::pid() const
{
    return m_pid;
}

void TaskRunningInfo::setPid(int pid)
{
    m_pid = pid;
}

float TaskRunningInfo::cpuRate() const
{
    return m_cpuRate;
}

void TaskRunningInfo::setCpuRate(float cpuRate)
{
    m_cpuRate = cpuRate;
}

float TaskRunningInfo::memRate() const
{
    return m_memRate;
}

void TaskRunningInfo::setMemRate(float memRate)
{
    m_memRate = memRate;
}

float TaskRunningInfo::cpuTime() const
{
    return m_cpuTime;
}

void TaskRunningInfo::setCpuTime(float cpuTime)
{
    m_cpuTime = cpuTime;
}

QString TaskRunningInfo::status() const
{
    return m_status;
}

void TaskRunningInfo::setStatus(const QString &status)
{
    m_status = status;
}
