#include "cpagesysperformance.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QProcess>
#include <qdebug.h>

#include <Utils/csysutils.h>
#include <Utils/cwebutils.h>

CPageSysPerformance::CPageSysPerformance(QWidget *parent) : QWidget(parent)
{
    // 初始化左侧功能列表
    initItemList();

    // 初始化带宽测试页面
    initBandwidthWidget();

    // 初始化报告页面
    initReportWidget();

    // 将功能页面存放到堆栈里
    m_stackWidget = new QStackedWidget();
    m_stackWidget->addWidget(m_widgetBandWidth);
    m_stackWidget->addWidget(m_widgetAnalyzeReport);

    // 设置本页的主界面排版
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(m_itemList);
    main_layout->addWidget(m_stackWidget);
    main_layout->setStretchFactor(m_itemList, 1);
    main_layout->setStretchFactor(m_stackWidget, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    connect(m_itemList, SIGNAL(currentRowChanged(int)), m_stackWidget, SLOT(setCurrentIndex(int)));
    connect(m_buttonAccessURL, SIGNAL(clicked()), this, SLOT(curlURL()));
    connect(m_buttonPingURL, SIGNAL(clicked()), this, SLOT(pingURL()));
    connect(m_buttonPerformance, SIGNAL(clicked()), this, SLOT(networkPerformance()));

    this->setAutoFillBackground(true);


//    initLeft();

//    initRight();

//    main_splitter = new QSplitter();
//    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//可自行增大和收缩
//    main_splitter->setOrientation(Qt::Horizontal);//Qt::Vertical and Qt::Horizontal   qspliter的取向
//    main_splitter->setHandleWidth(4); //设置分界线的宽度
//    main_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");

//    main_splitter->addWidget(left_widget);
//    main_splitter->addWidget(right_splitter);

//    QHBoxLayout *main_layout = new QHBoxLayout();
//    main_layout->addWidget(main_splitter);
//    main_layout->setSpacing(0);//空隙
//    main_layout->setContentsMargins(0, 0, 0, 0);/*这是设置一个元素所有外边距的宽度，
//                                                                                    或者设置各边上外边距的宽度 */

//    this->setLayout(main_layout);//将main_layout设置为当前widget的布局

}

CPageSysPerformance::~CPageSysPerformance()
{

}

void CPageSysPerformance::curlURL()
{
    CSysUtils::resetTimerClock();
    CWebUtils webUtil;
    webUtil.curlUrl(m_inputURL->text());
    qint64 elpasedTime = CSysUtils::getElapsedMilliSeconds();

    QString strTitle = "\n=============== 主站响应时间 ===============\n";
    QString strOutput = QString("访问网络地址: %1 ... ...\n共耗时：%2毫秒。\n").arg(m_inputURL->text()).arg(elpasedTime);

    QString strOldRecord = m_textResult->placeholderText().left(512);

    m_textResult->setPlaceholderText(strTitle + strOutput + strOldRecord);
}

void CPageSysPerformance::pingURL()
{
    CSysUtils::resetTimerClock();
    CWebUtils webUtil;
    webUtil.pingUrl(m_inputURL->text());
    qint64 elpasedTime = CSysUtils::getElapsedMilliSeconds();

    QString strTitle = "\n=============== 主站响应时间 ===============\n";
    QString strOutput = QString("PING通: %1 ... ...\n共耗时：%2毫秒。\n").arg(m_inputURL->text()).arg(elpasedTime);

    QString strOldRecord = m_textResult->placeholderText().left(512);

    m_textResult->setPlaceholderText(strTitle + strOutput + strOldRecord);
}

void CPageSysPerformance::networkPerformance()
{
    QString strUrl = m_inputURL->text();
    m_procNetperf = new QProcess();
    QString strClientCmd = "iperf3 -c " + strUrl;

    m_procNetperf->start(strClientCmd);

    connect(m_procNetperf, SIGNAL(readyReadStandardOutput()), this, SLOT(outputNetperfInfo()));
//    connect(m_procNetperf, SIGNAL(readyRead()), this, SLOT(outputLineInfo()));
    bool bStarted = m_procNetperf->waitForStarted();

    m_textResult->setPlaceholderText("正在进行检测，请稍等 ... ...");
//    while (m_procNetperf->readyReadStandardOutput())

//    QString strOutput = m_procNetperf->readAllStandardOutput();

}

void CPageSysPerformance::outputNetperfInfo(){
    QString strOutput = m_procNetperf->readAllStandardOutput();
    qDebug()<<"final result: " + strOutput;
    m_textResult->setPlaceholderText(strOutput);

    m_procNetperf->waitForFinished();
    m_procNetperf->deleteLater();
}

void CPageSysPerformance::outputLineInfo(){
    QString strOldOutput = m_textResult->placeholderText();

    while (m_procNetperf->canReadLine()) {
        QString strLine = m_procNetperf->readLine();
        qDebug()<<"Read Line: " + strLine;
        strOldOutput += strLine;
        m_textResult->setPlaceholderText(strOldOutput);
    }
}

void CPageSysPerformance::initItemList(){
    m_itemList = new QListWidget();

    // listwidget按钮设置
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("性能分析"));
    Item_0->setIcon(QIcon(":/page_two/cpu1"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("报告"));
    Item_1->setIcon(QIcon(":/page_two/cpu2"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    m_itemList->insertItem(0,Item_0);
    m_itemList->insertItem(1,Item_1);
    // 标签字体大小
    QFont font;
    font.setPointSize(14);
    font.setUnderline(1);
    m_itemList->setFont(font);

}

void CPageSysPerformance::initBandwidthWidget()
{
    m_widgetBandWidth = new QWidget();
    m_inputURL = new QLineEdit();
    m_inputURL->setText("127.0.0.1");
    m_inputURL->setFixedSize(500, 24);
    m_textResult = new QTextBrowser();
    m_textResult->setFixedSize(680,320);

    // 设置
    QFont fontButtonUrl;
    fontButtonUrl.setPointSize(13);
    m_buttonAccessURL = new QPushButton();
    m_buttonAccessURL->setText(tr("访问网址"));
    m_buttonAccessURL->setFont(fontButtonUrl);
    m_buttonPingURL = new QPushButton();
    m_buttonPingURL->setText(tr("PING通"));
    m_buttonPingURL->setFont(fontButtonUrl);

    m_buttonPerformance = new QPushButton();
    m_buttonPerformance->setText(tr("检测网卡性能"));
    m_buttonPerformance->setFont(fontButtonUrl);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labelUrl = new QLabel();
    labelUrl->setText("请输入URL：");
    widget_1_H_layout->addWidget(labelUrl, 0, Qt::AlignCenter);
    widget_1_H_layout->addWidget(m_inputURL, 70, Qt::AlignCenter);
    widget_1_H_layout->addStretch();
//    widget_1_H_layout->addWidget(m_buttonTestURL, 0, Qt::AlignCenter);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);
    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(m_buttonAccessURL, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonPingURL, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonPerformance, 0, Qt::AlignLeft);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);
    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addWidget(m_textResult, 0, Qt::AlignCenter);
    widget_1_V_layout->setContentsMargins(0, 0, 5, 5);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    m_widgetBandWidth->setLayout(main_layout);
}

void CPageSysPerformance::initReportWidget()
{
    m_widgetAnalyzeReport = new QWidget();
    m_buttonTest = new QPushButton();

    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addWidget(m_buttonTest, 0, Qt::AlignCenter);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);

    m_widgetAnalyzeReport->setLayout(main_layout);
}


void CPageSysPerformance::initLeft() {
    left_widget = new QWidget();
    label = new QLabel();//图片
    time_label = new QLabel();
    sys_test_button = new QPushButton();//检测按钮
    left_widget->resize(650, 500);

    QPixmap label_pixmap(":/sys_test_widget/check");
    label->setPixmap(label_pixmap);
    label->setFixedSize(label_pixmap.size());

    QFont suggest_font = time_label->font();//返回默认应用程序字体
    suggest_font.setPointSize(15);//字体大小
    suggest_font.setBold(true);//加粗
    time_label->setFont(suggest_font);
    time_label->setObjectName("grayLabel");
    time_label->setText(tr("welcome make test"));

    QFont system_safe_font = this->font();
    system_safe_font.setPointSize(14);
    system_safe_font.setBold(true);

    QPixmap pixmap(":/sys_test_widget/power");
    sys_test_button->setIcon(pixmap);
    sys_test_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    sys_test_button->setIconSize(pixmap.size());
    sys_test_button->setFixedSize(180, 70);
    sys_test_button->setObjectName("greenButton");

    QFont power_font = sys_test_button->font();
    power_font.setPointSize(16);
    sys_test_button->setFont(power_font);
    sys_test_button->setText(tr("一键测评"));

    QVBoxLayout *v_layout = new QVBoxLayout();//纵向布局
    v_layout->addWidget(time_label);
//    v_layout->addWidget(system_safe_label);
    v_layout->addStretch();//平均分配的意思
    v_layout->setSpacing(15);//空隙
    v_layout->setContentsMargins(30, 30, 0, 0);

    QHBoxLayout *h_layout = new QHBoxLayout();//横向布局
    h_layout->addWidget(label, 0, Qt::AlignTop);//这个枚举类型是用来描述对齐方式的
    h_layout->addLayout(v_layout);
    h_layout->addStretch();
    h_layout->setSpacing(20);
    h_layout->setContentsMargins(30, 20, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(h_layout);
    main_layout->addWidget(sys_test_button, 0, Qt::AlignCenter);

    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    left_widget->setLayout(main_layout);

    this->setAutoFillBackground(true);
    left_widget->setStyleSheet("QPushButton{color:#030303;background:#63B8FF; border-style: double;\
                               border-width: 4px;\
                               border-color: #ffcc00;}");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:1px solid grey; border-radius: 8px;}");

 /*
    left_widget->setStyleSheet("QPushButton{image:url(:/skin/0.png); subcontrol-position: right center;\
                               color:black; background-color: red;\
                               border-style: double;\
                               border-width: 2px;\
                               border-radius: 10px;\
                               border-color: #ffccff;\
                               font: bold 18px;\
                               text-align: top;\
                               min-width: 8em;}");
*/

}

void CPageSysPerformance::initRight()
{
    right_splitter = new QSplitter();

    /* 右分屏的属性设置 */
    right_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    right_splitter->setOrientation(Qt::Vertical);
    right_splitter->setHandleWidth(1);
}
