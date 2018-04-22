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
    this->setupUi(this);//���ؽ���
    configEditor = new CodeEditor();//�½�һ���༭��

    configEditor->setMode(EDIT);//�Ǹ��༭��Ϊ�ɱ༭״̬
    gridLayout->addWidget(configEditor);//���ò���

    connect(configEditor,&CodeEditor::signalGetCurrentWord,this,&MainWindow::Deal);//������̧����źźʹ�����ҵĲۺ�����������

    root = new MultiTree(0);//�½�һ��������Ķ���
    initDictionary();//�������ʼ��
}

MainWindow::~MainWindow()
{
    //QString str;
    //str = textEdt->toPlainText();
}

void MainWindow::initDictionary()
{
    QFile dataFile(QCoreApplication::applicationDirPath() + "/dictionary.txt");//���ôʵ��ļ���·��
    if (!dataFile.exists())//�жϴʵ��ļ��Ƿ����
    {
        QMessageBox::information(this,"Error!","Not Find Dictionary !",QMessageBox::Ok);//��������ڵ�����ʾ�򣬲�����
        return ;
    }

    if (dataFile.open(QFile::ReadOnly|QIODevice::Text))//�򿪴ʵ��ļ�
    {
        QTextStream data(&dataFile);//�����ļ��е�����ȫ����ȡ����������

        QString line;
        while (!data.atEnd())//���ж�ȡ�ı�����ȥ��ÿ�еĻس�
        {
            line = data.readLine();
            line.remove('\n');
            wordsList << line;//�����ʲ����б���
            root->Insert(line);//���뵽�������

            wordzz.insert({ { line.toStdString(),0 } });       //���л�ȡ��Ҳ�Ǻ��Ǹ�һ����
        }
    }
    return ;

}

void MainWindow::Deal()
{
    QTextCharFormat keywordFormat;//����һ���ַ���ɫ�ĸ�ʽΪ��ɫ
    keywordFormat.setForeground(Qt::black);

    QTextCharFormat conFormat;//����һ���ַ���ɫΪ��ɫ�ĸ�ʽ
    conFormat.setForeground(Qt::red);

    QTextCharFormat porFormat;//����һ���ַ���ɫΪ��ɫ�ĸ�ʽ
    porFormat.setForeground(Qt::blue);


    QTextCursor tc;//����һ�����
    tc =configEditor->textCursor();//��õ�ǰ������ڵ�λ��

    tc.setCharFormat(keywordFormat);//���õ�ǰ�ܹ�����ڵ��ַ�Ϊ��ɫ��ʽ



    QString strtemp = tc.block().text();//��õ�ǰ������ڵ��е��ַ���
    QString temp = strtemp.toLower();//���ַ���ת����Сд


    //test
    QTextLayout *pLayout = tc.block().layout();

    int nCurpos = tc.position() - tc.block().position();//��õ�ǰ�е�λ��
   // int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() + tc.block().firstLineNumber();
     // qDebug()<<nTextline << "," << nCurpos <<endl;

      //�ƶ���굽ĩβ
     tc.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,strtemp.length()-nCurpos);
     configEditor->setTextCursor(tc);//���ñ༭��Ĺ��Ϊ��ǰ�ƶ������λ��

    std::unordered_map<std::string, double>::const_iterator got = wordzz.find(temp.toStdString());//


    if (got != wordzz.end())//�ж��Ƿ���map���ҵ��õ���
    {
        for (int i = 0 ; i < strtemp.length(); i++)//�����ȫƥ�������еĵ���,������ɾ����ǰ�е��ַ�
         {
             tc.deletePreviousChar();
             configEditor->setFocus();
             configEditor->setTextCursor(tc);
         }
         tc.insertText(strtemp,keywordFormat);//Ȼ�����õ��ʶ�Ӧ����ɫ������������ַ���

         tc.setBlockCharFormat(conFormat);//����ΪĬ����ɫ
         return ;//����
    }
    else
    {
        for (int i = 0; i < wordsList.size(); i++)//ѭ����������������Ҳ���ƥ��
        {
           if (root->findPrefix(temp))//����ƥ��
            {
                for (int i = 0 ; i < strtemp.length(); i++)//�������ƥ�������еĵ���,������ɾ����ǰ�е��ַ�
                 {
                     tc.deletePreviousChar();
                     configEditor->setFocus();
                     configEditor->setTextCursor(tc);
                 }
                 tc.insertText(strtemp,porFormat);//ͬ��
                 tc.setBlockCharFormat(conFormat);
                 return ;
            }
        }
    }



    for (int i = 0 ; i < strtemp.length(); i++)//����Ȳ���ȫƥ��Ҳ������ƥ�䣬����ɾ���ַ���
    {
        tc.deletePreviousChar();
         configEditor->setFocus();
        configEditor->setTextCursor(tc);
    }
    tc.insertText(strtemp,conFormat);//Ȼ���Ժ�ɫ��ʽ���������
}




