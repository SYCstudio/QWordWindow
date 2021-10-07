#ifndef SGLOBALSETTING_H
#define SGLOBALSETTING_H

#include <QJsonObject>

class SGlobalSetting
{
    static SGlobalSetting *mInstance;
    SGlobalSetting();
    qint32 mErrorAmount, mLastAmount, mNewAmount;
public:
    static void init(QJsonObject aObject);
    static void exit();
    QJsonObject parseToJson();
    static SGlobalSetting* getInstance() {return mInstance;}
    void setErrorAmount(qint32 aErrorAmount) {mErrorAmount = aErrorAmount;}
    void setLastAmount(qint32 aLastAmount) {mLastAmount = aLastAmount;}
    void setNewAmount(qint32 aNewAmount) {mNewAmount = aNewAmount;}
    qint32 getErrorAmount() {return mErrorAmount;}
    qint32 getLastAmount() {return mLastAmount;}
    qint32 getNewAmount() {return mNewAmount;}
};

#endif // SGLOBALSETTING_H
