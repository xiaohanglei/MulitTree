#ifndef TRIENODE_H
#define TRIENODE_H

#include <QObject>
#include <vector>
#define MAX 26

struct TrieNode
{
    // 以该节点为结尾的单词个数
    int count;
    TrieNode *next[MAX];
    TrieNode(int x) :count(x) {
        for (int i = 0; i < MAX; ++i) {
            next[i] = NULL;
        }//for
    }
};


class MultiTree
{
public:
    MultiTree(int x);
    TrieNode* getRoot()
    {
        return root;
    }

    // 插入
    void Insert( QString str);

    // 删除
    void Delete( QString str);

    // 查找
    bool Search(QString str);

    // 打印字典
    void PrintDic(TrieNode* root,std::vector<std::vector<char> > &words, std::vector<char> &word) ;

private:
    TrieNode* root;
};

#endif // TRIENODE_H
