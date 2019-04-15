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
    
    for(int i = 60; i > 0; i--){
        bt->insert(i, i);
    }

    bt->print();

    cout << "maxKey = " << bt->maxKey << endl;
    
    bt->clear();
    return 0;
}
