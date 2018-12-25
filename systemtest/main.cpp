#include "main_widget.h"
#include <QApplication>
#include <QtTest/QtTest>
#include <QSplashScreen>
#include <QMovie>
#include <QTranslator>

#include "Utils/csysutils.h"
#include "Utils/cwebutils.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTranslator translator;
//    translator.load(QString(":"));
//    a.installTranslator(&translator);

//    CSysUtils::resetTimerClock();
//    CWebUtils webUtil;
//    for (int i=0; i<100; i++)
//        webUtil.curlUrl("www.sohu.com");
//    qint64 elpasedTime = CSysUtils::getElapsedMilliSeconds();



    QSplashScreen splash(QPixmap(":/boot/img/loading.png"));
    splash.show();
    a.processEvents();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash.showMessage(QObject::tr("Setting up the MainWindow..."), topRight, Qt::white);

    QTest::qSleep(1000);
    splash.showMessage(QObject::tr("Loading modules..."), topRight, Qt::white);
    QTest::qSleep(1000);


    main_widget w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
