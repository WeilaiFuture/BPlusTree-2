#include <iostream>
#include "BPlusTree.h"

using namespace std;

void aaa(Node* node){
    for(int i = 0; i < node->keyNum; i++){
        cout << node->arrKeys[i] << " ";
    }
}

int main(int argc, char const *argv[])
{
    BPlusTree* bt = new BPlusTree();
    for(int i = 0; i < 35; i++){
        bt->insert(i, i);
    }

    bt->remove(8);
    bt->remove(9);
    bt->remove(10);
    // bt->remove(21);
    bt->remove(12);
    // bt->remove(13);
    // bt->remove(14);

    Node* root = bt->root;

    aaa(root);
    cout << endl;
    if(root->nodeType == INTERNAL){
        for(int i = 0; i < root->keyNum+1; i++){
            cout << "[ ";
            aaa(((InternalNode*)root)->childs[i]);
            cout << "]";
        }
        cout << endl;
        if(((InternalNode*)root)->childs[0]->nodeType == INTERNAL){
            for(int i = 0; i < root->keyNum+1; i++){
                for(int j = 0; j < (((InternalNode*)root)->childs[i]->keyNum)+1; j++){
                    InternalNode* child = (InternalNode*)(((InternalNode*)root)->childs[i]);
                    
                    if(child->childs[j] != NULL){
                        cout << "[ ";
                        aaa(child->childs[j]);
                        cout << "]";
                    }
                    
                }
            }
            cout << endl;
        }
    }
    
    // LeafNode* dataHead = bt->dataHead;
    // while(dataHead){
    //     for(int i = 0; i < dataHead->keyNum; i++){
    //         cout << dataHead->arrKeys[i] << " ";
    //     }
    //     dataHead = dataHead->rightSibling;
    //     cout << endl;
    // }
    
    cout << "maxKey = " << bt->maxKey << endl;
    return 0;
}
