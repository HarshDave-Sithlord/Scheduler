#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

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
	uint8_t schedule_day[8];//Can be translated to bitmap
} scheduler_handle_t;

#endif /* SCHEDULER_H_ */
