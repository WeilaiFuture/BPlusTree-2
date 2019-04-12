#ifndef __BPLUSTREE__
#define __BPLUSTREE__

#include <vector>

#include "Default.h"
#include "Node.h"
#include "LeafNode.h"

using namespace std;

struct NodeList{
		Node* node;
		NodeList* next;
		int isNewLine;
};

class BPlusTree{
    public:
      BPlusTree();
      virtual ~BPlusTree();
    public:
      bool insert(KeyType key, const DataType& data);
	  	bool remove(KeyType key);
			DataType* select(KeyType key); // 查找该key对应的value
			bool search(KeyType key); // 查找是否存在，若在内节点查找到则直接返回
			LeafNode* search(KeyType key, int& keyIndex); // 查找到该key的叶子节点，并返回lNode
			void clear();             // 清空
			void print();        // 打印树关键字
			// void printData();    // 打印数据
			// bool update(KeyType oldKey, KeyType newKey);

		private:
		  bool recursiveSearch(Node *pNode, KeyType key);
			LeafNode* recursiveSearch(Node *pNode, KeyType key, int& keyIndex);
			void recursiveInsert(Node* parentNode, KeyType key, const DataType& data);

		public:
		  static Node* root;
	    LeafNode* dataHead;
		  KeyType maxKey;  // B+树中的最大键

};

#endif // __BPLUSTREE__