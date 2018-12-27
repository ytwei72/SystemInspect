#include "cmemorydynamicchart.h"

#include <QTimer>

CMemoryDynamicChart::CMemoryDynamicChart(QWidget *parent) : QWidget(parent)
{
    // 设置内存图表的当前起始位置和窗宽
    m_nMemChartPointIndex = 0;
    m_nMemChartWindowWidth = 20;

    // 初始化内存占用率图表部件
    initMemChartWidget();

    // 创建一个横向布局
    m_mainLayout = new QHBoxLayout();
    // 在横向布局中加入图表部件
    m_mainLayout->addWidget(m_chartViewMemRate);

    // 设置页面的顶级布局
    setLayout(m_mainLayout);

    // 设置页面的背景自动填充模式
//    this->setAutoFillBackground(true);

    // 创建获取内存信息的进程对象
    m_procMemInfo = new QProcess();

//    return;
    // 创建定时器，用于定时获取内存信息
    m_timerRefresh = new QTimer(this);
    connect(m_timerRefresh, SIGNAL(timeout()), this, SLOT(refreshMemInfo()));
    m_timerRefresh->start(1000);
}

CMemoryDynamicChart::~CMemoryDynamicChart(){
    m_procMemInfo->close();
    m_procMemInfo->deleteLater();
}

void CMemoryDynamicChart::initMemRateSplineSeries() {
    m_seriesMemRate = new QLineSeries();
//    m_seriesMemRate->setName("内存使用率");
    m_seriesMemRateBase = new QLineSeries();
//    m_seriesMemRateBase->setName("内存使用率基线");
//    *m_seriesMemRate << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
//             << QPointF(16, 7) << QPointF(18, 5);
//    *m_seriesMemRateBase << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
//             << QPointF(16, 4) << QPointF(18, 3);


    m_areaSeriesMemRate = new QAreaSeries(m_seriesMemRate, m_seriesMemRateBase);
    m_areaSeriesMemRate->setName("内存使用率");

//    QPen pen(0x059605);
//    pen.setWidth(3);
//    m_areaSeriesMemRate->setPen(pen);

//    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
//    gradient.setColorAt(0.0, 0x3cc63c);
//    gradient.setColorAt(1.0, 0x26f626);
//    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
//    m_areaSeriesMemRate->setBrush(gradient);
}

void CMemoryDynamicChart::initMemChartWidget() {
    // 初始化曲线序列
    initMemRateSplineSeries();

    // 创建图表对象
    m_chartMemRate = new QChart();

    // 设置图表属性，并添加曲线序列
    m_chartMemRate->legend()->hide();
    m_chartMemRate->addSeries(m_areaSeriesMemRate);
    m_chartMemRate->setTitle("内存占用监测(%)");
    m_chartMemRate->createDefaultAxes();
    m_chartMemRate->axisY()->setRange(0, 100);
    m_chartMemRate->axisX()->setRange(0, m_nMemChartWindowWidth);

    // 新建一个容纳图表的视图
    m_chartViewMemRate = new QChartView(m_chartMemRate);
    m_chartViewMemRate->setRenderHint(QPainter::Antialiasing);


}

void CMemoryDynamicChart::refreshMemInfo() {
    // 设置运行脚本
    QString strCmd = "bash";
    QStringList strParams;
    strParams<<g_sWorkingPath + "/NewScripts/memory/mem_info.sh";

    // 启动进程，并等待结束
    m_procMemInfo->start(strCmd, strParams);
    bool bFinished = m_procMemInfo->waitForFinished();
    // 超时情况下，直接退出处理
    if (!bFinished)
        return;

    // 读取进程返回数据
    QString strOutput = m_procMemInfo->readAllStandardOutput();

    // 使用正则表达式提取数据
    // 	strOutput	"内存总量：\t\t\t4037772KB\n空闲内存：\t\t\t211236KB\n已用内存：\t\t\t3826536KB\n内存占用：\t\t\t94.77%\n共享内存：\t\t\t30584KB\n文件缓冲区：\t\t270952KB"... (116)	QString
    QRegExp regExp("内存总量：\t\t\t(.*)KB\n空闲内存：\t\t\t(.*)KB\n已用内存：\t\t\t(.*)KB\n内存占用：\t\t\t(.*)%\n共享内存：\t\t\t(.*)KB\n文件缓冲区：\t\t(.*)KB\nEND");
    int pos = strOutput.indexOf(regExp);
    if (pos < 0)
        return;

    // 获取所需内存信息数据，并转换成整数或浮点数
    QString strTotalMem = regExp.cap(1);
    QString strUsedMemRate = regExp.cap(4);
    QString strShareMem = regExp.cap(5);
    QString strBuffMem = regExp.cap(6);
    long nTotalMem = strTotalMem.toLong();
    double fUsedMemRate = strUsedMemRate.toDouble();
    long nShareMem = strShareMem.toLong();
    long nBuffMem = strBuffMem.toLong();

    // 添加新的内存使用率数据到图表中
    addNewMemoryRatePoint(fUsedMemRate);
}

void CMemoryDynamicChart::addNewMemoryRatePoint(double fRate) {
    // 添加新的内存使用率数据到图表中
    m_seriesMemRate->append(m_nMemChartPointIndex, fRate);
    m_seriesMemRateBase->append(m_nMemChartPointIndex, 0);
    m_nMemChartPointIndex++;

    // 根据数据大小调整Y轴的尺度
    if (fRate > 90)
        m_chartMemRate->axisY()->setRange(85, 100);
    else if (fRate > 80)
        m_chartMemRate->axisY()->setRange(75, 100);
    else if (fRate > 50)
        m_chartMemRate->axisY()->setRange(40, 100);
    else
        m_chartMemRate->axisY()->setRange(0, 100);

    // 调整横坐标（曲线向左移动）
    if (m_nMemChartPointIndex > m_nMemChartWindowWidth)
        m_chartMemRate->axisX()->setRange(m_nMemChartPointIndex-m_nMemChartWindowWidth, m_nMemChartPointIndex);

}
