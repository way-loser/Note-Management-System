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
    char name[NAMEMAXN];           // 节点文件名或者文件夹名
    struct FileNode *fchild, *sbi; // 指向第一个子节点和下一个兄弟节点的指针
} FileNode, *FileTree;

void UsersOperation(char *filename);
void ShowInfo();

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char *getDateTime();

/**
 * @brief 将保存树数据的数组保存到文件中去
 *
 * @param file 储存数据的数组
 * @param n 数组的数量
 * @param filename 用户文件名称
 */
void SaveFile(FileType file[], int n, char *filename);

/**
 * @brief 从文件中读取保存树数据的数组
 *
 * @param file
 * @param n 数字（表示数组的长度）的地址值
 * @param filename 用户文件名称
 */
void ReadFile(FileType file[], int *n, char *filename);

/**
 * @brief Create a File Tree object
 *
 * @param root 根节点传入"Root"
 * @param file
 * @param n
 * @return FileTree
 */
FileTree CreateFileTree(char *root, FileType file[], int n);

/**
 * @brief ls: 显示当前目录下所有的笔记文件和文件夹
 *
 * @param pNode
 */
void ls(FileTree pNode);

/**
 * @brief ls -a: 按照树状结构显示所有的笔记文件夹以及笔记文件
 *
 * @param pNode
 * @param level = -1
 */
void ls_a(FileTree pNode, int level);

/**
 * @brief rm <笔记文件名>：对笔记文件进行删除
 *
 * @param pNode
 * @param filename
 * @param file 数组
 * @param n 数组长度
 */
void rm(FileTree pNode, char *filename, FileType file[], int *n);

/**
 * @brief rm -r <笔记文件夹名称>：删除制定文件以及其内部所有内容
 *
 * @param pNode
 * @param dirname
 * @param file 数组
 * @param n 数组长度
 */
void rm_r(FileTree pNode, char *filename, FileType file[], int *n);
void PostOrderTraverse(FileTree pNode, FileType file[], int *n);
void DeleteNode(FileTree pNode, FileType file[], int *n);

/**
 * @brief mkdir<笔记文件名>: 在当前文件夹pNode下新建文件
 *
 * @param pNode
 * @param filename
 * @param file 数组
 * @param n 数组长度
 */
void mkdir(FileTree pNode, char *filename, FileType file[], int *n);

/**
 * @brief mkdir -r<笔记文件夹名>: 新建文件夹
 *
 * @param pNode
 * @param dirname
 * @param file 数组
 * @param n 数组长度
 */
void mkdir_r(FileTree pNode, char *filename, FileType file[], int *n);

#endif