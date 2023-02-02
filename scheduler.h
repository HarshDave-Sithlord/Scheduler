#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"
#include "linklist.h"
#include "exception_handler.h"

typedef enum {
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	ONE_TIME
} weekdays_t;

typedef enum {
	ACTIVE = 0,
	SCHEDULED,
	NOT_ACTIVE
}scheduler_state;

struct schedule_time{
	int hour;
	int min;
};

typedef struct{
	uint8_t	scheduler_index;
	struct schedule_time start_time;
	struct schedule_time stop_time;
	uint8_t active_status;
	//TODO: change the following array to bitmap.
	uint8_t schedule_day[8];
} scheduler_handle_t;

typedef void (*addalarm)(struct schedule_time start_time, struct schedule_time end_time, uint8_t schedule_day, struct sl_node_t **alarm_head);
typedef void (*schedulealarm)(struct tm *tm, struct sl_node_t **alarm_head);
typedef void (*dispalarm)(struct sl_node_t **alarm_head);

typedef struct{
	//Data
	struct sl_node_t *alarm_head;
	scheduler_handle_t handle;
	//Functions
	dispalarm displayAlarm;
	schedulealarm scheduleAlarm;
	addalarm addAlarm;
} Scheduler;

//Expose it to create_obj module.
bool_t instantiateScheduler(Scheduler *ptr);

#endif /* SCHEDULER_H_ */
