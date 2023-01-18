#include "scheduler.h"

void setup_alarms(void)
{
	struct schedule_time start = {11, 19};
	struct schedule_time stop = {11, 20};
	init_alarm();
	add_alarm(start, stop, SUNDAY);
	start.hour = 16;
	start.min = 16;
	stop.hour = 16;
	stop.min = 17;
	add_alarm(start, stop, MONDAY);
	start.hour = 17;
	start.min = 17;
	stop.hour = 17;
	stop.min = 18;
	add_alarm(start, stop, ONE_TIME);
	start.hour = 18;
	start.min = 18;
	stop.hour = 18;
	stop.min = 19;
	add_alarm(start, stop, THURSDAY);
	disp_alarm();
}

void main(void)
{
	int loop_breaker = 0;
	setup_alarms();
	while(loop_breaker < 180)
	{
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		printf("now: %d %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_wday, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		schedule_alarm(&tm);
		sleep(1);
		loop_breaker++;
	}
}
