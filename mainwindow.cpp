#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);
    configEditor = new CodeEditor();
    but = new QPushButton("testbutton");
    configEditor->setMode(EDIT);
    gridLayout->addWidget(configEditor);
    gridLayout->addWidget(but);
   // MyHighLighter *highlighter = new MyHighLighter(configEditor->document());
    connect(but,&QPushButton::clicked,this,&MainWindow::test_but_click);
}

MainWindow::~MainWindow()
{
    //QString str;
    //str = textEdt->toPlainText();

}

void MainWindow::test_but_click()
{
    //
    //QString content = configEditor->document()->findBlockByLineNumber(1).text();
    //QMessageBox::information(this,QString::fromLocal8Bit("²âÊÔ°´Å¥"),content,QMessageBox::Ok);
    QMessageBox::information(this,QString::fromLocal8Bit("²âÊÔ°´Å¥"),configEditor->getCurrRowValue(),QMessageBox::Ok);
}





