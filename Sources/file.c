#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Headers/file.h"

void UsersOperation(char *filename)
{
    FileType file[FILEMAXN];
    int n;
    ReadFile(file, &n, filename);
    FileTree root = CreateFileTree("Root", file, n); // 创建树，root为根节点
    ShowInfo();
    char operation[NAMEMAXN];
    while (gets(operation) != NULL) //获取输入
    {                               // 分割出操作命令和参数
        char *op_1 = strtok(operation, " ");
        char *op_2 = strtok(NULL, " ");
        char *op_3 = strtok(NULL, " ");
        char *op_4 = strtok(NULL, " ");
        if (strcmp(op_1, "ls") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "cd") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "mv") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "rm") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "mkdir") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "sort") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "tag") == 0)
        {
            /* code */
        }
        else
        {
            printf("ERROR:不支持\"%s\"命令, 请重新输入!\n", operation);
        }
    }
}

void ShowInfo()
{
    system("cls");
    printf("  ******************************************************\n\n");
    printf("  *                欢迎使用笔记管理系统                 *\n \n");
    printf("  ******************************************************\n\n");
    printf("  该系统目前支持如下功能：\n");
    printf("  1.显示当前目录下所有的笔记文件: ls\n");
    printf("  2.按照树状结构显示所有的笔记文件夹以及笔记文件: ls -a\n");
    printf("  3.显示命令指定文件下所有的内容: ls <文件夹路径>\n");
    printf("  4.显示命令指定文件下所有的带有搜索内容的文件夹名及文件名: ls <笔记文件夹路径> grep “搜索内容”\n");

    printf("  5.切换到当前路径的上级文件夹: cd ..\n");
    printf("  6.将路径切换为命令中输入的文件夹路径: cd <笔记文件夹路径>\n");

    printf("  7.将笔记文件移动到指定的文件夹目录下: mv <笔记文件名> <笔记文件夹目录>\n");
    printf("  8.将笔记文件进行重命名，从原文件名改为目标文件名: mv <笔记原文件名> <笔记目标文件名>\n");
    printf("  9.将指定的笔记文件夹移动到目标文件夹目录下: mv -r <被移动的文件夹> <目标文件夹>\n");

    printf("  10.对笔记文件进行删除: rm <笔记文件名>\n");
    printf("  11.删除指定文件夹以及其内部所有内容: rm -r <笔记文件夹名称>\n");

    printf("  12.在当前路径下新建文件夹: mkdir <文件名>\n");
    printf("  13.在当前路径下新建文件: mkdir -r <文件夹名>\n");

    printf("  14.对指定文件夹内的笔记文件按文件名首字母进行排序: sort <笔记文件夹名>\n");

    printf("  15.显示指定笔记/文件夹的标签: tag <笔记文件名/笔记文件夹名>\n");
    printf("  16.为指定笔记/笔记文件夹增加标签: tag -add <笔记文件名/笔记文件夹名> “标签内容”\n");
    printf("  17.删除指定笔记/文件夹的指定标签: tag -del <笔记文件名/笔记文件夹名> “标签内容”\n");
    printf("  18.在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名: tag -s “标签内容”\n");
    printf("  19.对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径: tag -sa “标签内容”\n");

    printf("  ******************************************************\n");
    printf("  请输入指令: ");
    system("pause");
}

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char *getDateTime()
{
    static char cur_time[20]; // 返回局部变量，故加static
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
        printf("  ");
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
 * @brief 根据所读取的数组构建一棵树
 *
 * @param root 根节点传入"Root"
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

//! 树状结构显示
/**
 * @brief ls -a: 按照树状结构显示所有的笔记文件夹以及笔记文件
 *
 * @param pNode
 * @param level = -1
 */
void ls_a(FileTree pNode, int level)
{
    if (strcmp(pNode->name, "Root")) // 首节点定义为的名称为Root
    {
        printf("%s\n", pNode->name);
    }
    else
    {

        for (int i = 0; i < level; i++)
        {
            printf("|    ");
        }
        printf("|---<%s>\n", pNode->name);
    }
    if (pNode->fchild) // 存在子节点
    {
        ls_a(pNode->fchild, level + 1); // 递归调用
    }
    if (pNode->sbi)
    {
        ls_a(pNode->sbi, level);
    }
    return;
}

/**
 * @brief ls <笔记文件夹路径>：显示命令指定文件下所有的内容(子笔记文件夹和笔记文件)
 * @brief 目前只支持绝对路径
 *
 * @param dirpath 输入的路径名称
 * @param file 数组
 * @param pNode 需要传入Root节点
 * @param n 数组长度
 */
void ls_dir(char *dirpath, FileType file[], FileTree pNode, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath))
        {
            FileTree b = PreOrderFindNode_Path(pNode, file[i].name); // 查找匹配的节点
            ls(b);                                                   // 调用ls()函数，打印路径下的所有内容
        }
        else
        {
            printf("未能找到此路径\n");
        }
    }
}
//! 未完成
/**
 * @brief 用先序遍历递归查找匹配的节点
 *
 * @param pNode
 * @param filename
 * @return FileTree
 */
FileTree PreOrderFindNode_Path(FileTree pNode, char *filename)
{
}

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
                FileTree q = p->sbi;
                while (q->sbi)
                {
                    if (strcmp(q->name, filename) == 0)
                    {
                        p->sbi = q->sbi;
                        free(q);
                        break;
                    }
                    else
                    {
                        p = p->sbi;
                        q = q->sbi;
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
                FileTree q = p->sbi;
                while (q->sbi)
                {
                    if (strcmp(q->name, filename) == 0)
                    {
                        p->sbi = q->sbi;
                        PostOrderTraverse(q, file, n);
                        free(q);
                        break;
                    }
                    else
                    {
                        p = p->sbi;
                        q = q->sbi;
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

    for (int i = 0; i < *n; i++)
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
            // 生成当前路径
            char tmp[PATHMAXN];
            strcpy(tmp, file[i].path);
            strcat(tmp, "\\");
            strcat(tmp, filename);
            strcpy(file[*n].path, tmp);

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

/**
 * @brief tag <笔记文件名/笔记文件夹名> 显示当前目录下的指定笔记/文件夹的标签
 *
 * @param pNode,当前目录的节点
 * @param filename 指定的文件夹或文件
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag(FileNode *pNode, char *filename, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0) //找到相同的名字, 但不一定是该目录下的
        {
            if (strcmp(file[i].fathername, pNode->name) == 0) //表示在该目录下
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    printf("标签%d: %s\n", j + 1, file[i].tag[j]); //打印标签
                }
                break;
            }
        }
    }
    if (i == n) //没有找到该文件(夹)
    {
        printf("该目录下没有指定的文件(夹)\n");
    }
}

/**
 * @brief tag-add <笔记文件名/笔记文件夹名> 在当前目录下指定的笔记/笔记文件夹增加标签
 *
 * @param pNode,当前目录的节点
 * @param filename 指定的文件夹或文件
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_add(FileNode *pNode, char *filename, char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0) //找到相同的名字, 但不一定是该目录下的
        {
            if (strcmp(file[i].fathername, pNode->name) == 0) //表示在该目录下
            {
                if (file[i].tagnum > 2) //表示超过当前最大的标签数量
                {
                    printf("超过最大的标签数\n");
                }
                else
                {
                    for (j = 0; j < file[i].tagnum; j++) //寻找是否有相同的标签名字
                    {
                        if (strcmp(file[i].tag[j], tagname) == 0)
                        {
                            printf("添加失败, 该标签已存在\n");
                            break;
                        }
                    }
                    if (j == file[i].tagnum) //没有找到相同的标签名字
                    {
                        strcpy(file[i].tag[j], tagname);
                        file[i].tagnum++;
                        printf("添加成功\n");
                    }
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("该目录下没有找到指定的文件(夹)\n");
    }
}

/**
 * @brief tag-add <笔记文件名/笔记文件夹名>> “标签内容”: 在当前目录下指定的笔记/笔记文件夹删除指定的标签
 *
 * @param pNode,当前目录的节点
 * @param filename 指定的文件夹或文件
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_del(FileNode *pNode, char *filename, char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0) //找到相同的名字, 但不一定是该目录下的
        {
            if (strcmp(file[i].fathername, pNode->name) == 0) //表示在该目录下
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    if (strcmp(file[i].tag[j], tagname) == 0) //找到该标签
                    {
                        file[i].tagnum--;                                  //标签数量-1
                        memset(file[i].tag[j], 0, sizeof(file[i].tag[j])); //清空内容
                        printf("删除成功\n");
                    }
                }
                if (j == file[i].tagnum)
                {
                    printf("没有找到该标签\n");
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("该目录下没有找到指定的文件(夹)\n");
    }
}

/**
 * @brief tag-s “标签内容”： 根据标签内容，在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名
 * @param pNode,当前目录的节点
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_s(FileNode *pNode, char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++) // 找到当前路径下的文件(夹)
    {
        if (strcmp(file[i].fathername, pNode->name) == 0) //在当前目录下的
        {
            for (j = 0; j < file[i].tagnum; j++)
            {
                if (strcmp(file[i].tag[j], tagname) == 0) //找到相同的标签
                {
                    printf("<%s>\n", file[i].name); //打印文件(夹)名字
                }
            }
        }
    }
}

/**
 * @brief tag-sa “标签内容”： 根据标签内容，对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_sa(char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < file[i].tagnum; j++)
        {
            if (strcmp(tagname, file[i].tag[j]) == 0) //找到相同名称的标签
            {
                printf("%-20s\t%-20s", file[i].name, file[i].path); //打印文件名和文件路径
            }
        }
    }
}