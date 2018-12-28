/*
 内存检测项
 */
#ifndef MAIN_PAGE_THREE_H
#define MAIN_PAGE_THREE_H

#include <QWidget>
#include <QToolButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QTextBrowser>
#include "qprocess.h"
#include "common.h"
#include "input_pwd.h"
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>

#include "Charts/cmemorydynamicchart.h"
#include <Charts/cmemallocchart.h>

class Main_Page_three : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Page_three(QWidget *parent = 0);

protected:
/*列表窗口*/
    QListWidget *list;
    QStackedWidget *stack;
/*布局窗口*/
    QWidget *work_window;
    QPushButton *re_test;
    QLabel *test_options;
    QLabel *line_label;
    QTextBrowser *show_msg;
/*密码弹窗*/
    Input_Pwd *Input_Pwd_Widget;

    /*进程*/
    QProcess *pro;
    QString out;
    int current_bash;//标志位(当前页面)

    // 内存动态使用率图的部件
    QWidget *               m_widgetMemChart;
    CMemoryDynamicChart *   m_chartMemInfo;

    // 内存分配情况的部件
    QWidget *               m_widgetMemAllocChart;
    CMemAllocChart *        m_chartMemAlloc;

private:
    void initMemChartWidget();
    void initMemAllocChartWidget();

protected:

    bool eventFilter(QObject *obj, QEvent *event);

signals:

protected slots:
    void change_widget_cfg(int n);
    void show_msg_to_browser();
    void flush_msg();
public slots:

};

#endif // MAIN_PAGE_THREE_H
