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
};

#endif // CWORDDATA_H
