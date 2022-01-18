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

void CWordDataSet::parseFromJson(QJsonArray aJarray, QString aVersion)
{
    int size = aJarray.size();
    for (auto it :mWordMap) delete it;
    for (int i = 0; i < size; i++) {
        CWordData *p;
        p = new CWordData();
        p->parseFromJson(aJarray[i].toObject(), aVersion);
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
    if (mWordMap.count(data->getKey()) == 0)
        mWordMap[data->getKey()] = data;
    return;
}

QSet<CWordData*> CWordDataSet::getWordsByArg(int aNew, int aError, int aPast)
{
    QSet<CWordData*> set;//用于去重

    //首先处理新学习的词
    CRandomQueue<CWordData*> rque;
    for (auto it:mWordMap)
        if (it->getPracticeCount() == 0)
            rque.append(it);
    rque.forceMove();
    while (aNew && !rque.isEmpty()) {
        set.insert(rque.pop());
        aNew--;
    }
    rque.clear();
    qDebug() << "case 1:" << set.size();

    //随机选择上一次出现时间超过 15 天的单词，如果不够就按时间选最远的
    for (auto it:mWordMap)
        if (it->getPracticeCount() != 0 && it->getDayCount(0, 15) == 0)
            rque.append(it);
    rque.forceMove();
    while (aPast && !rque.isEmpty()) {
        set.insert(rque.pop());
        aPast--;
    }
    if (aPast) {
        QVector<CWordData*> svec;
        for (auto it:mWordMap)
            if (it->getPracticeCount() != 0 && set.contains(it) == false)
                svec.append(it);
        qSort(svec.begin(), svec.end(), CWordData::cmpByLastDatep);
        for (int i = 0, sz = svec.size(); i < sz && i < aPast; i++) {
            set.insert(svec[i]);
        }
    }
    qDebug() << "case 2:" << set.size();

    //根据权值选择最近错误的单词
    double sum = 0;
    QVector<QPair<CWordData*, double> > ssvec;
    for (auto it:mWordMap)
        if (it->getPracticeCount() != 0 && set.contains(it) == false) {
            double value = 0.5;
            value = value + 5.0 * it->getDayWrongCount(0,1);
            value = value + 3.5 * it->getDayWrongCount(2);
            value = value + 1.5 * it->getDayWrongCount(3);
            value = value + 0.5 * it->getDayWrongCount(4, 5);
            value = value + 0.04 * it->getDayWrongCount(6, 15);
            sum += value;
            ssvec.append(qMakePair(it, sum));
        }
    qDebug() << "sum:" << sum;
    while (aError > 0) {
        double randvalue = ((double)qrand()) / ((double)RAND_MAX) * sum;
        qDebug() << randvalue;
        for (auto it:ssvec)
            if (it.second >= randvalue) {
                qDebug() << "fetch:" << it.first->getKey();
                set.insert(it.first);
                break;
            }
        aError--;
    }
    qDebug() << "case 3:" << set.size();

    return set;
}

int CWordDataSet::getUnLearnedAmount()
{
    int ret = 0;
    for (auto p : mWordMap)
        if (p->getPracticeCount() == 0) ret++;
    return ret;
}
