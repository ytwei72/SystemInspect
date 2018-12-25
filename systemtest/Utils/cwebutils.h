#ifndef WEBUTILS_H
#define WEBUTILS_H

#include <QObject>

class CWebUtils : public QObject
{
    Q_OBJECT
public:
    explicit CWebUtils(QObject *parent = nullptr);

public:
    bool curlUrl(QString strUrl);
    bool pingUrl(QString strUrl);
    long getDataCount();
    long getPingTime();

private:
    long m_nPingTime;
    QString m_strOutput;

signals:

public slots:
};

#endif // WEBUTILS_H
