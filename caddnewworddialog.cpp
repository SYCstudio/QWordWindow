#include "caddnewworddialog.h"

CAddNewWordDialog::CAddNewWordDialog(QWidget *parrent, CWordData *aWordData)
    : QDialog(parrent), mWordData(aWordData)
{
    mLayout = new QGridLayout();
    mKeyLabel = new QLabel();
    mKeyEdit = new QLineEdit();
    mTranslationLabel = new QLabel();
    mTranslationEdit = new QLineEdit();
    mOkButton = new QPushButton();
    mCancelButton = new QPushButton();

    mLayout->addWidget(mKeyLabel, 0, 0);
    mLayout->addWidget(mKeyEdit, 0, 1);
    mLayout->addWidget(mTranslationLabel, 1, 0);
    mLayout->addWidget(mTranslationEdit, 1, 1);
    mLayout->addWidget(mOkButton, 2, 0);
    mLayout->addWidget(mCancelButton, 2, 1);

    setLayout(mLayout);

    mKeyLabel->setText(tr("Key:"));
    mTranslationLabel->setText(tr("Translation:"));
    mOkButton->setText(tr("OK"));
    mCancelButton->setText(tr("Cancel"));

    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
}

CAddNewWordDialog::~CAddNewWordDialog()
{
    delete mLayout;
    delete mKeyLabel;
    delete mKeyEdit;
    delete mTranslationLabel;
    delete mTranslationEdit;
    delete mOkButton;
    delete mCancelButton;
}

void CAddNewWordDialog::okButtonClicked()
{
    mWordData->setKey(mKeyEdit->text());
    mWordData->setTranslation(mTranslationEdit->text());
    done(QDialog::Accepted);
}

void CAddNewWordDialog::cancelButtonClicked()
{
    done(QDialog::Rejected);
}
