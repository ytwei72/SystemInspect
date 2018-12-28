#include "cmemallocchart.h"

#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>

#include <QTimer>
#include "common.h"

CMemAllocChart::CMemAllocChart(QWidget *parent) : QWidget(parent)
{
    m_bInitialSeries = true;
    m_nMaxRankings = 10;

    // 初始化内存分配情况表

    // 初始化内存分配情况图
    initMemChartWidget();

    // 创建一个横向布局
    m_mainLayout = new QHBoxLayout();
    // 在横向布局中加入图表部件
    m_mainLayout->addWidget(m_chartViewMemAlloc);

    // 设置页面的顶级布局
    setLayout(m_mainLayout);

    // 设置页面的背景自动填充模式
    this->setAutoFillBackground(true);

    // 创建获取内存信息的进程对象
    m_procMemAlloc = new QProcess();

    // 创建定时器，用于定时获取内存信息
    m_timerRefresh = new QTimer(this);
    connect(m_timerRefresh, SIGNAL(timeout()), this, SLOT(refreshMemAllocInfo()));
    m_timerRefresh->start(3000);

}

void CMemAllocChart::initHorizonBarSeries() {
    m_barSeries = new QHorizontalBarSeries();

    m_barSeries->setBarWidth(0.8);
}

void CMemAllocChart::initMemChartWidget() {
    // 初始化横条数据序列
    initHorizonBarSeries();

    // 创建内存分配图，并添加横向条序列
    m_chartMemAlloc = new QChart();
//    m_chartMemAlloc->addSeries(m_barSeries);
    m_chartMemAlloc->setTitle("内存占用排行");
//    m_chartMemAlloc->setAnimationOptions(QChart::SeriesAnimations);

    m_chartMemAlloc->legend()->setVisible(true);
    m_chartMemAlloc->legend()->setAlignment(Qt::AlignLeft);

    // 新建一个容纳图表的视图
    m_chartViewMemAlloc = new QChartView(m_chartMemAlloc);
    m_chartViewMemAlloc->setRenderHint(QPainter::Antialiasing);
}

void CMemAllocChart::refreshMemAllocInfo() {
    // 设置运行脚本
    QString strCmd = "bash";
    QStringList strParams;
    strParams<<g_sWorkingPath + "/NewScripts/memory/mem_ranking.sh";

    // 启动进程，并等待结束
    m_procMemAlloc->start(strCmd, strParams);
    bool bFinished = m_procMemAlloc->waitForFinished();
    // 超时情况下，直接退出处理
    if (!bFinished)
        return;

    // 清空进程信息的链表
    m_procList.clear();

    // 读取进程返回数据
//    QString strOutput = m_procMemAlloc->readAllStandardOutput();
    QString strReadLine;
    float fTotalRate = 0;
    for (int i=0; i<m_nMaxRankings; i++) {
        // 没有新行可读，则退出循环
        if (!m_procMemAlloc->canReadLine())
            break;

        // 读取当前行的数据
        strReadLine = m_procMemAlloc->readLine();

        // 使用正则表达式提取数据
        QRegExp regExp("PID:(.*)RATE:(.*)NAME:(.*)END");
        int pos = strReadLine.indexOf(regExp);
        if (pos < 0)
            return;

        // 创建一个对象保存：提取出来的进程各数据项
        CProcMemRanking * procInfo = new CProcMemRanking();
        procInfo->setNPID(regExp.cap(1).toInt());
        procInfo->setFRate(regExp.cap(2).toFloat());
        fTotalRate += regExp.cap(2).toFloat();
        procInfo->setStrProcName(regExp.cap(3));

        // 添加到链表中
        m_procList.append(procInfo);
    }

    // 增加一个"其它进程"
//    CProcMemRanking * procInfo = new CProcMemRanking();
//    procInfo->setNPID(0);
//    procInfo->setFRate(100 - fTotalRate);
//    procInfo->setStrProcName("其它进程");
//    m_procList.append(procInfo);

    // 更新排名图
    refreshRankingChart();


    // TODO: 清理历史数据，防止长时间运行后，曲线点数过多
}

void CMemAllocChart::refreshRankingChart() {
    // 清空已有的序列
    m_barSeries->clear();

    // 记录最大的数值，用于调整坐标轴的尺度
    float fMaxRate = 0;
    for (int i=0; i<m_procList.count(); i++) {
        CProcMemRanking * procInfo = m_procList.at(i);
        // 创建柱状数据集
        QBarSet * barRank = new QBarSet(procInfo->strProcName());
//        barRank->append(procInfo->fRate());
        float fRate = procInfo->fRate();
        *barRank << fRate;
//        barRank->setLabel(QString("%1.2f%%").arg(fRate));
        if (fRate > fMaxRate)
            fMaxRate = fRate;
        // 添加数据集到数据序列中
        m_barSeries->append(barRank);
    }

    // 首次需要创建坐标轴（如果初始化时建好坐标轴会有BUG，暂无其它解决方案）
    if (m_bInitialSeries) {
        // 创建横坐标
        m_axisX = new QValueAxis();
        // 设置横坐标的尺度
        m_axisX->setLabelFormat("%.2f%%");
        m_axisX->setRange(0, fMaxRate);
        m_chartMemAlloc->setAxisX(m_axisX, m_barSeries);
        m_axisX->applyNiceNumbers();

        // 创建纵坐标
        m_axisY = new QValueAxis();
        m_axisY->setReverse();
        m_chartMemAlloc->setAxisY(m_axisY, m_barSeries);

        // 添加序列到图中
        m_chartMemAlloc->addSeries(m_barSeries);

        m_bInitialSeries = false;
    }

}

