#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "pgm.h"
#include "filtro.h"

#define TAM 100

int main(int argc, char *argv[])
{
	int k;
	clock_t begin, end;
	double time_per_img, time_total = 0;
	long long int a = 999999999;
	struct pgm img;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_type == DT_DIR)
			{
				continue;
			}
			if (!(strcmp(ent->d_name, "main.e")))
			{
				continue;
			}
			readPGMImage(&img, ent->d_name);
			begin = clock();
			int c = 0;
			int l = 0;

			int *pn = NULL;
			int *pb = NULL;
			int *pv2 = NULL;

			pv2 = malloc(sizeof(int) * img.c * img.r);
			pn = malloc(sizeof(int) * 8);
			pb = malloc(sizeof(int) * 8);

			for (c = 0; c < img.c; c++)
			{
				for (l = 0; l < img.r; l++)
				{
					getNeighbors(img.pData, l, c, img.c, pn, pb);
					*(pv2 + (l * img.c + c)) = getDecimal(pb);
				}
			}

			unsigned char hist[256] = {0};
			for (int k = 0; k < img.c * img.r; k++)
			{
				hist[*(pv2 + k)]++;
			}

			unsigned char name[TAM];
			strcpy(name, ent->d_name);

			FILE *pf;
			pf = fopen("Hist.csv", "ab");
			for (int i = 0; i <= 256; i++)
			{
				fprintf(pf, "%d,", hist[i]);
			}
			hist[256] = (int)name[0] - 48;

			fprintf(pf, "\n");
			fclose(pf);
			end = clock();
			time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
			time_total += time_per_img;
		}
		closedir(dir);
	}
	else
	{
		perror("");
		exit(3);
	}
	return 0;
}
