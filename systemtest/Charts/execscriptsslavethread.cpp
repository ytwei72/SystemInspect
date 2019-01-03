#include "execscriptsslavethread.h"
#include "common.h"

ExecScriptsSlaveThread::ExecScriptsSlaveThread(QObject *parent) :
    QThread(parent)
{
}

ExecScriptsSlaveThread::~ExecScriptsSlaveThread()
{
    m_mutex.lock();
    m_quit = true;
    m_mutex.unlock();
    wait();
}

void ExecScriptsSlaveThread::execScipts(QString script) {
    m_mutex.lock();
    m_script = script;
    m_bExecShell = true;
    m_mutex.unlock();
}

void ExecScriptsSlaveThread::startSlave()
{
    //! [1]
    const QMutexLocker locker(&m_mutex);

    //! [2]
    if (!isRunning()) {
        m_procShell = new QProcess();
        start();
    }
}

void ExecScriptsSlaveThread::run()
{
    while (!m_quit) {
        if (!m_bExecShell) {
            sleep(1);
            continue;
        }

        m_mutex.lock();

        // 设置运行脚本
        QString strCmd = "bash";
        QStringList strParams;
        strParams<<m_script;

        // 启动进程，并等待结束
        m_procShell->start(strCmd, strParams);
        QString errorInfo;
        bool bReadyRead = m_procShell->waitForReadyRead();
        // 进程结束后，将数据读取出来
        if (bReadyRead) {
            m_result = m_procShell->readAllStandardOutput();
            // 发出脚本执行完成的信号
            emit scriptResult(m_result);
        } else {
            errorInfo = m_procShell->readAllStandardError();
        }

        m_bExecShell = false;

        m_mutex.unlock();
    }
}

