#include "Node.h"

Node::Node(){
    nodeType = LEAF;
    keyNum = 0;
    parentNode = NULL;
}
Node::~Node(){}

// 返回比key大于或等于的index
int Node::getKeyIndex(KeyType key){
    if(keyNum == 0){
        return 0;
    }
    int left = 0;
    int right = keyNum-1;
    int current;
    while(left != right){
        current = (left+right)/2;
        if(key > arrKeys[current]){
            left = current+1;
        }else if(key < arrKeys[current]){
            right = current;
        }else{
            return current;
        }
    }
    return left;
}