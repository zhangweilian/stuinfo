#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char cname[32] = "\0";
	char cno[32] = "\0";
	char no[32] = "\0";
	char cgrade[32] = "\0";

	int status = 0;

	status = cgiFormString("cname",  cname, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cname error!\n");
		return 1;
	}

	status = cgiFormString("cno",  cno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("no",  no, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get no error!\n");
		return 1;
	}
	status = cgiFormString("cgrade",  cgrade, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cgrade error!\n");
		return 1;
	}




	fprintf(cgiOut, " no= %s,cno = %s, cname= %s,cgrade= %s\n", no,cno,cname,cgrade);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	strcpy(sql, "create table score(no int not null,cno int not null primary key,cname varchar(20) not null, cgrade int not null)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return  -1;
		}
	}



	sprintf(sql, "insert into score values(%d, %d,'%s', %d)", atoi(no), atoi(cno), cname, atoi(cgrade));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
