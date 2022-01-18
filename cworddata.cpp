#include "cworddata.h"

CWordData::CWordData()
{

}

QDateTime CWordData::getLastTime()
{
    if (mPracticeQueue.isEmpty()) return mCreateTime;
    return mPracticeQueue.back();
}

void CWordData::parseFromJson(QJsonObject aObject, QString aVersion)
{
    mKey = aObject["key"].toString();
    QString stime = aObject["create_time"].toString();
    mCreateTime = QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss");
    mTotalCount = aObject["total_count"].toInt();
    mErrorCount = aObject["error_count"].toInt();

    mPracticeCount = aObject["practice_count"].toInt();
    if (aVersion == "0.1.0") {// upgrade from 0.1.0 to 0.1.1
        qDebug() << "update from 0.1.0 to 0.1.1";
        stime = aObject["last_time"].toString();
        mPracticeQueue.append(QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss"));
        mUseDictInfo = false;
        mAddition = aObject["translation"].toString();
        mUseAddition = true;
    }
    else {
        mUseDictInfo = aObject["use_dict_info"].toInt();
        mUseAddition = aObject["use_addition"].toInt();
        if (mUseAddition)
            mAddition = aObject["addition"].toString();
        QJsonArray arr = aObject["recently_practice_date"].toArray();
        for (auto data:arr) {
            stime = data.toString();
            mPracticeQueue.append(QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss"));
        }
        arr = aObject["recently_wrong_date"].toArray();
        for (auto data:arr) {
            stime = data.toString();
            mWrongQueue.append(QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss"));
        }
    }
    return;
}

QJsonObject CWordData::parseToJson()
{
    QJsonObject ret;
    ret["key"] = mKey;
    ret["use_addition"] = mUseAddition;
    if (mUseAddition)
        ret["addition"] = mAddition;
    ret["create_time"] = mCreateTime.toString("yyyy-MM-dd hh:mm:ss");
    ret["total_count"] = mTotalCount;
    ret["error_count"] = mErrorCount;
    ret["use_dict_info"] = mUseDictInfo;
    QJsonArray obj1, obj2;
    for (auto data:mPracticeQueue) {
        obj1.append(data.toString("yyyy-MM-dd hh:mm:ss"));
    }
    ret["recently_practice_date"] = obj1;
    for (auto data:mWrongQueue) {
        obj2.append(data.toString("yyyy-MM-dd hh:mm:ss"));
    }
    ret["recently_wrong_date"] = obj2;
    ret["practice_count"] = mPracticeCount;
    return ret;
}

bool CWordData::cmpByKey(CWordData a, CWordData b)
{
    return a.getKey() < b.getKey();
}

bool CWordData::cmpByPracticeTime(CWordData a, CWordData b)
{
    return cmpByPracticeTimep(&a, &b);
}

bool CWordData::cmpByErrorRate(CWordData a, CWordData b)
{
    return cmpByErrorRatep(&a, &b);
}

bool CWordData::cmpByPracticeTimep(CWordData *a, CWordData *b)
{
    return a->getPracticeCount() < b->getPracticeCount();
}

bool CWordData::cmpByErrorRatep(CWordData *a, CWordData *b)
{
    if (a->getPracticeCount() == 0 || b->getPracticeCount() == 0){
        return a->getPracticeCount() > b->getPracticeCount();
    }
    if (a->getErrorCount() == 0 && b->getErrorCount() == 0) {
        return a->getPracticeCount() < b->getPracticeCount();
    }
    return a->getErrorCount() * b->getTotalCount() > b->getErrorCount() * a->getTotalCount();
}

bool CWordData::cmpByLastDatep(CWordData *a, CWordData *b)
{
    if (a->getPracticeCount() == 0 || b->getPracticeCount() == 0){
        return a->getPracticeCount() > b->getPracticeCount();
    }
    return a->getLastTime() < b->getLastTime();
}

bool CWordData::cmpByLastDate(CWordData a, CWordData b)
{
    return cmpByLastDatep(&a, &b);
}

qint32 CWordData::getDayWrongCount(int mDay)
{
    return getDayWrongCount(mDay, mDay);
}

qint32 CWordData::getDayWrongCount(int mLower, int mUpper)
{
    qint32 ret = 0;
    auto today = QDateTime::currentDateTime();
    for (auto t:mWrongQueue) {
        qint32 day = t.daysTo(today);
        if (day >= mLower && day <= mUpper)
            ret++;
    }
    return ret;
}

qint32 CWordData::getDayCount(int mDay)
{
    return getDayCount(mDay, mDay);
}

qint32 CWordData::getDayCount(int mLower, int mUpper)
{
    qint32 ret = 0;
    auto today = QDateTime::currentDateTime();
    for (auto t:mPracticeQueue) {
        qint32 day = t.daysTo(today);
        if (day >= mLower && day <= mUpper)
            ret++;
    }
    return ret;
}
