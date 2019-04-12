#ifndef __INTERNALNODE__
#define __INTERNALNODE__

#include "Node.h"

class InternalNode: public Node{
    public:
      InternalNode();
      virtual ~InternalNode();

    public:
      void insert(KeyType key, Node* childNode);
      Node* findChildByKey(KeyType key);

      // 从结点中移除键值
      void removeKey(int keyIndex);
      // 分裂结点
      int split(Node* newInternalNode);
      // 清空结点，同时会清空结点所包含的子树结点
      void clear();
      // 从兄弟结点中借一个键值
      void borrowFromLeftNode(InternalNode* rightNode, InternalNode* leftNode, int parentKeyIndex);
      void borrowFromRightNode(InternalNode* leftNode, InternalNode* rightNode, int parentKeyIndex);
      // 根据键值获取孩子结点指针下标
      int getChildIndex(KeyType key, int keyIndex);

      void merge(InternalNode* leftNode, InternalNode* rightNode, int parentKeyIndex);
      void searchAndChangeKey(KeyType key, KeyType newKey);

    public:
      Node* childs[MAXNUM_CHILD];
};

#endif // __INTERNALNODE__