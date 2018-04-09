#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "ui_mainwindow.h"
#include "src/codeeditor.h"
#include "src/myhighlighter.h"
#include "src/typedef.h"
#include <QPushButton>
#include <QLabel>
#include "trienode.h"
class MainWindow : public QMainWindow,Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initDictionary();
public slots:
    void test_but_click();
    void test_();

private:
     CodeEditor *configEditor;
     QPushButton * but;
     QLabel * label_DisplayWord;
     MyHighLighter *highlighter;
     QStringList list;
     MultiTree * root;
     QStringList wordsList;
};

#endif // MAINWINDOW_H
