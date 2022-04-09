/**
 * @brief sort<笔记文件夹名>: 对文件夹里的文件按首字母进行排序
 *
 * @param pNode
 * @param filename 文件（夹）名
 */
void sort(FileTree pNode, char* filename)
{

    if (strcmp(pNode->name, filename) == 0 && pNode->fchild)
    {
        FileTree tem = (FileTree)malloc(sizeof(FileNode));
        for (int i = 0; i < *n; i++)
        {
            FileTree p = pNode->fchild;
            while (p->sbi) {
                if (p->name[0] > p->sbi->name[0]) {
                    tem = p;
                    p = p->sbi;
                    p->sbi = tem;
                }
                p = p->sbi;
            }
        }
    }
    else {
        if (pNode->fchild)
        {
            pNode = pNode->fchild;
            sort(pNode, filename);
        }
        else
        {
            printf("未能找到此文件夹\n");
            return;
        }
    }


}
