

#include "modeltablechartwidget.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTableView>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QVBarModelMapper>
#include <QtWidgets/QHeaderView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <QTimer>

#include "common.h"

QT_CHARTS_USE_NAMESPACE

ModelTableChartWidget::ModelTableChartWidget(QWidget *parent)
    : QWidget(parent)
{
    //! [1]: 创建一个自定义模式表格对象，用以存储数据
    m_model = new RankingTableModel;
    //! [1]

    //! [2]: 创建一个表格视图容纳模式表格
    QTableView *tableView = new QTableView;
    tableView->setModel(m_model);
    tableView->setMinimumWidth(300);
//    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    tableView->horizontalHeader()->setMaximumSectionSize(240);
    tableView->setColumnWidth(0, 60);
    tableView->setColumnWidth(1, 200);
    tableView->setColumnWidth(2, 60);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_model->setParent(tableView);
    //! [2]

    //! [3]: 创建一个图对象
    QChart *chart = new QChart;
//    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    //! [4]: 创建条形数据序列
    m_barSeries = new QHorizontalBarSeries();

    // 数据序列映射到表格的指定行列区域
    int first = 0;
    int count = 11;
    QVBarModelMapper *mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(2);
    mapper->setLastBarSetColumn(2);
    mapper->setFirstRow(first);
    mapper->setRowCount(count);
    mapper->setSeries(m_barSeries);
    mapper->setModel(m_model);
    chart->addSeries(m_barSeries);
    //! [4]

    //! [5]: 从BarChart中取出序列数据的颜色，来设置表格中对应单元的颜色
    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
    QList<QBarSet *> barsets = m_barSeries->barSets();
    for (int i = 0; i < barsets.count(); i++) {
        seriesColorHex = "#" + QString::number(barsets.at(i)->brush().color().rgb(), 16).right(6).toUpper();
        m_model->addMapping(seriesColorHex, QRect(i+2, first, 1, barsets.at(i)->count()));
    }
    //! [5]

    //! [6]: 条行图的目录只有一项：内存占用率
    QStringList categories;
    for (int i=0; i<count; i++)
        categories << QString("%1").arg(i+1);
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
//    chart->createDefaultAxes();
    axisY->setReverse(true);
    chart->setAxisY(axisY, m_barSeries);
    m_axisX = new QValueAxis();
    chart->setAxisX(m_axisX, m_barSeries);
    m_axisX->applyNiceNumbers();
    //! [6]

    //! [7]: 创建视图对象容纳条形图
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //! [7]

    //! [8]: 创建主布局，横向排列表格和图形
    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 0, 0);
    mainLayout->addWidget(chartView, 0, 1);
    mainLayout->setColumnStretch(0, 0);
    mainLayout->setColumnStretch(1, 0);
    setLayout(mainLayout);
    //! [8]

    // 处理执行脚本线程的信号
    connect(&m_scriptThread, &ExecScriptsSlaveThread::scriptResult, this, &ModelTableChartWidget::processScriptResult);

    // 启动线程
    m_scriptThread.startSlave();

    // 创建定时器，用于定时获取内存信息
    m_timerPolling = new QTimer(this);
    connect(m_timerPolling, SIGNAL(timeout()), this, SLOT(fetchMemInfo()));
    m_timerPolling->start(3000);

}

void ModelTableChartWidget::fetchMemInfo() {
    QString script = g_sWorkingPath + "/NewScripts/memory/mem_ranking.sh";

    m_scriptThread.execScipts(script);
}

void ModelTableChartWidget::processScriptResult(const QString & result) {
    // 对脚本执行结果用换行符分割
    QStringList resultList = result.split("\n");

    int modelRowCount = m_model->rowCount();

    float maxRate = 0;
    QString record;
    QStringList rowData;
    for (int i=0; i < modelRowCount; i++) {
        rowData.clear();
        if (i < resultList.count()) {
            // 按顺序取记录
            record = resultList[i];

            // 使用正则表达式提取数据
            QRegExp regExp("PID:(.*)RATE:(.*)NAME:(.*)END");
            int pos = record.indexOf(regExp);
            if (pos < 0)
                continue;

            if (maxRate < regExp.cap(2).toFloat())
                maxRate = regExp.cap(2).toFloat();

            // 设置表格的行数据
            rowData<<regExp.cap(1)<<regExp.cap(3)<<regExp.cap(2);

        } else {
            // 取到的数据不够model的行数时，采用空行
            rowData<<""<<""<<"";
        }
        m_model->setRowData(i, rowData);

    }

    // 调整横坐标的尺度，使得图形更协调
    m_axisX->setRange(0, maxRate * 8 / 7);

    // 更新图表
    m_model->refresh();

}
