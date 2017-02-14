#include<windows.h>
#include<mysql.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma comment(lib,"libmysql.lib")

MYSQL_RES *res;
MYSQL_ROW row;

void my_connect(MYSQL *mysql);
void show_menu();
void inquire();
void my_op(MYSQL *mysql);
void show_all(MYSQL *mysql);
void add_book(MYSQL *mysql);
void del_book(MYSQL *mysql);
void del_by_id(MYSQL *mysql);
void del_by_na(MYSQL *mysql);
int main(void)
{
	MYSQL mysql;
	int n = 0;
	my_connect(&mysql);//连接
	show_menu();
	(void)scanf("%d",&n);
	while( n != 6)
	{
		switch( n )
		{
		case 1:
			show_all(&mysql);
			break;
		case 2:
			add_book(&mysql);
			break;
		case 3:
			del_book(&mysql);
			break;
		case 4:
		case 5:
		case 6:
			printf("\t该功能尚未实现\n");
		default:
			printf("\tplease in num at 1~6!:");
		}
		(void)scanf("%d",&n);
	}
	mysql_close(&mysql);//关闭
	return 0;
}

void my_op(MYSQL *mysql)
{
	if(mysql_query(mysql,"select * from tb_book"))
	{
		printf("query error %s\n",mysql_error(mysql));
	}
}
//查询所有书籍
void show_all(MYSQL *mysql)
{
	if( mysql_query(mysql,"select * from tb_book") )
		printf("select all error\n");
	else
	{
		res = mysql_store_result(mysql);
		if( mysql_num_rows(res) != NULL )
		{
			 printf("\t ════════════════════════════ \n");
			 printf("\t                 显 示 所 有 图 书 信 息                  \n");
			 printf("\t ════════════════════════════ \n");
			 printf("\t -------------------------------------------------------- \n");
			 while( (row = mysql_fetch_row(res)) )
			 {
				printf("\t图书编号%s   图书名%s   作者%s   出版社%s\n",row[0],row[1],row[2],row[3]);
			 }
		}
		else
		{
			printf("无记录\n");
		}
		mysql_free_result(res);
	}
	inquire();
}
void add_book(MYSQL *mysql)
{
    char id[10];       /*编号*/
    char *bookname;
    char *author;
    char *bookconcern;
    char *sql;    
    char dest[500] ={"  "};    

	printf("\t ════════════════════════════ \n");
    printf("\t                     添 加 图 书 信 息                    \n");
    printf("\t ════════════════════════════ \n");
    printf("\t 图书编号:");
    scanf("%s",id);   /*输入图书编号*/    
    
    sql="insert into tb_book values (";
    strcat(dest,sql);
    strcat(dest,"'");
    strcat(dest,id);
    strcat(dest,"', '");
	bookname = (char*)malloc(50);
    author = (char*)malloc(50);
    bookconcern = (char*)malloc(50);
    
    //不存在相同的编号            
    printf("\t 图书名:");
    scanf("%s",bookname);   /*输入图书名*/
    strcat(dest,bookname);    /*将图书编号追加到sql语句后面*/
    
    printf("\t 作者:");
    scanf("%s",author);    /*输入作者*/
    strcat(dest,"', '");
    strcat(dest,author);
    
    printf("\t 出版社:");
    scanf("%s",bookconcern);    /*输入出版社*/
    strcat(dest,"', '");
    strcat(dest,bookconcern);
    strcat(dest,"');");

	if( mysql_query(mysql,dest) != 0 )
	{
		printf("add error\n");
	}
	else
		printf("add success\n");
	inquire();
}
/*******
删除书籍
********/
void del_book(MYSQL *mysql)
{
	char ch[2];//判断如何删除图书。
	printf("\t ════════════════════════════ \n");
    printf("\t                     删 除 图 书 信 息                    \n");
    printf("\t ════════════════════════════ \n");
    printf("\t 1 - 按照图书编号删除");
	printf("\t 2 - 按照图书书名删除");
	printf("\n              ENTER YOUR CHOICE(1 or 2):");
	scanf("%s",&ch);
	if( strcmp(ch,"1") == 0 )
		del_by_id(mysql);
	else if( strcmp(ch,"2") == 0 )
		del_by_na(mysql);
	else
	{
		printf("\t 选择错误 没有该功能\n");
		inquire();
	}
}
void del_by_id(MYSQL *mysql)
{
	char id[10];       /*编号*/
	char dest[500] ={"  "};
	char *sql;
	printf("\t输入图书编号:");
	scanf("%s",id);   /*输入图书编号*/       
    sql="delete from tb_book where id = '";
	strcat(dest,sql);
	strcat(dest,id);
    strcat(dest,"'");
	if( mysql_query(mysql,dest) != 0 )
	{
		printf("\tdel_by_id error\n");
	}
	else
		printf("\tdel success\n");
	inquire();
}
void del_by_na(MYSQL *mysql)
{
	char *bookname;       /*编号*/
	char dest[500] ={"  "};
	char *sql;
	printf("\t输入图书书名:");
	bookname = (char*)malloc(50);//需要先分配内存。
	scanf("%s",bookname);
    sql="delete from tb_book where bookname = '";
	strcat(dest,sql);
	strcat(dest,bookname);
    strcat(dest,"'");
	if( mysql_query(mysql,dest) != 0 )
	{
		printf("\tdel_by_na error\n");
	}
	else
		printf("\tdel success\n");
	inquire();
}

/******
*连接数据库
*******/
void my_connect(MYSQL *mysql)
{
	char name[20];
	char pass[20];
	printf("\t ════════════════════════════ \n");
	printf("\t                 登     陆     信     息                  \n");
	printf("\t ════════════════════════════ \n");
	printf("\t -------------------------------------------------------- \n");
	printf("\t输入用户名：");
	fgets(name,20,stdin);
	printf("\t输入密  码：");
	fgets(pass,20,stdin);
	if( !mysql_init(mysql))
	{
		printf("init mysql error\n");
		return;
	}
	if(!mysql_real_connect(mysql,"localhost",name,pass,"db_database19",0,NULL,0))
	{
		printf("connect error %s\n",mysql_error(mysql));
		inquire();
	}
}
void inquire()
{
	char ch[2];
	printf("\t显示主菜单？（Y/N）:");
	scanf("%s",&ch);
	if( strcmp(ch,"Y") == 0 || strcmp(ch,"y") == 0)
		show_menu();
	else
	{
		printf("\t是否退出？（Y/N）:");
		scanf("%s",&ch);
		if( strcmp(ch,"Y") == 0 || strcmp(ch,"y") == 0)
			exit(0);
		show_menu();
	}
}
void show_menu()
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t╔═══════════════════════════╗\n");
    printf("\t║            Welcome To Lemon Books System             ║\n");
    printf("\t╠═══════════════════════════╣\n");
    printf("\t║\t 1 - 显示所有图书信息                           ║\n");
    printf("\t║\t 2 - 添加图书信息                               ║\n");
    printf("\t║\t 3 - 删除图书信息                               ║\n");
    printf("\t║\t 4 - 修改图书信息                               ║\n");
    printf("\t║\t 5 - 查询图书信息                               ║\n");
    printf("\t║\t 6 - 退出                                       ║\n");
    printf("\t╚═══════════════════════════╝\n");
    printf("\n              ENTER YOUR CHOICE(1-6):");
}
