#ifndef SGLOBALSETTING_H
#define SGLOBALSETTING_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "cworddataset.h"

class SGlobalSetting
{
    static SGlobalSetting *mInstance;
    SGlobalSetting(){};
    qint32 mErrorAmount, mLastAmount, mNewAmount;
    QString mCurrentDataset;
    QMap<QString, CWordDataSet*> mDataSet;
public:
    void initSetting(QString filename);
    void initData(QString filename);
    void saveSetting(QString filename);
    void saveData(QString filename);
    void exit();
    QJsonObject parseToJson();
    static SGlobalSetting* getInstance() {return mInstance;}
    void setErrorAmount(qint32 aErrorAmount) {mErrorAmount = aErrorAmount;}
    void setLastAmount(qint32 aLastAmount) {mLastAmount = aLastAmount;}
    void setNewAmount(qint32 aNewAmount) {mNewAmount = aNewAmount;}
    void setCurrentDataset(QString aCurrentDataset) {mCurrentDataset = aCurrentDataset;}
    qint32 getErrorAmount() {return mErrorAmount;}
    qint32 getLastAmount() {return mLastAmount;}
    qint32 getNewAmount() {return mNewAmount;}
    QString getCurrentDataset() {return mCurrentDataset;}
    QMap<QString, CWordDataSet*> * getDataset() {return &mDataSet;}
};

#endif // SGLOBALSETTING_H
