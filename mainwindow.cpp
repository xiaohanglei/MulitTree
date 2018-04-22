#include "mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QTextCharFormat>
#include <fstream>
#include <QTextStream>
#include <QFile>
#include <unordered_map>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setupUi(this);//加载界面
    configEditor = new CodeEditor();//新建一个编辑框

    configEditor->setMode(EDIT);//是个编辑框为可编辑状态
    gridLayout->addWidget(configEditor);//设置布局

    connect(configEditor,&CodeEditor::signalGetCurrentWord,this,&MainWindow::Deal);//将键盘抬起的信号和处理查找的槽函数进行连接

    root = new MultiTree(0);//新建一个多叉树的对象
    initDictionary();//多叉树初始化
}

MainWindow::~MainWindow()
{
    //QString str;
    //str = textEdt->toPlainText();
}

void MainWindow::initDictionary()
{
    QFile dataFile(QCoreApplication::applicationDirPath() + "/dictionary.txt");//设置词典文件的路径
    if (!dataFile.exists())//判断词典文件是否存在
    {
        QMessageBox::information(this,"Error!","Not Find Dictionary !",QMessageBox::Ok);//如果不存在弹出提示框，并返回
        return ;
    }

    if (dataFile.open(QFile::ReadOnly|QIODevice::Text))//打开词典文件
    {
        QTextStream data(&dataFile);//将该文件中的内容全部读取到文字留种

        QString line;
        while (!data.atEnd())//逐行读取文本，并去除每行的回车
        {
            line = data.readLine();
            line.remove('\n');
            wordsList << line;//将单词插入列表中
            root->Insert(line);//插入到多叉树中

            wordzz.insert({ { line.toStdString(),0 } });       //逐行获取，也是和那个一样的
        }
    }
    return ;

}

void MainWindow::Deal()
{
    QTextCharFormat keywordFormat;//定义一个字符颜色的格式为黑色
    keywordFormat.setForeground(Qt::black);

    QTextCharFormat conFormat;//定义一个字符颜色为红色的格式
    conFormat.setForeground(Qt::red);

    QTextCharFormat porFormat;//定义一个字符颜色为蓝色的格式
    porFormat.setForeground(Qt::blue);


    QTextCursor tc;//定义一个光标
    tc =configEditor->textCursor();//获得当前光标所在的位置

    tc.setCharFormat(keywordFormat);//设置当前管光标所在的字符为黑色格式



    QString strtemp = tc.block().text();//获得当前光标所在的行的字符串
    QString temp = strtemp.toLower();//将字符串转换成小写


    //test
    QTextLayout *pLayout = tc.block().layout();

    int nCurpos = tc.position() - tc.block().position();//获得当前列的位置
   // int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() + tc.block().firstLineNumber();
     // qDebug()<<nTextline << "," << nCurpos <<endl;

      //移动光标到末尾
     tc.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,strtemp.length()-nCurpos);
     configEditor->setTextCursor(tc);//设置编辑框的光标为当前移动过后的位置

    std::unordered_map<std::string, double>::const_iterator got = wordzz.find(temp.toStdString());//


    if (got != wordzz.end())//判断是否在map中找到该单词
    {
        for (int i = 0 ; i < strtemp.length(); i++)//如果完全匹配多叉树中的单词,则依次删除当前行的字符
         {
             tc.deletePreviousChar();
             configEditor->setFocus();
             configEditor->setTextCursor(tc);
         }
         tc.insertText(strtemp,keywordFormat);//然后设置单词对应的颜色，并重新输出字符串

         tc.setBlockCharFormat(conFormat);//设置为默认颜色
         return ;//结束
    }
    else
    {
        for (int i = 0; i < wordsList.size(); i++)//循环遍历多叉树，查找部分匹配
        {
           if (root->findPrefix(temp))//部分匹配
            {
                for (int i = 0 ; i < strtemp.length(); i++)//如果部分匹配多叉树中的单词,则依次删除当前行的字符
                 {
                     tc.deletePreviousChar();
                     configEditor->setFocus();
                     configEditor->setTextCursor(tc);
                 }
                 tc.insertText(strtemp,porFormat);//同上
                 tc.setBlockCharFormat(conFormat);
                 return ;
            }
        }
    }



    for (int i = 0 ; i < strtemp.length(); i++)//如果既不完全匹配也不部分匹配，则先删除字符，
    {
        tc.deletePreviousChar();
         configEditor->setFocus();
        configEditor->setTextCursor(tc);
    }
    tc.insertText(strtemp,conFormat);//然后以红色格式，重新输出
}




