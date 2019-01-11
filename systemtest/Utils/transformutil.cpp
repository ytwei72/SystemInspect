#include "transformutil.h"

#include <QJsonDocument>
#include <QRegExp>

TransformUtil::TransformUtil()
{

}



QJsonObject TransformUtil::stringToJson(QString jsonString)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    if(jsonDocument.isNull())
    {
        return QJsonObject();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

QString TransformUtil::jsonToString(QJsonObject jsonObject)
{
    return QString(QJsonDocument(jsonObject).toJson());
}

void TransformUtil::clearJsonObject(QJsonObject * jsonObject)
{
    if (jsonObject->count() <= 0)
        return;

    QJsonObject::Iterator iter;
    QString key = "";
    iter = jsonObject->begin();
    while (iter != jsonObject->end()) {
        iter = jsonObject->erase(iter);
    }
}

// 使用一个空格替换掉连续的多余的空格，并去掉首尾的空格
QString TransformUtil::trimSpace(QString inString) {
    QString trimmed = inString.trimmed();
    return trimmed.replace(QRegExp("\\s{1,}"), " ");
}

// 输入参数vol为以KB为单位
QString TransformUtil::autoVolume(double vol) {
    if (vol >= 1024 * 1024 * 1024) {
        return QString("%1 TB").arg(vol / (1024 * 1024 * 1024));
    } else if (vol >= 1024 * 1024) {
        return QString("%1 GB").arg(vol / (1024 * 1024));
    } else if (vol >= 1024) {
        return QString("%1 MB").arg(vol / (1024));
    }

    return QString("%1 KB").arg(vol);
}
