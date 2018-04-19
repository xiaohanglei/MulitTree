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
#include <unordered_map>
#include <string>
class MainWindow : public QMainWindow,Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initDictionary();
public slots:
    void Deal();

private:
     CodeEditor *configEditor;

     QStringList list;
     MultiTree * root;
     QStringList wordsList;
     std::unordered_map<std::string, double>wordzz,nonezz;

};

#endif // MAINWINDOW_H
