/*

    this bitch displays the logfile into the screen.

 */

#include <stdio.h>
#include <pmc.h>

FILE *datafile;

Fastest FU;

int i = 0;

int ViewLog()
{
	datafile = fopen("pmcfasts.dat", "rb");
	if (!datafile)
	{
		printf("error at pmcfasts.dat!\n");
		exit (1);
		return 1;
	}

	while (!feof(datafile))
	{
		i++;
		fread(&FU, sizeof(Fastest), 1, datafile);
		if (feof(datafile))
			break;
		printf("********************************\n");
		printf("user-record number: %i of database\n", i);
		printf("Username: %s\n", FU.User_Name);
		printf("zeroday  %llu bytes\n", FU.ZeroDay);
		printf("oneday   %llu bytes\n", FU.OneDay);
		printf("twoday   %llu bytes\n", FU.TwoDay);
		printf("threeday %llu bytes\n", FU.ThreeDay);
		printf("fourday  %llu bytes\n", FU.FourDay);
		printf("older    %llu bytes\n", FU.Older);
	}
	printf("********************************\n");

	fclose(datafile);
	exit (1);
	return 0;
}

int main()
{
	ViewLog();

	return 0;
}