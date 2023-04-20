#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct time {
	int hours, mins;
};

void print_usage_and_exit(const char *argv0)
{
	printf("Usage %s: [-t times]\n", argv0);
	exit(EXIT_FAILURE);
}

struct time time_parse(const char *time_str)
{
	char *minute_str = strchr(time_str, ':') + 1;
	int hour_num_cnt = minute_str - time_str - 1;
	char *hour_str = malloc(sizeof(char) * hour_num_cnt);

	memcpy(hour_str, time_str, sizeof(char) * hour_num_cnt);

	int hours_num = atoi(hour_str);
	int mins_num = atoi(minute_str);

	free(hour_str);

	return (struct time){hours_num, mins_num};
}

int time_get_as_mins(struct time t)
{
	return t.hours * 60 + t.mins;
}

struct time time_get_from_mins(int min)
{
	struct time t;

	t.hours = min / 60;
	t.mins = min % 60;

	return t;
}

struct time time_get_diff(struct time a, struct time b)
{
	int am, bm;

	am = time_get_as_mins(a);
	bm = time_get_as_mins(b);

	return time_get_from_mins(bm - am);
}

struct time time_add(struct time a, struct time b)
{
	int ta, tb;

	ta = time_get_as_mins(a);
	tb = time_get_as_mins(b);

	return time_get_from_mins(ta + tb);
}

int main(int argc, char **argv)
{
	if(argc == 1) {
		print_usage_and_exit(*argv);
	}

	struct time time_total = {0, 0};

	for(int i = 1; i < argc; i++) {
		struct time a, b, diff;
		int next = i + 1;

		if(!strchr(argv[i], ':')) {
			printf("Invalid time input.\n");
			print_usage_and_exit(*argv);
		}

		if(next >= argc)
			continue;

		a = time_parse(argv[i]);
		b = time_parse(argv[next]);
		diff = time_get_diff(a, b);
		time_total = time_add(time_total, diff);

		printf("%d:%d%d to %d:%d%d = %dh %dm (diff: %dh %dm)\n",
				a.hours, a.mins / 10, a.mins % 10,
				b.hours, b.mins / 10, b.mins % 10,
				time_total.hours, time_total.mins,
				diff.hours, diff.mins);
	}

	return 0;
}
