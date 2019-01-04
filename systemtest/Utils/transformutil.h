#ifndef TRANSFORMUTIL_H
#define TRANSFORMUTIL_H

#include <QJsonObject>



class TransformUtil
{
public:
    TransformUtil();

    static QJsonObject stringToJson(QString jsonString);
    static QString jsonToString(QJsonObject jsonObject);

};

#endif // TRANSFORMUTIL_H
