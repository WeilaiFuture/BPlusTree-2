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
      void removeKey(int keyIndex);
      // 分裂结点
      KeyType split(LeafNode* newLeafNode);
      // 合并结点
      void merge(LeafNode* lNode, LeafNode* rNode);
      // 清空结点，同时会清空结点所包含的子树结点
      void clear();
      // 从兄弟结点中借一个键值
      void borrowFromRightNode();
      void borrowFromLeftNode();
      // 根据键值获取孩子结点指针下标
      int getChildIndex(KeyType key, int keyIndex);
      // 检查删除的key是否在父节点上，若在，则替换
      void checkKeyInParentNode(KeyType key, KeyType newKey);

    public:
      // LeafNode* leftSibling;
	    LeafNode* rightSibling;
      LeafNode* leftSibling;
	    DataType datas[MAXNUM_LEAF];

};

#endif // __LEAFNODE__