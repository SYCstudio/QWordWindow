#ifndef CADDNEWDATASET_H
#define CADDNEWDATASET_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include "sglobalsetting.h"

class CAddNewDatasetDialog : public QDialog
{
    Q_OBJECT
    QString *mStr;
    QLabel *mNameLabel;
    QLineEdit *mNameEdit;
    QPushButton *mOkButton, *mCancelButton;
    QGridLayout *mLayout;
public:
    CAddNewDatasetDialog(QWidget *parent, QString *aStr);
    ~CAddNewDatasetDialog();

public slots:
    void okButtonClicked();
    void cancelButtonClicked();

};

#endif // CADDNEWDATASET_H
