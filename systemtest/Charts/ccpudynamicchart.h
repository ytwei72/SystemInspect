#ifndef CCPUDYNAMICCHART_H
#define CCPUDYNAMICCHART_H

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>
#include <QHBoxLayout>
#include <QWidget>

QT_CHARTS_USE_NAMESPACE

class CCpuDynamicChart : public QWidget
{
    Q_OBJECT
public:
    explicit CCpuDynamicChart(QWidget *parent = nullptr);

private:
    void initCpuChartWidget();
    void initSplineSeries();

private:
    QSplineSeries *         m_seriesCpuRate;
    QSplineSeries *         m_seriesSysCpuRate;
    QSplineSeries *         m_seriesUserCpuRate;
    // CPU使用率图表
    QChart *                m_chart;
    // 加载CPU图表的视图
    QChartView *            m_chartView;
    // 本页面的主布局
    QHBoxLayout *           m_mainLayout;

    // 记录当前的点位置
    int                     m_nPointIndex;
    // 图的宽度（可展现的点数）
    int                     m_nWindowWidth;

signals:

public slots:
    void refreshCpuInfo(QString strCpuInfo);
};

#endif // CCPUDYNAMICCHART_H
