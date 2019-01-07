#include "memusagerate.h"

#include <QProcess>

#include "Utils/transformutil.h"

MemUsageRate::MemUsageRate()
{
    m_maxTaskCount = 16;
}

bool MemUsageRate::fetchInfo() {
    QProcess procMem;

    //! top命令获取系统监控信息
    // 查询系统监控信息，只获取一次
    QString cmd = "top";
    QStringList paramsList;
    // -b 参数防止命令执行的错误："TERM environment variable not set"
    paramsList << "-b" << "-o" << "%MEM" << "-n" << "1";

    // 启动命令
    procMem.start(cmd, paramsList);

    // 读取命令返回结果
    procMem.waitForFinished();
    QString errorInfo = procMem.readAllStandardError();
    if (!errorInfo.isEmpty())
        return false;

    QString rankData = procMem.readAllStandardOutput();
    QString taskRankTitle = "PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND\n";
    int pos = rankData.indexOf(taskRankTitle);
    if (pos < 0)
        return false;

    if (!parseMemRankData(rankData.mid(pos + taskRankTitle.length())))
        return false;

    return true;
}

bool MemUsageRate::parseMemRankData(QString rankData) {
    QStringList rankList = rankData.split("\n");

    QStringList detailsList;
    TaskRunningInfo runInfo;
    m_memRankList.clear();
    foreach (QString row, rankList) {
        if (row.isEmpty())
            continue;

        // 使用一个空格替换掉连续的多余的空格，并去掉首尾的空格
        row = TransformUtil::trimSpace(row);

        detailsList = row.split(" ");
        runInfo.setPid(detailsList[0].toInt());
        runInfo.setCpuRate(detailsList[8].toFloat());
        runInfo.setMemRate(detailsList[9].toFloat());
        runInfo.setCpuTime(detailsList[10]);
        runInfo.setCmd(detailsList[11]);
        runInfo.setStatus(detailsList[7]);

        m_memRankList.append(runInfo);

        if (m_memRankList.count() >= m_maxTaskCount)
            break;
    }

    return (m_memRankList.count() > 0);
}
