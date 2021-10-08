#include "cworddata.h"

CWordData::CWordData()
{

}

void CWordData::parseFromJson(QJsonObject aObject)
{
    mKey = aObject["key"].toString();
    mTranslation = aObject["translation"].toString();
    QString stime = aObject["create_time"].toString();
    mCreateTime = QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss");
    mTotalCount = aObject["total_count"].toInt();
    mErrorCount = aObject["error_count"].toInt();
    stime = aObject["last_time"].toString();
    mLastTime = QDateTime::fromString(stime, "yyyy-MM-dd hh:mm:ss");
    mPracticeCount = aObject["practice_count"].toInt();
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
    ret["last_time"] = mLastTime.toString("yyyy-MM-dd hh:mm:ss");
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
    return a->getErrorCount() * b->getTotalCount() > b->getErrorCount() * a->getTotalCount();
}

bool CWordData::cmpByLastDatep(CWordData *a, CWordData *b)
{
    if (a->getPracticeCount() == 0 || b->getPracticeCount() == 0){
        return a->getPracticeCount() > b->getPracticeCount();
    }
    return a->getLastTime() > b->getLastTime();
}

bool CWordData::cmpByLastDate(CWordData a, CWordData b)
{
    return cmpByLastDatep(&a, &b);
}
