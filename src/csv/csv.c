/* Copyright (c) 2012, Johannes Thumshirn */
/* See COPYING for Licence details */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <errno.h>

#include "csv.h"

bool csv_get_data_from_file(char *fname, struct data **ret, int *retcnt)
{
	FILE *f;
	char tmp[256];
	char *tt;
	int col_cnt;
	int row_cnt;
	struct data *data;
	const char *delim = ",";

	/* Initialize variables */
	row_cnt = 0;
	col_cnt = 0;

	/* Open fname for reading */
	f = fopen(fname, "r");
	if (f == NULL) {
		fprintf(stderr, "Could not open datafile %s: %s\n", fname,
			strerror(errno));
		return false;
	}

	/* Allocate memory for 1st row */
	data = malloc(sizeof(struct data));
	if (data == NULL)
		goto error;

	while (!feof(f)) {
		if (fgets(tmp, sizeof(tmp) - 1, f) != NULL) {
			tt = strtok(tmp, delim);
			if (row_cnt > 0) {
				data = realloc(data,
						sizeof(struct data) *
						(row_cnt + 1));
				if (data == NULL)
					goto error;
			}
			while (tt != NULL) {
				switch (col_cnt) {
				case 0:
					data[row_cnt].when = atoi(tt);
					break;
				case 1:
					data[row_cnt].ammount = atoi(tt);
					break;
				}
				col_cnt++;
				tt = strtok(NULL, delim);
			}
			row_cnt++;
			col_cnt = 0;
		}
	}

	fclose(f);

	*ret = data;
	*retcnt = row_cnt;
	return true;

error:
	fclose(f);
	fprintf(stderr, "Could not allocate memory for data structure: %s\n",
		strerror(errno));
	return false;
}
