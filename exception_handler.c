#include "exception_handler.h"

void exception_handler(char const * caller_name, exception_t exception)
{
    switch(exception)
    {
        case NULL_POINTER_EXCEPTION:
        {
            printf("%s caused NULL_POINTER_EXCEPTION\n", caller_name);
            break;
        }
        case MEMORY_ALLOCATION_FAIL_EXCEPTION:
        {
            printf("%s caused MEMORY_ALLOCATION_FAIL_EXCEPTION\n", caller_name);
            break;
        }
        default:
        {
            break;
        }
    }
}