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
    //读取文本
//    std::ifstream in("dictionary.txt");
//    QString line;
//    std::string temp;
//    while (std::getline(in, temp)) // line中不包括每行的换行符
//    {
//            line = QString::fromStdString(temp);
//          root->Insert(line);
//            //cout << line<<endl;
//    }

    QFile dataFile("C:/Users/Administrator/Desktop/build-aweSomeEditorhiahia-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/dictionary.txt");

    if (dataFile.open(QFile::ReadOnly|QIODevice::Text))
    {
        QTextStream data(&dataFile);

        QString line;
        while (!data.atEnd())//逐行读取文本，并去除每行的回车
        {
            line = data.readLine();
            line.remove('\n');
            //root->Insert(line);
            this->wordsList << line;
        }
    }
    return ;

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

    for (int i = 0; i < wordsList.size(); i++)
    {
        if (strtemp == wordsList.at(i))
        //if (root->Search(strtemp))
        {
            for (int i = 0 ; i < strtemp.length(); i++)
            {
                tc.deletePreviousChar();
                configEditor->setTextCursor(tc);
            }
            tc.insertText(strtemp,keywordFormat);
            configEditor->setFocus();
            tc.setBlockCharFormat(conFormat);
            return ;
        }
    }

    for (int i = 0 ; i < strtemp.length(); i++)
    {
        tc.deletePreviousChar();
        configEditor->setTextCursor(tc);
    }
    tc.insertText(strtemp,conFormat);
    configEditor->setFocus();

}
void MainWindow::test_but_click()
{
    //
    //QString content = configEditor->document()->findBlockByLineNumber(1).text();
    //QMessageBox::information(this,QString::fromLocal8Bit("测试按钮"),content,QMessageBox::Ok);
    //QMessageBox::information(this,QString::fromLocal8Bit("测试按钮"),configEditor->getCurrRowValue(),QMessageBox::Ok);
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
    //QMessageBox::information(this,QString::fromLocal8Bit("测试按钮"),QString::number(c,10),QMessageBox::Ok);

//    label_DisplayWord->setText(configEditor->getCurrRowValue());
//    QFont font;
//    font.setUnderline(true);
//    configEditor->setFont(font);

}





