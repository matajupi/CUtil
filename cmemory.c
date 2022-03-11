#include "cmemory.h"

SharedPtr create_sp(void *obj)
{
    SharedPtr sp;

    sp.is_available = true;
    sp.reference_counter = malloc(sizeof(unsigned int));
    *sp.reference_counter = 1;
    sp.object = obj;

    return sp;
}

SharedPtr copy_sp(SharedPtr sp)
{
    if (sp.is_available)
        (*sp.reference_counter)++;
    return sp;
}

SharedPtr move_sp(SharedPtr *sp)
{
    SharedPtr new_sp = copy_sp(*sp);
    destroy_sp(sp);
    return new_sp;
}

void *borrow_sp(SharedPtr sp)
{
    return sp.is_available ? sp.object : NULL;
}

void destroy_sp(SharedPtr *sp)
{
    if (!sp->is_available)
        return;
    sp->is_available = false;
    (*sp->reference_counter)--;
    if (*sp->reference_counter == 0) {
        free(sp->object);
        free(sp->reference_counter);
    }
    sp->object = NULL;
    sp->reference_counter = NULL;
}

UniquePtr create_up(void *obj)
{
    UniquePtr up;

    up.is_available = true;
    up.object = obj;

    return up;
}

UniquePtr move_up(UniquePtr *up)
{
    UniquePtr new_up = create_up(up->object);

    up->is_available = false;
    up->object = NULL;

    return new_up;
}

void *borrow_up(UniquePtr up)
{
    return up.is_available ? up.object : NULL;
}

void destroy_up(UniquePtr *up)
{
    up->is_available = false;
    free(up->object);
    up->object = NULL;
}

void *move_ptr(void **source)
{
    void *dest = *source;
    *source = NULL;
    return dest;
}

