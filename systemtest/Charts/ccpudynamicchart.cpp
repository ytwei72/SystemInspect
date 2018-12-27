#include "ccpudynamicchart.h"


CCpuDynamicChart::CCpuDynamicChart(QWidget *parent) : QWidget(parent)
{

    m_nPointIndex = 0;
    m_nWindowWidth = 30;

    // 初始化图表部件
    initCpuChartWidget();

    // 创建一个横向布局
    m_mainLayout = new QHBoxLayout();
    // 在横向布局中加入图表部件
    m_mainLayout->addWidget(m_chartView);

    // 设置页面的顶级布局
    setLayout(m_mainLayout);

    // 设置页面的背景自动填充模式
    this->setAutoFillBackground(true);
}

void CCpuDynamicChart::initCpuChartWidget(){
    // 初始化曲线序列
    initSplineSeries();

    // 创建图表对象
    m_chart = new QChart();

    // 设置图表属性，并添加曲线序列
//    m_chart->legend()->hide();
    m_chart->addSeries(m_seriesCpuRate);
    m_chart->addSeries(m_seriesSysCpuRate);
    m_chart->addSeries(m_seriesUserCpuRate);
    m_chart->setTitle("CPU性能监测(%)");
    m_chart->createDefaultAxes();
    m_chart->axisY()->setRange(0, 100);
    m_chart->axisX()->setRange(0, m_nWindowWidth);

    // 新建一个容纳图表的视图
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void CCpuDynamicChart::initSplineSeries() {
    // 新建一个CPU使用率的曲线序列，并设置序列名称
    m_seriesCpuRate = new QSplineSeries();
    m_seriesCpuRate->setName("CPU使用率");

    // 新建一个系统CPU使用率的曲线序列，并设置序列名称
    m_seriesSysCpuRate = new QSplineSeries();
    m_seriesSysCpuRate->setName("系统CPU占用率");

    // 新建一个用户CPU使用率的曲线序列，并设置序列名称
    m_seriesUserCpuRate = new QSplineSeries();
    m_seriesUserCpuRate->setName("用户CPU占用率");

//    m_splineSeries->append(0, 6);
//    m_splineSeries->append(2, 4);
//    m_splineSeries->append(3, 8);
//    m_splineSeries->append(7, 4);
//    m_splineSeries->append(10, 5);
//    *m_splineSeries << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

}

void CCpuDynamicChart::refreshCpuInfo(QString strCpuInfo) {
    // 定义正则表达式
    QRegExp regExp("CPU占用：\t\t\t\t (.*)%\n\n可运行队列的线程数：\t\t\t(.*)\n\n用户占用率：\t\t\t (.*)%\n\n系统占用率：\t\t\t (.*)%\n\nIO等待占用率");

    // 用正则表达式提取数据
    int pos = strCpuInfo.indexOf(regExp);
    if (pos < 0)
        return;

    // 保存提取出来的数据
    QString strTemp = regExp.cap(0);
    QString strCpuRate = regExp.cap(1);
    QString strUserCpuRate = regExp.cap(3);
    QString strSysCpuRate = regExp.cap(4);

    // 从字符串转换成浮点数
    double fCpuRate = strCpuRate.toDouble();
    double fUserCpuRate = strUserCpuRate.toDouble();
    double fSysCpuRate = strSysCpuRate.toDouble();

    // 添加三条曲线的点
    m_seriesCpuRate->append(m_nPointIndex, fCpuRate);
    m_seriesUserCpuRate->append(m_nPointIndex, fUserCpuRate);
    m_seriesSysCpuRate->append(m_nPointIndex, fSysCpuRate);
    m_nPointIndex++;

    // 调整横坐标（曲线向左移动）
    if (m_nPointIndex > m_nWindowWidth)
        m_chart->axisX()->setRange(m_nPointIndex-m_nWindowWidth, m_nPointIndex);

//    m_chart->
//    strCpuInfo
}
