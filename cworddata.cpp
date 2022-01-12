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
    mTranslation = aObject["translation"].toString();
    QString stime = aObject["create_time"].toString();
    mCreateTime = QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss");
    mTotalCount = aObject["total_count"].toInt();
    mErrorCount = aObject["error_count"].toInt();

    mPracticeCount = aObject["practice_count"].toInt();
    if (aVersion == "0.1.0") {// upgrade from 0.1.0 to 0.1.1
        qDebug() << "update from 0.1.0 to 0.1.1";
        stime = aObject["last_time"].toString();
        mPracticeQueue.append(QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss"));
    }
    else {
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
    ret["translation"] = mTranslation;
    ret["create_time"] = mCreateTime.toString("yyyy-MM-dd hh:mm:ss");
    ret["total_count"] = mTotalCount;
    ret["error_count"] = mErrorCount;
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
