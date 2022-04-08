#ifndef FILE_H
#define FILE_H

#define NAMEMAXN 100
#define PATHMAXN 1000
#define FILEMAXN 200 // 文件夹最多储存文件数

//! 第三版
typedef struct FileType
{
    char fathername[NAMEMAXN]; // 父节点名称
    char name[NAMEMAXN];       // 文件名或者文件夹名
    char path[PATHMAXN];       // 文件（夹）路径
    int flag;                  // 区分文件或者文件夹的标识->0: 文件夹，1: 文件
    char datetime[20];         // 文件创建日期
    int tagnum;                // 标签数量
    char tag[3][30];           // 至多支持3个标签
} FileType;
typedef struct FileNode
{
    char name[NAMEMAXN];           // 节点文件名或者文件夹名
    struct FileNode *father,*fchild, *sbi; // 指向夫节点、第一个子节点和下一个兄弟节点的指针
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
 * @brief ls <笔记文件夹路径>：显示命令指定文件下所有的内容(子笔记文件夹和笔记文件)
 * //!目前只支持绝对路径
 *
 * @param dirpath 输入的路径名称
 * @param file 数组
 * @param pNode 需要传入Root节点
 * @param n 数组长度
 */
void ls_dir(char *dirpath, FileType file[], FileTree pNode, int n);

/**
 * @brief 通过file[i].name与pNode->name匹配
 * 用先序遍历递归查找匹配的节点
 *
 * @param pNode
 * @param filename
 * @param b 将要获取的目标节点
 */
void PreOrderFindNode_Path(FileTree pNode, char *filename, FileTree b);

/**
 * @brief ls <笔记文件夹路径> grep “搜索内容”：显示命令指定文件下所有的带
有搜索内容的文件夹名及文件名
 *
 * @param dirpath 笔记文件夹路径
 * @param SearchContent 搜索内容
 * @param file 数组
 * @param pNode 需要传入Root节点
 * @param n 数组长度
 */
void ls_grep(char *dirpath, char *SearchContent, FileType file[], FileTree pNode, int n);

/**
 * @brief 模糊搜索判断是否符合筛选条件
 *
 * @param key 关键字
 * @param str 被查找的字符串
 * @return int 1为符合,0不符合
 */
int result_mohu(const char *key, char *str);

/**
 * @brief cd ..：将路径切换为当前目录的父目录.若是根目录则则不进行切换
 * 现在操作函数里判断再进行调用，记得输出当前节点路径哟
 *
 * @param pNode 当前节点
 * @return FileTree
 */
FileTree cd(FileTree pNode);

/**
 * @brief cd <笔记文件夹路径>：将路径切换为命令中输入的文件夹路径
 * //!目前只支持绝对路径
 *
 * @param dirpath 输入的路径名称
 * @param file 数组
 * @param pNode 先节点
 * @param root 需要传入Root节点
 * @param n 数组长度
 * @return FileTree 返回节点
 */
FileTree cd_dir(char *dirpath, FileType file[],FileTree pNode, FileTree root, int n);

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

/**
 * @brief tag <笔记文件名/笔记文件夹名> 显示当前目录下的指定笔记/文件夹的标签
 *
 * @param pNode,当前目录的节点
 * @param filename 指定的文件夹或文件
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag(FileNode *pNode, char *filename, FileType file[], int n);

/**
 * @brief tag-add <笔记文件名/笔记文件夹名> 在当前目录下指定的笔记/笔记文件夹增加标签
 *
 * @param pNode,当前目录的节点
 * @param filename 指定的文件夹或文件
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_add(FileNode *pNode, char *filename, char *tagname, FileType file[], int n);

/**
 * @brief tag-add <笔记文件名/笔记文件夹名>> “标签内容”: 在当前目录下指定的笔记/笔记文件夹删除指定的标签
 *
 * @param pNode,当前目录的节点
 * @param filename 指定的文件夹或文件
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_del(FileNode *pNode, char *filename, char *tagname, FileType file[], int n);

/**
 * @brief tag-s “标签内容”： 根据标签内容，在当前目录下进行笔记搜索，输出匹配的标签所对应的笔记文件名
 * @param pNode,当前目录的节点
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_s(FileNode *pNode, char *tagname, FileType file[], int n);

/**
 * @brief tag-sa “标签内容”： 根据标签内容，对所有笔记进行搜索，输出匹配的标签所对应的笔记的文件名以及绝对路径
 * @param tagname 标签的名字
 * @param file  该用户的数组
 * @param n    数组的长度
 */
void tag_sa(char *tagname, FileType file[], int n);

#endif