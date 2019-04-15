#include "InternalNode.h"
#include "BPlusTree.h"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

InternalNode::InternalNode(){
    nodeType = INTERNAL;
}
InternalNode::~InternalNode(){}

void InternalNode::insert(KeyType key, Node* childNode){
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
            newInternalNode->childs[0] = childs[keyNum];
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
        // 找到key值下标
        int keyIndex = getKeyIndex(key);
        // 说明此时key为最大
        if(key > arrKeys[keyIndex]){
            arrKeys[keyNum] = key;
            childs[keyNum+1] = childNode;
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
}

void InternalNode::removeKey(KeyType key){
    // 此key必在该内节点上,故该keyIndex必为该key所在下标
    int keyIndex = getKeyIndex(key);
    for(int i = keyIndex; i < keyNum-1; i++){
        arrKeys[i] = arrKeys[i+1];
        childs[i+1] = childs[i+2];
    }
    keyNum--;

    // 若该节点的keyNum为0，首先说明此节点一定是根节点，其次该节点只有一个孩子节点，设置为新的根节点，free掉该节点
    if(keyNum == 0){
        BPlusTree::root = childs[0];
        free(this);
        return;
    }

    // 若父节点为空，说明为根节点
    if(parentNode == NULL){
        return;
    }

    // 若keyNum < MAXNUM_KEY/2，先向右邻节点借一个key，或者合并，否则向左邻节点
    if(keyNum < MAXNUM_KEY/2){
        // 找到相邻的右节点，若该节点为最右节点，则找左邻节点
        int parentKeyIndex = parentNode->getKeyIndex(arrKeys[0]);
        int childIndex = parentNode->getChildIndex(arrKeys[0], parentKeyIndex);

        InternalNode* bNode = NULL;
        // 如果该节点为最右节点
        if(childIndex == parentNode->keyNum){
            bNode = (InternalNode*)(((InternalNode*)parentNode)->childs[childIndex-1]);
            if(bNode->keyNum == MAXNUM_KEY/2){
                merge(bNode, this, parentKeyIndex);
            }else{
                borrowFromLeftNode(this, bNode, parentKeyIndex);
            }
        }else{
            bNode = (InternalNode*)(((InternalNode*)parentNode)->childs[childIndex+1]);
            if(bNode->keyNum == MAXNUM_KEY/2){
                merge(this, bNode, parentKeyIndex);
            }else{
                borrowFromRightNode(this, bNode, parentKeyIndex);
            }
        }
    }
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
void InternalNode::clear(){
    for(int i = 0; i <= keyNum; i++){
        childs[i]->clear();
        delete childs[i];
    }
}

void InternalNode::borrowFromLeftNode(InternalNode* rightNode, InternalNode* leftNode, int parentKeyIndex){
    // 将rightNode的key向后移动一个单位
    for(int i = rightNode->keyNum; i > 0; i--){
        rightNode->arrKeys[i] = rightNode->arrKeys[i-1];
        rightNode->childs[i+1] = rightNode->childs[i];
    }
    rightNode->childs[1] = rightNode->childs[0];
    // 将左节点的最后一个孩子节点移动到右节点的第一个孩子节点
    rightNode->childs[0] = leftNode->childs[leftNode->keyNum];
    rightNode->childs[0]->parentNode = rightNode;
    // 将父节点的该index上的key移动到右节点的第一个key
    rightNode->arrKeys[0] = parentNode->arrKeys[parentKeyIndex];
    // 将左节点的最后一个key移动到父节点的该index位置
    parentNode->arrKeys[parentKeyIndex] = leftNode->arrKeys[leftNode->keyNum-1];
    rightNode->keyNum++;
    leftNode->keyNum--;
}

void InternalNode::borrowFromRightNode(InternalNode* leftNode, InternalNode* rightNode, int parentKeyIndex){
    leftNode->arrKeys[leftNode->keyNum] = parentNode->arrKeys[parentKeyIndex];
    leftNode->childs[leftNode->keyNum+1] = rightNode->childs[0];
    leftNode->childs[leftNode->keyNum+1]->parentNode = leftNode;
    parentNode->arrKeys[parentKeyIndex] = rightNode->arrKeys[0];
    // 将右节点向前移动一个单位
    for(int i = 0; i < rightNode->keyNum-1; i++){
        rightNode->arrKeys[i] = rightNode->arrKeys[i+1];
        rightNode->childs[i] = rightNode->childs[i+1];
    }
    rightNode->childs[rightNode->keyNum-1] = rightNode->childs[rightNode->keyNum];
    leftNode->keyNum++;
    rightNode->keyNum--;
}

int InternalNode::getChildIndex(KeyType key, int keyIndex){
    if(key >= arrKeys[keyIndex]){
        return keyIndex+1;
    }else{
        return keyIndex;
    }
}

void InternalNode::merge(InternalNode* leftNode, InternalNode* rightNode, int parentKeyIndex){
    // 将父节点index位置上的key添加到左节点的最后
    leftNode->arrKeys[leftNode->keyNum] = parentNode->arrKeys[parentKeyIndex];
    leftNode->keyNum++;
    // 将右节点合并到左节点
    for(int i = 0; i < rightNode->keyNum; i++){
        leftNode->arrKeys[leftNode->keyNum+i] = rightNode->arrKeys[i];
        leftNode->childs[leftNode->keyNum+i] = rightNode->childs[i];
        leftNode->childs[leftNode->keyNum+i]->parentNode = leftNode;
    }
    leftNode->childs[leftNode->keyNum+rightNode->keyNum] = rightNode->childs[rightNode->keyNum];
    leftNode->childs[leftNode->keyNum+rightNode->keyNum]->parentNode = leftNode;
    leftNode->keyNum += rightNode->keyNum;
    free(rightNode);

    // 删除父节点上该index位置的key
    // -----此处唯一在内节点调用删除------
    parentNode->removeKey(parentNode->arrKeys[parentKeyIndex]);
    // -------------------------------
}

void InternalNode::searchAndChangeKey(KeyType key, KeyType newKey){
    if(parentNode == NULL){
        return;
    }else{
        int keyIndex = parentNode->getKeyIndex(key);
        if(parentNode->arrKeys[keyIndex] == key){
            parentNode->arrKeys[keyIndex] = newKey;
        }else{
            ((InternalNode*)parentNode)->searchAndChangeKey(key, newKey);
        }
    }
}