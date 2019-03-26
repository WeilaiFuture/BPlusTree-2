#include "InternalNode.h"

InternalNode::InternalNode(){
    nodeType = INTERNAL;
    parentNode = NULL;
}
InternalNode::~InternalNode(){}

void InternalNode::insert(Node* leftNode, Node* rightNode){
    // 判断内节点的key是否等于最大数目，若等于， 则分裂该节点，否则直接插入
    if(keyNum == MAXNUM_KEY){
        InternalNode* newInternalNode = new InternalNode();
        split(newInternalNode); 
        // 将中间节点添加到父节点
        parentNode->insert(newInternalNode, this); 



    }else{
        int i;
        for(i = keyNum; i > 0 && rightNode->arrKeys[0] < arrKeys[i-1]; i--){
            arrKeys[i] = arrKeys[i-1];
        }
        arrKeys[i-1] = rightNode->arrKeys[0];
        keyNum++;
    }
}

void InternalNode::removeKey(int keyIndex, int childIndex){

}
void InternalNode::split(Node* newInternalNode){
    // 将满节点的key的前半部分添加到新节点上，并将满节点的后半部分key移动到前半部分
    for(int i = 0; i < MAXNUM_KEY/2; i++){
        // 分配key
        newInternalNode->arrKeys[i] = arrKeys[i];
        arrKeys[i] = arrKeys[MAXNUM_KEY/2+i];
        arrKeys[MAXNUM_KEY/2+i] = NULL;
    }
    // 暂存中间孩子节点
    Node* middleChild;
    // 判断MAXNUM_KEY是否是奇数
    if(MAXNUM_KEY%2 == 1){
        arrKeys[MAXNUM_KEY/2] = arrKeys[MAXNUM_KEY-1];
        keyNum = MAXNUM_KEY/2+1;
        // MAXNUM_CHILD为偶数
        middleChild = childs[MAXNUM_CHILD/2-1];
        // 分配孩子节点，中间节点除外
        for(int i = 0; i < MAXNUM_CHILD/2-1; i++){
            ((InternalNode*)newInternalNode)->childs[i] = childs[i];
            childs[i+1] = childs[MAXNUM_CHILD/2+i];
        }
        childs[MAXNUM_CHILD/2] = childs[MAXNUM_CHILD-1];
        // 分配孩子节点，中间节点
        splitMiddleChild(newInternalNode, this, middleChild);
    }else{
        keyNum = MAXNUM_KEY/2;
    }
    newInternalNode->keyNum = MAXNUM_KEY/2;
    
}
void InternalNode::mergeChild(Node* parentNode, Node* childNode, int keyIndex){
    
}
void InternalNode::clear(){
    
}
void InternalNode::borrowFrom(Node* destNode, Node* parentNode, int keyIndex, SIBLING_DIRECTION d){
    
}
int InternalNode::getChildIndex(KeyType key, int keyIndex){
    if(key == arrKeys[keyIndex]){
        return keyIndex+1;
    }else{
        return keyIndex;
    }
}

// --------private---------
void InternalNode::splitMiddleChild(Node* leftNode, Node* rightNode, Node* middleChild){
    // 如果中间孩子最小的key都比其爷爷节点的key
    if(){

    }
}