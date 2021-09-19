#ifndef CPRACTICEDIALOG_H
#define CPRACTICEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include "cworddata.h"
#include <QGridLayout>

class CPracticeDialog : public QDialog
{
    Q_OBJECT
    CWordData *mWorddata;
    QPushButton *mOkButton, *mTipsButton, *mQuitButton;
    QLabel *mKeyLabel, *mTranslationLabel;
    QGridLayout *mLayout;
    bool isShowtips;
public:
    CPracticeDialog(QWidget *parent, CWordData *aWorddata);
    ~CPracticeDialog();
private slots:
    void okButtonClicked();
    void tipsButtonClicked();
    void quitButtonClicked();
};

#endif // CPRACTICEDIALOG_H
