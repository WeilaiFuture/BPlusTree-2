#ifndef __NODE__
#define __NODE__

#include "Default.h"

class Node{
    public:
      Node();
      virtual ~Node();

      // 找到键值在结点中存储的下标
      int getKeyIndex(KeyType key);

      // 纯虚函数，定义接口
      // 从结点中移除键值
      virtual void removeKey(int keyIndex)=0;
      // 清空结点，同时会清空结点所包含的子树结点
      virtual void clear()=0;
      // 根据键值获取孩子结点指针下标
      virtual int getChildIndex(KeyType key, int keyIndex)=0;
    
    public:
	    NODE_TYPE nodeType;
	    int keyNum;
      Node* parentNode;
	    KeyType arrKeys[MAXNUM_KEY];

};

#endif // __NODE__
