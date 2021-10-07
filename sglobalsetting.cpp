#include "sglobalsetting.h"

SGlobalSetting *SGlobalSetting::mInstance = new SGlobalSetting();

void SGlobalSetting::initSetting(QJsonObject aObject)
{
    mInstance->setErrorAmount(aObject["error_amount"].toInt());
    mInstance->setLastAmount(aObject["last_amount"].toInt());
    mInstance->setNewAmount(aObject["new_amount"].toInt());
    mInstance->setCurrentDataset(aObject["current_dataset_name"].toString());
}

void SGlobalSetting::exit()
{
    auto p = getInstance()->getDataset();
    for (auto value : *p) delete value;
    delete mInstance;
}

SGlobalSetting::SGlobalSetting()
{

}

QJsonObject SGlobalSetting::parseToJson()
{
    QJsonObject ret;
    ret["error_amount"] = mInstance->getErrorAmount();
    ret["last_amount"] = mInstance->getLastAmount();
    ret["new_amount"] = mInstance->getNewAmount();
    ret["current_dataset_name"] = mInstance->getCurrentDataset();
    return ret;
}
