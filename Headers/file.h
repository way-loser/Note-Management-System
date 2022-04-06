#ifndef FILE_H
#define FILE_H

#define NAMEMAXN 100
#define PATHMAXN 1000
#define FILEMAXN 100 // 文件夹最多储存文件数

//! 第一版
/* typedef struct FileNode
{
    char name[NAMEMAXN]; // 文件名或者文件夹名
    char path[PATHMAXN]; // 文件（夹）路径
    int flag;            // 区分文件或者文件夹的标识->0: 文件夹，1: 文件
    char datetime[20];   // 文件创建日期
    int filenumber;      // 文件夹包含的文件（夹）数量
    FileTree *files;     // 文件夹包含的文件（夹）列表
    FileTree pNode;      // 上级目录
    char tag[3][30];     // 至多支持3个标签
} FileNode, *FileTree; */

//! 第二版
/* typedef struct Elem
{
    char name[NAMEMAXN]; // 文件名或者文件夹名
    char path[PATHMAXN]; // 文件（夹）路径
    char datetime[20];   // 文件创建日期
    char tag[3][30];     // 至多支持3个标签
} Elem;
typedef struct Node
{
    Elem data;       // 节点数据
    Tree child, sbi; // 指向第一个子节点和下一个兄弟节点的指针
} Node, *Tree; */

//! 第三版
typedef struct FileType
{
    char fathername[NAMEMAXN]; // 父节点名称
    char name[NAMEMAXN];       // 文件名或者文件夹名
    int flag;                  // 区分文件或者文件夹的标识->0: 文件夹，1: 文件
    char datetime[20];         // 文件创建日期
    char tag[3][30];           // 至多支持3个标签
} FileType;
typedef struct FileNode
{
    char name[NAMEMAXN];  // 节点文件名或者文件夹名
    FileTree fchild, sbi; // 指向第一个子节点和下一个兄弟节点的指针
} FileNode, *FileTree;

#endif