/*
 * 整个程序的主窗口
 * Date: 2021.9.17
 * Last update: 2021.9.18
 * Author: syc
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QApplication>
#include "cworddataset.h"
#include "caddnewworddialog.h"
#include "crandomqueue.h"
#include "cpracticedialog.h"
#include "sglobalsetting.h"
#include "csettingdialog.h"

class MainWindow : public QWidget
{
    Q_OBJECT

    QLabel *mInfoLabel;
    QPushButton *mStartButton, *mAddNewWordButton, *mExitButton, *mSettingButton;
    QVBoxLayout *mMainLayout;
    //CWordDataSet mWordDataSet;
    //QMap<QString, CWordDataSet*> mDataSet;
    static const QString cWordsDataFileName;
    static const QString cSettingFileName;

    void saveData();
    void loadData();
    void saveSetting();
    void loadSetting();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void leaveApp();
    void addNewWord();
    void startNewPractice();
    void setting();
    void refreshInfo();
};
#endif // MAINWINDOW_H
