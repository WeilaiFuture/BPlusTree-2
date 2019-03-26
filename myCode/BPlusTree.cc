#include "BPlusTree.h"
#include "InternalNode.h"

BPlusTree::BPlusTree(){}
BPlusTree::~BPlusTree(){}

bool BPlusTree::insert(KeyType key, const DataType& data){
    // 判断是否重复
    if(search(key)){
        return false; // 暂定不允许有重复
    }
    // 判断是否有根节点
    if(root == NULL){
        root = new LeafNode();
        dataHead = (LeafNode*)root;
        maxKey = key;
    }
    // 判断新的key值是否大于最大key值
    if(key > maxKey){
        maxKey = key;
    }
    // 插入key
    recursiveInsert(root, key, data);

    return true;
}
bool BPlusTree::remove(KeyType key){
    return true;
}
bool BPlusTree::update(KeyType oldKey, KeyType newKey){
    return true;
}
bool BPlusTree::search(KeyType key){
    return recursiveSearch(root, key);
}
void BPlusTree::clear(){
    
}
void BPlusTree::print(){

}
void BPlusTree::printData(){
    
}

// -------private----------

bool BPlusTree::recursiveSearch(Node *pNode, KeyType key){
    if(pNode == NULL){
        return false;
    }else{
        int keyIndex = pNode->getKeyIndex(key);
        int childIndex = pNode->getChildIndex(key, keyIndex);
        if(key == pNode->arrKeys[keyIndex]){
            return true;
        }else{
            if(pNode->nodeType == LEAF){
                return false;
            }else{
                return recursiveSearch(((InternalNode*)pNode)->childs[childIndex], key);
            }
        }
    }
}
void BPlusTree::recursiveInsert(Node* parentNode, KeyType key, const DataType& data){
    // 判断是否时叶子节点，若是，则直接插入
    if(parentNode->nodeType == LEAF){
        ((LeafNode*)parentNode)->insert(key, data);
    }
}