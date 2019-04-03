#ifndef __LEAFNODE__
#define __LEAFNODE__

#include "Node.h"
#include "InternalNode.h"

class LeafNode: public Node{
    public:
      LeafNode();
      virtual ~LeafNode();

    public:
      // 插入key和data
      void insert(KeyType key, const DataType& data);

      // 从结点中移除键值
      void removeKey(int keyIndex, int childIndex);
      // 分裂结点
      KeyType split(LeafNode* newLeafNode);
      // 合并结点
      void mergeChild(Node* parentNode, Node* childNode, int keyIndex);
      // 清空结点，同时会清空结点所包含的子树结点
      void clear();
      // 从兄弟结点中借一个键值
      void borrowFrom(Node* destNode, Node* parentNode, int keyIndex, SIBLING_DIRECTION d);
      // 根据键值获取孩子结点指针下标
      int getChildIndex(KeyType key, int keyIndex);

    public:
      // LeafNode* leftSibling;
	    LeafNode* rightSibling;
      
	    DataType datas[MAXNUM_LEAF];

};

#endif // __LEAFNODE__