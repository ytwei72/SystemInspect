
#ifndef MODELTABLECHARTWIDGET_H
#define MODELTABLECHARTWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QValueAxis>
#include <Utils/chartcallout.h>
#include "rankingtablemodel.h"
#include "execscriptsslavethread.h"

QT_CHARTS_USE_NAMESPACE

class ModelTableChartWidget : public QWidget
{
    Q_OBJECT

public:
    ModelTableChartWidget(QWidget *parent = 0);

private:
    void initModelTableChart();

    QString generateToolTipText(QPointF point, int index);

private:
    RankingTableModel *     m_model;
    QTimer *                m_timerPolling;
    ExecScriptsSlaveThread  m_scriptThread;
    QChart *                m_chart;
    // 横向条数据序列
    QHorizontalBarSeries *  m_barSeries;
    QValueAxis *            m_axisX;
    ChartCallout *          m_tooltip;


public slots:
    void fetchMemInfo();
    void processScriptResult(const QString & result);
    void tooltip(int index, QBarSet *barset);
};

#endif // MODELTABLECHARTWIDGET_H
