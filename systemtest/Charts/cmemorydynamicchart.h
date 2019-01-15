#ifndef CMEMORYDYNAMICCHART_H
#define CMEMORYDYNAMICCHART_H

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>
#include <QAreaSeries>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QHBoxLayout>
#include <QProcess>
#include <QValueAxis>
#include <QWidget>
#include "common.h"
#include "czoomchartview.h"

QT_CHARTS_USE_NAMESPACE

class CMemoryDynamicChart : public QWidget
{
    Q_OBJECT
public:
    explicit CMemoryDynamicChart(QWidget *parent = nullptr);
    ~CMemoryDynamicChart();

private:
    void initMemChartWidget();
    void initMemRateSplineSeries();

    void addNewMemoryRatePoint(double fRate);

private:
    // 内存占用率(%)
    QLineSeries *           m_seriesMemRate;
    QLineSeries *           m_seriesMemRateBase;
    QAreaSeries *           m_areaSeriesMemRate;
    // 共享内存(单位：MB)
    QSplineSeries *         m_seriesShareMem;
    // 文件缓冲区(单位：MB)
    QSplineSeries *         m_seriesBuffMem;

    // 内存占用率图表
    QChart *                m_chartMemRate;
    // 内存占用率图表的视图
    QChartView *            m_chartViewMemRate;
    // 记录内存占用率图表当前的点位置
    int                     m_nMemChartPointIndex;
    // 内存占用率图表的宽度（可展现的点数）
    int                     m_nMemChartWindowWidth;


    QChart *                m_chartShareMem;
    QChartView *            m_chartViewShareMem;
    QChart *                m_chartBuffMem;
    QValueAxis *            m_axisY;
    CZoomChartView *        m_chartViewBuffMem;

    // 本布局的主布局
    QHBoxLayout *           m_mainLayout;

    QTimer *                m_timerRefresh;
    QProcess *              m_procMemInfo;

    QDateTime               m_startTime;
    qint64                  m_startTimeMS;
    QDateTimeAxis           m_dateAxisX;


signals:

public slots:
    void refreshMemInfo();
};

#endif // CMEMORYDYNAMICCHART_H
