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
      void removeKey(int keyIndex, int childIndex);
      // 分裂结点
      int split(Node* newInternalNode);
      // 合并结点
      void mergeChild(Node* parentNode, Node* childNode, int keyIndex);
      // 清空结点，同时会清空结点所包含的子树结点
      void clear();
      // 从兄弟结点中借一个键值
      void borrowFrom(Node* destNode, Node* parentNode, int keyIndex, SIBLING_DIRECTION d);
      // 根据键值获取孩子结点指针下标
      int getChildIndex(KeyType key, int keyIndex);

    public:
      Node* childs[MAXNUM_CHILD];
};

#endif // __INTERNALNODE__