#include "cworddataset.h"

CWordDataSet::CWordDataSet()
{

}

CWordDataSet::~CWordDataSet()
{
    for (auto it : mWordMap)
        delete it;
    return;
}

void CWordDataSet::parseFromJson(QJsonArray aJarray)
{
    int size = aJarray.size();
    for (auto it :mWordMap) delete it;
    for (int i = 0; i < size; i++) {
        CWordData *p;
        p = new CWordData();
        p->parseFromJson(aJarray[i].toObject());
        append(p);
    }
    return;
}

QJsonArray CWordDataSet::parseToJson()
{
    QJsonArray ret;
    for (auto it : mWordMap) ret.append(it->parseToJson());
    //for (int i = 0; i < size; i++) ret.append(mWordList[i].parseToJson());
    return ret;
}

void CWordDataSet::append(CWordData *data)
{
    mWordMap[data->getKey()] = data;
    return;
}

CRandomQueue<CWordData*> CWordDataSet::getWordsByArg(int aNew, int aError, int aPast)
{
    QVector<CWordData*> vec;
    QSet<QString> set;
    for (auto it : mWordMap) vec.append(it);
    int size = vec.size();
    qSort(vec.begin(), vec.end(),CWordData::cmpByPracticeTimep);
    for (int i = 0; i < size && i < aNew; i++) set.insert(vec[i]->getKey());
    qSort(vec.begin(), vec.end(), CWordData::cmpByErrorRatep);
    for (int i = 0; i < size && i < aError; i++) set.insert(vec[i]->getKey());
    qSort(vec.begin(), vec.end(), CWordData::cmpByLastDatep);
    for (int i = 0; i < size && i < aPast; i++) set.insert(vec[i]->getKey());

    CRandomQueue<CWordData*> ret;
    for (auto it : set) ret.append(mWordMap[it]);
    return ret;
}
