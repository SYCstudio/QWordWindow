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
    mSaveButton = new QPushButton();

    mStartButton -> setText(tr("start"));
    mAddNewWordButton -> setText(tr("add"));
    mExitButton -> setText(tr("exit"));
    mSettingButton -> setText(tr("setting"));
    mSaveButton -> setText(tr("save"));

    mInfoLabel = new QLabel();

    mMainLayout->addWidget(mInfoLabel);
    mMainLayout->addWidget(mStartButton);
    mMainLayout->addWidget(mAddNewWordButton);
    mMainLayout->addWidget(mSettingButton);
    mMainLayout->addWidget(mSaveButton);
    mMainLayout->addWidget(mExitButton);
    setLayout(mMainLayout);

    setWindowTitle(tr("QWordWindow"));

    connect(mExitButton, SIGNAL(clicked()), this, SLOT(leaveApp()));
    connect(mAddNewWordButton, SIGNAL(clicked()), this, SLOT(addNewWord()));
    connect(mStartButton, SIGNAL(clicked()), this, SLOT(startNewPractice()));
    connect(mSettingButton, SIGNAL(clicked()), this, SLOT(setting()));
    connect(mSaveButton, SIGNAL(clicked()), this, SLOT(save()));

    load();
    return;
}

MainWindow::~MainWindow()
{
    delete mMainLayout;
    delete mStartButton;
    delete mAddNewWordButton;
    delete mExitButton;
    delete mSettingButton;
    delete mInfoLabel;
}

void MainWindow::leaveApp()
{
    save();
    SGlobalSetting::getInstance()->exit();
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
    refreshInfo();
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
    queue.forceMove();
    while (!queue.isEmpty()) {
        CWordData* p = queue.pop();
        CPracticeDialog *dialog;
        dialog = new CPracticeDialog(this, p,
                                     QString::number(bp.getSize() - queue.getSize())
                                     + "/" + QString::number(bp.getSize()));
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
        //p->setLastTime(QDateTime::currentDateTime());
        p->setPracticeTime(p->getPracticeCount() + 1);
    }
    refreshInfo();
    return;
}

void MainWindow::setting()
{
    CSettingDialog *dialog;
    dialog = new CSettingDialog(this);
    (void) dialog->exec();
    delete dialog;
    refreshInfo();
    return;
}

void MainWindow::refreshInfo()
{
    QString name = SGlobalSetting::getInstance()->getCurrentDataset();
    auto p = SGlobalSetting::getInstance()->getDataset()->find(name).value();
    int unlearned = p->getUnLearnedAmount();
    int total = p->getSize();
    QString label = name + ":" + QString::number(total - unlearned) + "/" + QString::number(total);
    mInfoLabel->setText(label);
    return;
}

void MainWindow::load()
{
    SGlobalSetting::getInstance()->initSetting(cSettingFileName);
    SGlobalSetting::getInstance()->initData(cWordsDataFileName);
    SGlobalSetting::getInstance()->initFinish();
    refreshInfo();
    return;
}

void MainWindow::save()
{
    SGlobalSetting::getInstance()->saveData(cWordsDataFileName);
    SGlobalSetting::getInstance()->saveSetting(cSettingFileName);
    refreshInfo();
    return;
}
