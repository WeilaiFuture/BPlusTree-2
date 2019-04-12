#include "LeafNode.h"
#include "BPlusTree.h"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

LeafNode::LeafNode(){
    nodeType = LEAF;
    rightSibling = NULL;
    leftSibling = NULL;
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

void LeafNode::removeKey(int keyIndex){
    KeyType key = arrKeys[keyIndex];
    for(int i = keyIndex; i < keyNum-1; i++){
        arrKeys[i] = arrKeys[i+1];
        datas[i] = datas[i+1];
    }
    arrKeys[keyNum-1] = -1;
    keyNum--;

    if(parentNode == NULL){
        return;
    }
    // 检查父节点是否有该key，并替换
    checkKeyInParentNode(key, arrKeys[0]);

    // 判断keyNum是否小于MAXNUM_KEY/2,若小于，则向右邻节点借一个key或合并
    if(keyNum < MAXNUM_KEY/2){
        // 判断是否是最右节点
        if(((InternalNode*)parentNode)->childs[parentNode->keyNum] == this){
            // 判断左邻孩子节点keyNum是否等于MAXNUM_KEY,若等于，则将两个节点合并
            if(leftSibling->keyNum == MAXNUM_KEY/2){
                merge(leftSibling, this);
            }else{
                borrowFromLeftNode();
            }
        }else{
            // 判断右邻孩子节点keyNum是否等于MAXNUM_KEY,若等于，则将两个节点合并
            if(rightSibling->keyNum == MAXNUM_KEY/2){
                merge(this, rightSibling);
            }else{
                borrowFromRightNode();
            }
        }
    }
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
    if(rightSibling != NULL){
        newLeafNode->rightSibling = rightSibling;
        rightSibling->leftSibling = newLeafNode;
    }
    rightSibling = newLeafNode;
    newLeafNode->leftSibling = this;
    return middleKey;
}

void LeafNode::merge(LeafNode* lNode, LeafNode* rNode){
    for(int i = 0; i < rNode->keyNum; i++){
        lNode->arrKeys[lNode->keyNum+i] = rNode->arrKeys[i];
        lNode->datas[lNode->keyNum+i] = rNode->arrKeys[i];
    }

    lNode->keyNum += rNode->keyNum;
    // 重新链接左右叶子节点
    if(rNode->rightSibling == NULL){
        lNode->rightSibling = NULL;
    }else{
        lNode->rightSibling = rNode->rightSibling;
        rNode->rightSibling->leftSibling = lNode;
    }
    // -----唯有此处连接到内节点的删除操作------
    parentNode->removeKey(rNode->arrKeys[0]);
    // ------------------------------------
    free(rNode);
}

void LeafNode::clear(){
    // if data is pointer
    // for(int i = 0; i < keyNum; i++){
    //     delete datas[i];
    // }
}

void LeafNode::borrowFromRightNode(){
    arrKeys[keyNum] = rightSibling->arrKeys[0];
    // 将右邻节点的key向前移动一个单位
    for(int i = 0; i < rightSibling->keyNum-1; i++){
        rightSibling->arrKeys[i] = rightSibling->arrKeys[i+1];
        rightSibling->datas[i] = rightSibling->datas[i+1];
    }
    rightSibling->checkKeyInParentNode(arrKeys[keyNum], rightSibling->arrKeys[0]);
    keyNum++;
    rightSibling->keyNum--;
}

void LeafNode::borrowFromLeftNode(){
    for(int i = keyNum; i > 0; i++){
        arrKeys[i] = arrKeys[i-1];
        datas[i] = datas[i-1];
    }
    arrKeys[0] = leftSibling->arrKeys[keyNum-1];
    datas[0] = leftSibling->arrKeys[keyNum-1];
    leftSibling->arrKeys[keyNum-1] = -1;
    leftSibling->arrKeys[keyNum-1] = -1;
    leftSibling->keyNum--;
    keyNum++;
    checkKeyInParentNode(arrKeys[1], arrKeys[0]);
}

int LeafNode::getChildIndex(KeyType key, int keyIndex){
    return keyIndex;
}

void LeafNode::checkKeyInParentNode(KeyType key, KeyType newKey){
    // 查找该key是否是内节点的索引。 另一种方式可以在搜索key的时候将keyIndex的数组传过来，记录每一层该key 的位置，数组大小为树的高度
    int parentKeyIndex = parentNode->getKeyIndex(key);
    // 如果父节点存在该key，则将该key换为移动后叶子节点的第一个key
    if(key == parentNode->arrKeys[parentKeyIndex]){   
        parentNode->arrKeys[parentKeyIndex] = newKey;
    }else{
        // 向上递归查询该key是否作为索引,若是，则替换
        ((InternalNode*)parentNode)->searchAndChangeKey(key, newKey);
    }
}