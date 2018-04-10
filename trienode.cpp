#include "trienode.h"
#include <QString>
MultiTree::MultiTree(int x)
{
    root = new TrieNode(0);
}
// 插入
void MultiTree::Insert( QString str)
{
    int size = str.size();
    int val;
    TrieNode *p = root;
    // 一个一个字符插入
    for (int i = 0; i < size; ++i)
    {
        val = str.at(i).toLatin1() - 'a';

        if (str.at(i).toLatin1() == '\'')
            val = MAX - 1;
        // 之前没有该字符
        if (p->next[val] == NULL)
        {
            p->next[val] = new TrieNode(0);
        }//if
        p = p->next[val];
    }//for
     // 以该字符为结尾
    p->count++;
}
// 删除
void MultiTree::Delete(QString str) {
    int size = str.size();
    int val;
    TrieNode *p = root;
    // 一个一个字符插入
    for (int i = 0; i < size; ++i) {
        val = str.at(i).toLatin1() - 'a';

        if (str.at(i).toLatin1() == '\'')
            val = MAX - 1;
        // 删除的字符串不在字典中
        if (p->next[val] == NULL)
        {
            return;
        }//if
        p = p->next[val];
    }//for
     // 以该字符为结尾
    p->count--;
}
// 查找
bool MultiTree::Search( QString str)
{
    if (root == NULL) {
        return false;
    }//if
    int size = str.size();
    TrieNode *p = root;
    int val;
    for (int i = 0; i < size; ++i) {
        val = str.at(i).toLatin1() - 'a';
        // 无法转移到下一个字符
        if (str.at(i).toLatin1() == '\'')
            val = MAX - 1;
        if (p->next[val] == NULL) {
            return false;
        }//if
         // 继续下一个字符
        p = p->next[val];
    }//for
    return p->count > 0;
}
//这个是查找是否存在树中，不管他是部分存在还是完全存在树中
bool MultiTree::findPrefix(QString str)
{
    if (root == NULL)
    {
        return false;
    }//if
    int size = str.size();
    TrieNode *p = root;
    int inn;
    for (int i = 0; i < size; ++i)
    {
        inn = str.at(i).toLatin1() - 'a';
        if (str.at(i).toLatin1() == '\'')
            inn = MAX - 1;
        // 无法转移到下一个字符
        if (p->next[inn] == NULL)
        {
            return false;
        }//if
         // 继续下一个字符
        p = p->next[inn];
    }//for
	return p->count > 0;
}// 打印字典
void MultiTree::PrintDic(TrieNode* root,std::vector<std::vector<char> > &words, std::vector<char> &word) {
    if (root == NULL) {
        return;
    }//if
    if (root->count > 0) {
        words.push_back(word);
    }//if
    for (int i = 0; i < 26; ++i) {
        if (root->next[i]) {
            word.push_back('a' + i);
            PrintDic(root->next[i], words, word);
            word.pop_back();
        }//if
    }//for
}

