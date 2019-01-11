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
#include "Report/diskgeneralinfo.h"
#include "Report/osgeneralinfo.h"
#include "Report/networkgeneralinfo.h"

class SystemPerfReport : public QWidget
{
    Q_OBJECT
public:
    explicit SystemPerfReport(QWidget *parent = nullptr);

    OsGeneralInfo * getOsGeneralInfo() { return &m_osGeneralInfo; }
    CpuGeneralInfo * getCpuGeneralInfo() { return &m_cpuGeneralInfo; }
    CpuUsageInfo * getCpuUsageInfo() { return &m_cpuUsageInfo; }
    MemGeneralInfo * getMemGeneralInfo() { return &m_memGeneralInfo; }
    MemUsageRate * getMemRankInfo() { return &m_memRankInfo; }
    DiskGeneralInfo * getDiskGeneralInfo() { return &m_diskGeneralInfo; }
    NetworkGeneralInfo * getNetGeneralInfo() { return &m_netGeneralInfo; }


private:
    enum {
        ROW_OS_GENERAL_INFO = 0,
        ROW_CPU_GENERAL_INFO,
        ROW_TASKS_INFO,
        ROW_CPU_USAGE_INFO,
        ROW_CPU_RATE_RANKING,
        ROW_MEM_GENERAL_INFO,
        ROW_MEM_RATE_RANKING,
        ROW_DISK_INFO,
        ROW_NETWORK_INFO,
    };
    void initReportLayout();

    void openReport();

    QModelIndex updateTitleNode(int rowIndex, QVariant title);
    QModelIndex updateChildNode(int rowIndex, QVariant key, QVariant value, QModelIndex parentIndex);

    // 获取系统信息
    bool refreshOsGeneralInfo();
    OsGeneralInfo       m_osGeneralInfo;

    // 获取CPU基本信息
    bool refreshCpuGeneralInfo();
    CpuGeneralInfo      m_cpuGeneralInfo;

    // 获取CPU运行信息
    bool refreshCpuUsageInfo();
    CpuUsageInfo        m_cpuUsageInfo;

//    // 获取CPU使用率排行信息
//    bool getCpuRateRanking();
//    QList<TaskRunningInfo>  m_cpuRankingList;

    // 获取内存信息
    bool refreshMemoryGeneralInfo();
    MemGeneralInfo      m_memGeneralInfo;

    // 获取内存占用排行信息
    bool refreshMemoryRankInfo();
    MemUsageRate        m_memRankInfo;

    // 获取磁盘信息
    bool refreshDiskInfo();
    DiskGeneralInfo     m_diskGeneralInfo;

    // 获取网卡信息
    bool refreshNetworkInfo();
    NetworkGeneralInfo  m_netGeneralInfo;


    // 获取系统信息按钮
    QPushButton *       m_buttonGetSysInfo;
    // 生成报告按钮
    QPushButton *       m_buttonGenerateReport;

    // 报告临时文件路径，PDF格式
    QString             m_pdfReportFile;

    MyTreeModel *       m_treeSystemReport;


signals:

public slots:
    void getSystemInfo();
    void generateReport();

};

#endif // SYSTEMPERFREPORT_H
