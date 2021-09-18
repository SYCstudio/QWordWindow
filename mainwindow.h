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

class MainWindow : public QWidget
{
    Q_OBJECT

    QPushButton *mStartButton, *mAddNewWordButton, *mExitButton;
    QVBoxLayout *mMainLayout;
    CWordDataSet mWordDataSet;
    static const QString cWordsDataFileName;

    void saveData();
    void loadData();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void leaveApp();
    void addNewWord();
};
#endif // MAINWINDOW_H
