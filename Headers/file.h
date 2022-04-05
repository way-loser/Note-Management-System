#ifndef FILE_H
#define FILE_H

#define NAMEMAXN 100
#define PATHMAXN 1000
#define FILEMAXN 100 // 文件夹最多储存文件数

typedef struct FileNode
{
    char name[NAMEMAXN]; // 文件名或者文件夹名
    char path[PATHMAXN]; // 文件（夹）路径
    int flag;            // 区分文件或者文件夹的标识->0: 文件夹，1: 文件
    char datetime[20];   // 文件创建日期
    int filenumber;      // 文件夹包含的文件（夹）数量
    FileTree *files;     // 文件夹包含的文件（夹）列表
    FileTree pNode;      // 上级目录
    char tag[3][30];     // 至多支持3个标签标签
} FileNode, *FileTree;

/**
 * @brief 初始化文件系统，新建一个根目录节点ROOT
 * 
 * @return FileTree 
 */
FileTree init();

#endif