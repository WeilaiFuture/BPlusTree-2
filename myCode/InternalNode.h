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
      // 合并结点
      void mergeChild(Node* parentNode, Node* childNode, int keyIndex);
      // 清空结点，同时会清空结点所包含的子树结点
      void clear();
      // 从兄弟结点中借一个键值
      void borrowFromLeftNode(InternalNode* rightNode, InternalNode* leftNode, int parentKeyIndex);
      void borrowFromRightNode(InternalNode* leftNode, InternalNode* rightNode, int parentKeyIndex);
      void borrowFrom(Node* destNode, Node* parentNode, int keyIndex, SIBLING_DIRECTION d);
      // 根据键值获取孩子结点指针下标
      int getChildIndex(KeyType key, int keyIndex);

      // 处理merge和borroe共有的代码段，考虑最右节点情况的不同
      void handleMergeOrBorrow(InternalNode* targetNode, InternalNode* fromNode, int keyIndex, int flag);
      void borrow(InternalNode* targetNode, InternalNode* fromNode, int parentKeyIndex);
      void merge(InternalNode* leftNode, InternalNode* rightNode, int parentKeyIndex);
      void searchAndChangeKey(KeyType key, KeyType newKey);

    public:
      Node* childs[MAXNUM_CHILD];
};

#endif // __INTERNALNODE__