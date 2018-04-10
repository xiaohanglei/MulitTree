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

    QString strtemp = tc.block().text();

    for (int i = 0; i < wordsList.size(); i++)
    {
        int itemp = 0;
        //if (strtemp == wordsList.at(i))
        if (root->Search(strtemp))//w是否完全匹配
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
        else if (itemp = root->findPrefix(strtemp))//部分匹配
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


    QTextDocument * dd = configEditor->document();

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::red);

    QTextCharFormat conFormat;
    conFormat.setForeground(Qt::black);


    QTextCursor tc;
    tc =configEditor->textCursor();
    int a = tc.columnNumber();

    int position =dd->findBlockByNumber ( 2-1 ).position();
    tc.setPosition(position,QTextCursor::MoveAnchor);
    configEditor->setFocus();
    configEditor->setTextCursor( tc );
}





