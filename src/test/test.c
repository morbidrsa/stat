/* Copyright (c) 2012, Johannes Thumshirn
 * See COPYING for license details.
 */
#include "tinytest.h"
#include "tinytest_macros.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "csv.h"

static void test_csv(void* data)
{
	int retcnt;
	struct data *ret;
	FILE *f;
	char *filename = "test.csv";
	char *tmp = "1,2\n2,3\n1,1\n";

	/* This test takes no data */
	(void)data;

	/* Some pre-test setup */
	f = fopen(filename, "wb");
	if (!f) {
		fprintf(stderr, "Cannot open %s for writing\n", filename);
		perror("");
		goto end;
	}
	fwrite(tmp, 1, strlen(tmp), f);
	fflush(f);
	fclose(f);

	/* Fail if get_data_from_file does not return true */
	tt_assert(csv_get_data_from_file(filename, &ret, &retcnt) == true);
	/* Fail if retcnt != 3 */
	tt_assert(retcnt == 3);
	/* Fail if one of the elements in ret isn't like we want */
	tt_assert(ret[0].when == 1);
	tt_assert(ret[0].ammount == 2);
	tt_assert(ret[1].when == 2);
	tt_assert(ret[1].ammount == 3);
	tt_assert(ret[2].when == 1);
	tt_assert(ret[2].ammount == 1);

	/* remove test.csv after unit testing */
	unlink(filename);
end:
	;
}

static struct testcase_t csv_tests[] = {
	{ "csv", test_csv, },
	END_OF_TESTCASES
};

static struct testgroup_t testgroups[] = {
	{ "csv/", csv_tests },
	END_OF_GROUPS
};

int main(int argc, const char **argv)
{
	return tinytest_main(argc, argv, testgroups);
}
