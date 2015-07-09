#include <stdio.h>
#include <string.h>
#include "fastest.h"

#define MAXUSERS    200

struct Record
{
	char User_Name[25];
	unsigned long long ZeroDay; /* what the fuck is this long long ?? :) */
	unsigned long long OneDay;  /* flowers note: its 64bit integer == huge ;) */
	unsigned long long TwoDay;
	unsigned long long ThreeDay;
	unsigned long long FourDay;
	unsigned long long Older;
};

FILE *infile;
FILE *bulletinANS;
FILE *bulletinASC;
FILE *cfg_file;
int c = 0, i, dog = 0;
char daystatus[80];
char buf[1024];
struct Record pmc[MAXUSERS];
struct int_list *sorted;
unsigned long long tmptop[MAXUSERS];
unsigned long long alltotal = 0;

char temp[80];
char temp1[80];
char temp2[80];
int user_num;
char clr_frame[10];
char clr_header[10];
char clr_footer[10];
char clr_uname[10];
char clr_pos[10];
char clr_0day[10];
char clr_1day[10];
char clr_2day[10];
char clr_3day[10];
char clr_4day[10];
char clr_5day[10];
char clr_older[10];
char clr_total[10];
char clr_status[10];

/* defines the int-list */
struct int_list {
	int num;
	unsigned long long bytes;
	struct int_list *next;
};

/* inserts an id in the list sorted */
struct int_list *insert_sorted(struct int_list *l, int num, unsigned long long b) {
	struct int_list *tmp;

	if (l == NULL)
	{
		tmp = (struct int_list*)malloc(sizeof(struct int_list));
		tmp->num = num;
		tmp->bytes = b;
		tmp->next = NULL;
		l = tmp;
	}
	else if (l->bytes > b)
		l->next = insert_sorted(l->next, num, b);
	else if (l->bytes <= b)
	{
		tmp = (struct int_list*)malloc(sizeof(struct int_list));
		tmp->num = num;
		tmp->bytes = b;
		tmp->next = l;
		l = tmp;
	}
	return l;
}

struct int_list *sort_top(unsigned long long top[MAXUSERS]) {
	int i = 0;
	struct int_list *t = NULL;

	for (; i < MAXUSERS; i++)
		if (top[i])
			t = insert_sorted(t, i, top[i]);

	return t;
}

int Writer(char *fish)
{
	sorted = sort_top(tmptop);

	sprintf(temp, "%s.gfx", fish);

	bulletinANS = fopen(temp, "wt");
	if (!bulletinANS)
	{
		printf("error at %s!\n", temp);
		exit(1);
	}

	sprintf(temp, "%s.txt", fish);

	bulletinASC = fopen(temp, "wt");
	if (!bulletinASC)
	{
		printf("error at %s!\n", temp);
		exit(1);
	}

	sprintf(buf, "[2J[H%s", clr_header);
	fprintf(bulletinANS, buf);
	sprintf(buf, "[2J[H");
	fprintf(bulletinASC, buf);

	sprintf(buf, "%s                      fastest uploaders (c) pmc 1996-2015.\n", clr_header);
	fprintf(bulletinANS, buf);
	sprintf(buf, "                      fastest uploaders (c) pmc 1996-2015.\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s", daystatus); /* how many days writing */
	fprintf(bulletinANS, buf);
	sprintf(buf, " %s", daystatus);
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s.---------------------------------------------------------------------------.\n", clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " .---------------------------------------------------------------------------.\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, " | %spos  username       %s|  %s0day  %s|  %s1day  %s|   %s2day %s|   %s3day %s|   %s4day %s|  %solder %s|\n", clr_status, clr_frame, clr_status, clr_frame, clr_status, clr_frame, clr_status, clr_frame, clr_status, clr_frame, clr_status, clr_frame, clr_status, clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " | pos  username       |   0day |   1day |   2day |   3day |   4day |  older |\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s|---------------------+--------+--------+--------+--------+--------+--------|\n", clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " |---------------------+--------+--------+--------+--------+--------+--------|\n");
	fprintf(bulletinASC, buf);
	dog = 0;

	while (sorted)
	{
		dog++;
		if (dog == user_num + 1)
			break;
		sprintf(buf, " %s| %s%2d) %s%-15s %s| %s%6.0f %s| %s%6.0f %s| %s%6.0f %s| %s%6.0f %s| %s%6.0f %s| %s%6.0f %s|\n",
		        clr_frame, clr_pos, dog, clr_uname, pmc[sorted->num].User_Name,
		        clr_frame,
		        clr_0day, (float)(pmc[sorted->num].ZeroDay / (1024 * 1024)),
		        clr_frame,
		        clr_1day, (float)(pmc[sorted->num].OneDay / (1024 * 1024)),
		        clr_frame,
		        clr_2day, (float)(pmc[sorted->num].TwoDay / (1024 * 1024)),
		        clr_frame,
		        clr_3day, (float)(pmc[sorted->num].ThreeDay / (1024 * 1024)),
		        clr_frame,
		        clr_4day, (float)(pmc[sorted->num].FourDay / (1024 * 1024)),
		        clr_frame,
		        clr_older, (float)(pmc[sorted->num].Older / (1024 * 1024)), clr_frame);
		fprintf(bulletinANS, buf);

		sprintf(buf, " | %2d) %-15s | %6.0f | %6.0f | %6.0f | %6.0f | %6.0f | %6.0f |\n",
		        dog, pmc[sorted->num].User_Name,
		        (float)(pmc[sorted->num].ZeroDay / (1024 * 1024)),
		        (float)(pmc[sorted->num].OneDay / (1024 * 1024)),
		        (float)(pmc[sorted->num].TwoDay / (1024 * 1024)),
		        (float)(pmc[sorted->num].ThreeDay / (1024 * 1024)),
		        (float)(pmc[sorted->num].FourDay / (1024 * 1024)),
		        (float)(pmc[sorted->num].Older / (1024 * 1024)));
		fprintf(bulletinASC, buf);
		sorted = sorted->next;
	}

	sprintf(buf, " %s`---------------------------------------------------------------------------'\n", clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " `---------------------------------------------------------------------------'\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, "   %sfu daydream/linux %s -idea by lone wolf, coding flower/snake man (c) pmc[0m\n", clr_footer, Version);
	fprintf(bulletinANS, buf);
	sprintf(buf, "   fu daydream/linux %s -idea by lone wolf, coding flower/snake man (c) pmc\n", Version);
	fprintf(bulletinASC, buf);

	return 0;
}

int totalwrite(char *tfish)
{
	sorted = sort_top(tmptop);

	sprintf(temp, "%s.gfx", tfish);

	bulletinANS = fopen(temp, "wt");
	if (!bulletinANS)
	{
		printf("error at %s!\n", temp);
		exit(1);
	}

	sprintf(temp, "%s.txt", tfish);

	bulletinASC = fopen(temp, "wt");
	if (!bulletinASC)
	{
		printf("error at %s!\n", temp);
		exit(1);
	}

	sprintf(buf, "[2J[H%s", clr_header);
	fprintf(bulletinANS, buf);

	sprintf(buf, "                      fastest uploaders (c) pmc 1996-2015.\n");
	fprintf(bulletinANS, buf);
	sprintf(buf, "                      fastest uploaders (c) pmc 1996-2015.\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, "                           total uploaded bytes / user\n");
	fprintf(bulletinANS, buf);
	sprintf(buf, "                           total uploaded bytes / user\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s.---------------------------------------------------------------------------.\n", clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " .---------------------------------------------------------------------------.\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s| %spos  username       %s|                   %stotal megs                        %s|\n", clr_frame, clr_status, clr_frame, clr_status, clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " | pos  username       |                   total megs                        |\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s|---------------------+-----------------------------------------------------|\n", clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " |---------------------+-----------------------------------------------------|\n");
	fprintf(bulletinASC, buf);
	dog = 0;

	while (sorted)
	{
		dog++;
		if (dog == user_num + 1)
			break;
		sprintf(buf, " %s| %s%2d) %s%-15s %s|                     %s%6.0fmb                        %s|\n",
		        clr_frame, clr_pos, dog, clr_uname, pmc[sorted->num].User_Name,
		        clr_frame, clr_total,
		        (float)((pmc[sorted->num].ZeroDay + pmc[sorted->num].OneDay + pmc[sorted->num].TwoDay + pmc[sorted->num].ThreeDay + pmc[sorted->num].FourDay + pmc[sorted->num].Older) / (1024 * 1024)), clr_frame);

		fprintf(bulletinANS, buf);

		sprintf(buf, " | %2d) %-15s |                     %6.0fmb                        |\n",
		        dog, pmc[sorted->num].User_Name,
		        (float)((pmc[sorted->num].ZeroDay + pmc[sorted->num].OneDay + pmc[sorted->num].TwoDay + pmc[sorted->num].ThreeDay + pmc[sorted->num].FourDay + pmc[sorted->num].Older) / (1024 * 1024)));

		fprintf(bulletinASC, buf);
		sorted = sorted->next;
	}

	sprintf(buf, " %s|---------------------+-----------------------------------------------------|\n", clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " |---------------------+-----------------------------------------------------|\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s|    %sall users        %s|       %sall bytes:    %s%6.0fmb                        %s|\n", clr_frame, clr_status, clr_frame, clr_status, clr_total, (float)(alltotal / (1024 * 1024)), clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " |    all users        |       all bytes:    %6.0fmb                        |\n", (float)(alltotal / (1024 * 1024)));
	fprintf(bulletinASC, buf);

	sprintf(buf, " %s`---------------------------------------------------------------------------'\n", clr_frame);
	fprintf(bulletinANS, buf);
	sprintf(buf, " `---------------------------------------------------------------------------'\n");
	fprintf(bulletinASC, buf);

	sprintf(buf, "   %sfu daydream/linux %s -idea by lone wolf, coding flower/snake man (c) pmc[0m\n", clr_footer, Version);
	fprintf(bulletinANS, buf);
	sprintf(buf, "   fu daydream/linux %s -idea by lone wolf, coding flower/snake man (c) pmc\n", Version);
	fprintf(bulletinASC, buf);

	return 0;
}

int sortMySuff()
{
	/* created zeroday sorted list */

	strcpy(daystatus, "                            top 0 day uploaders\n");
	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].ZeroDay;
	Writer("pmcfast0");

	/* created oneday sorted list */
	strcpy(daystatus, "                            top 1 day uploaders\n");
	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].OneDay;
	Writer("pmcfast1");

	/* created twoday sorted list */
	strcpy(daystatus, "                            top 2 day uploaders\n");
	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].TwoDay;
	Writer("pmcfast2");

	/* created threeday sorted list */
	strcpy(daystatus, "                            top 3 day uploaders\n");
	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].ThreeDay;
	Writer("pmcfast3");

	/* created fourday sorted list */
	strcpy(daystatus, "                            top 4 day uploaders\n");
	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].FourDay;
	Writer("pmcfast4");

	/* created older sorted list */
	strcpy(daystatus, "                            top older uploaders\n");
	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].Older;
	Writer("pmcfast5");

	/* created allday sorted list */
	strcpy(daystatus, "                               all uploads\n");
	for (i = 0; i < c; i++)
	{
		tmptop[i] = pmc[i].ZeroDay + pmc[i].OneDay + pmc[i].TwoDay + pmc[i].ThreeDay + pmc[i].FourDay + pmc[i].Older;
		alltotal = (alltotal + tmptop[i]);
	}
	totalwrite("pmcfast6");

	return 0;
}

int Configread()
{
	/* lets read the how_many_users_to_list_in_the_bulletin & colors */
	cfg_file = fopen("fast.cfg", "rt");
	if (!cfg_file)
	{
		printf("error at fast.cfg!\n");
		exit(1);
	}

	fgets(temp, 80, cfg_file);
	user_num = atoi(temp);      /* how many users to list */
	fgets(temp1, 80, cfg_file); /* frame color */
	fgets(temp2, 80, cfg_file); /* header color */
	strncpy(clr_frame, temp1, strlen(temp1) - 1);
	strncpy(clr_header, temp2, strlen(temp2) - 1);

	fgets(temp1, 80, cfg_file); /* footer color */
	fgets(temp2, 80, cfg_file); /* pos color */
	strncpy(clr_footer, temp1, strlen(temp1) - 1);
	strncpy(clr_pos, temp2, strlen(temp2) - 1);

	fgets(temp1, 80, cfg_file); /* username color */
	fgets(temp2, 80, cfg_file); /* 0 day color */
	strncpy(clr_uname, temp1, strlen(temp1) - 1);
	strncpy(clr_0day, temp2, strlen(temp2) - 1);

	fgets(temp1, 80, cfg_file); /* 1 day color */
	fgets(temp2, 80, cfg_file); /* 2 day color */
	strncpy(clr_1day, temp1, strlen(temp1) - 1);
	strncpy(clr_2day, temp2, strlen(temp2) - 1);

	fgets(temp1, 80, cfg_file); /* 3 day color */
	fgets(temp2, 80, cfg_file); /* 4 day color */
	strncpy(clr_3day, temp1, strlen(temp1) - 1);
	strncpy(clr_4day, temp2, strlen(temp2) - 1);

	fgets(temp1, 80, cfg_file); /* older color */
	fgets(temp2, 80, cfg_file); /* total color */
	strncpy(clr_older, temp1, strlen(temp1) - 1);
	strncpy(clr_total, temp2, strlen(temp2) - 1);

	fgets(temp1, 80, cfg_file); /* status color */
	strncpy(clr_status, temp1, strlen(temp1) - 1);
}

void main(int argc, char *argv[])
{
	printf("\n\n\tFastest Uploaders %s (c) PMC 1996-2015.\n\n", Version);

	bzero(&pmc, sizeof(struct Record) * MAXUSERS);

	if (infile = fopen("pmcfasts.dat", "r"))
		while (fread(&pmc[c], sizeof(struct Record), 1, infile))
		{
			c++;
		}
	fclose(infile);

	Configread();

	fclose(cfg_file);

	/* zeroday sorting */

	sortMyStuff();
}
