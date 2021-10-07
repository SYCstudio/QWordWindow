#include "caddnewdatasetdialog.h"

CAddNewDatasetDialog::CAddNewDatasetDialog(QWidget *parent, QString *aStr) : QDialog(parent), mStr(aStr)
{
    mNameLabel = new QLabel();
    mNameLabel->setText(tr("name"));

    mNameEdit = new QLineEdit();

    mOkButton = new QPushButton();
    mOkButton->setText(tr("ok"));
    mCancelButton = new QPushButton();
    mCancelButton->setText(tr("cancel"));

    mLayout = new QGridLayout();
    mLayout->addWidget(mNameLabel, 0, 0);
    mLayout->addWidget(mNameEdit, 0, 1);
    mLayout->addWidget(mOkButton, 1, 0);
    mLayout->addWidget(mCancelButton, 1, 1);

    setLayout(mLayout);

    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
}

CAddNewDatasetDialog::~CAddNewDatasetDialog()
{
    delete mNameLabel;
    delete mNameEdit;
    delete mOkButton; delete mCancelButton;
    delete mLayout;
}

void CAddNewDatasetDialog::okButtonClicked()
{
    if (mNameEdit->text().isEmpty()) {
        done(QDialog::Rejected);
        return;
    }
    QString name = mNameEdit->text();
    auto p = SGlobalSetting::getInstance()->getDataset();
    //qDebug() << name << p->count(name);
    if (p->count(name) == 0) {
        CWordDataSet *dataset;
        dataset = new CWordDataSet();
        p->insert(name, dataset);
        *mStr = name;
        done(QDialog::Accepted);
        return;
    }
    done(QDialog::Rejected);
}

void CAddNewDatasetDialog::cancelButtonClicked()
{
    done(QDialog::Rejected);
}
