#include "cwebutils.h"

#include <QProcess>

CWebUtils::CWebUtils(QObject *parent) : QObject(parent)
{

}

bool CWebUtils::curlUrl(QString strUrl){
    QProcess procCurl;

    QString strCmd = "curl " + strUrl;
    procCurl.start(strCmd);
    bool bFinished = procCurl.waitForFinished();
    if (!bFinished)
        return false;

    m_strOutput = procCurl.readAllStandardOutput();
    if (m_strOutput.isEmpty())
        return false;

    return true;
}

bool CWebUtils::pingUrl(QString strUrl){
    QProcess procCurl;

    QString strCmd = "ping " + strUrl + " -c 1";
    procCurl.start(strCmd);
    bool bFinished = procCurl.waitForFinished();
    if (!bFinished)
        return false;

    QString errorInfo = procCurl.readAllStandardError();
    if (!errorInfo.isEmpty())
        return false;

    m_strOutput = procCurl.readAllStandardOutput();

    return true;
}
