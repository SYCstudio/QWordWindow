#ifndef CSETTINGDIALOG_H
#define CSETTINGDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include "sglobalsetting.h"
#include "caddnewdatasetdialog.h"

class CSettingDialog : public QDialog
{
    Q_OBJECT
    QGridLayout *mLayout;
    QLabel *mNewLabel, *mErrorLabel, *mDateLabel, *mDatasetSelectorLabel;
    QLineEdit *mNewEdit, *mErrorEdit, *mDateEdit;
    QComboBox *mDatasetSelectorBox;
    QPushButton *mOkButton, *mCancelButton, *mAddNewDatasetButton;
public:
    CSettingDialog(QWidget *parent);
    ~CSettingDialog();
public slots:
    void okButtonClicked();
    void cancelButtonClicked();
    void addNewDatasetButtonClicked();
};

#endif // CSETTINGDIALOG_H
