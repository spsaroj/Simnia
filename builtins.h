#ifndef BUILTINS_H
#define BUILTINS_H
#include "strvec.h"
#include <stdio.h>
/*
 *  * builtins.h
 *   * \author Saroj Paudel
 *    * \Header file for builtins.h
 *     */

extern const char* BUILTINS[];
void _cd(const strvec * cmd);
extern const void (*FCNS[])(const strvec * cmd);

#endif
