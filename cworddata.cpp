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
    return ret;
}
