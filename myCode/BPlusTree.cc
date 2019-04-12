#include "BPlusTree.h"
#include "InternalNode.h"

Node* BPlusTree::root = NULL;

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
    LeafNode* lNode;
    int keyIndex;
    // 判断是否存在
    if((lNode = search(key, keyIndex)) == NULL){
        return false;
    }
    // 判断要删除的key是否是最大值
    if(key == maxKey){
        // 找到最后一个节点
        LeafNode* lNode = dataHead;
        while(lNode->rightSibling != NULL){
            lNode = lNode->rightSibling;
        }
        // 找到最后一个节点的倒数第二个key，设置为最大值
        // 若最后一个节点只有一个key，则最大值设置为倒数第二个节点的最后一个key
        if(lNode->keyNum == 1){
            maxKey = lNode->leftSibling->arrKeys[lNode->leftSibling->keyNum-1];
        }else{
            maxKey = lNode->arrKeys[lNode->keyNum-2];
        }
    }
    lNode->removeKey(keyIndex);
    return true;
}
bool BPlusTree::search(KeyType key){
    return recursiveSearch(root, key);
}
LeafNode* BPlusTree::search(KeyType key, int& keyIndex){
    return recursiveSearch(root, key, keyIndex);
}
void BPlusTree::clear(){
    if(root != NULL){
        root->clear();
        delete root;
    }
}
void BPlusTree::print(){
    if(root == NULL){
        return;
    }
    NodeList *nodeList = new NodeList;
    NodeList *tail, *head, *p;
    nodeList->node = root;
    nodeList->next = NULL;
    nodeList->isNewLine = 1;
    tail = nodeList;
    head = nodeList;
    p = nodeList;
    while(p != NULL){
        cout << "[";
        for(int i = 0; i < p->node->keyNum; i++){
            cout << " " << p->node->arrKeys[i];
        }
        cout << " ]";
        if(p->isNewLine == 1){
            cout << endl;
        }
        if(p->node->nodeType == INTERNAL){
            for(int i = 0; i < p->node->keyNum+1; i++){
                NodeList *n = new NodeList;
                n->node = ((InternalNode*)p->node)->childs[i];
                n->next = NULL;
                if(i == p->node->keyNum && p->isNewLine == 1){
                    n->isNewLine = 1;
                }else{
                    n->isNewLine = 0;
                }
                tail->next = n;
                tail = tail->next;
            }
        }
        head = p;
        p = p->next;
        delete head;
    }
}
DataType* BPlusTree::select(KeyType key){
    LeafNode* lNode;
    int keyIndex;
    if((lNode = search(key, keyIndex)) == NULL){
        return NULL;
    }
    return &(lNode->datas[keyIndex]);
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
LeafNode* BPlusTree::recursiveSearch(Node *pNode, KeyType key, int& keyIndex){
    if(pNode == NULL){
        return NULL;
    }else{
        keyIndex = pNode->getKeyIndex(key);
        int childIndex = pNode->getChildIndex(key, keyIndex);
        if(pNode->nodeType == LEAF && key == pNode->arrKeys[keyIndex]){
            return (LeafNode*)pNode;
        }else{
            if(pNode->nodeType == LEAF){
                return NULL;
            }else{
                return recursiveSearch(((InternalNode*)pNode)->childs[childIndex], key, keyIndex);
            }
        }
    }
}
void BPlusTree::recursiveInsert(Node* parentNode, KeyType key, const DataType& data){
    Node* node = parentNode;
    // 判断是否时叶子节点，若是，则直接插入
    if(node->nodeType == LEAF){
        ((LeafNode*)node)->insert(key, data);
    }else if(node->nodeType == INTERNAL){
        node = ((InternalNode*)node)->findChildByKey(key);
        recursiveInsert(node, key, data);
    }else{
        cout << "error:BPlusTree::recursiveInsert" << endl;
        return;
    }
}