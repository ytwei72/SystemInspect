#ifndef MEMUSAGERATE_H
#define MEMUSAGERATE_H

#include <QList>
#include <QString>

#include "Report/taskrunninginfo.h"


class MemUsageRate
{
public:
    MemUsageRate();

    bool fetchInfo();

    int getMemRankDataCount() { return m_memRankList.count(); }
    TaskRunningInfo getMemRankData(int index) { return m_memRankList[index]; }

private:
    bool parseMemRankData(QString rankData);
    QList<TaskRunningInfo>      m_memRankList;
    int                         m_maxTaskCount;
};

#endif // MEMUSAGERATE_H
