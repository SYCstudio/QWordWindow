#include "sglobalsetting.h"

SGlobalSetting *SGlobalSetting::mInstance = new SGlobalSetting();
const QString SGlobalSetting::cCurrentVersion = "0.1.1";

void SGlobalSetting::initSetting(QString filename)
{
    QFile reader(filename);
    if (!reader.open(QIODevice::ReadOnly | QIODevice::Text)) {//处理空情况，创建初始数据
        setVersion(cCurrentVersion);
        setErrorAmount(0);
        setLastAmount(0);
        setNewAmount(0);
        setCurrentDataset("default");
        return;
    }
    QJsonParseError errorTag;
    QJsonDocument doc = QJsonDocument::fromJson(reader.readAll(), &errorTag);
    if (doc.isNull() || errorTag.error != QJsonParseError::NoError) {
        qDebug() << "parse error";
        return;
    }
    auto obj = doc.object();
    if (obj.contains("version")) setVersion(obj["version"].toString());
    else setVersion("0.1.0");
    setErrorAmount(obj["error_amount"].toInt());
    setLastAmount(obj["last_amount"].toInt());
    setNewAmount(obj["new_amount"].toInt());
    setCurrentDataset(obj["current_dataset_name"].toString());
    reader.close();
    return;
}

void SGlobalSetting::initData(QString filename)
{
    QFile reader(filename);
    if (!reader.open(QIODevice::ReadOnly | QIODevice::Text)) {//处理空情况，创建一个名为 default 的空单词本
        auto wordbooks = SGlobalSetting::getInstance()->getDataset();
        CWordDataSet *dataset = new CWordDataSet();
        wordbooks->insert("default", dataset);
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
        dataset->parseFromJson(obj["dataset"].toArray(), mVersion);
        wordsbooks->insert(name, dataset);
    }
    reader.close();
    return;
}

void SGlobalSetting::initDict(QString filename)
{
    //qDebug() << filename;
    mDict = QSqlDatabase::addDatabase("QSQLITE");
    mDict.setDatabaseName(filename);
    if (mDict.open() == false) {
        qDebug() << "Error: can't open database";
        return;
    }
    /*
    qDebug() << "Dict load ok";
    QSqlQuery sql_query;
    sql_query.exec("SELECT id, word, definition, translation FROM stardict where word = \"hello\";");
    while (sql_query.next()) {
        int id = sql_query.value(0).toInt();
        QString word = sql_query.value(1).toString();
        QString definition = sql_query.value(2).toString();
        QString translation = sql_query.value(3).toString();
        qDebug() << id << word << definition << translation;
    }
    //*/
}

void SGlobalSetting::initFinish()
{
    mVersion = cCurrentVersion;
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
    obj["version"] = getVersion();
    obj["error_amount"] = getErrorAmount();
    obj["last_amount"] = getLastAmount();
    obj["new_amount"] = getNewAmount();
    obj["current_dataset_name"] = getCurrentDataset();
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

QString SGlobalSetting::findInDict(QString aWord)
{
    const QString cq1("SELECT * FROM stardict where word = \'"), cq2("\';");
    QSqlQuery sql_query;
    sql_query.exec(cq1 + aWord + cq2);
    if (sql_query.next()) {
        QString phonetic = sql_query.value(3).toString();
        QString definition ;//= sql_query.value(4).toString();
        QString translation = sql_query.value(5).toString();
        QString exchange = sql_query.value(12).toString();
        QString merged;
        if (!phonetic.isEmpty())
            merged += "\\" + phonetic + "\\";
        if (!translation.isEmpty()) {
            if (!merged.isEmpty()) merged += "\n";
            merged += translation;
        }
        if (!definition.isEmpty()) {
            if (!merged.isEmpty()) merged += "\n";
            merged += definition;
        }
        if (!exchange.isEmpty()) {
            if (!merged.isEmpty()) merged += "\n";
            merged += exchange;
        }
        return merged;
    }
    return "";
}
