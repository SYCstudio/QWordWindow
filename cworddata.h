/*
 * 定义单词的基本数据
 * Date: 2021.9.17
 * Last update: 2021.9.18
 * Author: syc
*/
#ifndef CWORDDATA_H
#define CWORDDATA_H
#include <QString>
#include <QDateTime>
#include <QJsonObject>

class CWordData
{
    QString mKey, mTranslation;
    QDateTime mCreateTime;
    qint32 mTotalCount, mErrorCount;
public:
    CWordData();
    void parseFromJson(QJsonObject aObject);
    QJsonObject parseToJson();
    QString getKey() {return mKey;}
    QString getTranslation() {return mTranslation;}
    QDateTime getCreateTime() {return mCreateTime;}
    qint32 getTotalCount() {return mTotalCount;}
    qint32 getErrorCount() {return mErrorCount;}
    void setKey(QString aKey) {mKey = aKey;}
    void setTranslation(QString aTranslation) {mTranslation = aTranslation;}
    void setCreateTime(QDateTime aCreateTime) {mCreateTime = aCreateTime;}
    void setTotalCount(qint32 aTotalCount) {mTotalCount = aTotalCount;}
    void setErrorCount(qint32 aErrorCount) {mErrorCount = aErrorCount;}
    static bool cmpByKey(CWordData a, CWordData b);
    static bool cmpByTotalCount(CWordData a, CWordData b);
    static bool cmpByRating(CWordData a, CWordData b);
};

#endif // CWORDDATA_H
