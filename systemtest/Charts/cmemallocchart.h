#ifndef CMEMALLOCCHART_H
#define CMEMALLOCCHART_H

#include <QHBoxLayout>
#include <QProcess>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "cprocmemranking.h"

QT_CHARTS_USE_NAMESPACE

class CMemAllocChart : public QWidget
{
    Q_OBJECT
public:
    explicit CMemAllocChart(QWidget *parent = nullptr);

private:
    void initMemChartWidget();
    void initHorizonBarSeries();

    void refreshRankingChart();

private:
    // 内存分配图
    QChart *                m_chartMemAlloc;
    // 加载内存分配图的视图
    QChartView *            m_chartViewMemAlloc;
    // 本页面的主布局
    QHBoxLayout *           m_mainLayout;

    // 横向条数据序列
    QHorizontalBarSeries *  m_barSeries;
    bool                    m_bInitialSeries;
    QValueAxis *            m_axisY;
//    QBarCategoryAxis *      m_axisY;
    QValueAxis *            m_axisX;

    // 实名的排序数量
    int                     m_nMaxRankings;

    // 更新数据的定时器
    QTimer *                m_timerRefresh;
    // 运行脚本的进程
    QProcess *              m_procMemAlloc;

    QList<CProcMemRanking *> m_procList;


signals:

public slots:
    void refreshMemAllocInfo();

};

#endif // CMEMALLOCCHART_H
