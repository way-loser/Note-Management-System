#define _CRT_SECURE_NO_WARNINGS 1
#include "../Headers/user.h"

//初始化用户链表
//头节点不存放数据
Status InitUserList(UserList *L)
{
	*L = (UserList)malloc(sizeof(UserNode)); //开辟用户链表空间
	if ((*L) == NULL)						 //开辟空间失败
	{
		printf("%s\n", strerror(errno)); //打印开辟失败的原因
		return ERROR;
	}
	UserList p = (*L);
	p->data = (UserInfo *)malloc(sizeof(UserInfo)); //为指向的数据开辟空间
	if (p->data == NULL)							//开辟空间失败
	{
		printf("%s\n", strerror(errno));
		return ERROR;
	}
	p->next = NULL; //下一个节点指向空
	return SUCCESS;
}

//加入新用户
Status InsertNewUser(UserList *L, UserInfo *data)
{
	UserList La = (*L), Ltail = (*L);
	while (La) //找到尾节点
	{
		Ltail = La;
		La = La->next;
	}
	UserList user;
	user = (UserList)malloc(sizeof(UserNode)); //开辟空间
	if (user == NULL)						   //开辟空间失败
	{
		printf("%s\n", strerror(errno));
		return ERROR;
	}
	user->data = (UserInfo *)malloc(sizeof(UserInfo)); //开辟空间
	if (user->data == NULL)							   //开辟空间失败
	{
		printf("%s\n", strerror(errno));
		return ERROR;
	}
	user->data = data;	//获取数据
	user->next = NULL;	//下一个节点指向空
	Ltail->next = user; //用户链表连接新用户信息
	return SUCCESS;
}

//寻找用户
//返回其节点的地址,如果没有就返回NULL
UserNode *SearchUser(UserList L, const char *userid)
{
	UserList p = L->next; //指向第一个元素
	while (p)			  //寻找用户名
	{
		if ((strcmp(userid, p->data->userid)) == 0) //找到对应的用户名
		{
			return p; //返回用户的节点
		}
		p = p->next; //没有找到指向下一个节点
	}
	return NULL; //找不到就返回空指针
}

//读取字符串
//返回读取到的字符个数
//返回-1表读取发生错误
// num表最大字符数,读取成功则将字符串存放到str中
int getstring(int num, char *str)
{
	int i = 0;
	char ch;				 //存放读取到的字符
	int count = 1;			 //计数
	scanf(" %c", &(str[0])); //读取第一个非空字符
	for (i = 1; i < num; i++)
	{
		ch = getchar();
		if (ch == '\n')
		{
			str[i] = '\0';
			break;
		}
		str[i] = ch; //将每个字符存放到str中
		count++;	 //字符数加1
	}
	if (i == num) //超过最大字符数
	{
		scanf("%*[^\n]%*c");	  //清空缓冲区
		for (i = 0; i < num; i++) //清空数组
			str[i] = 0;
		printf("输入的字符过长，请重新输入!\n");
		return -1;
	}
	return count; //返回读取到的字符数
}

//读取数字
//返回读取到数字
// 将读取成功的数字，赋值给num
long long getlonglong(long long *num)
{
	long long numtemp;
	while (1)
	{
		if (scanf("%lld", &numtemp) == 1) //成功读取到数字
		{
			*num = numtemp; //将读取到的数赋值给num
			return numtemp;
		}
		scanf("%*[^\n]%*c"); //清空缓冲区
		printf("输入错误，请重新输入:> ");
	}
}

//获取数字
int getint(int *num)
{
	int numtemp;
	while (1)
	{
		if (scanf("%d", &numtemp) == 1) //成功读取到数字
		{
			*num = numtemp; //将读取到的数赋值给num
			return numtemp;
		}
		//读取不成功，即输入的不是数字
		scanf("%*[^\n]%*c"); //清空缓冲区
		printf("输入错误，请重新输入:> ");
	}
}

//需要修改
//文件保存
Status FileSave(UserInfo *user)
{
	FILE *fwrite = fopen("userinfo.txt", "a+");
	fprintf(fwrite, "%-30s\t", user->userid);		//用户名称录入
	fprintf(fwrite, "%-20s\t", user->password);		//用户密码录入
	fprintf(fwrite, "%-12lld\t", user->phonenum);	//录入手机号码
	fprintf(fwrite, "%-40s\t", user->userfilename); //录入文件名
	fprintf(fwrite, "%-2d\t", user->privacyflag);	//录入隐私标志位
	fprintf(fwrite, "%-2d\n", user->modifyflag);	//录入增改权力

	fclose(fwrite);
	fwrite = NULL;
	return SUCCESS;
}

//需进行改动
//注册一个新用户
// n当前文件的个数
// file[]存放文件的数组
void RegisterUser(UserList *L, FileType file[], int *n)
{
	UserInfo userdata; //创建一个用户信息的结构体

	/*******************用户注册新用户名***********************/
	do
	{
		printf("请输入你想创建的用户名(不超过20个字符): ");
		if (-1 == getstring(MAX_USERIDSZ, userdata.userid)) //获取id,如果不符合条件，则循环继续
		{
			continue;
		}
		if (SearchUser(*L, userdata.userid) != NULL) // ID重复
		{
			printf("该用户名已被注册,请重新创建一个新的用户名!!!\n");
		}
		else
			break; //如果满足以上条件则退出循环
	} while (1);
	/**********************************************************/

	/********************用户设置密码**************************/
mode1:
	do //如果输入的密码一直不符合输入的要求，就一直卡在死循环里
	{
		printf("请输入你想创建的密码(最少6个字符、最多20个字符): ");
		int length = getstring(MAX_PASSWORDSZ, userdata.password);
		if (length == -1) //输入的长度过长
			continue;	  //循环继续
		if (length < 6)	  //输入的长度过短
		{
			printf("设置的密码少于6个字符，请重新输入!\n");
			continue; //循环继续
		}
		break;
	} while (1);
mode2:
	do //如果输入的密码一直不符合输入的要求，就一直卡在死循环里
	{
		char str[MAX_PASSWORDSZ + 1] = {0};
		printf("请再次确认密码(最少6个字符、最多20个字符): ");
		int length = getstring(MAX_PASSWORDSZ, str); //获取密码长度
		int flag = strcmp(str, userdata.password);	 //比较前后密码是否一致
		if (flag == 0)								 //密码一致退出循环
		{
			break;
		}
		else //密码不一致
		{
			printf("密码输入错误\n");
		mode0:
			printf("1. 重新设置密码\n");
			printf("2. 重新确认密码\n");
			printf("请选择功能: "); //让用户选择功能
			int mode = 0;
			mode = getint(&mode);
			if (mode == 1) //重新设置密码
			{
				goto mode1; //回到设置密码的页面
			}
			else if (mode == 2) //重新确认密码
			{
				goto mode2; //回到重新确认密码的页面
			}
			else //没有该功能
			{
				scanf("%*[^\n]%*c"); //清空缓冲区
				printf("没有该功能\n");
				printf("请选择已有的功能!\n");
				goto mode0; //回到重新确认密码的页面
			}
		}
	} while (1);
	/*******************************************************/

	/********************密保设置************************/
	do
	{
		printf("请输人你的手机号码(用于忘记密码找回): ");
		long long telephonenum = 0; //存放电话号码
		getlonglong(&telephonenum);
		if (telephonenum >= pow(10, 10) && telephonenum < pow(10, 11)) //输入的手机号位数为11时
		{
			userdata.phonenum = telephonenum;
			break;
		}
		else //输入的电话号码不符合位数
		{
			printf("不符合手机号码的格式\n");
		}
	} while (1);

	userdata.privacyflag = 0; //默认为隐私模式
	userdata.modifyflag = 0;  //默认只能查看状态

	char userfile[MAX_USERIDSZ + 1] = {0};
	strcpy(userfile, userdata.userid);
	strcat(userfile, ".info");				 //防止命名重复 文件名: userid.info
	strcpy(userdata.userfilename, userfile); //将文件名复制过去

	//创建一个新的文件夹(以用户名为名字)
	*n = 0;									  //初始化为0
	strcpy(file[*n].name, userdata.userid);	  //以用户名为名字创建文件夹
	strcpy(file[*n].datetime, getDateTime()); //获取创建时间
	file[*n].flag = 0;						  // 0表示文件夹
	(*n)++;
	SaveFile(file, *n, userdata.userfilename); //保存到文件中

	InsertNewUser(L, &userdata); //插入新节点
	//进行保存数据
	FileSave(&userdata);
	InitUserInfo(L); //初始化用户信息
}

//需改动
//初始化用户信息
Status InitUserInfo(UserList *L)
{
	InitUserList(L);
	FILE *pfread = fopen("userinfo.txt", "r");
	if (pfread == NULL)
	{
		return ERROR;
	}
	while (!feof(pfread))
	{
		UserInfo *userdata = (UserInfo *)malloc(sizeof(UserInfo)); //开辟一个新的空间
		if (userdata == NULL)
		{
			printf("%s\n", strerror(errno));
			return ERROR;
		}
		fscanf(pfread, "%s", userdata->userid);
		fscanf(pfread, "%s", userdata->password);
		fscanf(pfread, "%lld", &(userdata->phonenum));
		fscanf(pfread, "%s", userdata->userfilename); //读取文件位置  需要测试
		fscanf(pfread, "%d", &(userdata->privacyflag));
		fscanf(pfread, "%d\n", &(userdata->modifyflag));
		InsertNewUser(L, userdata); //插入新节点
	}
	fclose(pfread);
	pfread = NULL;
	return SUCCESS;
}

//需修改
//更改用户信息后，文件进行更新
//文件更新数据
Status FileUpdata(UserList L)
{
	UserList user = L->next;
	FILE *fupdate = fopen("temp.txt", "a+");
	while (user) //
	{
		fprintf(fupdate, "%-30s\t", user->data->userid);	   //将用户id信息存到文件中
		fprintf(fupdate, "%-20s\t", user->data->password);	   //将用户密码信息存到文件中
		fprintf(fupdate, "%-12lld\t", user->data->phonenum);   //将用户手机号码存到文件中
		fprintf(fupdate, "%-40s\t", user->data->userfilename); //将用户文件名存到文件中
		fprintf(fupdate, "%-2d\t", user->data->privacyflag);   //将访问权限放到文件中
		fprintf(fupdate, "%-2d\n", user->data->modifyflag);	   //将修改权限放到文件中
		user = user->next;									   //指向下一个节点
	}
	fclose(fupdate);
	fupdate = NULL;
	remove("userinfo.txt");				//将原有的文件名删除
	rename("temp.txt", "userinfo.txt"); //将新建立的文件名改为userinfo.txt
	return SUCCESS;
}

//密码找回
Status FindPasswod(UserList L)
{
	int findmode = 0;
	char nameid[MAX_USERIDSZ + 1] = {0};
findmode1:
	do //获取用户名
	{
		printf("请输入你的用户名: ");
	} while (-1 == getstring(MAX_USERIDSZ, nameid));
	UserList user = SearchUser(L, nameid); //寻找是否有该用户名

	if (user == NULL) //没有找到该用户名
	{
		printf("没有找到该用户\n");
	findmode0:
		printf("1. 重新输入用户名\n");
		printf("2. 返回\n");
		getint(&findmode);	//获取数字
		if (findmode == 1)	//模式1
			goto findmode1; //返回到重新输入用户名模式
		if (findmode == 2)	//模式2
			return ERROR;	//返回
		else				//输入的模式不符合以上情况
			goto findmode0;
	}
phonemode1:
	printf("请输人你的手机号码: ");
	long long telephonenum = 0; //存放电话号码
	int phonemode;
	getlonglong(&telephonenum); //获取输入的手机号码

	if (telephonenum != user->data->phonenum) //电话号码不一致
	{
		printf("输入的手机号码不正确\n");
	phonemode0:
		printf("1. 重新输入手机号码\n");
		printf("2. 重新输入用户名\n");
		printf("3. 返回\n");
		getint(&phonemode); //获取数字
		if (phonemode == 1) //模式1
			goto phonemode1;
		else if (phonemode == 2) //模式2
			goto findmode1;
		else if (phonemode == 3) //模式3
			return ERROR;
		else //输入的模式不存在
			goto phonemode0;
	}

	//手机号码正确,重新创建密码
modifymode1:
	do //如果输入的密码一直不符合输入的要求，就一直卡在死循环里
	{
		printf("请输入新的密码(最少6个字符、最多20个字符): ");
		int length = getstring(MAX_PASSWORDSZ, user->data->password);
		if (length == -1) //输入的长度过长
			continue;	  //循环继续
		if (length < 6)	  //输入的长度过短
		{
			printf("设置的密码少于6个字符，请重新输入!\n");
			continue; //循环继续
		}
		break;
	} while (1);
modifymode2:
	do //如果输入的密码一直不符合输入的要求，就一直卡在死循环里
	{
		char str[MAX_PASSWORDSZ + 1] = {0};
		printf("请再次确认密码(最少6个字符、最多20个字符): ");
		int length = getstring(MAX_PASSWORDSZ, str);  //获取密码长度
		int flag = strcmp(str, user->data->password); //比较前后密码是否一致
		if (flag == 0)								  //密码一致退出循环
		{
			break;
		}
		else //密码不一致
		{
			printf("密码输入错误\n");
		modifymode0:
			printf("1. 重新设置密码\n");
			printf("2. 重新确认密码\n");
			printf("请选择功能: "); //让用户选择功能
			int mode = 0;
			mode = getint(&mode);
			if (mode == 1) //重新设置密码
			{
				goto modifymode1; //回到设置密码的页面
			}
			else if (mode == 2) //重新确认密码
			{
				goto modifymode2; //回到重新确认密码的页面
			}
			else //没有该功能
			{
				scanf("%*[^\n]%*c"); //清空缓冲区
				printf("没有该功能\n");
				printf("请选择已有的功能!\n");
				goto modifymode0; //回到重新确认密码的页面
			}
		}
	} while (1);

	printf("更改成功\n");
	FileUpdata(L); //更新文件数据
	return SUCCESS;
}

//用户登录
//登录成功，返回用户节点
UserNode *LogUser(UserList L, FileType file[], int *n, FileTree *Userrootfile)
{
	char struser[MAX_USERIDSZ + 1] = {0}; //存放用户名
	int errorflag = 0;					  //错误标志位
	UserList user;
	//输入用户名
passwordmode1:
	do
	{
		printf("用户名(不超过30个字符): ");
		if (-1 == getstring(MAX_USERIDSZ, struser)) //输入的用户名过长
		{
			continue;
		}
		user = SearchUser(L, struser); //寻找是否有该用户名
		if (user == NULL)			   //找不到该用户名
		{
			errorflag = 1; //错误标志位置1
			break;
		}
		else
			break;
	} while (1);

	//输入密码
	char strpassword[MAX_PASSWORDSZ + 1] = {0};
	do
	{
		printf("密码: ");
		int length = getstring(MAX_PASSWORDSZ, strpassword); //获取长度
		if (length == -1)									 //密码输入不规范
			continue;
		break;
	} while (1);

	int judgeflag = -1; //判断
	if (errorflag == 1) //用户名输入不匹配
	{
		errorflag = 0; //标志位清0
		printf("用户名输入错误\n");
	passwordmode3:
		printf("1. 重新输入\n");
		printf("2. 返回\n");
		printf("请选择模式: ");
		int passwordmode = 0;
		if (scanf("%d", &passwordmode))
		{
			if (passwordmode == 1)
			{
				goto passwordmode1;
			}
			else if (passwordmode == 2)
			{
				return NULL;
			}
			else
			{
				scanf("%*[^\n]%*c"); //清空缓冲区
				printf("没有该功能,请重新输入\n");
				goto passwordmode3;
			}
		}
		else
		{
			printf("输入错误\n");
			scanf("%*[^\n]%*c"); //清空缓冲区
			goto passwordmode3;
		}
	}
	else
	{
		judgeflag = strcmp(strpassword, user->data->password);
		if (judgeflag == 0) //密码输入正确
		{
			printf("登录成功\n");

			ReadFile(file, n, user->data->userfilename);					//给file初始化
			(*Userrootfile) = CreateFileTree(user->data->userid, file, *n); //创建一颗树，根节点是用户名的文件夹
			system("pause");
			return user;
		}
		else
		{
			printf("密码输入错误\n");
		passwordmode0:
			printf("1. 重新输入\n");
			printf("2. 返回\n");
			printf("请输入模式: ");
			int passwordmode = 0;
			if (scanf("%d", &passwordmode))
			{
				if (passwordmode == 1)
				{
					goto passwordmode1;
				}
				else if (passwordmode == 2)
				{
					return NULL;
				}
				else
				{
					scanf("%*[^\n]%*c"); //清空缓冲区
					printf("没有该功能,请重新输入\n");
					goto passwordmode0;
				}
			}
			else
			{
				printf("输入错误\n");
				scanf("%*[^\n]%*c"); //清空缓冲区
				goto passwordmode0;
			}
		}
	}
}
