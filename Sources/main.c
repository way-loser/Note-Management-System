#include "../Headers/file.h"
#include "file.c"
#include "../Headers/user.h"
#include "user.c"

#define _CRT_SECURE_NO_WARNINGS 1

int main()
{
    UserList L;
    FileType file[FILEMAXN]; //存放用户文件
    FileTree Userrootfile;   //用户根目录
    int n = 0;               //用来表示数组的长度
    UserNode *user;
    InitUserInfo(&L); //初始化所有用户信息
    // RegisterUser(&L, file, &n);
    user = LogUser(L, file, &n, &Userrootfile); //用户登录
    FileTree usertree;
    if (user == NULL)
        printf("登录失败");
    else
    {
        ReadFile(file, &n, user->data->userfilename); //将用户信息放到数组中
    }
    return 0;
}