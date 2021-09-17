/*
定义与Json交互的基础接口
Date: 2021.9.17
Last update: 2021.9.17
Author: syc
*/
#ifndef IJSONIOBASE_H
#define IJSONIOBASE_H
#include <QJsonArray>

class IJsonIOBase
{
public:
    IJsonIOBase();
    virtual void parseFromJson(QJsonArray aJarray);
    virtual QJsonArray parseToJson();
};

#endif // IJSONIOBASE_H
