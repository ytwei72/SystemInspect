#include "cpagesysperformance.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPrinter>
#include <QProcess>
#include <qdebug.h>
#include <QPainter>
#include <QFile>
#include <QPdfWriter>
#include <QDateTime>

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

    connect(m_buttonTest, SIGNAL(clicked()), this, SLOT(testExportFiles()));

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

#if 1
void CPageSysPerformance::testExportFiles() {
    QFile pdfFile("./test_QPdfWriter.pdf");
        pdfFile.open(QIODevice::WriteOnly);
        QPdfWriter *pdfWriter = new QPdfWriter(&pdfFile);
        pdfWriter->setPageSize(QPagedPaintDevice::A4);
        pdfWriter->setResolution(300);//像素3508*2479
        pdfWriter->setTitle("Report");
        int pageMargin = 100;
        pdfWriter->setPageMargins(QMarginsF(pageMargin, pageMargin, pageMargin, pageMargin));
        QDateTime currentTime = QDateTime::currentDateTime();
        QString timeString = currentTime.toString("yyyy-MM-dd hh:mm:ss ddd");
        QPainter *pdfPainter = new QPainter(pdfWriter);
        QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WordWrap);
        int yCurrentP = 0;
        int xCurrentP = 0;
        int contentWidth = 2479 - pageMargin;
        QFont font;
        font.family();
    //    font.setFamily("simsun.ttc");
        font.setFamily("Times New Roman");
        int fontSize =9;
        int textHeight = 90;
        font.setPointSize(fontSize);
        pdfPainter->setFont(font);
        QPixmap titleImage("./logo2.png");
        //    pdfPainter->drawPixmap(xCurrentP, yCurrentP, titleImage.width(), titleImage.height(), titleImage);
        //    pdfPainter->scale(0.5, 0.5);
        pdfPainter->drawPixmap(xCurrentP, yCurrentP, titleImage.width()/2, titleImage.height()/2, titleImage);
        //    pdfPainter->scale(1.5, 1.5);
        option.setAlignment(Qt::AlignRight | Qt::AlignBottom);
        int pageIndex = 1;
        int totalPageIndex = 2;
        QString pageIndexString = QString::number(pageIndex) + "/" + QString::number(totalPageIndex);
        pdfPainter->drawText(QRect(xCurrentP, yCurrentP, contentWidth,titleImage.height()/2),
                             pageIndexString, option);
        yCurrentP += (titleImage.height()/2 + 4);
        QPen pen;
        int penHeigth = 4;
        pen.setWidth(penHeigth);
        pen.setColor(Qt::blue);
        pdfPainter->setPen(pen);
        pdfPainter->drawLine(xCurrentP, yCurrentP, contentWidth, yCurrentP);
        pen.setColor(Qt::black);
        pdfPainter->setPen(pen);
        yCurrentP += penHeigth;
        yCurrentP += 100;
        fontSize =22;
        font.setPointSize(fontSize);
        pdfPainter->setFont(font);
        option.setAlignment(Qt::AlignCenter);
        pdfPainter->drawText(QRect(0, yCurrentP, contentWidth, textHeight),
                             QString("性能测试报告"), option);
        yCurrentP += (textHeight + 100);
        fontSize = 16;
        font.setPointSize(fontSize);
        pdfPainter->setFont(font);
        option.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        pdfPainter->drawText(QRect(xCurrentP, yCurrentP, contentWidth, 80),
                             QString("CPU使用情况"));
        yCurrentP += (80 + 100);
        xCurrentP += 200;
        option.setWrapMode(QTextOption::WordWrap);
        pdfPainter->drawText(QRect(xCurrentP, yCurrentP, contentWidth - xCurrentP, 400),
                             QString("内存使用情况"),
                             option);
        yCurrentP +=(400 +100);
        QPixmap roxImage("./logo2.png");
        //    int multipe = rect.width() / roxImage.width();
        //    pdfPainter->scale(multipe, multipe);
        pdfPainter->drawPixmap(0, yCurrentP, roxImage.width()/2, roxImage.height()/2, roxImage);
        //    pdfPainter->scale(1, 1);
        QPixmap famImage("./logo2.png");
        //    multipe = rect.width()/ famImage.width();
        //    pdfPainter->scale(multipe, multipe);
        pdfPainter->drawPixmap(contentWidth/2, yCurrentP, famImage.width()/2, famImage.height()/2, famImage);
        //    pdfPainter->scale(1, 1);
        yCurrentP +=( std::max(roxImage.height(), famImage.height()) + 100);
        xCurrentP = 0;
        pdfPainter->drawText(QRect(xCurrentP, yCurrentP, contentWidth-xCurrentP, 80),
                             QString("硬盘使用情况"), option);
        QPixmap logoImage("./logo2.png");
        yCurrentP = 3508-pageMargin -( logoImage.height()/2) + 4;
        pen.setColor(Qt::blue);
        pdfPainter->setPen(pen);
        pdfPainter->drawLine(0, yCurrentP, contentWidth, yCurrentP);
        yCurrentP = 3508-pageMargin -( logoImage.height()/2);
        option.setAlignment(Qt::AlignLeft | Qt::AlignTop);
        fontSize = 9;
        font.setPointSize(fontSize);
        pen.setColor(Qt::black);
        pdfPainter->setPen(pen);
        pdfPainter->drawPixmap(contentWidth-xCurrentP-logoImage.width()/2, yCurrentP, logoImage.width()/2, logoImage.height()/2, logoImage);
        pdfPainter->setFont(font);
        pdfPainter->drawText(QRect(0, yCurrentP, 600, logoImage.height()), timeString, option);
        delete pdfPainter;
        delete pdfWriter;
        pdfFile.close();

//    QFile pdfFile("./test_QPdfWriter.pdf");
//    pdfFile.open(QIODevice::WriteOnly);
//    QPdfWriter * pdfWriter = new QPdfWriter(&pdfFile);
//    QPainter * pdfPainter = new QPainter(pdfWriter);

//    pdfWriter->setPageSize(QPagedPaintDevice::A4);

//    pdfPainter->drawText(QRect(100,100,2000,2000), "PDF文本示例--第一页");

//    pdfWriter->newPage();
//    pdfPainter->drawText(QRect(100,100,2000,2000), "PDF文本示例--第二页");
//    delete pdfPainter;
//    delete pdfWriter;

//    pdfFile.close();
}

#else
void CPageSysPerformance::testExportFiles() {
    QPrinter printer;

        printer.setOutputFormat(QPrinter::PdfFormat);//设置输出格式为pdf
        printer.setPageSize(QPrinter::A4);//设置纸张大小为A4
        printer.setOutputFileName("./test.pdf");//设置输出路径

        QPainter painter(this);
        painter.begin(&printer);

        //正常使用painter 绘制文字、pixmap等在printer上
        //要先画图片，然后画图片上面的内容，否则图片会覆盖其他内容
        QPixmap pixmap("./logo2.png");
        painter.drawPixmap(rect(), pixmap);

        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(rect(), Qt::AlignCenter, "Qt生成PDF......");


        QPen pen;
        pen.setWidth(40);
        painter.drawLine(10,20,200,400);

        QBrush brush;
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
        painter.setPen(pen);
        painter.drawRect(200,400,500,600);

        //至此，文件被保存
        painter.end();

}
#endif

void CPageSysPerformance::curlURL()
{
    CSysUtils::resetTimerClock();
    CWebUtils webUtil;
    bool bRv = webUtil.curlUrl(m_inputURL->text());

    QString strOldRecord = m_textResult->placeholderText().left(512);
    QString strTitle;
    QString strOutput;
    if (!bRv)
    {
        strOutput = "\n=============== 网络访问失败 ===============\n";
    } else {
        qint64 elpasedTime = CSysUtils::getElapsedMilliSeconds();

        strTitle = "\n=============== 主站响应时间 ===============\n";
        strOutput = QString("访问网络地址: %1 ... ...\n共耗时：%2毫秒。\n").arg(m_inputURL->text()).arg(elpasedTime);
    }

    m_textResult->setPlaceholderText(strTitle + strOutput + strOldRecord);
}

void CPageSysPerformance::pingURL()
{
    CSysUtils::resetTimerClock();
    CWebUtils webUtil;
    bool bRv = webUtil.pingUrl(m_inputURL->text());
    qint64 elpasedTime = CSysUtils::getElapsedMilliSeconds();

    QString strOldRecord = m_textResult->placeholderText().left(512);

    QString strTitle;
    QString strOutput;
    if (!bRv)
    {
        strOutput = "\n=============== PING指定网址失败 ===============\n";
    } else {
        strTitle = "\n=============== 主站响应时间 ===============\n";
        strOutput = QString("PING: %1 ... ...\n共耗时：%2毫秒。\n").arg(m_inputURL->text()).arg(elpasedTime);
    }


    m_textResult->setPlaceholderText(strTitle + strOutput + strOldRecord);
}

void CPageSysPerformance::networkPerformance()
{
    QString strUrl = m_inputURL->text();
    m_procNetperf = new QProcess();
    QString strClientCmd = "iperf3 -c " + strUrl;

    connect(m_procNetperf, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(procFinished(int, QProcess::ExitStatus)));
    m_procNetperf->start(strClientCmd);
    bool bStarted = m_procNetperf->waitForStarted();

    m_textResult->setPlaceholderText("正在进行检测，请稍等 ... ...");
}


void CPageSysPerformance::procFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    QString errorInfo;
    if (exitCode == 0) {
        QString strOutput = m_procNetperf->readAllStandardOutput();
        qDebug()<<"final result: " + strOutput;
        m_textResult->setPlaceholderText(strOutput);

        m_procNetperf->waitForFinished();
        m_procNetperf->deleteLater();
    } else {
        errorInfo = m_procNetperf->readAllStandardError();
        m_textResult->setPlaceholderText(errorInfo);
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
    m_buttonPingURL->setText(tr("PING"));
    m_buttonPingURL->setFont(fontButtonUrl);

    m_buttonPerformance = new QPushButton();
    m_buttonPerformance->setText(tr("检测网卡性能"));
    m_buttonPerformance->setFont(fontButtonUrl);

    // 水平布局-1
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    QLabel * labelUrl = new QLabel();
    labelUrl->setText("请输入网址或IP：");
    widget_1_H_layout->addWidget(labelUrl);//, 0, Qt::AlignLeft);
    widget_1_H_layout->addWidget(m_inputURL);//, 70, Qt::AlignRight);
//    widget_1_H_layout->addStretch();
//    widget_1_H_layout->addWidget(m_buttonTestURL, 0, Qt::AlignCenter);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);
    // 水平布局-2
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(m_buttonAccessURL);//, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonPingURL);//, 0, Qt::AlignLeft);
    widget_2_H_layout->addWidget(m_buttonPerformance);//, 0, Qt::AlignLeft);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);
    // 垂直布局
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addLayout(widget_2_H_layout);
    widget_1_V_layout->addWidget(m_textResult);//, 0, Qt::AlignTop);
//    widget_1_V_layout->setContentsMargins(20, 5, 20, 5);
//    widget_1_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    m_widgetBandWidth->setLayout(main_layout);
}

void CPageSysPerformance::initReportWidget()
{
    m_widgetAnalyzeReport = new SystemPerfReport();
//    m_widgetAnalyzeReport = new QWidget();
//    m_buttonTest = new QPushButton();

//    m_buttonTest->setText("生成PDF文件");

//    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
//    widget_1_V_layout->addWidget(m_buttonTest, 0, Qt::AlignCenter);
//    QHBoxLayout *main_layout = new QHBoxLayout();
//    main_layout->addLayout(widget_1_V_layout);

//    m_widgetAnalyzeReport->setLayout(main_layout);
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
