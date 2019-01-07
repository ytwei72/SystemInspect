#ifndef TRANSFORMUTIL_H
#define TRANSFORMUTIL_H

#include <QJsonObject>



class TransformUtil
{
public:
    TransformUtil();

    static QJsonObject stringToJson(QString jsonString);
    static QString jsonToString(QJsonObject jsonObject);

    static void clearJsonObject(QJsonObject * jsonObject);

    static QString trimSpace(QString inString);

};

#endif // TRANSFORMUTIL_H
