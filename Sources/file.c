#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/file.h"

/**
 * @brief 初始化文件系统，新建一个根目录节点ROOT
 * 
 * @return FileTree 
 */
FileTree init()
{
    FileTree root;
    root = (FileTree)malloc(sizeof(FileNode)); // 分配内存空间
    strcpy(root->name, "ROOT");                // 命名
    strcpy(root->path, "ROOT");                // 命名路径
    root->flag = 0;                            // 标识为文件夹
    root->filenumber = 0;                      // 初始包含文件夹为0
    root->files = NULL;                        // 包含列表为空
    root->pNode;                               // 无上级目录
    return root;                               // 返回初始化的节点
}

/**
 * @brief ls: 显示当前目录下所有的笔记文件和文件夹
 * 
 * @param pNode 
 */
void ls(FileTree pNode)
{
    for (int i = 0; i < pNode->filenumber; i++)
    {
        printf("%s ", pNode->files[i]->name);
    }
    printf("\n");
}

//! 有大问题
/**
 * @brief ls -a: 按照树状结构显示所有的笔记文件夹以及笔记文件
 * 
 * @param pNode 
 */
void ls_a(FileTree pNode)
{
    for (int i = 0; i < pNode->filenumber; i++)
    {
        printf("%s ", pNode->files[i]->name);
        if (pNode->files[i]->flag == 0) // 如果是文件夹
        {
            printf("<");
            ls_a(pNode->files[i]); // 递归调用
            printf(">");
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief ls <笔记文件夹路径>：显示命令指定文件下所有的内容(子笔记文件夹和笔记文件)
 * 
 */

/**
 * @brief mkdir<笔记文件名>: 在当前文件夹pNode下新建文件
 * 
 * @param pNode 
 * @param filename 
 */
void mkdir(FileTree pNode, char *filename)
{
    if (pNode->files == NULL) // 给当前文件夹pNode的下级列表分配内存
    {
        pNode->files = (FileTree *)malloc(sizeof(FileTree) * FILEMAXN);
    }
    pNode->files[pNode->filenumber] = (FileTree)malloc(sizeof(FileNode));

    FileTree dir = pNode->files[pNode->filenumber++];
    strcpy(dir->name, filename); // 文件名
    dir->flag = 1;               // 标识1为文件
    dir->filenumber = 0;         // 不包含其他文件（夹）
    dir->files = NULL;           // 无包含文件列表
    dir->pNode = pNode;          // 上级目录
}

/**
 * @brief mkdir -r<笔记文件夹名>: 新建文件夹
 * 
 * @param pNode 
 * @param dirname 
 */
void mkdir_r(FileTree pNode, char *dirname)
{
    if (pNode->files == NULL) // 给当前文件夹pNode的下级列表分配内存
    {
        pNode->files = (FileTree *)malloc(sizeof(FileTree) * FILEMAXN);
    }
    pNode->files[pNode->filenumber] = (FileTree)malloc(sizeof(FileNode));

    FileTree dir = pNode->files[pNode->filenumber++];
    strcpy(dir->name, dirname); // 文件夹名
    dir->flag = 0;              // 标识0为文件夹
    dir->filenumber = 0;        // 不包含其他文件（夹）
    dir->files = NULL;          // 无包含文件列表
    dir->pNode = pNode;         // 上级目录
                                // 生成当前路径
    char tmp[PATHMAXN];
    strcpy(tmp, pNode->path);
    strcat(tmp, "\\");
    strcat(tmp, dirname);
    strcpy(dir->path, tmp);
}
