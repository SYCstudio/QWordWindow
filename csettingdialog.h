#ifndef CSETTINGDIALOG_H
#define CSETTINGDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include "sglobalsetting.h"

class CSettingDialog : public QDialog
{
    Q_OBJECT
    QGridLayout *mLayout;
    QLabel *mNewLabel, *mErrorLabel, *mDateLabel;
    QLineEdit *mNewEdit, *mErrorEdit, *mDateEdit;
    QPushButton *mOkButton, *mCancelButton;
public:
    CSettingDialog(QWidget *parent);
    ~CSettingDialog();
public slots:
    void okButtonClicked();
    void cancelButtonClicked();
};

#endif // CSETTINGDIALOG_H
