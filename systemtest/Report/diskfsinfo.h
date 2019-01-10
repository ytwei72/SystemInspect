#ifndef DISKFSINFO_H
#define DISKFSINFO_H

#include <QString>
#include <QStringList>



class DiskFSInfo
{
public:
    DiskFSInfo();

    void loadFSInfo(QStringList recordList);

    QString fsName() const;
    void setFsName(const QString &fsName);

    QString totalVolume() const;
    void setTotalVolume(const QString &totalVolume);

    QString usedVolume() const;
    void setUsedVolume(const QString &usedVolume);

    QString usedRate() const;
    void setUsedRate(const QString &usedRate);

    QString availVolume() const;
    void setAvailVolume(const QString &availVolume);

    QString mountPoint() const;
    void setMountPoint(const QString &mountPoint);

private:
    QString             m_fsName;
    QString             m_totalVolume;
    QString             m_usedVolume;
    QString             m_availVolume;
    QString             m_usedRate;
    QString             m_mountPoint;
};

#endif // DISKFSINFO_H
