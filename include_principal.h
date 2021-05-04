#ifndef MAIN_INCLUDES
#define DEBUG 0
#define INT_MAX 2147483646
#define MAX_NOME 75
#define MAX_ARQ_BUFFER 256

#define DATA_HOME "./data/"
#define MIN_SINTOMAS 2
#define MAX_SINTOMAS 6
#define MAX_BUFFER_SINTOMAS 2 * MAX_SINTOMAS *MAX_NOME
#define MAX_BUFFER_DOENCAS 2 * MAX_SINTOMAS *MAX_NOME

#define MAX_SINTOMAS_BUSCA 25
#define MAX_DOENCAS_BUSCA 25

#define AUTO_SALVAR 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#endif