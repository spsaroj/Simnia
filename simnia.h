#ifndef SIMNIA_H
#define SIMNIA_H

/*
 * simnia.h
 * \author Saroj Paudel
 * \Header file for simnia.c
 */

void prompt();
void read_cmd(strvec * cmd);
void exec_cmd(const strvec * cmd);

#endif