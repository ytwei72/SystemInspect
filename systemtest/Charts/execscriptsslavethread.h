#ifndef EXECSCRIPTSSLAVETHREAD_H
#define EXECSCRIPTSSLAVETHREAD_H

#include <QMutex>
#include <QProcess>
#include <QThread>
#include <QWaitCondition>

class ExecScriptsSlaveThread : public QThread
{
    Q_OBJECT

public:
    explicit ExecScriptsSlaveThread(QObject *parent = nullptr);
    ~ExecScriptsSlaveThread() Q_DECL_OVERRIDE;

    void startSlave();
    void execScipts(QString script);

signals:
    void scriptResult(const QString & result);

private:
    void run() Q_DECL_OVERRIDE;

    // 轮询间隔时间
//    int         m_pollingInterval = 5000;
    QMutex          m_mutex;
    bool            m_quit = false;
    QProcess *      m_procShell;
    bool            m_bExecShell = false;
    QString         m_script;
    QString         m_result;

//    int m_waitTimeout = 0;

};

#endif // EXECSCRIPTSSLAVETHREAD_H
