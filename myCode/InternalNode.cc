#include "InternalNode.h"
#include "BPlusTree.h"

#include <unistd.h>
#include <iostream>
using namespace std;

InternalNode::InternalNode(){
    nodeType = INTERNAL;
}
InternalNode::~InternalNode(){}

void InternalNode::insert(KeyType key, Node* childNode){
    cout << "key = " << key << endl;
    cout << "InternalNode::insert keyNum = " << keyNum << endl;
    cout << "InternalNode::insert MAXNUM_KEY = " << MAXNUM_KEY << endl;
    // 判断内节点的key是否等于最大数目，若等于， 则分裂该节点，否则直接插入
    if(keyNum == MAXNUM_KEY){
        InternalNode* newInternalNode = new InternalNode();
        if(parentNode != NULL){
            newInternalNode->parentNode = parentNode;
        }else{
            parentNode = new InternalNode();
            newInternalNode->parentNode = parentNode;
            BPlusTree::root = parentNode;
            ((InternalNode*)parentNode)->childs[0] = this;
            ((InternalNode*)parentNode)->childs[1] = newInternalNode;
        }
        // 返回原节点中间key值， 分裂的新节点为右节点
        KeyType middleKey = split(newInternalNode); 
        // 判断新key值的在原arrKeys中的位置，决定middleKey的值
        if(key < arrKeys[keyNum-1]){
            middleKey = arrKeys[keyNum-1];
            arrKeys[keyNum-1] = -1;
            keyNum--;
            insert(key, childNode);
        }else if(key > newInternalNode->arrKeys[0]){
            int i;
            // 将newInternalNode->arrKeys[0]置为NULL，所有元素前移一个单元，newInternalNode->keyNum--
            for(i = 0; i < newInternalNode->keyNum-1; i++){
                newInternalNode->arrKeys[i] = newInternalNode->arrKeys[i+1];
                newInternalNode->childs[i] = newInternalNode->childs[i+1];
            }
            // 孩子节点最后一个节点还没移动
            newInternalNode->childs[i] = newInternalNode->childs[i+1];
            newInternalNode->keyNum--;
            newInternalNode->insert(key, childNode);
            childNode->parentNode = newInternalNode;
        }else{
            middleKey = key;
            // 直接插入右节点第一个孩子节点
            newInternalNode->childs[0] = childNode;
            childNode->parentNode = newInternalNode;
        }
        // 将中间节点添加到父节点
        ((InternalNode*)parentNode)->insert(middleKey, newInternalNode); 
    }else{ // 分裂后递归到这里开始重新插入
        if(keyNum == 0){
            arrKeys[0] = key;
            keyNum++;
            return;
        }
        if(keyNum == 1){
            if(arrKeys[0] > key){
                arrKeys[1] = arrKeys[0];
                arrKeys[0] = key;
                childs[2] = childs[1];
                if(childs[0]->arrKeys[0] > key){
                    childs[1] = childs[0];
                    childs[0] = childNode;
                }else{
                    childs[1] = childNode;
                }
            }else{
                arrKeys[1] = key;
                childs[2] = childNode;
            }
            keyNum++;
            return;
        }
        // 找到key值下标
        int keyIndex = getKeyIndex(key);
        cout << "keyIndex = " << keyIndex << endl;
        if(key > arrKeys[keyIndex]){
            for(int i = keyNum; i > keyIndex; i--){
                arrKeys[i] = arrKeys[i-1];
                childs[i+1] = childs[i];
            }
            arrKeys[keyIndex+1] = key;
            childs[keyIndex+2] = childNode;
        }else{
            for(int i = keyNum; i >= keyIndex; i--){
                arrKeys[i] = arrKeys[i-1];
                childs[i+1] = childs[i];
            }
            arrKeys[keyIndex] = key;
            childs[keyIndex+1] = childNode;
        }
        keyNum++;
    }
}

Node* InternalNode::findChildByKey(KeyType key){
    int childIndex = getChildIndex(key, getKeyIndex(key));
    return childs[childIndex];
    // if(node == NULL){
    //     cout << "node == NULL" << endl;
    // }else{
    //     cout << "node->keys[keyNum-1] == " << node->arrKeys[keyNum-1] << endl;
    // }
}


void InternalNode::removeKey(int keyIndex, int childIndex){

}
int InternalNode::split(Node* newInternalNode){
    // 找到中间位置的key
    KeyType middleKey = arrKeys[MAXNUM_KEY/2];
    // 原节点变为左节点，新节点为右节点，右节点keyNum >= 左节点keyNum
    // 判断MAXNUM_KEY的奇偶性
    int count;
    if(MAXNUM_KEY%2 == 1){
        count = MAXNUM_KEY/2 +1;
        newInternalNode->keyNum = MAXNUM_KEY/2+1;
    }else{
        count = MAXNUM_KEY/2;
        newInternalNode->keyNum = MAXNUM_KEY/2;
    }
    for(int i = 0; i < count; i++){
        // 分配key
        newInternalNode->arrKeys[i] = arrKeys[MAXNUM_KEY/2+i];
        arrKeys[MAXNUM_KEY/2+i] = -1;
    }
    keyNum = MAXNUM_KEY/2;

    int beginChildIndex;
    // 分配孩子节点,中间孩子节点分给左节点
    if(MAXNUM_CHILD%2 == 1){
        beginChildIndex = MAXNUM_CHILD/2+1;
    }else{
        beginChildIndex = MAXNUM_CHILD/2;
    }
    for(int i = 0; i < MAXNUM_CHILD/2; i++){
        ((InternalNode*)newInternalNode)->childs[i+1] = childs[beginChildIndex+i];
        (((InternalNode*)newInternalNode)->childs[i+1])->parentNode = (InternalNode*)newInternalNode;
        childs[beginChildIndex+i] = NULL;
    }
    return middleKey;
}
void InternalNode::mergeChild(Node* parentNode, Node* childNode, int keyIndex){
    
}
void InternalNode::clear(){
    
}
void InternalNode::borrowFrom(Node* destNode, Node* parentNode, int keyIndex, SIBLING_DIRECTION d){
    
}
int InternalNode::getChildIndex(KeyType key, int keyIndex){
    if(key > arrKeys[keyIndex]){
        return keyIndex+1;
    }else{
        return keyIndex;
    }
}
