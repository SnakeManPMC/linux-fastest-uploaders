/*

     Fastest Uploaders for DayDream/linux
             by Snake Man, PMC.
        Copyright (c) PMC 1996 - 2015.

 */

#include <dd.h>
#include <ddlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include "fastest.h"
#include "pmc.h"

struct dif *d;
Fastest FU;             /* struct from pmc.h */

FILE *datafile;

char cmdline[80];
char username[25];
char *endptr;
char buf[300];
char DizzyBuf[80];

unsigned long FileSize = 0;
int DizzyDate = 0, DizzyMonth = 0, cur_date = 0, newuser = 0;
int day, month, year, hour, min, c_day, c_month, c_year, c_hour, c_min;

/*
 ***************************************************************************
 ********[ My Bytes ]********************************************************
 *************************************************************************** */
int My_Bytes() /* if we have old userdatas */
{
	if (DizzyDate == 0)
	{
		FU.ZeroDay = (FU.ZeroDay + FileSize);
	}

	if (DizzyDate == 1)
	{
		FU.OneDay = (FU.OneDay + FileSize);
	}

	if (DizzyDate == 2)
	{
		FU.TwoDay = (FU.TwoDay + FileSize);
	}

	if (DizzyDate == 3)
	{
		FU.ThreeDay = (FU.ThreeDay + FileSize);
	}

	if (DizzyDate == 4)
	{
		FU.FourDay = (FU.FourDay + FileSize);
	}

	if (DizzyDate >= 5)
	{
		FU.Older = (FU.Older + FileSize);
	}

	fwrite(&FU, sizeof(Fastest), 1, datafile);
	return 0;
}

/*
 ****************************************************************************
 *********[ Me Search ]*******************************************************
 **************************************************************************** */
int Me_Search() /* search for me! */
{
	fseek(datafile, 0, SEEK_SET);
	fread(&FU, sizeof(Fastest), 1, datafile);

	if (feof(datafile))
	{
		strcpy(FU.User_Name, username);
		FU.ZeroDay = 0;
		FU.OneDay = 0;
		FU.TwoDay = 0;
		FU.ThreeDay = 0;
		FU.FourDay = 0;
		FU.Older = 0;

		My_Bytes();

		fclose(datafile);
		exit(1);
	}

	while (strcasecmp(username, FU.User_Name))
	{
		fread(&FU, sizeof(Fastest), 1, datafile);
		if (feof(datafile))
		{                    /* if end of database AND still no newuser... */
			newuser = 1; /* we have newuser, lets flag him */
			return 0;
		}
	}

	fseek(datafile, -sizeof(Fastest), SEEK_CUR);
	newuser = 0; /* no newuser here */
	return 0;
}

/*
 ***************************************************************************
 ********[ WriteNewbie ]*****************************************************
 *************************************************************************** */
int WriteNewbie() /* if we have new user uploading. */
{
	FU.ZeroDay = 0;
	FU.OneDay = 0;
	FU.TwoDay = 0;
	FU.ThreeDay = 0;
	FU.FourDay = 0;
	FU.Older = 0;

	if (DizzyDate == 0)
	{
		FU.ZeroDay = 0;
		FU.ZeroDay = (FU.ZeroDay + FileSize);
		FU.OneDay = 0;
		FU.TwoDay = 0;
		FU.ThreeDay = 0;
		FU.FourDay = 0;
		FU.Older = 0;
	}

	if (DizzyDate == 1)
	{
		FU.ZeroDay = 0;
		FU.OneDay = (FU.OneDay + FileSize);
		FU.TwoDay = 0;
		FU.ThreeDay = 0;
		FU.FourDay = 0;
		FU.Older = 0;
	}

	if (DizzyDate == 2)
	{
		FU.ZeroDay = 0;
		FU.OneDay = 0;
		FU.TwoDay = (FU.TwoDay + FileSize);
		FU.ThreeDay = 0;
		FU.FourDay = 0;
		FU.Older = 0;
	}

	if (DizzyDate == 3)
	{
		FU.ZeroDay = 0;
		FU.OneDay = 0;
		FU.TwoDay = 0;
		FU.ThreeDay = (FU.ThreeDay + FileSize);
		FU.FourDay = 0;
		FU.Older = 0;
	}

	if (DizzyDate == 4)
	{
		FU.ZeroDay = 0;
		FU.OneDay = 0;
		FU.TwoDay = 0;
		FU.ThreeDay = 0;
		FU.FourDay = (FU.FourDay + FileSize);
		FU.Older = 0;
	}

	if (DizzyDate == 5)
	{
		FU.ZeroDay = 0;
		FU.OneDay = 0;
		FU.TwoDay = 0;
		FU.ThreeDay = 0;
		FU.FourDay = 0;
		FU.Older = (FU.Older + FileSize);
	}

	if (DizzyDate > 5)
	{
		FU.ZeroDay = 0;
		FU.OneDay = 0;
		FU.TwoDay = 0;
		FU.ThreeDay = 0;
		FU.FourDay = 0;
		FU.Older = (FU.Older + FileSize);
	}

	strcpy(FU.User_Name, username);            /* username */
	fwrite(&FU, sizeof(Fastest), 1, datafile); /* write the wh0re */

	return 0;
}

/*
 ***************************************************************************
 ********[ DizzyCompute ]****************************************************
 *************************************************************************** */
void DizzyCompute()
{
	struct tm *tm; /* file time */
	/* struct tm *t; */
	time_t t;
	struct stat ft;

	stat(DizzyBuf, &ft); /* grab the file time */
	tm = localtime(&ft.st_mtime);

	day = tm->tm_mday;
	month = tm->tm_mon + 1;
	year = tm->tm_year;
	hour = tm->tm_hour;
	min = tm->tm_min;

/*
   (void *) t=time(0);
   tm=localtime(&t);


   struct tm *tm;
 */
	t = time(0);
	tm = localtime(&t);

	c_day = tm->tm_mday;
	c_month = tm->tm_mon + 1;
	c_year = tm->tm_year;
	c_hour = tm->tm_hour;
	c_min = tm->tm_min;

	if ((month - c_month) == 0)
	{
		DizzyDate = (c_day - day);
	}
	else
	{
		if (month == 1) /* if month is 1 */
		{
			DizzyDate = (c_day - day + 31);
		}
		if (month == 2) /* if month is 2 */
		{
			DizzyDate = (c_day - day + 29);
		}
		if (month == 3) /* if month is 3 */
		{
			DizzyDate = (c_day - day + 30);
		}
		if (month == 4) /* if month is 4 */
		{
			DizzyDate = (c_day - day + 30);
		}
		if (month == 5) /* if month is 5 */
		{
			DizzyDate = (c_day - day + 31);
		}
		if (month == 6) /* if month is 6 */
		{
			DizzyDate = (c_day - day + 30);
		}
		if (month == 7) /* if month is 7 */
		{
			DizzyDate = (c_day - day + 31);
		}
		if (month == 8) /* if month is 8 */
		{
			DizzyDate = (c_day - day + 31);
		}
		if (month == 9) /* if month is 9 */
		{
			DizzyDate = (c_day - day + 30);
		}
		if (month == 10) /* if month is 10 */
		{
			DizzyDate = (c_day - day + 31);
		}
		if (month == 11) /* if month is 11 */
		{
			DizzyDate = (c_day - day + 30);
		}
		if (month == 12) /* if month is 12 */
		{
			DizzyDate = (c_day - day + 31);
		}
	}
}

/* opening fastest database */
int DataBitch()
{
	strcpy(buf, "/home/bbs/doors/pmcfasts.dat");
	datafile = fopen(buf, "r+b");           /* open datafile */
	if (!datafile)
		datafile = fopen(buf, "w+b");   /* if not found, MAKE it */

	return 0;
}

/* unzip and get filesize */
int Unzipper()
{
	FILE *FileName; /* uploaded filename */
	FILE *checkDiz; /* file_id.diz temp'o */

	sprintf(cmdline, "unzip -o %s FILE_ID.DIZ file_id.diz -d /home/bbs/doors >/dev/null", buf);

	system(cmdline);

	strcpy(DizzyBuf, "/home/bbs/doors/file_id.diz");

	checkDiz = fopen("/home/bbs/doors/file_id.diz", "rt");
	if (!checkDiz)
	{
		checkDiz = fopen("/home/bbs/doors/FILE_ID.DIZ", "rt");
		if (!checkDiz)
		{
			printf("no fucking DIZZY here, lame zip :)\n");
			dd_close(d);
			exit(1);
		}
		strcpy(DizzyBuf, "/home/bbs/doors/FILE_ID.DIZ");
	}

	DizzyCompute();         /* dizzy date calculation */

	FileName = fopen(buf, "r");   /* open the parameter filename */
	fseek(FileName, 0, SEEK_END); /* zoom to end */
	FileSize = 0;                 /* make sure the size is zero */
	FileSize = ftell(FileName);   /* grab the position (filesize) */
	fclose(FileName);             /* close the filen */

	return 0;
}

/*
 ***************************************************************************
 ********[ The Main ]********************************************************
 *************************************************************************** */
int main(int argv, char *argc[])
{
	if (argv == 1)
	{
		printf("need to run from DayDream!\n");
		exit(1);
	}

	d = dd_initdoor(argc[1]);

	dd_getstrval(d, username, USER_HANDLE);
	dd_getstrval(d, buf, DOOR_PARAMS);

	Unzipper();     /* unzip & get filesize */
	DataBitch();    /* open fastest database */
	Me_Search();    /* search for user record */

	if (newuser == 1)
		WriteNewbie();           /* if we are newbie */
	if (newuser == 0)
		My_Bytes();              /* if we do have bytes */

	fclose(datafile); /* close files */
	unlink(DizzyBuf);
	unlink(DizzyBuf);
	dd_close(d);
	return 0;
}
