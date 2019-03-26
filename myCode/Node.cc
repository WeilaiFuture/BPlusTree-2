#include "Node.h"

Node::Node(){
    nodeType = LEAF;
    keyNum = 0;
}
Node::~Node(){}

int Node::getKeyIndex(KeyType key){
    int left = 0;
    int right = keyNum-1;
    int current;
    while(left != right){
        current = (left+right)/2;
        if(key > arrKeys[current]){
            left = current+1;
        }else{
            right = current;
        }
    }
    return left;
}