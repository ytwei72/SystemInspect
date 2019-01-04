#include "transformutil.h"

#include <QJsonDocument>

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
