#ifndef SGLOBALSETTING_H
#define SGLOBALSETTING_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "cworddataset.h"

class SGlobalSetting
{
    static SGlobalSetting *mInstance;
    static const QString cCurrentVersion;
    SGlobalSetting(){};
    qint32 mErrorAmount, mLastAmount, mNewAmount;
    QString mCurrentDataset, mVersion;
    QMap<QString, CWordDataSet*> mDataSet;
    QSqlDatabase mDict;
public:
    void initSetting(QString filename);
    void initData(QString filename);
    void initDict(QString filename);
    void initFinish();
    void saveSetting(QString filename);
    void saveData(QString filename);
    void exit();
    QJsonObject parseToJson();
    static SGlobalSetting* getInstance() {return mInstance;}
    void setErrorAmount(qint32 aErrorAmount) {mErrorAmount = aErrorAmount;}
    void setLastAmount(qint32 aLastAmount) {mLastAmount = aLastAmount;}
    void setNewAmount(qint32 aNewAmount) {mNewAmount = aNewAmount;}
    void setCurrentDataset(QString aCurrentDataset) {mCurrentDataset = aCurrentDataset;}
    void setVersion(QString aVersion) {mVersion = aVersion;}
    qint32 getErrorAmount() {return mErrorAmount;}
    qint32 getLastAmount() {return mLastAmount;}
    qint32 getNewAmount() {return mNewAmount;}
    QString getCurrentDataset() {return mCurrentDataset;}
    QString getVersion() {return mVersion;}
    QMap<QString, CWordDataSet*> * getDataset() {return &mDataSet;}
    QString findInDict(QString aWord);
};

#endif // SGLOBALSETTING_H
