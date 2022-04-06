#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Headers/file.h"

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char *getDateTime()
{
    char cur_time[20];
    time_t t;
    struct tm *lt;
    time(&t);
    lt = localtime(&t); //转为时间结构
    sprintf(cur_time, "%04d/%02d/%02d %02d:%02d:%02d", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    return cur_time;
}

/**
 * @brief 将保存树数据的数组保存到文件中去
 *
 * @param file 储存数据的数组
 * @param n 数组的数量
 * @param filename 用户文件名称
 */
void SaveFile(FileType file[], int n, char *filename)
{
    int i;
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("数据文件无法打开");
        return;
    }
    for (i = 0; i < n; i++)
    {
        fwrite(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief 从文件中读取保存树数据的数组
 *
 * @param file
 * @param n 数字（表示数组的长度）的地址值
 * @param filename 用户文件名称
 */
void ReadFile(FileType file[], int *n, char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        *n = 0;
        return;
    }
    fseek(fp, 0, SEEK_END);         // 重定位流上的文件指针,把fp指针退回到离文件结尾0字节处
    long length = ftell(fp);        // 调用函数ftell()获得当前位置相对于文件首的位移，该位移值等于文件所含字节数
    rewind(fp);                     // 将位置指针重新指向文件的开头
    *n = length / sizeof(FileType); // 得到一共有多少个结构数据
    for (int i = 0; i < *n; i++)
    {
        fread(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief Create a File Tree object
 *
 * @param root
 * @param file
 * @param n
 * @return FileTree
 */
FileTree CreateFileTree(char *root, FileType file[], int n)
{
    FileTree bt = (FileTree)malloc(sizeof(FileNode));
    strcpy(bt->name, root);
    bt->fchild = bt->sbi = NULL;
    int i, j;
    for (i = 0; i < n && strcmp(file[i].fathername, root) != 0; i++)
    {
        ;
    }
    if (i < n) // 若找到第一个父节点名称为root的
    {
        FileTree p = (FileTree)malloc(sizeof(FileNode)); // 创建一个临时指针
        p->fchild = p->sbi = NULL;
        strcpy(p->name, file[i].name);
        bt->fchild = p;

        for (j = i; j < n; j++)
        {
            if (strcmp(file[j].fathername, root) == 0)
            {
                p = CreateFileTree(file[j].name, file, n); //! 递归
                p = p->sbi;
            }
        }
    }
    return bt;
}

/**
 * @brief ls: 显示当前目录下所有的笔记文件和文件夹
 *
 * @param pNode
 */
void ls(FileTree pNode)
{
    FileTree p = pNode->fchild;
    for (; p; p = p->sbi)
    {
        printf("%s ", p->name);
    }
    printf("\n");
}

//! 有大问题，树状结构如何显示
/**
 * @brief ls -a: 按照树状结构显示所有的笔记文件夹以及笔记文件
 *
 * @param pNode
 */
void ls_a(FileTree pNode)
{
    FileTree p = pNode->fchild;
    for (; p; p = p->sbi)
    {
        printf("%s ", p->name);
        if (p->fchild) // 存在子节点
        {
            printf("<");
            ls_a(p->fchild); // 递归调用
            printf(">");
        }
    }
    printf("\n");
}

/**
 * @brief ls <笔记文件夹路径>：显示命令指定文件下所有的内容(子笔记文件夹和笔记文件)
 * 可以采用遍历
 */

/**
 * @brief rm <笔记文件名>：对笔记文件进行删除
 *
 * @param pNode
 * @param filename
 * @param file 数组
 * @param n 数组长度
 */
void rm(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (file[i].fathername != pNode->name)
            {
                printf("此文件不在当前目录下\n");
                return;
            }

            if (file[i].flag == 0)
            {
                printf("这是一个文件夹,若要删除,请输入“rm -r <要删除的笔记文件夹名称>”\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // 如果是亲代的第一个子节点
            {
                pNode->fchild = p->sbi;
                free(p);
            }
            else // 如果是兄弟节点，“嫁接”
            {
                while (p->sbi->sbi)
                {
                    if (strcmp(p->sbi->name, filename) == 0)
                    {
                        p->sbi = p->sbi->sbi;
                        free(p->sbi);
                        break;
                    }
                }
            }

            for (int j = i; j < *n; j++) // 后面的数据前移
            {
                file[j] = file[j + 1];
            }

            (*n)--;
        }
    }
    printf("未能找到次文件\n");
    return;
}

/**
 * @brief rm -r <笔记文件夹名称>：删除制定文件以及其内部所有内容
 *
 * @param pNode
 * @param dirname
 * @param file 数组
 * @param n 数组长度
 */
void rm_r(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (file[i].fathername != pNode->name)
            {
                printf("此文件不在当前目录下\n");
                return;
            }

            if (file[i].flag == 1)
            {
                printf("这是一个文件,若要删除,请输入“rm <要删除的笔记文件名>”\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // 如果是亲代的第一个子节点
            {
                pNode->fchild = p->sbi;
                PostOrderTraverse(p, file, n);
                free(p);
            }
            else // 如果是兄弟节点，“嫁接”
            {
                while (p->sbi->sbi)
                {
                    if (strcmp(p->sbi->name, filename) == 0)
                    {
                        p->sbi = p->sbi->sbi;
                        PostOrderTraverse(p, file, n);
                        free(p->sbi);
                        break;
                    }
                }
            }
        }
    }
    printf("未能找到次文件\n");
    return;
}
void PostOrderTraverse(FileTree pNode, FileType file[], int *n)
{
    if (pNode)
    {
        PostOrderTraverse(pNode->fchild, file, n);
        PostOrderTraverse(pNode->sbi, file, n);
        DeleteNode(pNode, file, n);
    }
    return; //如果结点为空，返回上一层
}
void DeleteNode(FileTree pNode, FileType file[], int *n)
{

    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].name, pNode->name) == 0)
        {
            for (int j = i; j < *n; j++) // 后面的数据前移
            {
                file[j] = file[j + 1];
            }

            (*n)--;
        }
    }
}

/**
 * @brief mkdir<笔记文件名>: 在当前文件夹pNode下新建文件
 *
 * @param pNode
 * @param filename
 * @param file 数组
 * @param n 数组长度
 */
void mkdir(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("此文件（夹）名称已存在\n");
            return;
        }

        if (strcmp(file[i].name, pNode->name) == 0)
        {
            if (file[i].flag == 1)
            {
                printf("这是一个文件，无法在次目录下创建文件\n");
                return;
            }
            strcpy(file[*n].fathername, pNode->name);
            strcpy(file[*n].name, filename);
            file[*n].flag = 1; // 1表示这是一个文件
            strcpy(file[*n].datetime, getDateTime());
            FileTree p = pNode->fchild;
            if (p)
            {
                while (p->sbi)
                {
                    p = p->sbi;
                }
                strcpy(p->sbi->name, filename);
            }
            else
            {
                strcpy(p->name, filename);
            }

            (*n)++;
        }
    }
}

/**
 * @brief mkdir -r<笔记文件夹名>: 新建文件夹
 *
 * @param pNode
 * @param dirname
 * @param file 数组
 * @param n 数组长度
 */
void mkdir_r(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("此文件（夹）名称已存在\n");
            return;
        }

        if (strcmp(file[i].name, pNode->name) == 0)
        {
            if (file[i].flag == 1)
            {
                printf("这是一个文件，无法在次目录下创建文件");
                return;
            }
            strcpy(file[*n].fathername, pNode->name);
            strcpy(file[*n].name, filename);
            file[*n].flag = 0; // 0表示这是一个文件夹
            strcpy(file[*n].datetime, getDateTime());
            FileTree p = pNode->fchild;
            if (p)
            {
                while (p->sbi)
                {
                    p = p->sbi;
                }
                strcpy(p->sbi->name, filename);
            }
            else
            {
                strcpy(p->name, filename);
            }

            (*n)++;
        }
    }
}