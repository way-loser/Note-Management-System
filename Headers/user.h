#ifndef _USER_H_
#define _USER_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "../Headers/file.h"
typedef int Status;//函数返回类型


#define SUCCESS 1
#define ERROR   0
#define MAX_USERIDSZ        30
#define MAX_PASSWORDSZ      20
#define MAX_FINDPASSWORDSZ  20
#define MAX_USERFILENAMESZ  40


//用户信息
typedef struct UserInfo
{
    char userid[MAX_USERIDSZ + 1];  //最大支持20个字符       用户id
    char password[MAX_PASSWORDSZ + 1];//最大支持20个字符     用户密码
    long long phonenum;//用户手机号码，用来找回密码
    char userfilename[MAX_USERFILENAMESZ + 1];//用户对应的文件名，可通过文件名找到自己的文件信息
    int privacyflag;//0表示为隐私模式，1表示为开放状态
    int modifyflag;//0表示只能查看用户笔记，1表示其他人能对其增删改
}UserInfo;

typedef struct UserNode
{
    UserInfo* data;  //存放用户数据
    struct UserNode* next;//指向下一个节点
}UserNode, * UserList;


Status InitUserList(UserList* L);//初始化用户链表
Status InsertNewUser(UserList* L, UserInfo* data);//加入新用户
UserNode* SearchUser(UserList L, const char* userid);//寻找用户返回其节点的地址,如果没有就返回NULL
int getstring(int num, char* str);//读取字符串
long long getlonglong(long long* num);//读取数字
Status getint(int* num); //获取数字
/***********需要测试************************/
Status FileSave(UserInfo* user);//文件保存
/***********需要测试************************/
//注册一个新用户,同时创建一个以用户名为名称的文件夹，保存到以(user.id+.info)的文件中
void RegisterUser(UserList* L, FileType file[], int* n);
Status InitUserInfo(UserList* L);//初始化用户信息
Status FileUpdata(UserList L);//文件更新数据 
Status FindPasswod(UserList L);//找回密码
/************需要测试**********************/
//用户登录，并初始化file, 以及n的值, 并建一颗树
UserNode* LogUser(UserList L, FileType file[], int* n, FileTree* Userrootfile);//用户登录




#endif
