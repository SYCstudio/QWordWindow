#ifndef CADDNEWWORDDIALOG_H
#define CADDNEWWORDDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "cworddata.h"

class CAddNewWordDialog : public QDialog
{
    Q_OBJECT
    CWordData *mWordData;
    QPushButton *mOkButton, *mCancelButton;
    QLabel *mKeyLabel, *mTranslationLabel;
    QLineEdit *mKeyEdit, *mTranslationEdit;
    QGridLayout *mLayout;
public:
    CAddNewWordDialog(QWidget *parrent, CWordData *aWordData);
    ~CAddNewWordDialog();
public slots:
    void okButtonClicked();
    void cancelButtonClicked();
};

#endif // CADDNEWWORDDIALOG_H
