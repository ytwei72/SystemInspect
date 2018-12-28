#ifndef CMEMRANKING_H
#define CMEMRANKING_H

#include <QString>



class CProcMemRanking
{
public:
    CProcMemRanking();

    int nPID() const;
    void setNPID(int nPID);

    float fRate() const;
    void setFRate(float fRate);

    QString strProcName() const;
    void setStrProcName(const QString &strProcName);

private:
    // 进程ID
    int             m_nPID;
    // 进程的内存占用率
    float           m_fRate;
    // 进程名
    QString         m_strProcName;
};

#endif // CMEMRANKING_H
