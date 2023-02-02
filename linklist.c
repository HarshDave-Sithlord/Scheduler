#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"

static struct list_t *list_head = NULL;
static sl_disp_fptr sl_disp[TOTAL_TYPES];

static void SLlist_display_char(struct sl_node_t * head)
{
	while(head)
	{
		printf("%c ->\t", *(char *)head->data);
		head = head->next;
	}
	printf("\n");
}

static void SLlist_display_byte1(struct sl_node_t * head)
{
	while(head)
	{
		printf("%d ->\t", *(unsigned char *)head->data);
		head = head->next;
	}
	printf("\n");
}

static void SLlist_display_byte2(struct sl_node_t * head)
{
	while(head)
	{
		printf("%d ->\t", *(unsigned short *)head->data);
		head = head->next;
	}
	printf("\n");
}

static void SLlist_display_byte4(struct sl_node_t * head)
{
	while(head)
	{
		printf("%d ->\t", *(unsigned int *)head->data);
		head = head->next;
	}
	printf("\n");
}

static void SLlist_display_byte8(struct sl_node_t * head)
{
	while(head)
	{
		printf("%5.4f ->\t", *(double *)head->data);
		head = head->next;
	}
	printf("\n");
}


static void SLlist_display_string(struct sl_node_t * head)
{
	while(head)
	{
		printf("%c %c %c %c %c %c ->\t", *(char *)head->data, *(char *)head->data + 1,
				*(char *)head->data + 2,*(char *)head->data + 3,
				*(char *)head->data + 4, *(char *)head->data + 5);
		head = head->next;
	}
	printf("\n");
}

static void SLlist_display_default(struct sl_node_t *head)
{
	;//eat 5star and do nothing
}

void sl_list_init(void)
{
	sl_disp[CHAR] = SLlist_display_char;
	sl_disp[BYTE1] = SLlist_display_byte1;
	sl_disp[BYTE2] = SLlist_display_byte2;
	sl_disp[BYTE4] = SLlist_display_byte4;
	sl_disp[BYTE8] = SLlist_display_byte8;
	sl_disp[STRING] = SLlist_display_string;
	sl_disp[USER_DEFINED] = SLlist_display_default;
}

void sl_register_display(sl_disp_fptr ptr)
{
	if(ptr)
	{
		sl_disp[USER_DEFINED] = ptr;
	}
	else
	{
		exception_handler(__func__, NULL_POINTER_EXCEPTION);
	}
}

/**
 * list_t is strcuture that can hold N list and N datatype.
 * It is top level linklist, which holds other N linklists
 * of primitive and non-primitive datatypes.
 * Here we create a head of control linklist and return address of
 * pointer which is going to hold sub-linklist of some X datatype
*/
struct sl_node_t ** SLlist_create(unsigned char datatype)
{
	struct list_t *temp = (struct list_t *)malloc(sizeof(struct list_t));
	if(temp)
	{
		temp->datatype = datatype;
		temp->head = NULL;
		temp->next = NULL;

		if(list_head == NULL)
		{
			list_head = temp;
		}
		else
		{
			temp->next = list_head;
			list_head = temp;
		}
	}
	else
	{
		exception_handler(__func__, NULL_POINTER_EXCEPTION);
	}

	printf("%p and %p\n", &temp->head, temp->head);
	return &temp->head;
}

void SLlist_add_element(struct sl_node_t **head, void *data, unsigned int datasize)
{
	//Taking double pointer as we are mimicing stack storage.
	if(data)
	{
		struct sl_node_t *temp = (struct sl_node_t *)malloc(sizeof(struct sl_node_t));
		if(temp)
		{
			temp->data = malloc(datasize + 1);
			memset(temp->data, '\0', datasize+1);
			memcpy(temp->data, data, datasize);

			temp->next = NULL;

			if(*head == NULL)
			{
				*head = temp;
			}
			else
			{
				temp->next = *head;
				*head = temp;
			}
		}
		else
		{
			exception_handler(__func__, MEMORY_ALLOCATION_FAIL_EXCEPTION);
		}
	}
	else
	{
		exception_handler(__func__, NULL_POINTER_EXCEPTION);
	}
}

void display_list(struct sl_node_t * head)
{
	struct list_t *temp = list_head;
	while(temp)
	{
		printf("Datatype is :: %d %p\n", temp->datatype, head);
		if(temp->head == head)
		{
			sl_disp[temp->datatype](head);
			break;
		}
		temp = temp->next;
	}
}
