/**
 * @file main.c
 * @author Vinogradov Aleksandr (vinogradov.alek@gmail.com)
 * @brief Crack for program CrackMe from Acronis entering task
 * @version 0.1
 * @date 2020-05-18
 * 
 * main idea is to calculate sum from id and then generate key suitable for sum from id, that will give sum form key equal to sum form id
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ID_MAX_LENGTH 3698
#define ID_EFFECTIVE_LENGHT 10
#define KEY_LENGHT 16

uint32_t id_calc_sum(const char *id);
char *key_generate(uint32_t id_sum);

int main(int argc, char const *argv[])
{
    argc--;
    argv++;
    if (argc != 1)
    {
        printf("usege:\t./main [Name]\n");
        return EXIT_FAILURE;
    }

    const char *id = *argv;
    uint32_t sum = id_calc_sum(id);
    //printf("id sum is 0x%X\n", sum);
    char *key = key_generate(sum);
    printf("Name   = %s\nSerial = %s\n", id, key);
    free(key);
    return 0;
}

uint32_t id_calc_sum(const char *id)
{
    size_t len = strlen(id);
    if(len > ID_MAX_LENGTH)
    {
        printf("Name is too long and it could broke program. Use with your own risk\n");
    }
    if(len > ID_EFFECTIVE_LENGHT)
    {
        len = ID_EFFECTIVE_LENGHT;
    }
    uint32_t sum = 0;
    for (size_t i = 0; i < len;i++)
    {
        if (id[i] < 0x41)
        {
            printf("id chars must be above or equal to code 0x41, or 'A' in ASCII\nid contains char: '%c'\n", id[i]);
            exit(EXIT_FAILURE);
        }
        sum += (id[i] >= 0x5A) ? id[i] - 0x20 : id[i];
    }
    sum ^= 0x5678;
    return sum;
}

char *key_generate(uint32_t id_sum)
{
    id_sum ^= 0x1234; // undo xor
    char *key = (char *)calloc(KEY_LENGHT, sizeof(char));
    // sum of key is just it's deciminal representation in string, in big-endian notation, so
    snprintf(key,KEY_LENGHT, "%d", id_sum);
    return key;
}
