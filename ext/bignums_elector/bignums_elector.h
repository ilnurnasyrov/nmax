#ifndef BIGNUM_ELECTOR_H
#define BIGNUM_ELECTOR_H

#define BN_SIZE 1000

void Init_bignums_elector();

VALUE method_elect(VALUE self, VALUE size, VALUE input_fd, VALUE output_fd);

#endif

#ifndef RESULT_H
#define RESULT_H
#define BN_SIZE 1000

#include <stdbool.h>

struct Bignum {
  char digits[BN_SIZE];
  int len;
};

typedef struct Bignum Bignum;

struct Result {
  int min_index;
  int size;
  Bignum *bignums;
};

typedef struct Result Result;

struct Result result_init(int size);
void result_add(Result *result, Bignum *bignum);
void result_set_min_index(Result *result);

void bignum_zerify(struct Bignum *bignum);
int bignum_compare(Bignum *bignum, Bignum *another_bignum);
void bignum_copy(Bignum *target, Bignum *bignum);

#endif
