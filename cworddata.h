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
#include <QVector>
#include <QJsonArray>
#include <QDebug>

class CWordData
{
    QString mKey, mTranslation;
    QDateTime mCreateTime;
    QVector<QDateTime> mPracticeQueue, mWrongQueue;
    qint32 mTotalCount, mErrorCount, mPracticeCount;
public:
    CWordData();
    void parseFromJson(QJsonObject aObject, QString aVersion);
    QJsonObject parseToJson();
    QString getKey() {return mKey;}
    QString getTranslation() {return mTranslation;}
    QDateTime getCreateTime() {return mCreateTime;}
    qint32 getTotalCount() {return mTotalCount;}
    qint32 getErrorCount() {return mErrorCount;}
    QDateTime getLastTime();
    qint32 getPracticeCount() {return mPracticeCount;}
    void setKey(QString aKey) {mKey = aKey;}
    void setTranslation(QString aTranslation) {mTranslation = aTranslation;}
    void setCreateTime(QDateTime aCreateTime) {mCreateTime = aCreateTime;}
    void setTotalCount(qint32 aTotalCount) {mTotalCount = aTotalCount;}
    void setErrorCount(qint32 aErrorCount) {mErrorCount = aErrorCount;}
    void setPracticeTime(qint32 aPracticeCount) {mPracticeCount = aPracticeCount;}
    static bool cmpByKey(CWordData a, CWordData b);
    static bool cmpByErrorRate(CWordData a, CWordData b);
    static bool cmpByPracticeTime(CWordData a, CWordData b);
    static bool cmpByLastDate(CWordData a, CWordData b);
    static bool cmpByErrorRatep(CWordData *a, CWordData *b);
    static bool cmpByPracticeTimep(CWordData *a, CWordData *b);
    static bool cmpByLastDatep(CWordData *a, CWordData *b);
};

#endif // CWORDDATA_H
