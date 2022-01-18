/*
 * 定义单词集
 * Date: 2021.9.18
 * Last update: 2021.9.18
 * Author: syc
*/
#ifndef CWORDDATASET_H
#define CWORDDATASET_H

#include <QVector>
#include <QJsonArray>
#include <QDebug>
#include <QMap>
#include <QSet>
#include <algorithm>
#include "cworddata.h"
#include "crandomqueue.h"

class CWordDataSet
{
    //QVector<CWordData> mWordList;
    QMap<QString, CWordData*> mWordMap;
public:
    CWordDataSet();
    void parseFromJson(QJsonArray aJarray, QString aVersion);
    QJsonArray parseToJson();
    void append(CWordData *aData);
    QSet<CWordData*> getWordsByArg(int aNew, int aError, int aPast);
    CRandomQueue<CWordData*> getWordsByDays(int aDays);
    int getSize() {return mWordMap.size();}
    int getUnLearnedAmount();
    CWordData* getWordByName(QString aName);
    ~CWordDataSet();
};

#endif // CWORDDATASET_H
