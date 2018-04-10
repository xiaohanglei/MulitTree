#ifndef TRIENODE_H
#define TRIENODE_H

#include <QObject>
#include <vector>
#define MAX 27

struct TrieNode
{
    //
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

    //插入
    void Insert( QString str);

    // 鍒犻櫎
    void Delete( QString str);

    // 鏌ユ壘
    bool Search(QString str);

    // 鎵撳嵃瀛楀吀
    void PrintDic(TrieNode* root,std::vector<std::vector<char> > &words, std::vector<char> &word) ;

private:
    TrieNode* root;
};

#endif // TRIENODE_H
