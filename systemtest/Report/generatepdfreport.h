#ifndef GENERATEPDFREPORT_H
#define GENERATEPDFREPORT_H

#include "Report/systemperfreport.h"

#include <QPdfWriter>
#include <QPen>
#include "Report/cpugeneralinfo.h"
#include "Report/cpuusageinfo.h"
#include "Report/taskrunninginfo.h"
#include "Report/memgeneralinfo.h"
#include "Report/memusagerate.h"
#include "Report/diskgeneralinfo.h"
#include "Report/osgeneralinfo.h"
#include "Report/networkgeneralinfo.h"


class GeneratePdfReport
{
    friend class SystemPerfReport;

public:
    GeneratePdfReport();
    ~GeneratePdfReport();

    bool writeReport(SystemPerfReport * sysInfoPage);

private:
    SystemPerfReport *  m_sysInfoPage;

    bool initPdfFile();
    // 要生成的报告文件
    QFile           m_pdfFile;
    // 写报告的 writer 和 painter
    QPainter *      m_pdfPainter;
    QPdfWriter *    m_pdfWriter;
    // 页面的尺寸（单位：像素）
    QSizeF          m_pageSizePixel;
    // 标题字体
    QFont           m_fontTitle;
    // 章节标题字体
    QFont           m_fontSectTitle;
    // 内容字段名字体
    QFont           m_fontField;
    // 内容值字体
    QFont           m_fontValue;
    // 实线分隔线段画笔
    QPen            m_penSolidSplitterLine;
    // 虚线分隔线段画笔
    QPen            m_penDotSplitterLine;
    // 表格线段画笔
    QPen            m_penTableLine;
    // 生成PDF内容时纵向偏移量
    int             m_vertiOffset;
    // 行间距
    int             m_lineGap;
    // 行高
    int             m_lineHeight;

    void drawSectionTitle(QString title);
    void drawDashSplitLine();
    void newPage();

    bool writeTitle();

    bool writeSystemInfo();

    bool writeCpuInfo();

    bool writeMemInfo();

    bool writeDiskInfo();

    bool writeNetworkInfo();

    bool writeRankingInfo();

    bool writeReportEnd();
};

#endif // GENERATEPDFREPORT_H
