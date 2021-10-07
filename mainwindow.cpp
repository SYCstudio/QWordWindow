#include "mainwindow.h"

const QString MainWindow::cWordsDataFileName = "words_data.json";
const QString MainWindow::cSettingFileName = "setting.json";

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    mMainLayout = new QVBoxLayout();
    mStartButton = new QPushButton();
    mAddNewWordButton = new QPushButton();
    mExitButton = new QPushButton();
    mSettingButton = new QPushButton();

    mStartButton -> setText(tr("start"));
    mAddNewWordButton -> setText(tr("add"));
    mExitButton -> setText(tr("exit"));
    mSettingButton -> setText(tr("setting"));

    mMainLayout->addWidget(mStartButton);
    mMainLayout->addWidget(mAddNewWordButton);
    mMainLayout->addWidget(mSettingButton);
    mMainLayout->addWidget(mExitButton);
    setLayout(mMainLayout);

    setWindowTitle(tr("QWordWindow"));

    connect(mExitButton, SIGNAL(clicked()), this, SLOT(leaveApp()));
    connect(mAddNewWordButton, SIGNAL(clicked()), this, SLOT(addNewWord()));
    connect(mStartButton, SIGNAL(clicked()), this, SLOT(startNewPractice()));
    connect(mSettingButton, SIGNAL(clicked()), this, SLOT(setting()));

    loadData();
    loadSetting();
}

MainWindow::~MainWindow()
{
    delete mMainLayout;
    delete mStartButton;
    delete mAddNewWordButton;
    delete mExitButton;
    delete mSettingButton;
}

void MainWindow::loadData()
{
    QFile reader(cWordsDataFileName);
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

void MainWindow::saveData()
{
    QFile writer(cWordsDataFileName);
    if (!writer.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "can't write file";
        return;
    }
    QJsonArray arr;
    QMap<QString, CWordDataSet*>* wordsbooks = SGlobalSetting::getInstance()->getDataset();
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

void MainWindow::leaveApp()
{
    saveData();
    saveSetting();
    qApp -> quit();
}

void MainWindow::addNewWord()
{
    CWordData *data;
    CAddNewWordDialog *dialog;
    data = new CWordData();
    dialog = new CAddNewWordDialog(this, data);
    int result = dialog->exec();
    qDebug() << result;
    if (result == QDialog::Accepted && !data -> getKey().isEmpty()) {
        QMap<QString, CWordDataSet*>* wordsbooks = SGlobalSetting::getInstance()->getDataset();
        QString name = SGlobalSetting::getInstance()->getCurrentDataset();
        wordsbooks->find(name).value()->append(data);
    }
    delete dialog;
    return;
}

void MainWindow::startNewPractice()
{
    CRandomQueue<CWordData*> queue = SGlobalSetting::getInstance()->getDataset()
            ->find(SGlobalSetting::getInstance()->getCurrentDataset()).value()->getWordsByArg(
                SGlobalSetting::getInstance()->getNewAmount(),
                SGlobalSetting::getInstance()->getErrorAmount(),
                SGlobalSetting::getInstance()->getLastAmount()),
            bp = queue;
    while (!queue.isEmpty()) {
        CWordData* p = queue.pop();
        CPracticeDialog *dialog;
        dialog = new CPracticeDialog(this, p);
        int ret = dialog->exec();
        delete dialog;
        if (ret == QDialog::Rejected) return;
        p->setTotalCount(p->getTotalCount() + 1);
        if (ret == 3) {
            p->setErrorCount(p->getErrorCount() + 1);
            queue.append(p);
        }
    }
    while (!bp.isEmpty()) {
        CWordData *p = bp.pop();
        p->setLastTime(QDateTime::currentDateTime());
        p->setPracticeTime(p->getPracticeCount() + 1);
    }
    return;
}

void MainWindow::loadSetting()
{
    QFile reader(cSettingFileName);
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
    SGlobalSetting::initSetting(doc.object());
    reader.close();
    return;
}

void MainWindow::saveSetting()
{
    QFile writer(cSettingFileName);
    if (!writer.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "can't write file";
        return;
    }
    QJsonDocument doc;
    doc.setObject(SGlobalSetting::getInstance() -> parseToJson());
    writer.write(doc.toJson());
    writer.close();
    return;
}

void MainWindow::setting()
{
    CSettingDialog *dialog;
    dialog = new CSettingDialog(this);
    int ret = dialog->exec();
    delete dialog;
    return;
}
