#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char name[20] = "\0";
	char age[16] = "\0";
	char no[20] = "\0";
	char sex[32] = "\0";
	char sno[32] = "\0";
	char sign[32] = "\0";

	int status = 0;

	status = cgiFormString("name",  name, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}

	status = cgiFormString("age",  age, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get age error!\n");
		return 1;
	}

	status = cgiFormString("no",  no, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get no error!\n");
		return 1;
	}
	status = cgiFormString("sex",  sex, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}
	status = cgiFormString("sno",  sno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}
	status = cgiFormString("sign",  sign, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sign error!\n");
		return 1;
	}


 //fprintf(cgiOut, "name = %s,age = %s no = %s, stuId = %s\n", name, age, stuId)

	fprintf(cgiOut, " no= %s,name = %s, age = %s,sex= %s, sno= %s,sign=%s\n", no,name, age,sex,sno,sign);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	mysql_options(db,MYSQL_SET_CHARSET_NAME,"utf8");
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



	strcpy(sql, "create table information(no varchar(20) not null primary key, name varchar(20) not null,sex varchar(20) not null, age int not null,sno int not null,sign int not null)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return  -1;
		}
	}



	sprintf(sql, "insert into information values('%s', '%s','%s', %d, %d,%d)", no, name, sex, atoi(age),atoi(sno),atoi(sign));
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
