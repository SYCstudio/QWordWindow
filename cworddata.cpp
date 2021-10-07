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

bool CWordData::cmpByTotalCount(CWordData a, CWordData b)
{
    return a.getTotalCount() < b.getTotalCount();
}

bool CWordData::cmpByRating(CWordData a, CWordData b)
{
    return a.getErrorCount() * b.getTotalCount() < b.getErrorCount() * a.getTotalCount();
}
