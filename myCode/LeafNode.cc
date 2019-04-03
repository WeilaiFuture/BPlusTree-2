#include "LeafNode.h"
#include "BPlusTree.h"

#include <unistd.h>
#include <iostream>
using namespace std;

LeafNode::LeafNode(){
    nodeType = LEAF;
    rightSibling = NULL;
}
LeafNode::~LeafNode(){}

void LeafNode::insert(KeyType key, const DataType& data){
    // 判断该叶子节点是否等于最大key数量，若等于，则分裂该叶子节点，否则直接插入
    if(keyNum == MAXNUM_LEAF){
        LeafNode* newLeafNode = new LeafNode();
        if(parentNode != NULL){
            newLeafNode->parentNode = parentNode;
        }else{
            parentNode = new InternalNode();
            newLeafNode->parentNode = parentNode;
            BPlusTree::root = parentNode;
            ((InternalNode*)parentNode)->childs[0] = this;
            ((InternalNode*)parentNode)->childs[1] = newLeafNode;
        }
        // 分裂叶子节点，返回中间key值,新叶子节点为右边
        KeyType middleKey = split(newLeafNode);
        // 将中间的key加入父节点中
        ((InternalNode*)parentNode)->insert(middleKey, newLeafNode);
        // 判断新需要插入的key应该属于哪个节点
        if(key < middleKey){
            insert(key, data);
        }else{
            newLeafNode->insert(key, data);
        }
    }else{
        int i;
        for(i = keyNum; i > 0 && arrKeys[i-1] > key; i--){
            arrKeys[i] = arrKeys[i-1];
            datas[i] = datas[i-1];
        }
        arrKeys[i] = key;
        datas[i] = data; 
        keyNum++;
    }
}

void LeafNode::removeKey(int keyIndex, int childIndex){

}
KeyType LeafNode::split(LeafNode* newLeafNode){
    // 找到中间位置的key
    KeyType middleKey = arrKeys[MAXNUM_KEY/2];
    // 将满的叶子节点的前半部分key和data添加到新叶子节点的key和data，并将满的叶子节点的后半部分移动到前半部分
    // 判断MAXNUM_KEY的奇偶性
    int count;
    if(MAXNUM_KEY%2 == 1){
        count = MAXNUM_KEY/2+1;
        newLeafNode->keyNum = MAXNUM_KEY/2+1;
    }else{
        count = MAXNUM_KEY/2;
        newLeafNode->keyNum = MAXNUM_KEY/2;
    }
    for(int i = 0; i < count; i++){
        newLeafNode->arrKeys[i] = arrKeys[MAXNUM_KEY/2+i];
        newLeafNode->datas[i] = datas[MAXNUM_KEY/2+i];
        arrKeys[MAXNUM_KEY/2+i] = -1;
        datas[MAXNUM_KEY/2+i] = -1;
    }
    keyNum = MAXNUM_KEY/2;

    // 将左右孩子节点串起来
    rightSibling = newLeafNode;
    return middleKey;
}
void LeafNode::mergeChild(Node* parentNode, Node* childNode, int keyIndex){
    
}
void LeafNode::clear(){
    
}
void LeafNode::borrowFrom(Node* destNode, Node* parentNode, int keyIndex, SIBLING_DIRECTION d){
    
}
int LeafNode::getChildIndex(KeyType key, int keyIndex){

    return keyIndex;
}