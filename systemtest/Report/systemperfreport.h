#ifndef SYSTEMPERFREPORT_H
#define SYSTEMPERFREPORT_H

#include <QPushButton>
#include <QWidget>
#include "CustomWidgets/mytreemodel.h"
#include "Report/cpugeneralinfo.h"
#include "Report/cpuusageinfo.h"
#include "Report/taskrunninginfo.h"
#include "Report/memgeneralinfo.h"
#include "Report/memusagerate.h"

class SystemPerfReport : public QWidget
{
    Q_OBJECT
public:
    explicit SystemPerfReport(QWidget *parent = nullptr);

private:
    enum {
        ROW_CPU_GENERAL_INFO = 0,
        ROW_TASKS_INFO,
        ROW_CPU_USAGE_INFO,
        ROW_CPU_RATE_RANKING,
        ROW_MEM_GENERAL_INFO,
        ROW_MEM_RATE_RANKING,
    };
    void initReportLayout();

    void openReport();

    void updateTitleNode(int rowIndex, QVariant title);
    void updateChildNode(int rowIndex, QVariant key, QVariant value, QModelIndex parentIndex);

    // 获取CPU基本信息
    bool getCpuGeneralInfo();
    CpuGeneralInfo      m_cpuGeneralInfo;

    // 获取CPU运行信息
    bool getCpuUsageInfo();
    CpuUsageInfo        m_cpuUsageInfo;

//    // 获取CPU使用率排行信息
//    bool getCpuRateRanking();
//    QList<TaskRunningInfo>  m_cpuRankingList;

    // 获取内存信息
    bool getMemoryGeneralInfo();
    MemGeneralInfo      m_memGeneralInfo;

    // 获取内存占用排行信息
    bool getMemoryRankInfo();
    MemUsageRate        m_memRankInfo;

    // 临时测试按钮
    QPushButton *       m_buttonTest;

    // 报告临时文件路径，PDF格式
    QString             m_pdfReportFile;

    MyTreeModel *       m_treeSystemReport;


signals:

public slots:
    void generateReport();

};

#endif // SYSTEMPERFREPORT_H
