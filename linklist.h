#ifndef GENERAL_PROGRAMS_LINKLIST_H_
#define GENERAL_PROGRAMS_LINKLIST_H_

#include "exception_handler.h"
#include "utils.h"

typedef enum{
	CHAR = 0,
	BYTE1,
	BYTE2,
	BYTE4,
	BYTE8,
	STRING,
	USER_DEFINED,
	TOTAL_TYPES
}datatypes_t;

struct sl_node_t{
	struct sl_node_t *next;
	void *data;
};

struct dl_node_t{
	struct dl_node_t *next;
	struct dl_node_t *prev;
	void *data;
};

struct list_t{
	unsigned char datatype;
	struct list_t *next;
	struct sl_node_t *head;
};

typedef void (*sl_disp_fptr)(struct sl_node_t *head);

void sl_list_init(void);
void sl_register_display(sl_disp_fptr ptr);
struct sl_node_t ** SLlist_create(unsigned char datatype);
void SLlist_add_element(struct sl_node_t **head, void *data, unsigned int datasize);
void display_list(struct sl_node_t * head);

#endif /* GENERAL_PROGRAMS_LINKLIST_H_ */
