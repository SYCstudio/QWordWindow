#include "sglobalsetting.h"

SGlobalSetting *SGlobalSetting::mInstance = new SGlobalSetting();

void SGlobalSetting::initSetting(QString filename)
{
    QFile reader(filename);
    if (!reader.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't find file";
        return;
    }
    QJsonParseError errorTag;
    QJsonDocument doc = QJsonDocument::fromJson(reader.readAll(), &errorTag);
    if (doc.isNull() || errorTag.error != QJsonParseError::NoError) {
        qDebug() << "parse error";
        return;
    }
    auto obj = doc.object();
    mInstance->setErrorAmount(obj["error_amount"].toInt());
    mInstance->setLastAmount(obj["last_amount"].toInt());
    mInstance->setNewAmount(obj["new_amount"].toInt());
    mInstance->setCurrentDataset(obj["current_dataset_name"].toString());
    reader.close();
    return;
}

void SGlobalSetting::exit()
{
    auto p = getInstance()->getDataset();
    for (auto value : *p) delete value;
    delete mInstance;
}

void SGlobalSetting::saveSetting(QString filename)
{
    QFile writer(filename);
    if (!writer.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "can't write file";
        return;
    }
    QJsonObject obj;
    obj["error_amount"] = mInstance->getErrorAmount();
    obj["last_amount"] = mInstance->getLastAmount();
    obj["new_amount"] = mInstance->getNewAmount();
    obj["current_dataset_name"] = mInstance->getCurrentDataset();
    QJsonDocument doc;
    doc.setObject(obj);
    writer.write(doc.toJson());
    writer.close();
    return;
}

void SGlobalSetting::saveData(QString filename)
{
    QFile writer(filename);
    if (!writer.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "can't write file";
        return;
    }
    QJsonArray arr;
    QMap<QString, CWordDataSet*>* wordsbooks = getDataset();
    for (QMap<QString, CWordDataSet*>::iterator it = wordsbooks->begin(); it != wordsbooks->end(); it++) {
        QString name = it.key();
        CWordDataSet *p = it.value();
        QJsonObject obj;
        obj["name"] = name;
        obj["dataset"] = p->parseToJson();
        arr.append(obj);
    }
    QJsonDocument doc;
    doc.setArray(arr);
    writer.write(doc.toJson());
    writer.close();
    return;
}

void SGlobalSetting::initData(QString filename)
{
    QFile reader(filename);
    if (!reader.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't find file";
        return;
    }
    QJsonParseError errorTag;
    QJsonDocument doc = QJsonDocument::fromJson(reader.readAll(), &errorTag);
    if (doc.isNull() || errorTag.error != QJsonParseError::NoError) {
        qDebug() << "parse error";
        return;
    }
    //qDebug() << doc.isArray();
    //mWordDataSet.parseFromJson(doc.array());

    QMap<QString, CWordDataSet*>* wordsbooks = SGlobalSetting::getInstance()->getDataset();

    QJsonArray arr = doc.array();
    int size = arr.size();
    for (int i = 0; i < size; i++) {
        QJsonObject obj = arr[i].toObject();
        QString name = obj["name"].toString();
        CWordDataSet *dataset;
        dataset = new CWordDataSet();
        dataset->parseFromJson(obj["dataset"].toArray());
        wordsbooks->insert(name, dataset);
    }
    reader.close();
    return;
}
