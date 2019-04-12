#ifndef __DEFAULT__
#define __DEFAULT__

#include <iostream>
const int ORDER = 7;                      // B+树的阶（非根内结点的最大key数目）
const int MAXNUM_KEY = ORDER;             // 最大键值个数
const int MAXNUM_CHILD = ORDER+1;         // 最大子树个数
const int MAXNUM_LEAF = ORDER;            // 最大叶子结点键值个数

enum NODE_TYPE{INTERNAL, LEAF};        // 结点类型：内结点、叶子结点
enum SIBLING_DIRECTION{LEFT, RIGHT};   // 兄弟结点方向：左兄弟结点、右兄弟结点
typedef int KeyType;                   // 键类型
typedef int DataType;                  // 值类型

#endif // __DEFAULT__