#ifndef __BPLUSTREE__
#define __BPLUSTREE__

#include <vector>

#include "Default.h"
#include "Node.h"
#include "LeafNode.h"

using namespace std;

class BPlusTree{
    public:
      BPlusTree();
      virtual ~BPlusTree();
    public:
      bool insert(KeyType key, const DataType& data);
	  bool remove(KeyType key);
	  bool update(KeyType oldKey, KeyType newKey);
	//   // 定值查询，compareOperator可以是LT(<)、LE(<=)、EQ(=)、BE(>=)、BT(>)
	//   vector<DataType> select(KeyType compareKey, int compareOpeartor);
	//   // 范围查询，BETWEEN
  	//   vector<DataType> select(KeyType smallKey, KeyType largeKey);
	  bool search(KeyType key); // 查找是否存在
	  void clear();             // 清空
	  void print();        // 打印树关键字
	  void printData();    // 打印数据

		private:
		  bool recursiveSearch(Node *pNode, KeyType key);
			void recursiveInsert(Node* parentNode, KeyType key, const DataType& data);

		public:
		  Node* root;
	    LeafNode* dataHead;
		  KeyType maxKey;  // B+树中的最大键

};

#endif // __BPLUSTREE__