#include "cworddataset.h"

CWordDataSet::CWordDataSet()
{

}

void CWordDataSet::parseFromJson(QJsonArray aJarray)
{
    int size = aJarray.size();
    mWordList.clear();
    mWordList.resize(size);
    //qDebug() << "size:" << size;
    for (int i = 0; i < size; i++) mWordList[i].parseFromJson(aJarray[i].toObject());
    return;
}

QJsonArray CWordDataSet::parseToJson()
{
    int size = mWordList.size();
    QJsonArray ret;
    for (int i = 0; i < size; i++) ret.append(mWordList[i].parseToJson());
    return ret;
}

void CWordDataSet::append(CWordData data)
{
    mWordList.append(data);
    return;
}
