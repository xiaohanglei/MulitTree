#include "mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QTextCharFormat>
#include <fstream>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);
    configEditor = new CodeEditor();
    label_DisplayWord = new QLabel("");
    but = new QPushButton("testbutton");
    but->setVisible(false);
    configEditor->setMode(EDIT);
    gridLayout->addWidget(label_DisplayWord);
    gridLayout->addWidget(configEditor);
    gridLayout->addWidget(but);
    //but->setVisible(false);
   // highlighter = new MyHighLighter(configEditor->document());
    connect(but,&QPushButton::clicked,this,&MainWindow::test_but_click);
    connect(configEditor,&CodeEditor::signalGetCurrentWord,this,&MainWindow::test_);

    list << "lxh" << "hxl" << "xhl" <<"xlh" << "lhx";
    root = new MultiTree(0);
    initDictionary();
}

MainWindow::~MainWindow()
{
    //QString str;
    //str = textEdt->toPlainText();
}

void MainWindow::initDictionary()
{

    QString path =QCoreApplication::applicationDirPath() + "/dictionary.txt";
    QFile dataFile(QCoreApplication::applicationDirPath() + "/dictionary.txt");
    if (!dataFile.exists())
    {
        QMessageBox::information(this,"Error!","Not Find Dictionary !",QMessageBox::Ok);
    }

    if (dataFile.open(QFile::ReadOnly|QIODevice::Text))
    {
        QTextStream data(&dataFile);

        QString line;
        while (!data.atEnd())//逐行读取文本，并去除每行的回车
        {
            line = data.readLine();
            line.remove('\n');
            root->Insert(line);
            this->wordsList << line;
        }
    }
    return ;

}


void MainWindow::test_()
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::black);

    QTextCharFormat conFormat;
    conFormat.setForeground(Qt::red);

    QTextCharFormat porFormat;
    porFormat.setForeground(Qt::blue);


    QTextCursor tc;
    tc =configEditor->textCursor();

    tc.setCharFormat(keywordFormat);

    //移动光标到末尾

    tc.movePosition(QTextCursor::End);
   configEditor->setTextCursor(tc);

    QString strtemp = tc.block().text();
    QString temp = strtemp.toLower();

    for (int i = 0; i < wordsList.size(); i++)
    {
        int itemp = 0;
        //if (strtemp == wordsList.at(i))
        if (root->Search(temp))//w是否完全匹配
        {
           for (int i = 0 ; i < strtemp.length(); i++)
            {
                tc.deletePreviousChar();
                configEditor->setFocus();
                configEditor->setTextCursor(tc);
            }
            tc.insertText(strtemp,keywordFormat);

            tc.setBlockCharFormat(conFormat);
            return ;
        }
        else if (itemp = root->findPrefix(temp))//部分匹配
        {
            for (int i = 0 ; i < strtemp.length(); i++)
             {
                 tc.deletePreviousChar();
                 configEditor->setFocus();
                 configEditor->setTextCursor(tc);
             }
             tc.insertText(strtemp,porFormat);
             tc.setBlockCharFormat(conFormat);
             return ;
        }
    }

    for (int i = 0 ; i < strtemp.length(); i++)
    {
        tc.deletePreviousChar();
         configEditor->setFocus();
        configEditor->setTextCursor(tc);
    }
    tc.insertText(strtemp,conFormat);


}
void MainWindow::test_but_click()
{


    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::black);

    QTextCharFormat conFormat;
    conFormat.setForeground(Qt::red);

    QTextCharFormat porFormat;
    porFormat.setForeground(Qt::blue);


    QTextCursor tc;
    tc =configEditor->textCursor();

    tc.setCharFormat(keywordFormat);

    QString strtemp = tc.block().text();

    QString str = strtemp.split(" ").last();
    QMessageBox::information(this,"test",str,QMessageBox::Ok);
}





