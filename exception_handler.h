#ifndef EXCEPTION_HANDLER_H_
#define EXCEPTION_HANDLER_H_

typedef enum {
	NULL_POINTER_EXCEPTION = 0,
	MEMORY_ALLOCATION_FAIL_EXCEPTION,
    EXCEPTION_3,
    EXCEPTION_4,
    EXCEPTION_5,
    EXCEPTION_6
} exception_t;

exception_t exception_list;

void exception_handler(char const * caller_name, exception_t exception);

#endif /* EXCEPTION_HANDLER_H_ */