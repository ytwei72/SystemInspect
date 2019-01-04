#ifndef PAGE_SYS_PERFORMANCE_H
#define PAGE_SYS_PERFORMANCE_H

#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QProcess>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextBrowser>

#include <Report/systemperfreport.h>

class CPageSysPerformance : public QWidget
{
    Q_OBJECT
public:
    explicit CPageSysPerformance(QWidget *parent = 0);
    ~CPageSysPerformance();

public:
    void initItemList();
    void initBandwidthWidget();
    void initReportWidget();

private:
//    QSplitter *
    // 左侧功能列表
    QListWidget *       m_itemList;
    QStackedWidget*     m_stackWidget;

    // 测试网络性能的widget
    QWidget *           m_widgetBandWidth;
    // URL输入框
    QLineEdit *         m_inputURL;
    // 测试URL访问的按钮
    QPushButton *       m_buttonAccessURL;
    // 测试ping通网址的按钮
    QPushButton *       m_buttonPingURL;
    // 测试网卡性能的按钮
    QPushButton *       m_buttonPerformance;
    // 信息框（测试结果）
    QTextBrowser *      m_textResult;
    // 测试网络性能的进程
    QProcess *          m_procNetperf;

    // 展示性能分析图表的widget
//    QWidget *           m_widgetAnalyzeReport;
    SystemPerfReport *    m_widgetAnalyzeReport;
    // 临时测试按钮
    QPushButton *       m_buttonTest;

protected slots:
    void curlURL();
    void pingURL();
    void networkPerformance();
    void procFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void testExportFiles();

public:
//    CPageSysPerformance();
    void initLeft();
    void initRight();

private:
    QWidget *       left_widget;
    QLabel *        label;
    QLabel *        time_label;
    QPushButton *   sys_test_button;
    QSplitter *     main_splitter;
    QSplitter *     right_splitter;
};

#endif // PAGE_SYS_PERFORMANCE_H
