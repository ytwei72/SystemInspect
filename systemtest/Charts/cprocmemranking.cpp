#include "cprocmemranking.h"

CProcMemRanking::CProcMemRanking()
{

}

int CProcMemRanking::nPID() const
{
    return m_nPID;
}

void CProcMemRanking::setNPID(int nPID)
{
    m_nPID = nPID;
}

float CProcMemRanking::fRate() const
{
    return m_fRate;
}

void CProcMemRanking::setFRate(float fRate)
{
    m_fRate = fRate;
}

QString CProcMemRanking::strProcName() const
{
    return m_strProcName;
}

void CProcMemRanking::setStrProcName(const QString &strProcName)
{
    m_strProcName = strProcName;
}
