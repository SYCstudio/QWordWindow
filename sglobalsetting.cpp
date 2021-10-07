#include "sglobalsetting.h"

SGlobalSetting *SGlobalSetting::mInstance = new SGlobalSetting();

void SGlobalSetting::init(QJsonObject aObject)
{
    mInstance->setErrorAmount(aObject["error_amount"].toInt());
    mInstance->setLastAmount(aObject["last_amount"].toInt());
    mInstance->setNewAmount(aObject["new_amount"].toInt());
}

void SGlobalSetting::exit()
{
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
    return ret;
}
