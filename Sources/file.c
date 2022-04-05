#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXN 100
#define PATHMAXN 1000

typedef struct FileNode
{
    char name[NAMEMAXN]; //文件名或者文件夹名
    char path[PATHMAXN]; //文件（夹）路径
    int flag;            //区分文件或者文件夹的标识->0: 文件夹，1: 文件
    char datetime[20];   //文件创建日期
    int filenumber;      //文件夹包含的文件（夹）数量
    FileNode **files;    //文件夹包含的文件（夹）列表
    FileNode *pNode;     //上级目录
} FileNode, *FileTree;
