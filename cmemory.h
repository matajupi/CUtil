#ifndef CMEMORY_H
#define CMEMORY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

/* 参照カウントでメモリを管理する. */
typedef struct SharedPtr SharedPtr;
struct SharedPtr {
    /* 有効なSharedPtrか表すフラグ. */
    bool is_available;
    /* 参照カウンタ. */
    unsigned int *reference_counter;
    /*
        参照しているオブジェクト.
        is_availableがfalseの時にアクセスすると動作は未定義.
    */
    void *object;
};

/*
    SharedPtrを作成して引数のオブジェクトと結びつける.
    イニシャライズを行うため必ずこの関数でSharedPtrを作成する.
*/
SharedPtr create_sp(void *obj);

/*
    SharedPtrをコピーする.
    SharedPtrをコピーするときは代入演算子ではなく必ずこの関数を用いる.
*/
SharedPtr copy_sp(SharedPtr sp);

/*
    SharedPtrをムーブする.
    引数は参照渡しであるので注意してもらいたい.
    SharedPtrをムーブするときは必ずこの関数を用いる.
    ムーブ元のSharedPtrはis_availableがfalseとなり、Objectへの参照動作は未定義となる.
*/
SharedPtr move_sp(SharedPtr *sp);

/*
    SharedPtrの指すオブジェクトを借用（一時的に生のポインタとして貸し出す）する.
    is_availableがfalseのときはNULLを返す.
*/
void *borrow_sp(SharedPtr sp);

/*
    参照先のSharedPtrを破棄する.
    引数は参照渡しであるので注意してもらいたい.
    SharedPtrを使い終わったら必ず呼び出す.
    SharedPtrのis_availableをfalseにする.
    そのため、この関数を呼び出したあとのSharedPtrからのObjectへの参照動作は未定義.
*/
void destroy_sp(SharedPtr *sp);


/* 所有権の単一化でメモリを管理する. */
typedef struct UniquePtr UniquePtr;
struct UniquePtr {
    /* 有効なUniquePtrか表すフラグ. */
    bool is_available;
    /*
        参照しているオブジェクト.
        is_availableがfalseの時にアクセスすると動作は未定義.
    */
    void *object;
};

/*
    UniquePtrを作成して引数のオブジェクトと結びつける.
    イニシャライズを行うため必ずこの関数でUniquePtrを作成する.
*/
UniquePtr create_up(void *obj);

/*
    UniquePtrをムーブする.
    引数は参照渡しであるので注意してもらいたい.
    UniquePtrではムーブ時に代入演算子は使用してはならない.
    借用させるときに代入演算子を用いる.
    また、ムーブ元のUniquePtrのis_availableをfalseにする.
    そのため、この関数を呼び出したあとのムーブ元のUniquePtrからのObjectへの参照動作は未定義.
*/
UniquePtr move_up(UniquePtr *up);

/*
    UniquePtrの指すオブジェクトを借用する.
    is_availableがfalseのときはNULLを返す.
*/
void *borrow_up(UniquePtr up);

/*
    UniquePtrを破棄する.
    引数は参照渡しであるので注意してもらいたい.
    UniquePtrのis_availableをfalseにする.
    そのため、この関数を呼び出したあとのUniquePtrからObjectへの参照動作は未定義.
*/
void destroy_up(UniquePtr *up);


/*
    sourceのObjectをムーブする.
    sourceにはNULLが代入される.
*/
void *move_ptr(void **source);

#endif // CMEMORY_H

