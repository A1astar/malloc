/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:06:58 by alacroix          #+#    #+#             */
/*   Updated: 2026/02/02 14:46:44 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/malloc.h"
#include <stdio.h>
#include <pthread.h>
#define MAX_PTR 10
#define NB_THREADS 4

typedef struct s_thread_data
{
    size_t id;
    size_t succes;
    size_t failed;
} t_thread_data;

void error(char *msg)
{
    ft_printf("Error: %s\n", msg);
    exit(1);
}

void malloc_tests()
{
    ft_printf(BLUE BOLD "Malloc tests:\n" RESET);

    ft_printf(ITALIC BOLD " • tiny allocs\n" RESET);
    void *tiny_ptr[MAX_PTR] = {NULL};
    size_t tiny_size = 10;

    for (size_t i = 0; i < MAX_PTR; i++)
    {
        tiny_size += 2;
        tiny_ptr[i] = malloc(tiny_size);
        ft_printf("malloc(%z) -> %p ", tiny_size, tiny_ptr[i]);
        if (!tiny_ptr[i])
            ft_printf(BOLD RED "[ALLOC FAILED!] " RESET);
        else
            ft_printf(BOLD GREEN "[ALLOC SUCCESS!] " RESET);
        if ((uintptr_t)tiny_ptr[i] % 16 == 0)
            ft_printf(BOLD GREEN "[ALIGN OK!]\n" RESET);
        else
            ft_printf(BOLD RED "[NOT ALIGN!]\n" RESET);
    }

    ft_printf(ITALIC BOLD " • small allocs\n" RESET);
    void *small_ptr[MAX_PTR] = {NULL};
    size_t small_size = 80;

    for (size_t i = 0; i < MAX_PTR; i++)
    {
        small_size += 50;
        small_ptr[i] = malloc(small_size);
        ft_printf("malloc(%z) -> %p ", small_size, small_ptr[i]);
        if (!small_ptr[i])
            ft_printf(BOLD RED "[ALLOC FAILED!] " RESET);
        else
            ft_printf(BOLD GREEN "[ALLOC SUCCESS!] " RESET);
        if ((uintptr_t)small_ptr[i] % 16 == 0)
            ft_printf(BOLD GREEN "[ALIGN OK!]\n" RESET);
        else
            ft_printf(BOLD RED "[NOT ALIGN!]\n" RESET);
    }

    ft_printf(ITALIC BOLD " • large allocs\n" RESET);
    void *large_ptr[MAX_PTR] = {NULL};
    size_t large_size = 1000;

    for (size_t i = 0; i < MAX_PTR; i++)
    {
        large_size *= 2;
        large_ptr[i] = malloc(large_size);
        ft_printf("malloc(%z) -> %p ", large_size, large_ptr[i]);
        if (!large_ptr[i])
            ft_printf(BOLD RED "[ALLOC FAILED!] " RESET);
        else
            ft_printf(BOLD GREEN "[ALLOC SUCCESS!] " RESET);
        if ((uintptr_t)large_ptr[i] % 16 == 0)
            ft_printf(BOLD GREEN "[ALIGN OK!]\n" RESET);
        else
            ft_printf(BOLD RED "[NOT ALIGN!]\n" RESET);
    }

    ft_printf(ITALIC BOLD " • show alloc\n" RESET);
    show_alloc_mem();

    ft_printf(ITALIC BOLD " • free\n" RESET);
    for (size_t i = 0; i < MAX_PTR; i++)
    {
        ft_printf("free(%p)\n", tiny_ptr[i]);
        ft_printf("free(%p)\n", small_ptr[i]);
        ft_printf("free(%p)\n", large_ptr[i]);
        free(tiny_ptr[i]);
        free(small_ptr[i]);
        free(large_ptr[i]);
    }

    ft_printf(ITALIC BOLD " • show alloc\n" RESET);
    show_alloc_mem();
}

void realloc_tests()
{
    ft_printf(BLUE BOLD "Realloc tests:\n" RESET);

    ft_printf(ITALIC BOLD " • realloc(NULL, 400)\n" RESET);
    void *ptr = realloc(NULL, 400);
    ft_printf("realloc(NULL, 400) -> %p\n", ptr);
    show_alloc_mem();
    if (!ptr)
        ft_printf(BOLD RED "new allocation [FAILED!]\n\n" RESET);
    else
        ft_printf(BOLD GREEN "new allocation [SUCCESS!]\n\n" RESET);

    ft_printf(ITALIC BOLD " • realloc(ptr, 0)\n" RESET);
    void *ptr2 = realloc(ptr, 0);
    ft_printf("realloc(%p, 0) -> %p\n",ptr, ptr2);
    show_alloc_mem();
    if (ptr2)
    {
        ft_printf(BOLD RED "free current ptr [FAILED!]\n\n" RESET);
        free(ptr2);
    }
    else
        ft_printf(BOLD GREEN "free current ptr [SUCCESS!]\n\n" RESET);

    ft_printf(ITALIC BOLD " • realloc shrink\n" RESET);
    size_t original_size = 1000;
    size_t new_size = 200;

    unsigned char *origin_ptr = (unsigned char *)malloc(original_size);
    ft_printf("malloc(%z) -> %p\n", original_size, origin_ptr);
    if (!origin_ptr)
        error("Cannot create origin_ptr (Malloc failed)");

    for (size_t i = 0; i < original_size; i++)
        origin_ptr[i] = 0xff;

    unsigned char *shrinked_ptr = realloc(origin_ptr, new_size);
    ft_printf("realloc(%p, %z) -> %p\n", origin_ptr, new_size, shrinked_ptr);
    show_alloc_mem();
    if (!shrinked_ptr)
        error("Cannot create shrinked ptr (realloc failed)");
    int failed = 0;
    for (size_t i = 0; i < new_size; i++)
    {
        if (shrinked_ptr[i] != 0xff)
        {
            failed = 1;
            break;
        }
    }
    if (failed == 1)
        ft_printf(BOLD RED "data unpreserved [FAILED!]\n\n" RESET);
    else
        ft_printf(BOLD GREEN "data preserved [SUCCESS!]\n\n" RESET);
    free(shrinked_ptr);

    ft_printf(ITALIC BOLD " • realloc grow\n" RESET);
    original_size = 200;
    new_size = 1000;

    unsigned char *origin_ptr2 = (unsigned char *)malloc(original_size);
    ft_printf("malloc(%z) -> %p\n", original_size, origin_ptr2);
    if (!origin_ptr)
        error("Cannot create origin_ptr (Malloc failed)");

    for (size_t i = 0; i < original_size; i++)
        origin_ptr2[i] = 0xff;

    unsigned char *grow_ptr = realloc(origin_ptr2, new_size);
    ft_printf("realloc(%p, %z) -> %p\n", origin_ptr2, new_size, grow_ptr);
    show_alloc_mem();
    if (!grow_ptr)
        error("Cannot create shrinked ptr (realloc failed)");
    failed = 0;
    for (size_t i = 0; i < original_size; i++)
    {
        if (grow_ptr[i] != 0xff)
        {
            failed = 1;
            break;
        }
    }
    if (failed == 1)
        ft_printf(BOLD RED "data unpreserved [FAILED!]\n" RESET);
    else
        ft_printf(BOLD GREEN "data preserved [SUCCESS!]\n" RESET);
    grow_ptr[new_size - 1] ^= 0xff;
    ft_printf(BOLD GREEN "new size available for writing [SUCCESS!]\n\n" RESET);
    free(grow_ptr);
}

void *malloc_thread(void *arg)
{
    t_thread_data *thread_data = (t_thread_data *)arg;

    void *tiny_ptr[MAX_PTR] = {NULL};
    void *small_ptr[MAX_PTR] = {NULL};
    void *large_ptr[MAX_PTR] = {NULL};

    size_t tiny_size = 10;
    size_t small_size = 80;
    size_t large_size = 1000;

    for (size_t i = 0; i < MAX_PTR; i++)
    {
        tiny_size += 2;
        small_size += 50;
        large_size *= 2;

        tiny_ptr[i] = malloc(tiny_size);
        small_ptr[i] = malloc(small_size);
        large_ptr[i] = malloc(large_size);

        if (!tiny_ptr[i])
            thread_data->failed++;
        else
            thread_data->succes++;

        if (!small_ptr[i])
            thread_data->failed++;
        else
            thread_data->succes++;

        if (!large_ptr[i])
            thread_data->failed++;
        else
            thread_data->succes++;
    }
    for (size_t i = 0; i < MAX_PTR; i++)
    {
       free(tiny_ptr[i]);
       free(small_ptr[i]);
       free(large_ptr[i]);
    }
    return NULL;
}

void concurrent_malloc()
{
    ft_printf(BLUE BOLD "concurrent malloc:\n" RESET);

    pthread_t threads[NB_THREADS];
    t_thread_data thread_data[NB_THREADS] = {0};

    for (int i = 0; i < NB_THREADS; i++)
    {
        thread_data[i].id = i + 1;
        int val = pthread_create(&threads[i], NULL, malloc_thread, &thread_data[i]);
        if (val != 0)
            error("Cannot create thread");
    }

    for (int i = 0; i < NB_THREADS; i++)
        pthread_join(threads[i], NULL);

    size_t total_success = 0;
    size_t total_fail = 0;
    for (int i = 0; i < NB_THREADS; i++)
    {
        total_success += thread_data[i].succes;
        total_fail += thread_data[i].failed;
    }
    ft_printf("Total: succes: %z, failed: %z\n", total_success, total_fail);
    if(total_fail == 0)
        ft_printf(BOLD GREEN "alloc/free in threads [SUCCESS!]\n" RESET);
    else
        ft_printf(BOLD RED "alloc/free in threads [FAILED!]\n" RESET);
}

int main(void)
{
    malloc_tests();
    ft_printf("\n");

    realloc_tests();
    ft_printf("\n");

    concurrent_malloc();
    ft_printf("\n");

    return 0;
}
