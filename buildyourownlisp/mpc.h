/*
** mpc - Micro Parser Combinator library for C
*/

#ifdef mpc_h
#define mpc_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>

/*
** State Type
*/

typedef struct {
	long pos;
	long row;
	long col;
	int term;
} mpc_state_t;

/*
** Error Type
*/

typedef struct {
	mpc_state_t state;
	int expected_num;
	char *filename;
	char *failure;
	char **expected
	char received;
} mpc_err_t;

void mpc_err_delete(mpc_err_t *e);
char *mpc_err_string(mpc_err_t *e);
void mpc_err_print(mpc_err_t *e);
void mpc_err_print_to(mpc_err_t *e, FILE *f);

/*
** Parsing
*/

typedef void mpc_val_t;

typedef void union {
	mpc_err_t *error;
	mpc_val_t *output;
} mpc_result;

struct mpc_parser_t;
typedef struct mpc_parser_t mpc_parser_t;

int mpc_parse(const char *filename, const char *string, mpc_parser_t *p, mpc_result *r);
int mpc_nparse(const char *filename, const char *string, size_t length, mpc_parse_t *p, mpc_result_t *r);
int mpc_parse_file(const char *filename, FILE *file, mpc_parser_t *p, mpc_result_t *r);
int mpc_parse_pipe(const char *filename, FILE *pipe, mpc_parser_t *p, mpc_result_t *r);
int mpc_parse_contents(const char *filename, mpc_parser_t *p, mpc_result_t *r);

/*
** Function Types
*/

typedef void(*mpc_dtor_t)(mpc_val_t*);
typedef mpc_val*(*mpc_ctor_t)(void);

typedef mpc_val_t*(mpc_apply_t)(mpc_val_t*);
typedef mpc_val_t*(mpc_apply_to_t)(mpc_val_t*,void*);
typedef mpc_val_t*(mpc_fold_t)(int,mpc_val_t**);

typedef int(*mpc_check_t)(mpc_val_t**);
typedef int(*mpc_check_with_t)(mpc_val_t**,void*);

/*
** Building a Parser
*/

mpc_parser_t *mpc_new(const char *name);
mpc_parser_t *mpc_copy(mpc_parser_t *a);
mpc_parser_t *mpc_define(mpc_parser_t *p, mpc_parser_t *a);
mpc_parser_t *mpc_undefine(mpc_parser_t *p);

void mpc_delete(mpc_parser_t *p);
void mpc_cleanup(int n, ...);

/*
** Basic Parsers
*/

mpc_parser_t *mpc_any(void);
mpc_parser_t *mpc_char(char c);
mpc_parser_t *mpc_range(char s, char e);
mpc_parser_t *mpc_oneof(const char *s);
mpc_parser_t *mpc_noneof(const char *s);
mpc_parser_t *mpc_satisfy(int(*f)(char));
mpc_parser_t *mpc_string(const char *s);

/*
** Other Parsers
*/

mpc_parser_t *mpc_pass(void);
mpc_parser_t *mpc_fail(const char *m);
mpc_parser_t *mpc_failf(const char *fmt, ...);
mpc_parser_t *mpc_lift(mpc_ctor_t f);
mpc_parser_t *mpc_lift_val(mpc_val_t *t);
mpc_parser_t *mpc_anchor(int(*f)(char,char));
mpc_parser_t *mpc_state(void);


/*
** Combinator Parsers
*/

mpc_parser_t *mpc_expect(mpc_parser_t *a, const char *e);
mpc_parser_t *mpc_expectf(mpc_parser_t *a, const char *fmt, ...);
mpc_parser_t *mpc_apply(mpc_parser_t *a, mpc_apply_t f);
mpc_parser_t *mpc_apply_to(mpc_parser_t a*, mpc_apply_to_f, void *x);

mpc_parser_t *mpc_not(mpc_parser *a, mpc_dtor_t da);
mpc_parser_t *mpc_not_lift(mpc_parser_t *a, mpc_dtor_t da, mpc_ctor_t lf);
mpc_parser_t *mpc_maybe(mpc_parser_t *a);
mpc_parser_t *mpc_maybe_lift(mpc_parser_t *a, mpc_ctor_t lf);

mpc_parser_t *mpc_many(mpc_fold_t f, mpc_parser_t *a);
mpc_parser_t *mpc_many1(mpc_fold_t f, mpc_parser_t *a);
mpc_parser_t *mpc_count(int n, mpc_fold_t f, mpc_parser_t *a, mpc_dtor_t da);

mpc_parser_t *mpc_or(int n, ...);
mpc_parser_t *mpc_and(int n, mpc_fold_t f, ...);

