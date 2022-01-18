#include "caddnewworddialog.h"

CAddNewWordDialog::CAddNewWordDialog(QWidget *parrent, CWordData *aWordData)
    : QDialog(parrent), mWordData(aWordData)
{
    mLayout = new QGridLayout();
    mKeyLabel = new QLabel(tr("Key:"));
    mKeyEdit = new QLineEdit();
    mAdditionChecker = new QCheckBox("Addition:");
    mDictInfo = new QLabel();
    mAdditionInfoEdit = new QTextEdit();
    mOkButton = new QPushButton(tr("OK"));
    mCancelButton = new QPushButton(tr("Cancel"));
    mDictChecker = new QCheckBox(tr("from dict:"));

    mDictChecker->setCheckState(Qt::Checked);
    mAdditionChecker->setCheckState(Qt::Unchecked);

    mLayout->addWidget(mKeyLabel, 0, 0);
    mLayout->addWidget(mKeyEdit, 0, 1);
    mLayout->addWidget(mDictChecker, 2, 0);
    mLayout->addWidget(mDictInfo, 2, 1);
    mLayout->addWidget(mAdditionChecker, 1, 0);
    mLayout->addWidget(mAdditionInfoEdit, 1, 1);
    mLayout->addWidget(mOkButton, 3, 0);
    mLayout->addWidget(mCancelButton, 3, 1);

    setLayout(mLayout);

    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(mKeyEdit, SIGNAL(textChanged(QString)), this, SLOT(refresh(QString)));
}

CAddNewWordDialog::~CAddNewWordDialog()
{
    delete mLayout;
    delete mKeyLabel;
    delete mKeyEdit;
    delete mOkButton;
    delete mCancelButton;
    delete mAdditionChecker;
    delete mDictInfo;
    delete mAdditionInfoEdit;
    delete mDictChecker;
}

void CAddNewWordDialog::okButtonClicked()
{
    mWordData->setKey(mKeyEdit->text());
    mWordData->setUseDictInfo(mDictChecker->isChecked());
    mWordData->setUseAddition(mAdditionChecker->isChecked());
    if (mAdditionChecker->isChecked())
        mWordData->setAddition(mAdditionInfoEdit->toPlainText());
    mWordData->setCreateTime(QDateTime::currentDateTime());
    mWordData->setTotalCount(0);
    mWordData->setErrorCount(0);
    mWordData->setPracticeTime(0);
    done(QDialog::Accepted);
}

void CAddNewWordDialog::cancelButtonClicked()
{
    done(QDialog::Rejected);
}

void CAddNewWordDialog::refresh(const QString &aWord)
{
    if (aWord.isEmpty()) return;
    QString info = SGlobalSetting::getInstance()->findInDict(aWord);
    if (!info.isEmpty()){
        mDictInfo -> setText(info);
    }
    return;
}
