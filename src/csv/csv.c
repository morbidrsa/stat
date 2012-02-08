/* Copyright (c) 2012, Johannes Thumshirn */
/* See COPYING for Licence details */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <errno.h>

#include "csv.h"

struct csvctx {
	int refcnt;
	csv_callback *cb;
};

static struct csvctx *ctx = NULL;

bool csv_init(void)
{
	/* Check if we already have a context */
	if (ctx) {			/* if yes, return early */
		ctx->refcnt++;
		return true;
	}

	ctx = malloc(sizeof(struct csvctx));
	if (!ctx) {
		fprintf(stderr, "Cannot allocate memory for csv context\n");
		perror("");
		return false;
	}

	ctx->refcnt = 0;
	ctx->cb = NULL;

	return true;
}

void csv_free(void)
{
	/* Only free context structure if we hold no more references to it. */
	if (ctx->refcnt-- == 0) {
		free(ctx);
		ctx = NULL;			/* Set free()d memory to NULL, so we
						   can avoid double free()s */
	}
}

void csv_register_callback(csv_callback *cb)
{
	ctx->cb = cb;
}

void csv_unregister_callback(void)
{
	ctx->cb = NULL;
}

bool csv_get_data_from_file(char *fname, struct data **ret, int *retcnt)
{
	FILE *f;
	char tmp[256];
	char *tt;
	int col_cnt;
	int row_cnt;
	struct data *data;
	const char *delim = ",";

	if (!ctx->cb) {
		fprintf(stderr, "No callback registered\n");
		return false;
	}

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
				if (!ctx->cb(row_cnt, col_cnt, data, retcnt)) {
					fclose(f);
					fprintf(stderr,
						"Parse error on line %d\n",
						row_cnt);
					return false;
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
