#include "systemperfreport.h"

#include <QtWidgets/QGridLayout>

#include <QDesktopServices>
#include <QUrl>
#include "common.h"
#include "Utils/csysutils.h"
#include "Report/generatepdfreport.h"


#include <QMessageBox>
#include <QTreeView>

SystemPerfReport::SystemPerfReport(QWidget *parent) : QWidget(parent)
{
    m_pdfReportFile = g_sWorkingPath + "/test_QPdfWriter.pdf";
//    m_pdfReportFile = g_sWorkingPath + "/system_report.pdf";

    initReportLayout();
}

void SystemPerfReport::initReportLayout() {
    m_buttonGetSysInfo = new QPushButton();
    m_buttonGetSysInfo->setText("获取系统信息");

    m_buttonGenerateReport = new QPushButton();
    m_buttonGenerateReport->setText("生成报告");
    m_buttonGenerateReport->setEnabled(false);

    QStringList headers;
    headers << tr("名称") << tr("内容");
    m_treeSystemReport = new MyTreeModel(headers, "");

    QTreeView * viewReport = new QTreeView();
    viewReport->setModel(m_treeSystemReport);
    viewReport->setColumnWidth(0, 200);
    viewReport->setAlternatingRowColors(true);
    viewReport->setEditTriggers(QAbstractItemView::NoEditTriggers);
    viewReport->setMouseTracking(true);
//    viewReport->set

    QHBoxLayout * horiLayout = new QHBoxLayout();
    horiLayout->addWidget(m_buttonGetSysInfo);
    horiLayout->addWidget(m_buttonGenerateReport);
    QVBoxLayout * vertiLayout = new QVBoxLayout();
    vertiLayout->addLayout(horiLayout);
    vertiLayout->addWidget(viewReport);
//    QGridLayout * mainLayout = new QGridLayout;
//    mainLayout->addWidget(m_buttonGetSysInfo, 0, 0);
//    mainLayout->addWidget(m_buttonGenerateReport, 0, 1);
//    mainLayout->addWidget(viewReport, 1, 1);
//    mainLayout->setRowStretch(0, 0);
//    mainLayout->setRowStretch(1, 1);

    setLayout(vertiLayout);

    connect(m_buttonGetSysInfo, SIGNAL(clicked()), this, SLOT(getSystemInfo()));
    connect(m_buttonGenerateReport, SIGNAL(clicked()), this, SLOT(generateReport()));
}

void SystemPerfReport::getSystemInfo() {

    if (!refreshOsGeneralInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!refreshCpuGeneralInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!refreshCpuUsageInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!refreshMemoryGeneralInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!refreshMemoryRankInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!refreshDiskInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!refreshNetworkInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    m_buttonGenerateReport->setEnabled(true);

}

void SystemPerfReport::generateReport() {
    GeneratePdfReport pdfReport;
    pdfReport.writeReport(this);

    openReport();
}

bool SystemPerfReport::refreshOsGeneralInfo() {
    // 获取系统信息
    if (!m_osGeneralInfo.fetchInfo())
        return false;

    // 在表中插入内存信息行
    QModelIndex indexOsInfo = updateTitleNode(ROW_OS_GENERAL_INFO, "系统信息");

    QJsonObject osInfo = m_osGeneralInfo.getOsInfo();
    QJsonObject::Iterator iter;
    int index = 0;
    for (iter = osInfo.begin(); iter != osInfo.end(); iter++)
    {
        updateChildNode(index, iter.key(), iter.value().toVariant(), indexOsInfo);
        index++;
    }

    return true;
}

bool SystemPerfReport::refreshMemoryGeneralInfo() {
    // 取内存信息
    if ( !m_memGeneralInfo.fetchInfo() )
        return false;

    // 在表中插入内存信息行
    QModelIndex indexMemInfo = updateTitleNode(ROW_MEM_GENERAL_INFO, "内存基本信息");

    QStringList keyList = m_memGeneralInfo.getKeyList();
    for (int i=0; i<keyList.count(); i++) {
        QString value = m_memGeneralInfo.getKeyValue(keyList[i]);
        updateChildNode(i, keyList[i], value + " KB", indexMemInfo);
    }

    return true;
}

bool SystemPerfReport::refreshMemoryRankInfo() {
    // 获取内存占用排行信息
    if ( !m_memRankInfo.fetchInfo() )
        return false;

    // 在表中插入内存占用排行
    QModelIndex indexMemRank = updateTitleNode(ROW_MEM_RATE_RANKING, "内存占用排行");

    for (int i=0; i<m_memRankInfo.getMemRankDataCount(); i++) {
        TaskRunningInfo taskInfo = m_memRankInfo.getMemRankData(i);
        QString procName = QString("(%1%) %2").arg(taskInfo.memRate()).arg(taskInfo.cmd());
        updateChildNode(i, i+1, procName, indexMemRank);
    }

    return true;
}

QModelIndex SystemPerfReport::updateTitleNode(int rowIndex, QVariant title) {
    QModelIndex indexItem;

    // 查找指定行是否存在
    indexItem = m_treeSystemReport->index(rowIndex, 0);
    if ( !indexItem.isValid() ) {
        // 插入行
        m_treeSystemReport->insertRow(rowIndex);
        indexItem = m_treeSystemReport->index(rowIndex, 0);
    }

    m_treeSystemReport->setData(indexItem, title);

    return indexItem;
}

QModelIndex SystemPerfReport::updateChildNode(int rowIndex, QVariant key, QVariant value, QModelIndex parentIndex) {
    QModelIndex indexItem0;

    // 查找指定行是否存在
    indexItem0 = m_treeSystemReport->index(rowIndex, 0, parentIndex);
    if ( !indexItem0.isValid() ) {
        // 插入行
        m_treeSystemReport->insertRow(rowIndex, parentIndex);
        indexItem0 = m_treeSystemReport->index(rowIndex, 0, parentIndex);
    }

    // 填写第一列
    m_treeSystemReport->setData(indexItem0, key);

    // 填写第二列
    QModelIndex indexItem1 = m_treeSystemReport->index(rowIndex, 1, parentIndex);
    m_treeSystemReport->setData(indexItem1, value);

    return indexItem0;
}

bool SystemPerfReport::refreshCpuUsageInfo() {
    // 获取CPU的运行信息
    if (!m_cpuUsageInfo.fetchInfo())
        return false;

    //! 任务信息
    // 在表中插入任务信息行
    QModelIndex indexTasksInfo = updateTitleNode(ROW_TASKS_INFO, "进程信息");
    // 插入子节点：任务详细信息
    updateChildNode(0, "总任务数", m_cpuUsageInfo.getTasksCount(), indexTasksInfo);
    updateChildNode(1, "运行任务数", m_cpuUsageInfo.getRunningTasksCount(), indexTasksInfo);
    updateChildNode(2, "休眠任务数", m_cpuUsageInfo.getSleepingTasksCount(), indexTasksInfo);
    updateChildNode(3, "终止任务数", m_cpuUsageInfo.getStoppedTasksCount(), indexTasksInfo);
    updateChildNode(4, "僵尸任务数", m_cpuUsageInfo.getZombieTasksCount(), indexTasksInfo);

    //! CPU使用信息
    // 在表中插入CPU使用信息行
    QModelIndex indexCpuUsageInfo = updateTitleNode(ROW_CPU_USAGE_INFO, "CPU占用率(%)");
    // 插入子节点：CPU使用率
    updateChildNode(0, "用户态", m_cpuUsageInfo.getUserRate(), indexCpuUsageInfo);
    updateChildNode(1, "内核态", m_cpuUsageInfo.getKernelRate(), indexCpuUsageInfo);
    updateChildNode(2, "空闲率", m_cpuUsageInfo.getIdleRate(), indexCpuUsageInfo);
    updateChildNode(3, "IO等待", m_cpuUsageInfo.getIoRate(), indexCpuUsageInfo);
    updateChildNode(4, "硬中断", m_cpuUsageInfo.getHardIntRate(), indexCpuUsageInfo);
    updateChildNode(5, "软中断", m_cpuUsageInfo.getSoftIntRate(), indexCpuUsageInfo);

    //! CPU使用率任务排行
    QModelIndex indexCpuRateRank = updateTitleNode(ROW_CPU_RATE_RANKING, "CPU占用排行");
    for (int i=0; i<m_cpuUsageInfo.getCpuRankDataCount(); i++) {
        TaskRunningInfo taskInfo = m_cpuUsageInfo.getCpuRankData(i);
        QString procName = QString("(%1%) %2").arg(taskInfo.cpuRate()).arg(taskInfo.cmd());
        updateChildNode(i, i+1, procName, indexCpuRateRank);
    }

    return true;
}

bool SystemPerfReport::refreshCpuGeneralInfo() {
    //  获取系统的CPU信息
    if ( !m_cpuGeneralInfo.fetchInfo() )
        return false;

    // 在表中插入CPU基本信息行
    QModelIndex indexCpuInfo = updateTitleNode(ROW_CPU_GENERAL_INFO, "CPU基本信息");

    for (int i=0; i<m_cpuGeneralInfo.getCpuInfoCount(); i++) {
        // 逐个获取CPU信息（中文名称和值）
        QString itemName = m_cpuGeneralInfo.getKeyNameByIndex(i);
        QString itemValue = m_cpuGeneralInfo.getValueByIndex(i);

        // 插入新行，并填入CPU信息
        updateChildNode(i, itemName, itemValue, indexCpuInfo);
    }

    return true;
}

bool SystemPerfReport::refreshDiskInfo() {
    // 获取磁盘信息
    if ( !m_diskGeneralInfo.fetchInfo() )
        return false;

    // 在表中插入标题节点：磁盘信息
    QModelIndex indexDiskInfo = updateTitleNode(ROW_DISK_INFO, "磁盘信息");

    int diskCount = m_diskGeneralInfo.getDiskCount();
    for (int i = 0; i < diskCount; i++) {
        QModelIndex indexDiskName = updateChildNode(i, m_diskGeneralInfo.getFSName(i), "", indexDiskInfo);
        QJsonObject jsonObj = m_diskGeneralInfo.getFSInfo(i);

        QJsonObject::Iterator iter;
        int index = 0;
        for (iter = jsonObj.begin(); iter != jsonObj.end(); iter++)
        {
            updateChildNode(index, iter.key(), iter.value().toString(), indexDiskName);
            index++;
        }
    }

    return true;
}

void SystemPerfReport::openReport(){
    if (!CSysUtils::isFileExist(m_pdfReportFile)) {
        // 检查报告PDF文件是否存在
        QMessageBox::warning(NULL, "警告", "没有报告文件，请先生成报告。", QMessageBox::Ok);
        return;
    }

    bool bRV = QDesktopServices::openUrl(QUrl::fromLocalFile(m_pdfReportFile));
    if (!bRV) {
    }
}

bool SystemPerfReport::refreshNetworkInfo() {
    // 获取网络信息
    if ( !m_netGeneralInfo.fetchInfo() )
        return false;

    // 在表中插入标题节点：网络信息
    QModelIndex indexNetworkInfo = updateTitleNode(ROW_NETWORK_INFO, "网络信息");

    QJsonObject networkInfo = m_netGeneralInfo.getInfo();
    QJsonObject::Iterator iter;
    int index = 0;
    for (iter = networkInfo.begin(); iter != networkInfo.end(); iter++)
    {
        updateChildNode(index, iter.key(), iter.value().toVariant(), indexNetworkInfo);
        index++;
    }


    return true;
}
