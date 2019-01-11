#include "generatepdfreport.h"

#include <QDateTime>
#include <QPainter>
#include <QPdfWriter>

#include "Utils/transformutil.h"

GeneratePdfReport::GeneratePdfReport()
{
    m_pdfPainter = NULL;
}

GeneratePdfReport::~GeneratePdfReport() {
    if (m_pdfPainter != NULL)
        delete m_pdfPainter;
}

bool GeneratePdfReport::writeReport(SystemPerfReport * sysInfoPage) {
    m_sysInfoPage = sysInfoPage;

//    QString text = QString("%1ZZ").arg("ABC", 10, QLatin1Char(' '));

    if (!initPdfFile())
        return false;

    if (!writeTitle())
        return false;

    if (!writeSystemInfo())
        return false;

    if (!writeCpuInfo())
        return false;

    if (!writeMemInfo())
        return false;

    if (!writeDiskInfo())
        return false;

    newPage();

    if (!writeNetworkInfo())
        return false;

    if (!writeRankingInfo())
        return false;

    if (!writeReportEnd())
        return false;

    return true;
}

void GeneratePdfReport::newPage() {
    m_vertiOffset = 0;
    m_pdfWriter->newPage();
}

void GeneratePdfReport::drawSectionTitle(QString title) {
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    // 写章节标题
    m_pdfPainter->setFont(m_fontSectTitle);
    m_pdfPainter->drawText(QRect(0,m_vertiOffset,m_pageSizePixel.width(),50), title, option);
    m_vertiOffset += 100 + m_lineGap;
}

void GeneratePdfReport::drawDashSplitLine() {
    m_pdfPainter->setPen(m_penDotSplitterLine);
    m_pdfPainter->drawLine(0, m_vertiOffset, m_pageSizePixel.width(), m_vertiOffset);

    m_vertiOffset += 50 + m_lineGap;
}

bool GeneratePdfReport::writeTitle() {
    // 写大标题
    QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pdfPainter->setFont(m_fontTitle);
    QPen pen;
    pen.setColor(Qt::black);
    m_pdfPainter->setPen(pen);
    int titleHeight = 100;
    m_pdfPainter->drawText(QRect(0, m_vertiOffset, m_pageSizePixel.width(), titleHeight), "系统性能检测报告", option);

    // 写报告时间戳
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeStamp = currentTime.toString("报告生成时间：yyyy年MM月dd日 hh:mm:ss");
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(10);
    m_pdfPainter->setFont(font);
    option.setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_vertiOffset += titleHeight + m_lineGap;
    m_pdfPainter->drawText(QRect(0,m_vertiOffset,m_pageSizePixel.width(),50), timeStamp, option);
    m_vertiOffset += 50 + m_lineGap;

    // 画两条实线分隔线
    m_pdfPainter->setPen(m_penSolidSplitterLine);
    m_pdfPainter->drawLine(0, m_vertiOffset, m_pageSizePixel.width(), m_vertiOffset);
    m_pdfPainter->drawLine(0, m_vertiOffset+10, m_pageSizePixel.width(), m_vertiOffset+10);

    // 更新写的纵向位置
    m_vertiOffset += 50 + m_lineGap;

    return true;
}

bool GeneratePdfReport::writeSystemInfo() {
    // 写章节标题
    drawSectionTitle("一、操作系统");

    // 逐条写系统信息
    OsGeneralInfo * osInfo = m_sysInfoPage->getOsGeneralInfo();
    QJsonObject jsonInfo = osInfo->getOsInfo();
    QJsonObject::Iterator iter;
    int index = 0;
    m_pdfPainter->setFont(m_fontField);
    for (iter = jsonInfo.begin(); iter!=jsonInfo.end(); iter++) {
        QPoint ptPos;
        ptPos.setX(m_pageSizePixel.width() * (index % 2) / 2);
        ptPos.setY(m_vertiOffset + index / 2 * (m_lineHeight + m_lineGap));
        QString text = iter.key() + ": " + iter.value().toVariant().toString();
        if (text.count() > 40)
            text = text.left(37) + "...";
        m_pdfPainter->drawText(ptPos, text);
        index++;
    }
    m_vertiOffset += index / 2 * (m_lineHeight + m_lineGap);

    // 画一条虚线分隔线
    drawDashSplitLine();

    return true;
}

bool GeneratePdfReport::writeCpuInfo() {
    // 写章节标题
    drawSectionTitle("二、CPU");

    //! 逐条写CPU信息
    CpuGeneralInfo * cpuInfo = m_sysInfoPage->getCpuGeneralInfo();
    int count = cpuInfo->getCpuInfoCount();
    m_pdfPainter->setFont(m_fontField);
    int i;
    QString text;
    for (i=0; i<count; i++) {
        QPoint ptPos;
        ptPos.setX(m_pageSizePixel.width() * (i % 2) / 2);
        ptPos.setY(m_vertiOffset + i / 2 * (m_lineHeight + m_lineGap));
        text = cpuInfo->getKeyNameByIndex(i) + ": " + cpuInfo->getValueByIndex(i);
        if (text.count() > 40)
            text = text.left(37) + "...";
        m_pdfPainter->drawText(ptPos, text);
    }

    m_vertiOffset += (i + 1) / 2 * (m_lineHeight + m_lineGap);

    //! 写CPU使用率
    m_vertiOffset += 2 * m_lineGap;
    CpuUsageInfo * cpuUsage = m_sysInfoPage->getCpuUsageInfo();
    m_pdfPainter->drawText(0, m_vertiOffset, "CPU使用率：");
    m_vertiOffset += m_lineHeight + m_lineGap;

    // 画表格
    m_pdfPainter->setPen(m_penTableLine);
    int yPos = m_vertiOffset-50;
    int xStart = 0;
    int xEnd = 1440;
    for (int i=0; i<3; i++) {
        m_pdfPainter->drawLine(xStart, yPos, xEnd, yPos);
        yPos += m_lineHeight + m_lineGap;
    }
    int xPos = 0;
    int yStart = m_vertiOffset-50;
    int yEnd = m_vertiOffset + 1 * (m_lineHeight + m_lineGap) + 8;
    for (int i=0; i<7; i++) {
        m_pdfPainter->drawLine(xPos, yStart, xPos, yEnd);
        xPos += 240;
    }
    // 写表头
    m_pdfPainter->drawText(0, m_vertiOffset, "  用户态\t内核态\t空闲率\tIO等待\t硬中断\t软中断");
    m_vertiOffset += m_lineHeight + m_lineGap;

    // 写列数据
    text = QString("  %1%\t%2%\t%3%\t%4%\t%5%\t%6%")
            .arg(double(cpuUsage->getUserRate()))
            .arg(double(cpuUsage->getKernelRate()))
            .arg(double(cpuUsage->getIdleRate()))
            .arg(double(cpuUsage->getIoRate()))
            .arg(double(cpuUsage->getHardIntRate()))
            .arg(double(cpuUsage->getSoftIntRate()));
    m_pdfPainter->drawText(0, m_vertiOffset, text);
    m_vertiOffset += m_lineHeight + m_lineGap;

    // 画一条虚线分隔线
    drawDashSplitLine();

    return true;
}

bool GeneratePdfReport::writeMemInfo() {
    // 写章节标题
    drawSectionTitle("三、内存");

    // 分两列逐条写内存基本信息
    m_pdfPainter->setFont(m_fontField);
    MemGeneralInfo * memInfo = m_sysInfoPage->getMemGeneralInfo();
    QStringList keyList = memInfo->getKeyList();
    int i;
    for (i=0; i<keyList.count(); i++) {
        QPoint ptPos;
        ptPos.setX(m_pageSizePixel.width() * (i % 2) / 2);
        ptPos.setY(m_vertiOffset + i / 2 * (m_lineHeight + m_lineGap));
        double volume = memInfo->getKeyValue(keyList[i]).toDouble();
        QString text = keyList[i] + ": " + TransformUtil::autoVolume(volume);
        if (text.count() > 40)
            text = text.left(37) + "...";
        m_pdfPainter->drawText(ptPos, text);
    }
    m_vertiOffset += (i + 1) / 2 * (m_lineHeight + m_lineGap);

    // 画一条虚线分隔线
    drawDashSplitLine();

    return true;
}

bool GeneratePdfReport::writeDiskInfo() {
    // 写章节标题
    drawSectionTitle("四、磁盘");

    DiskGeneralInfo * diskInfo = m_sysInfoPage->getDiskGeneralInfo();
    m_pdfPainter->setFont(m_fontField);
    m_pdfPainter->drawText(0, m_vertiOffset, "  磁盘\t\t容量\t已用\t可用\t已用%\t挂载点");
    m_vertiOffset += m_lineHeight + m_lineGap;
    for (int i=0; i<diskInfo->getDiskCount(); i++) {
        DiskFSInfo diskFsInfo = diskInfo->getDiskFSInfo(i);
        QString diskName = diskFsInfo.fsName();
        QString text = QString("  %1\t\t%2\t%3\t%4\t%5\t%6")
                .arg(diskName)
                .arg(diskFsInfo.totalVolume())
                .arg(diskFsInfo.usedVolume())
                .arg(diskFsInfo.availVolume())
                .arg(diskFsInfo.usedRate())
                .arg(diskFsInfo.mountPoint());
        m_pdfPainter->drawText(0, m_vertiOffset, text);
        m_vertiOffset += m_lineHeight + m_lineGap;
    }

    // 画一条虚线分隔线
    drawDashSplitLine();

    return true;
}

bool GeneratePdfReport::writeNetworkInfo() {
    // 写章节标题
    drawSectionTitle("五、网络");

    // 分两列逐条写网络信息
    NetworkGeneralInfo * netInfo = m_sysInfoPage->getNetGeneralInfo();
    QJsonObject jsonInfo = netInfo->getInfo();
    QJsonObject::Iterator iter;
    int index = 0;
    m_pdfPainter->setFont(m_fontField);
    for (iter = jsonInfo.begin(); iter!=jsonInfo.end(); iter++) {
        QPoint ptPos;
        ptPos.setX(m_pageSizePixel.width() * (index % 2) / 2);
        ptPos.setY(m_vertiOffset + index / 2 * (m_lineHeight + m_lineGap));
        QString text = iter.key() + ": " + iter.value().toVariant().toString();
        if (text.count() > 40)
            text = text.left(37) + "...";
        m_pdfPainter->drawText(ptPos, text);
        index++;
    }
    m_vertiOffset += index / 2 * (m_lineHeight + m_lineGap);

    // 画一条虚线分隔线
    drawDashSplitLine();

    return true;
}

bool GeneratePdfReport::writeRankingInfo() {
    // 写章节标题
    drawSectionTitle("六、系统资源占用排行");

    //! CPU占用率排行
    int yCpuOffset = m_vertiOffset;
    m_pdfPainter->setFont(m_fontField);
    m_pdfPainter->drawText(0, yCpuOffset, "CPU占用率排行");
    yCpuOffset += m_lineHeight + m_lineGap;

    CpuUsageInfo * cpuUsage = m_sysInfoPage->getCpuUsageInfo();
    int cpuRankCount = cpuUsage->getCpuRankDataCount();
    for (int i=0; i<cpuRankCount; i++) {
        TaskRunningInfo taskInfo = cpuUsage->getCpuRankData(i);
        QString text = QString("  %1%2\t%3%")
                .arg(i+1, 4, 10, QLatin1Char(' '))
                .arg(taskInfo.cmd(), 16, QLatin1Char(' '))
                .arg(taskInfo.cpuRate() / 4);
        m_pdfPainter->drawText(0, yCpuOffset, text);
        yCpuOffset += m_lineHeight + m_lineGap;
    }

    //! 内存占用率排行
    int yMemOffset = m_vertiOffset;
    int xStart = m_pageSizePixel.width()/2;
    m_pdfPainter->setFont(m_fontField);
    m_pdfPainter->drawText(xStart, yMemOffset, "内存占用率排行");
    yMemOffset += m_lineHeight + m_lineGap;

    MemUsageRate * memRank = m_sysInfoPage->getMemRankInfo();
    int memRankCount = memRank->getMemRankDataCount();
    for (int i=0; i<memRankCount; i++) {
        TaskRunningInfo taskInfo = memRank->getMemRankData(i);
        QString text = QString("  %1%2\t%3%")
                .arg(i+1, 4, 10, QLatin1Char(' '))
                .arg(taskInfo.cmd(), 16, QLatin1Char(' '))
                .arg(taskInfo.memRate());
        m_pdfPainter->drawText(xStart, yMemOffset, text);
        yMemOffset += m_lineHeight + m_lineGap;
    }

    // 调整偏移量
    m_vertiOffset = yCpuOffset;

    return true;
}

bool GeneratePdfReport::writeReportEnd() {
    // 画两条实线分隔线
    m_pdfPainter->setPen(m_penSolidSplitterLine);
    m_pdfPainter->drawLine(0, m_vertiOffset, m_pageSizePixel.width(), m_vertiOffset);
    m_pdfPainter->drawLine(0, m_vertiOffset+10, m_pageSizePixel.width(), m_vertiOffset+10);

    // 更新写的纵向位置
    m_vertiOffset += 50 + m_lineGap;

    QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
    // 写报告结束
    m_pdfPainter->setFont(m_fontField);
    m_pdfPainter->drawText(QRect(0,m_vertiOffset,m_pageSizePixel.width(),50), "报告结束", option);
    m_vertiOffset += 100 + m_lineGap;

    return true;
}

bool GeneratePdfReport::initPdfFile() {
    // 设置要生成的文件路径和名称
    m_pdfFile.setFileName("./test_QPdfWriter.pdf");

    // 打开文件
    if ( !m_pdfFile.open(QIODevice::WriteOnly) )
        return false;

    // 新建一个PDF Writer
    m_pdfWriter = new QPdfWriter(&m_pdfFile);

    //! 设置PDF的基本属性
    // A4, 像素 3507 * 2480
    m_pdfWriter->setPageSize(QPagedPaintDevice::A4);
    QSizeF pageSizeMM = m_pdfWriter->pageSizeMM();
    int resolution = 300;
    m_pdfWriter->setResolution(resolution);
    m_pdfWriter->setTitle("系统性能测试报告");
    int pageMargin = 20;
    m_pdfWriter->setPageMargins(QMarginsF(pageMargin, pageMargin, pageMargin, pageMargin), QPageLayout::Millimeter);
//    m_pageSizePixel.setWidth((pageSizeMM.width() - 2 * pageMargin)/ 25.4 * resolution);
//    m_pageSizePixel.setHeight((pageSizeMM.height() - 2 * pageMargin )/ 25.4 * resolution);
    m_pageSizePixel.setWidth((pageSizeMM.width() - 2 * pageMargin)/ 25.4 * resolution);
    m_pageSizePixel.setHeight((pageSizeMM.height() - 2 * pageMargin )/ 25.4 * resolution);

    pageSizeMM = m_pdfWriter->pageSizeMM();

    m_pdfPainter = new QPainter(m_pdfWriter);

    // 偏移量清零，并设置行间距
    m_vertiOffset = 0;
    m_lineGap = 10;
    m_lineHeight = 50;

    // 标题字体
    m_fontTitle.setFamily("宋体");
    m_fontTitle.setPointSize(18);
//    m_fontTitle.setBold(true);

    // 章节标题字体
    m_fontSectTitle.setFamily("宋体");
    m_fontSectTitle.setPointSize(12);

    // 内容字段名字体
    m_fontField.setFamily("宋体");
    m_fontField.setPointSize(10);

    // 内容值字体
    m_fontValue.setFamily("宋体");
    m_fontValue.setPointSize(10);

    m_penSolidSplitterLine.setWidth(4);

    m_penDotSplitterLine.setWidth(2);
    m_penDotSplitterLine.setStyle(Qt::DashLine);

    m_penTableLine.setWidth(2);
    m_penTableLine.setStyle(Qt::SolidLine);

    return true;
}
