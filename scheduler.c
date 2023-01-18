#include "scheduler.h"
#include "linklist.h"

static struct sl_node_t **alarm_head = NULL;

void display_alarm(struct sl_node_t *head)
{
	scheduler_handle_t *temp = NULL;
	while(head)
	{
		temp = head->data;
		printf(">>>>>>>>>>%p %p>>>>>>>>>>>\n", head, head->data);
		printf("Scheduler index\t%d\n", temp->scheduler_index);
		printf("Scheduler start time\t%d:%d\n", temp->start_time.hour, temp->start_time.min );
		printf("Scheduler stop time\t%d:%d\n", temp->stop_time.hour, temp->stop_time.min);
		head = head->next;
		printf("<<<<<<<<<<<<<<<<<<<<<<\n");
	}
}

void init_alarm(void)
{
	alarm_head = SLlist_create(USER_DEFINED);
	sl_register_display(display_alarm);
}

void add_alarm(struct schedule_time start_time,
		struct schedule_time end_time, uint8_t schedule_day)
{
	static uint8_t index = 0;
	scheduler_handle_t *temp =
				(scheduler_handle_t *)malloc(sizeof(scheduler_handle_t));
	if(temp)
	{
		temp->scheduler_index = index++;
		printf("Inited :: %d\n", temp->scheduler_index);
		temp->start_time.hour = start_time.hour;
		temp->start_time.min = start_time.min;
		temp->stop_time.hour = end_time.hour;
		temp->stop_time.min = end_time.min;
		temp->schedule_day[schedule_day] = 1;
		temp->active_status = ACTIVE;

		SLlist_add_element(alarm_head, temp, sizeof(scheduler_handle_t));
	}
}


void disp_alarm(void)
{
	display_list(*alarm_head);
}


void schedule_alarm(struct tm *tm)
{
	static uint8_t flag = 0;
	struct sl_node_t *head = *alarm_head;
	scheduler_handle_t *temp = NULL;
	while(head)
	{
		temp = (scheduler_handle_t *)head->data;
		if(temp->active_status == ACTIVE && flag == 0)
		{
			if(temp->schedule_day[tm->tm_wday] == 1
					&& temp->start_time.hour == tm->tm_hour
					&& temp->start_time.min == tm->tm_min)
			{
				printf("Started alarm from Address :: %p\n", temp);
				temp->active_status = SCHEDULED;
				flag = 1;
				break;
			}
			else if(temp->schedule_day[ONE_TIME] == 1
					&& temp->start_time.hour == tm->tm_hour
					&& temp->start_time.min == tm->tm_min)
			{
				printf("Started one time alarm from Address :: %p\n", temp);
				temp->active_status = SCHEDULED;
				flag = 1;
				break;
			}
		}
		else if(temp->active_status == SCHEDULED)
		{
			if(temp->schedule_day[tm->tm_wday] == 1
					&& temp->stop_time.hour == tm->tm_hour
					&& temp->stop_time.min == tm->tm_min)
			{
				printf("Stopped alarm from Address :: %p\n", temp);
				flag = 0;
				temp->active_status = NOT_ACTIVE;
				break;
			}
			else if(temp->schedule_day[ONE_TIME] == 1
					&& temp->stop_time.hour == tm->tm_hour
					&& temp->stop_time.min == tm->tm_min)
			{
				printf("Stopped one time alarm from Address :: %p %d\n", temp, temp->scheduler_index);
				flag = 0;
				break;
			}
		}
		head = head->next;
	}
}
