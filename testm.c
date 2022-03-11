#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmemory.h"

typedef struct Data Data;
struct Data {
    int d1;
    const char *d2;
};

void dump_sp(const char *title, SharedPtr *sp)
{
    unsigned int frame_length = 64;
    unsigned int num_frame_symbols = 64 - strlen(title) - 2;
    unsigned int num_frame_symbols_left = num_frame_symbols / 2;
    unsigned int num_frame_symbols_right = num_frame_symbols % 2 == 0 ? num_frame_symbols / 2 : num_frame_symbols / 2 + 1;

    // Header
    for (unsigned int i = 0; num_frame_symbols_left > i; i++)
        printf("=");
    printf(" %s ", title);
    for (unsigned int i = 0; num_frame_symbols_right > i; i++)
        printf("=");
    printf("\n");

    // SharedPtr
    printf("is_available: %s\n", sp->is_available ? "true" : "false");
    printf("reference_counter-address: %p\n", sp->reference_counter);
    printf("reference_counter: ");
    if (sp->reference_counter)
        printf("%u\n", *sp->reference_counter);
    else
        printf("\n");
    printf("object-address: %p\n", sp->object);
    printf("\n");

    // Data
    Data *data = (Data *)(sp->object);
    if (data) {
        printf("Data d1: %d\n", data->d1);
        printf("Data d2: %c\n", *data->d2);
    }
    else
        printf("Data does not exists.\n");

    // Footer
    for (unsigned int i = 0; frame_length > i; i++)
        printf("=");
    printf("\n");

    printf("\n");
}

void dump_up(const char *title, UniquePtr *up)
{
    unsigned int frame_length = 64;
    unsigned int num_frame_symbols = 64 - strlen(title) - 2;
    unsigned int num_frame_symbols_left = num_frame_symbols / 2;
    unsigned int num_frame_symbols_right = num_frame_symbols % 2 == 0 ? num_frame_symbols / 2 : num_frame_symbols / 2 + 1;

    // Header
    for (unsigned int i = 0; num_frame_symbols_left > i; i++)
        printf("=");
    printf(" %s ", title);
    for (unsigned int i = 0; num_frame_symbols_right > i; i++)
        printf("=");
    printf("\n");

    // UniquePtr
    printf("is_available: %s\n", up->is_available ? "true" : "false");
    printf("object-address: %p\n", up->object);
    printf("\n");

    // Data
    Data *data = (Data *)(up->object);
    if (data) {
        printf("Data d1: %d\n", data->d1);
        printf("Data d2: %c\n", *data->d2);
    }
    else
        printf("Data does not exists.\n");

    // Footer
    for (unsigned int i = 0; frame_length > i; i++)
        printf("=");
    printf("\n");

    printf("\n");
}

void dump_data(const char *title, Data *data)
{
    unsigned int frame_length = 64;
    unsigned int num_frame_symbols = 64 - strlen(title) - 2;
    unsigned int num_frame_symbols_left = num_frame_symbols / 2;
    unsigned int num_frame_symbols_right = num_frame_symbols % 2 == 0 ? num_frame_symbols / 2 : num_frame_symbols / 2 + 1;

    // Header
    for (unsigned int i = 0; num_frame_symbols_left > i; i++)
        printf("=");
    printf(" %s ", title);
    for (unsigned int i = 0; num_frame_symbols_right > i; i++)
        printf("=");
    printf("\n");

    // Data
    if (data) {
        printf("Data d1: %d\n", data->d1);
        printf("Data d2: %c\n", *data->d2);
    }
    else
        printf("Data does not exists.\n");

    // Footer
    for (unsigned int i = 0; frame_length > i; i++)
        printf("=");
    printf("\n");

    printf("\n");
}

void shared_ptr_test1()
{
    Data *data = malloc(sizeof(Data));
    data->d1 = 300;
    data->d2 = "Hello";

    SharedPtr sp1 = create_sp(data);
    SharedPtr sp2 = copy_sp(sp1);

    dump_sp("create and copy sp1 to sp2 - sp1", &sp1);
    dump_sp("create and copy sp1 to sp2 - sp2", &sp2);

    ((Data *)(sp1.object))->d1 = 3;

    dump_sp("change d1 0 to 3 - sp1", &sp1);
    dump_sp("change d1 0 to 3 - sp2", &sp2);

    SharedPtr sp3 = move_sp(&sp2);

    dump_sp("move sp2 to sp3 - sp1", &sp1);
    dump_sp("move sp2 to sp3 - sp2", &sp2);
    dump_sp("move sp2 to sp3 - sp3", &sp3);

    destroy_sp(&sp1);

    dump_sp("free sp1 - sp1", &sp1);
    dump_sp("free sp1 - sp2", &sp2);
    dump_sp("free sp1 - sp3", &sp3);

    destroy_sp(&sp3);

    dump_sp("free sp3 - sp2", &sp2);
    dump_sp("free sp3 - sp3", &sp3);

    printf("data-address: %p\n", data);
    printf("Data d1: %d\n", data->d1);
    printf("Data d2: %c\n", *data->d2);
}

void unique_ptr_test1()
{
    Data *data = malloc(sizeof(Data));
    data->d1 = 10;
    data->d2 = "World";

    UniquePtr up1 = create_up(data);

    dump_up("create up1 - up1", &up1);

    UniquePtr up2 = move_up(&up1);

    dump_up("move up1 to up2 - up1", &up1);
    dump_up("move up1 to up2 - up2", &up2);

    ((Data *)(up2.object))->d1 = 20;

    dump_up("change d1 10 to 20 - up1", &up1);
    dump_up("change d1 10 to 20 - up2", &up2);

    UniquePtr up3 = move_up(&up2);

    dump_up("move up2 to up3 - up1", &up1);
    dump_up("move up2 to up3 - up2", &up2);
    dump_up("move up2 to up3 - up3", &up3);

    destroy_up(&up3);

    dump_up("destroy up3 - up1", &up1);
    dump_up("destroy up3 - up2", &up2);
    dump_up("destroy up3 - up3", &up3);

    printf("data-address: %p\n", data);
    printf("Data d1: %d\n", data->d1);
    printf("Data d2: %c\n", *data->d2);
}

void move_test1()
{
    Data *data1 = malloc(sizeof(Data));
    data1->d1 = 255;
    data1->d2 = "Memory management is very interesting.";

    dump_data("create data1 - data1", data1);

    Data *data2 = (Data *)move_ptr((void **)&data1);

    dump_data("move data1 to data2 - data1", data1);
    dump_data("move data1 to data2 - data2", data2);

    data2->d1 = 334;

    dump_data("change d1 255 to 334 - data1", data1);
    dump_data("change d1 255 to 334 - data2", data2);

    data1 = (Data *)move_ptr((void **)&data2);

    dump_data("move data2 to data1 - data1", data1);
    dump_data("move data2 to data1 - data2",  data2);

    free(data1);

    dump_data("free data1 - data1", data1);
    dump_data("free data1 - data2", data2);
}

int main(int argc, char **argv)
{
    // shared_ptr_test1();
    // unique_ptr_test1();
    move_test1();
    return EXIT_SUCCESS;
}
