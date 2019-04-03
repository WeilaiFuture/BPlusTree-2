#ifndef __DEFAULT__
#define __DEFAULT__

#include <iostream>

#define ORDER 7                   // B+树的阶（非根内结点的最小子树个数）
// #define MINNUM_KEY ORDER-1;        // 最小键值个数
#define MAXNUM_KEY 7      // 最大键值个数
// #define MINNUM_CHILD MINNUM_KEY+1; // 最小子树个数
#define MAXNUM_CHILD 8 // 最大子树个数
// #define MINNUM_LEAF MINNUM_KEY;    // 最小叶子结点键值个数
#define MAXNUM_LEAF 7    // 最大叶子结点键值个数

enum NODE_TYPE{INTERNAL, LEAF};        // 结点类型：内结点、叶子结点
enum SIBLING_DIRECTION{LEFT, RIGHT};   // 兄弟结点方向：左兄弟结点、右兄弟结点
typedef int KeyType;                 // 键类型
typedef int DataType;                  // 值类型

#endif // __DEFAULT__