#include "create_obj.h"


void setup_alarms(Scheduler *ptr)
{
	/**
	 * schedule_time structure simply combines hour and minutes.
	 * Here 22 is hour and 31 is minute. Uses 24 hour format.
	*/
	struct schedule_time start = {22, 31};
	struct schedule_time stop = {22, 32};
	printf("ADDRESS ::: %p %p %p\n", ptr, &(ptr->alarm_head), ptr->alarm_head);

	//create API, initializes an object of type scheduler type
	if(0 == create(ptr, SCHEDULER))
	{
		printf("Scheduler is ready to use\n");
		//addAlarm is method exposed to user to operate on scheduler data structure.
		ptr->addAlarm(start, stop, WEDNESDAY, ptr->alarm_head);
		ptr->addAlarm(start, stop, MONDAY, ptr->alarm_head);
		ptr->addAlarm(start, stop, SUNDAY, ptr->alarm_head);
		//Let's take an exception here by passing invalid argument
		ptr->addAlarm(start, stop, SUNDAY, NULL);
	}
}

void check_alarm_expired(struct tm *tm, Scheduler *ptr)
{
	ptr->scheduleAlarm(tm, ptr->alarm_head);
}

void main(void)
{
	/**
	 * Since this ain't even a pilot code,
	 * loop_breaker as name suggests it breaks the
	 * following while loop.
	*/
	int loop_breaker = 0;

	/**
	 * Creating a local variable of type Scheduler.
	 * Setting the element pointer to NULL.
	*/
	Scheduler my_schduler1;
	my_schduler1.alarm_head = NULL;

	/**
	 * setup_alarms function initialize my_scheduler1 variable
	 * to appropriate state.
	 * User can simply use exposed methods which operates on my_scheduler1
	 * data structure and does not need to be bothered about underlying implementation.
	*/
	setup_alarms(&my_schduler1);

	/**
	 * Loop for about 3 minutes and then break out of loop.
	*/
	while(loop_breaker < 180)
	{
		//Fetching current time date.
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		printf("now: %d %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_wday, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		//check whether alarm is scheduled for current time.
		check_alarm_expired(&tm, &my_schduler1);
		sleep(1);
		loop_breaker++;
	}
}
