#include "mainwindow.h"

const QString MainWindow::cWordsDataFileName = "words_data.json";

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    mMainLayout = new QVBoxLayout();
    mStartButton = new QPushButton();
    mAddNewWordButton = new QPushButton();
    mExitButton = new QPushButton();

    mStartButton -> setText(tr("start"));
    mAddNewWordButton -> setText(tr("add"));
    mExitButton -> setText(tr("exit"));

    mMainLayout->addWidget(mStartButton);
    mMainLayout->addWidget(mAddNewWordButton);
    mMainLayout->addWidget(mExitButton);
    setLayout(mMainLayout);

    setWindowTitle(tr("QWordWindow"));

    connect(mExitButton, SIGNAL(clicked()), this, SLOT(leaveApp()));
    connect(mAddNewWordButton, SIGNAL(clicked()), this, SLOT(addNewWord()));
    connect(mStartButton, SIGNAL(clicked()), this, SLOT(startNewPractice()));

    loadData();
}

MainWindow::~MainWindow()
{
    delete mMainLayout;
    delete mStartButton;
    delete mAddNewWordButton;
    delete mExitButton;
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
    mWordDataSet.parseFromJson(doc.array());
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
    QJsonDocument doc;
    doc.setArray(mWordDataSet.parseToJson());
    writer.write(doc.toJson());
    writer.close();
    return;
}

void MainWindow::leaveApp()
{
    saveData();
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

        mWordDataSet.append(data);
    }
    delete dialog;
    return;
}

void MainWindow::startNewPractice()
{
    CRandomQueue<CWordData*> queue = mWordDataSet.getWordsByArg(0, 0, 0), bp = queue;
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
