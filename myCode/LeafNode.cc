#include "LeafNode.h"

LeafNode::LeafNode(){
    nodeType = LEAF;
    leftSibling = NULL;
    rightSibling = NULL;
    parentNode = NULL;
}
LeafNode::~LeafNode(){}

void LeafNode::insert(KeyType key, const DataType& data){
    // 判断该叶子节点是否等于最大key数量，若等于，则分裂该叶子节点，否则直接插入
    if(keyNum == MAXNUM_KEY){
        LeafNode* newLeafNode = new LeafNode();
        split(newLeafNode);
        // 将中间的key加入父节点中
        parentNode->insert(newLeafNode, this);
        // 判断新需要插入的key应该属于哪个节点
        
    }else{
        int i;
        for(i = keyNum; i > 0 && arrKeys[i-1] > key; i--){
            arrKeys[i] = arrKeys[i-1];
            datas[i] = datas[i-1];
        }
        arrKeys[i-1] = key;
        datas[i-1] = data;
        keyNum++;
    }
}

void LeafNode::removeKey(int keyIndex, int childIndex){

}
void LeafNode::split(LeafNode* newLeafNode){
    // 将满的叶子节点的前半部分key和data添加到新叶子节点的key和data，并将满的叶子节点的后半部分移动到前半部分
    for(int i = 0; i < MAXNUM_KEY/2; i++){
        newLeafNode->arrKeys[i] = arrKeys[i];
        newLeafNode->datas[i] = datas[i];
        arrKeys[i] = arrKeys[MAXNUM_KEY/2+i];
        datas[i] = datas[MAXNUM_KEY/2+i];
        arrKeys[MAXNUM_KEY/2+i] = NULL;
        datas[MAXNUM_KEY/2+i] = NULL;
    }
    // 若最大key数量为奇数，则最后一个key没有被移动，需补充完整
    if(MAXNUM_KEY%2 == 1){
        arrKeys[MAXNUM_KEY/2] = arrKeys[MAXNUM_KEY-1];
        datas[MAXNUM_KEY/2] = datas[MAXNUM_KEY-1];
        arrKeys[MAXNUM_KEY-1] = NULL;
        datas[MAXNUM_KEY-1] = NULL;
        keyNum = MAXNUM_KEY/2+1;
    }else{
        keyNum = MAXNUM_KEY/2;
    }
    newLeafNode->keyNum = MAXNUM_KEY/2;
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