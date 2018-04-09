#include "mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);
    configEditor = new CodeEditor();
    label_DisplayWord = new QLabel("");
    but = new QPushButton("testbutton");
    configEditor->setMode(EDIT);
    gridLayout->addWidget(label_DisplayWord);
    gridLayout->addWidget(configEditor);
    gridLayout->addWidget(but);
   // highlighter = new MyHighLighter(configEditor->document());
    connect(but,&QPushButton::clicked,this,&MainWindow::test_but_click);
    connect(configEditor,&CodeEditor::signalGetCurrentWord,this,&MainWindow::test_);

    list << "lxh" << "hxl" << "xhl" <<"xlh" << "lhx";
}

MainWindow::~MainWindow()
{
    //QString str;
    //str = textEdt->toPlainText();
}


void MainWindow::test_()
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::red);

    QTextCharFormat conFormat;
    conFormat.setForeground(Qt::black);


    QTextCursor tc;
    tc =configEditor->textCursor();

    tc.setCharFormat(keywordFormat);
   // tc.insertText("lxh",keywordFormat);
    //tc.deleteChar();

    QString strtemp = tc.block().text();

    for (int i = 0; i < list.size(); i++)
    {
        if (strtemp == list.at(i))
        {
            for (int i = 0 ; i < strtemp.length(); i++)
            {
                tc.deletePreviousChar();
                configEditor->setTextCursor(tc);
            }
            tc.insertText(strtemp,keywordFormat);
            configEditor->setFocus();
            break;
        }
    }
    tc.setBlockCharFormat(conFormat);

}
void MainWindow::test_but_click()
{
    //
    //QString content = configEditor->document()->findBlockByLineNumber(1).text();
    //QMessageBox::information(this,QString::fromLocal8Bit("²âÊÔ°´Å¥"),content,QMessageBox::Ok);
    //QMessageBox::information(this,QString::fromLocal8Bit("²âÊÔ°´Å¥"),configEditor->getCurrRowValue(),QMessageBox::Ok);
    //label_DisplayWord->setText(configEditor->getCurrRowValue());

//    QTextDocument * dd = configEditor->document();

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::red);

    QTextCharFormat conFormat;
    conFormat.setForeground(Qt::black);


//    dd->setPlainText("gtttttttttttttttttt");

//    QFont font;
//    font.setUnderline(true);
//     highlighter->test(1,3,keywordFormat);


    QTextCursor tc;
    tc =configEditor->textCursor();

    tc.setCharFormat(keywordFormat);
   // tc.insertText("lxh",keywordFormat);
    //tc.deleteChar();

    QString strtemp = tc.block().text();
    for (int i = 0 ; i < strtemp.length(); i++)
    {
        tc.deletePreviousChar();
        configEditor->setTextCursor(tc);
    }
    tc.insertText(strtemp,keywordFormat);
    configEditor->setFocus();

    //tc.insertText("a",conFormat);// tc.deletePreviousChar();



   // QTextBlockFormat tempformat;
//    tempformat.setForeground(Qt::red);
   // tc.setBlockFormat(tempformat);
    //QMessageBox::information(this,QString::fromLocal8Bit("²âÊÔ°´Å¥"),QString::number(c,10),QMessageBox::Ok);

//    label_DisplayWord->setText(configEditor->getCurrRowValue());
//    QFont font;
//    font.setUnderline(true);
//    configEditor->setFont(font);

}





