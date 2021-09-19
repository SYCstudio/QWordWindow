#include "cpracticedialog.h"

CPracticeDialog::CPracticeDialog(QWidget *parent, CWordData *aWorddata)
    : QDialog(parent), mWorddata(aWorddata), isShowtips(false)
{
    mLayout = new QGridLayout();
    mOkButton = new QPushButton();
    mTipsButton = new QPushButton();
    mQuitButton = new QPushButton();
    mKeyLabel = new QLabel();
    mTranslationLabel = new QLabel();

    mOkButton->setText(tr("ok"));
    mTipsButton->setText(tr("tips"));
    mQuitButton->setText(tr("quit"));

    mKeyLabel->setText(mWorddata->getKey());
    mKeyLabel->setStyleSheet("font-size: 25px; font-family: Ubuntu Mono;");
    mTranslationLabel->setText(mWorddata->getTranslation());
    mTranslationLabel->setVisible(false);

    mLayout->addWidget(mKeyLabel, 0, 0, 1, 3);
    mLayout->addWidget(mTranslationLabel, 1, 0, 1, 3);
    mLayout->addWidget(mOkButton, 2, 0);
    mLayout->addWidget(mTipsButton,2, 1);
    mLayout->addWidget(mQuitButton, 2, 2);
    setLayout(mLayout);

    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mTipsButton, SIGNAL(clicked()), this, SLOT(tipsButtonClicked()));
    connect(mQuitButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));
}

CPracticeDialog::~CPracticeDialog()
{
    delete mOkButton;
    delete mTipsButton;
    delete mQuitButton;
    delete mKeyLabel;
    delete mTranslationLabel;
    delete mLayout;
}

void CPracticeDialog::okButtonClicked()
{
    if (isShowtips) done(3);
    else done(QDialog::Accepted);
}

void CPracticeDialog::tipsButtonClicked()
{
    isShowtips = true;
    mTranslationLabel->setVisible(true);
    mTipsButton->setEnabled(false);
}

void CPracticeDialog::quitButtonClicked()
{
    done(QDialog::Rejected);
}
