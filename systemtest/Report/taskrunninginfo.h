#ifndef TASKRUNNINGINFO_H
#define TASKRUNNINGINFO_H

#include <QString>



class TaskRunningInfo
{
public:
    TaskRunningInfo();

    QString cmd() const;
    void setCmd(const QString &cmd);

    int pid() const;
    void setPid(int pid);

    float cpuRate() const;
    void setCpuRate(float cpuRate);

    float memRate() const;
    void setMemRate(float memRate);

    QString cpuTime() const;
    void setCpuTime(QString cpuTime);

    QString status() const;
    void setStatus(const QString &status);

private:
    // 进程名
    QString     m_cmd;
    // 进程ID
    int         m_pid;
    // CPU占用率
    float       m_cpuRate;
    // 内存占用率
    float       m_memRate;
    // CPU使用时间总计，字符串形式，单位：1/100秒
    QString     m_cpuTime;
    // 进程状态：D=不可中断的睡眠状态 R=运行 S=睡眠 T=跟踪/停止 Z=僵尸进程
    QString     m_status;
};

#endif // TASKRUNNINGINFO_H
