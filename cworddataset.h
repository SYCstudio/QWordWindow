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
#include "cworddata.h"

class CWordDataSet
{
    QVector<CWordData> mWordList;
public:
    CWordDataSet();
    void parseFromJson(QJsonArray aJarray);
    QJsonArray parseToJson();
    void append(CWordData aData);
    QVector<CWordData> getWordList() {return mWordList;}
    int getSize() {return mWordList.size();}
};

#endif // CWORDDATASET_H
