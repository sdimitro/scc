#ifndef __ERRORMSG_H
#define __ERRORMSG_H

#include <stdbool.h>

extern bool EM_errors_exist;

void EM_newline(void);

extern int EM_tok_pos;

void EM_error(int, char *,...);
void EM_impossible(char *,...);
void EM_reset(char *);

#endif /* __ERRORMSG_H */

