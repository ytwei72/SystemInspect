#include "systemperfreport.h"

#include <QtWidgets/QGridLayout>

#include <QDesktopServices>
#include <QUrl>
#include "common.h"
#include "Utils/csysutils.h"


#include <QMessageBox>
#include <QTreeView>

SystemPerfReport::SystemPerfReport(QWidget *parent) : QWidget(parent)
{
    m_pdfReportFile = g_sWorkingPath + "/test_QPdfWriter.pdf";
//    m_pdfReportFile = g_sWorkingPath + "/system_report.pdf";

    initReportLayout();
}

void SystemPerfReport::initReportLayout() {
    m_buttonTest = new QPushButton();
    m_buttonTest->setText("生成系统性能PDF");

    QStringList headers;
    headers << tr("名称") << tr("内容");
    m_treeSystemReport = new MyTreeModel(headers, "");

    QTreeView * viewReport = new QTreeView();
    viewReport->setModel(m_treeSystemReport);
    viewReport->setColumnWidth(0, 200);
    viewReport->setAlternatingRowColors(true);
    viewReport->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(m_buttonTest, 0, 0);
    mainLayout->addWidget(viewReport, 1, 0);
    mainLayout->setRowStretch(0, 0);
    mainLayout->setRowStretch(1, 1);

    setLayout(mainLayout);

    connect(m_buttonTest, SIGNAL(clicked()), this, SLOT(generateReport()));
}

void SystemPerfReport::generateReport() {
    // 清空表格
//    m_treeSystemReport->removeRows(0, m_treeSystemReport->rowCount());

    if (!getCpuGeneralInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!getCpuUsageInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!getMemoryGeneralInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }

    if (!getMemoryRankInfo()) {
        // TODO: 目前版本不做失败处理
        return;
    }



//    openReport();
}

bool SystemPerfReport::getMemoryGeneralInfo() {
    // 取内存信息
    if ( !m_memGeneralInfo.fetchInfo() )
        return false;

    // 在表中插入内存信息行
    updateTitleNode(ROW_MEM_GENERAL_INFO, "内存基本信息");
    QModelIndex indexMemInfo = m_treeSystemReport->index(ROW_MEM_GENERAL_INFO, 0);

    QStringList keyList = m_memGeneralInfo.getKeyList();
    for (int i=0; i<keyList.count(); i++) {
        QString value = m_memGeneralInfo.getKeyValue(keyList[i]);
        updateChildNode(i, keyList[i], value + " KB", indexMemInfo);
    }

    return true;
}

bool SystemPerfReport::getMemoryRankInfo() {
    // 获取内存占用排行信息
    if ( !m_memRankInfo.fetchInfo() )
        return false;

    // 在表中插入内存占用排行
    updateTitleNode(ROW_MEM_RATE_RANKING, "内存占用排行");
    QModelIndex indexMemRank = m_treeSystemReport->index(ROW_MEM_RATE_RANKING, 0);

    for (int i=0; i<m_memRankInfo.getMemRankDataCount(); i++) {
        TaskRunningInfo taskInfo = m_memRankInfo.getMemRankData(i);
        QString procName = QString("(%1%) %2").arg(taskInfo.memRate()).arg(taskInfo.cmd());
        updateChildNode(i, i+1, procName, indexMemRank);
    }

    return true;
}

void SystemPerfReport::updateTitleNode(int rowIndex, QVariant title) {
    QModelIndex indexItem;

    // 查找指定行是否存在
    indexItem = m_treeSystemReport->index(rowIndex, 0);
    if ( !indexItem.isValid() ) {
        // 插入行
        m_treeSystemReport->insertRow(rowIndex);
        indexItem = m_treeSystemReport->index(rowIndex, 0);
    }

    m_treeSystemReport->setData(indexItem, title);
}

void SystemPerfReport::updateChildNode(int rowIndex, QVariant key, QVariant value, QModelIndex parentIndex) {
    QModelIndex indexItem;

    // 查找指定行是否存在
    indexItem = m_treeSystemReport->index(rowIndex, 0, parentIndex);
    if ( !indexItem.isValid() ) {
        // 插入行
        m_treeSystemReport->insertRow(rowIndex, parentIndex);
        indexItem = m_treeSystemReport->index(rowIndex, 0, parentIndex);
    }

    // 填写第一列
    m_treeSystemReport->setData(indexItem, key);

    // 填写第二列
    indexItem = m_treeSystemReport->index(rowIndex, 1, parentIndex);
    m_treeSystemReport->setData(indexItem, value);
}

bool SystemPerfReport::getCpuUsageInfo() {
    // 获取CPU的运行信息
    if (!m_cpuUsageInfo.fetchInfo())
        return false;

    //! 任务信息
    // 在表中插入任务信息行
    updateTitleNode(ROW_TASKS_INFO, "进程信息");
//    m_treeSystemReport->insertRow(ROW_TASKS_INFO);
    QModelIndex indexTasksInfo = m_treeSystemReport->index(ROW_TASKS_INFO, 0);
//    m_treeSystemReport->setData(indexTasksInfo, "进程信息");
    // 插入子节点：任务详细信息
    updateChildNode(0, "总任务数", m_cpuUsageInfo.getTasksCount(), indexTasksInfo);
    updateChildNode(1, "运行任务数", m_cpuUsageInfo.getRunningTasksCount(), indexTasksInfo);
    updateChildNode(2, "休眠任务数", m_cpuUsageInfo.getSleepingTasksCount(), indexTasksInfo);
    updateChildNode(3, "终止任务数", m_cpuUsageInfo.getStoppedTasksCount(), indexTasksInfo);
    updateChildNode(4, "僵尸任务数", m_cpuUsageInfo.getZombieTasksCount(), indexTasksInfo);

    //! CPU使用信息
    // 在表中插入CPU使用信息行
    updateTitleNode(ROW_CPU_USAGE_INFO, "CPU占用率(%)");
//    m_treeSystemReport->insertRow(ROW_CPU_USAGE_INFO);
    QModelIndex indexCpuUsageInfo = m_treeSystemReport->index(ROW_CPU_USAGE_INFO, 0);
//    m_treeSystemReport->setData(indexCpuUsageInfo, "CPU占用率(%)");
    // 插入子节点：CPU使用率
    updateChildNode(0, "用户态", m_cpuUsageInfo.getUserRate(), indexCpuUsageInfo);
    updateChildNode(1, "内核态", m_cpuUsageInfo.getKernelRate(), indexCpuUsageInfo);
    updateChildNode(2, "空闲率", m_cpuUsageInfo.getIdleRate(), indexCpuUsageInfo);
    updateChildNode(3, "IO等待", m_cpuUsageInfo.getIoRate(), indexCpuUsageInfo);
    updateChildNode(4, "硬中断", m_cpuUsageInfo.getHardIntRate(), indexCpuUsageInfo);
    updateChildNode(5, "软中断", m_cpuUsageInfo.getSoftIntRate(), indexCpuUsageInfo);

    //! CPU使用率任务排行
    updateTitleNode(ROW_CPU_RATE_RANKING, "CPU占用排行");
    QModelIndex indexCpuRateRank = m_treeSystemReport->index(ROW_CPU_RATE_RANKING, 0);
    for (int i=0; i<m_cpuUsageInfo.getCpuRankDataCount(); i++) {
        TaskRunningInfo taskInfo = m_cpuUsageInfo.getCpuRankData(i);
        QString procName = QString("(%1%) %2").arg(taskInfo.cpuRate()).arg(taskInfo.cmd());
        updateChildNode(i, i+1, procName, indexCpuRateRank);
    }

    return true;
}

bool SystemPerfReport::getCpuGeneralInfo() {
    //  获取系统的CPU信息
    if ( !m_cpuGeneralInfo.fetchInfo() )
        return false;

    // 在表中插入CPU基本信息行
    updateTitleNode(ROW_CPU_GENERAL_INFO, "CPU基本信息");
//    m_treeSystemReport->insertRow(ROW_CPU_GENERAL_INFO);
    QModelIndex indexCpuInfo = m_treeSystemReport->index(ROW_CPU_GENERAL_INFO, 0);
//    m_treeSystemReport->setData(indexCpuInfo, "CPU基本信息");

    for (int i=0; i<m_cpuGeneralInfo.getCpuInfoCount(); i++) {
        // 逐个获取CPU信息（中文名称和值）
        QString itemName = m_cpuGeneralInfo.getKeyNameByIndex(i);
        QString itemValue = m_cpuGeneralInfo.getValueByIndex(i);

        // 插入新行，并填入CPU信息
        updateChildNode(i, itemName, itemValue, indexCpuInfo);
//        m_treeSystemReport->insertRow(i, indexCpuInfo);
//        QModelIndex indexItem = m_treeSystemReport->index(i, 0, indexCpuInfo);
//        m_treeSystemReport->setData(indexItem, itemName);
//        indexItem = m_treeSystemReport->index(i, 1, indexCpuInfo);
//        m_treeSystemReport->setData(indexItem, itemValue);
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
