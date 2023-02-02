#include "create_obj.h"


bool_t create(void *data, uint8_t type)
{
    bool_t ret = FAIL;
    switch(type)
    {
        case SCHEDULER:
        {
            ret = instantiateScheduler(data);
            break;
        }
        default:
        {
            exception_handler(EXCEPTION_1);
            break;
        }
    }
}