#ifndef CADDNEWWORDDIALOG_H
#define CADDNEWWORDDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPlainTextEdit>
#include <QCheckBox>
#include "cworddata.h"
#include "sglobalsetting.h"

class CAddNewWordDialog : public QDialog
{
    Q_OBJECT
    CWordData *mWordData;
    QPushButton *mOkButton, *mCancelButton;
    QLabel *mKeyLabel, *mDictInfo;
    QLineEdit *mKeyEdit;
    QTextEdit *mAdditionInfoEdit;
    QGridLayout *mLayout;
    QCheckBox *mDictChecker, *mAdditionChecker;
public:
    CAddNewWordDialog(QWidget *parrent, CWordData *aWordData);
    ~CAddNewWordDialog();
public slots:
    void okButtonClicked();
    void cancelButtonClicked();
    void refresh(const QString &aWord);
};

#endif // CADDNEWWORDDIALOG_H
