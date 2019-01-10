#include "osgeneralinfo.h"

#include <QProcess>

#include "Utils/transformutil.h"
#include "Utils/csysutils.h"

OsGeneralInfo::OsGeneralInfo()
{

}

bool OsGeneralInfo::fetchInfo() {
    TransformUtil::clearJsonObject(&m_osInfo);

    QString cmdResult;

    //! 1. 操作系统信息
    cmdResult = CSysUtils::execCmd("head -n 1 /etc/issue.net");
    m_osInfo.insert("1. 系统信息", cmdResult);
//    QProcess procOsInfo;
//    procOsInfo.start("head -n 1 /etc/issue.net");
//    procOsInfo.waitForFinished();

//    QString errorInfo = procOsInfo.readAllStandardError();
//    if (!errorInfo.isEmpty())
//        return false;
//    QString result = procOsInfo.readAllStandardOutput();

    //! 1. 操作系统信息

    //! 2. 系统版本
    cmdResult = CSysUtils::execCmd("cat /proc/version");
    m_osInfo.insert("2. 操作系统版本", cmdResult);
    //! 2. 系统版本

    //! 3. 系统位数
    cmdResult = CSysUtils::execCmd("getconf LONG_BIT");
    m_osInfo.insert("3. 操作系统位数", cmdResult);
    //! 3. 系统位数

    //! 4. 用户组总数
    cmdResult = CSysUtils::execCmd("cut -d: -f1 /etc/group");
    QStringList groupsList = cmdResult.split("\n");
    m_osInfo.insert("4. 用户组总数", groupsList.count());
    //! 4. 用户组总数

    //! 5. 用户总数
    cmdResult = CSysUtils::execCmd("cut -d: -f1 /etc/passwd");
    QStringList usersList = cmdResult.split("\n");
    m_osInfo.insert("5. 用户总数", usersList.count());
    //! 5. 用户总数

    //! 6. 已加载内核模块总数
    cmdResult = CSysUtils::execCmd("lsmod");
    QStringList modsList = cmdResult.split("\n");
    m_osInfo.insert("6. 已加载内核模块总数", modsList.count());
    //! 6. 已加载内核模块总数

    return true;
}

