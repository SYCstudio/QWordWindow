#include "csettingdialog.h"

CSettingDialog::CSettingDialog(QWidget *parent) : QDialog(parent)
{
    mNewLabel = new QLabel();
    mNewLabel->setText(tr("new:"));
    mErrorLabel = new QLabel();
    mErrorLabel->setText(tr("error:"));
    mDateLabel = new QLabel();
    mDateLabel->setText(tr("date:"));
    mDatasetSelectorLabel = new QLabel();
    mDatasetSelectorLabel->setText(tr("dataset"));

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
    mAddNewDatasetButton = new QPushButton();
    mAddNewDatasetButton->setText("+");

    mDatasetSelectorBox = new QComboBox();
    int currentIndex;
    auto p = SGlobalSetting::getInstance()->getDataset();
    for (auto it = p->begin(); it != p->end(); it++) {
        mDatasetSelectorBox->addItem(it.key());
        if (it.key() == SGlobalSetting::getInstance()->getCurrentDataset())
            currentIndex = mDatasetSelectorBox->count() - 1;
    }
    mDatasetSelectorBox->setCurrentIndex(currentIndex);

    mLayout = new QGridLayout();

    mLayout->addWidget(mNewLabel, 0, 0);
    mLayout->addWidget(mNewEdit, 0, 1);
    mLayout->addWidget(mErrorLabel, 1, 0);
    mLayout->addWidget(mErrorEdit, 1, 1);
    mLayout->addWidget(mDateLabel, 2, 0);
    mLayout->addWidget(mDateEdit, 2, 1);
    mLayout->addWidget(mDatasetSelectorLabel, 3, 0);
    mLayout->addWidget(mDatasetSelectorBox, 3, 1);
    mLayout->addWidget(mAddNewDatasetButton, 3, 2);
    mLayout->addWidget(mOkButton, 4, 0);
    mLayout->addWidget(mCancelButton, 4, 1);

    setLayout(mLayout);

    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(mAddNewDatasetButton, SIGNAL(clicked()), this, SLOT(addNewDatasetButtonClicked()));
}

CSettingDialog::~CSettingDialog()
{
    delete mNewLabel; delete mErrorLabel; delete mDateLabel; delete mDatasetSelectorLabel;
    delete mNewEdit; delete mErrorEdit; delete mDateEdit;
    delete mOkButton; delete mCancelButton; delete mAddNewDatasetButton;
    delete mLayout;
    delete mDatasetSelectorBox;
}

void CSettingDialog::okButtonClicked()
{
    SGlobalSetting::getInstance() -> setNewAmount(mNewEdit->text().toInt());
    SGlobalSetting::getInstance() -> setErrorAmount(mErrorEdit->text().toInt());
    SGlobalSetting::getInstance() -> setLastAmount(mDateEdit->text().toInt());
    SGlobalSetting::getInstance() -> setCurrentDataset(mDatasetSelectorBox->currentText());
    done(QDialog::Accepted);
}

void CSettingDialog::cancelButtonClicked()
{
    done(QDialog::Rejected);
}

void CSettingDialog::addNewDatasetButtonClicked()
{
    CAddNewDatasetDialog *dialog;
    QString name;
    dialog = new CAddNewDatasetDialog(this, &name);
    int ret = dialog->exec();
    qDebug() << ret << name;
    if (ret == QDialog::Accepted) {
        qDebug() << name;
        mDatasetSelectorBox->addItem(name);
        mDatasetSelectorBox->setCurrentIndex(mDatasetSelectorBox->count() - 1);
    }
    return;
}
