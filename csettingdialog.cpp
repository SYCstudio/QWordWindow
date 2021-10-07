#include "csettingdialog.h"

CSettingDialog::CSettingDialog(QWidget *parent) : QDialog(parent)
{
    mNewLabel = new QLabel();
    mNewLabel->setText(tr("new:"));
    mErrorLabel = new QLabel();
    mErrorLabel->setText(tr("error:"));
    mDateLabel = new QLabel();
    mDateLabel->setText(tr("date:"));

    mNewEdit = new QLineEdit();
    mNewEdit->setText(QString::number(SGlobalSetting::getInstance()->getNewAmount()));
    mErrorEdit = new QLineEdit();
    mErrorEdit->setText(QString::number(SGlobalSetting::getInstance()->getErrorAmount()));
    mDateEdit = new QLineEdit();
    mDateEdit->setText(QString::number(SGlobalSetting::getInstance()->getLastAmount()));

    mOkButton = new QPushButton();
    mOkButton->setText(tr("ok"));
    mCancelButton = new QPushButton();
    mCancelButton->setText(tr("cancel"));

    mLayout = new QGridLayout();

    mLayout->addWidget(mNewLabel, 0, 0);
    mLayout->addWidget(mNewEdit, 0, 1);
    mLayout->addWidget(mErrorLabel, 1, 0);
    mLayout->addWidget(mErrorEdit, 1, 1);
    mLayout->addWidget(mDateLabel, 2, 0);
    mLayout->addWidget(mDateEdit, 2, 1);
    mLayout->addWidget(mOkButton, 3, 0);
    mLayout->addWidget(mCancelButton, 3, 1);

    setLayout(mLayout);

    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
}

CSettingDialog::~CSettingDialog()
{
    delete mNewLabel; delete mErrorLabel; delete mDateLabel;
    delete mNewEdit; delete mErrorEdit; delete mDateEdit;
    delete mOkButton; delete mCancelButton;
    delete mLayout;
}

void CSettingDialog::okButtonClicked()
{
    SGlobalSetting::getInstance() -> setNewAmount(mNewEdit->text().toInt());
    SGlobalSetting::getInstance() -> setErrorAmount(mErrorEdit->text().toInt());
    SGlobalSetting::getInstance() -> setLastAmount(mDateEdit->text().toInt());
    done(QDialog::Accepted);
}

void CSettingDialog::cancelButtonClicked()
{
    done(QDialog::Rejected);
}
