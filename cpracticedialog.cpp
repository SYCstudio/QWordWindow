#include "cpracticedialog.h"

CPracticeDialog::CPracticeDialog(QWidget *parent, CWordData *aWorddata)
    : QDialog(parent), mWorddata(aWorddata), isShowtips(false)
{
    mLayout = new QGridLayout();
    mOkButton = new QPushButton();
    mForgetButton = new QPushButton();
    mQuitButton = new QPushButton();
    mShowButton = new QPushButton();
    mKeyLabel = new QLabel();
    mTranslationLabel = new QLabel();

    mOkButton->setText(tr("ok"));
    mForgetButton->setText(tr("forget"));
    mQuitButton->setText(tr("quit"));
    mShowButton->setText(tr("show"));

    mKeyLabel->setText(mWorddata->getKey());
    mKeyLabel->setStyleSheet("font-size: 25px; font-family: Ubuntu Mono;");
    mTranslationLabel->setText(mWorddata->getTranslation());
    mTranslationLabel->setVisible(false);

    mLayout->addWidget(mKeyLabel, 0, 0, 1, 4);
    mLayout->addWidget(mTranslationLabel, 1, 0, 1, 4);
    mLayout->addWidget(mShowButton, 2, 0);
    mLayout->addWidget(mOkButton, 2, 1);
    mLayout->addWidget(mForgetButton,2, 2);
    mLayout->addWidget(mQuitButton, 2, 3);
    setLayout(mLayout);

    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(mForgetButton, SIGNAL(clicked()), this, SLOT(forgetButtonClicked()));
    connect(mQuitButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));
    connect(mShowButton, SIGNAL(clicked()), this, SLOT(showTranslation()));
}

CPracticeDialog::~CPracticeDialog()
{
    delete mOkButton;
    delete mForgetButton;
    delete mQuitButton;
    delete mKeyLabel;
    delete mTranslationLabel;
    delete mLayout;
    delete mShowButton;
}

void CPracticeDialog::okButtonClicked()
{
    done(QDialog::Accepted);
}

void CPracticeDialog::forgetButtonClicked()
{
    done(3);
}

void CPracticeDialog::quitButtonClicked()
{
    done(QDialog::Rejected);
}

void CPracticeDialog::showTranslation()
{
    mTranslationLabel->setVisible(true);
    mShowButton->setEnabled(false);
}
