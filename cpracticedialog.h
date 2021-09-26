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
    QPushButton *mOkButton, *mForgetButton, *mQuitButton, *mShowButton;
    QLabel *mKeyLabel, *mTranslationLabel;
    QGridLayout *mLayout;
    bool isShowtips;
public:
    CPracticeDialog(QWidget *parent, CWordData *aWorddata);
    ~CPracticeDialog();
private slots:
    void okButtonClicked();
    void forgetButtonClicked();
    void quitButtonClicked();
    void showTranslation();
};

#endif // CPRACTICEDIALOG_H
