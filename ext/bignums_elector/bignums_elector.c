#include <ruby.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bignums_elector.h"
#include "result.h"

VALUE BignumsElector = Qnil;

void Init_bignums_elector() {
  BignumsElector = rb_define_module("BignumsElector");
  rb_define_singleton_method(BignumsElector, "elect", method_elect, 3);
}

VALUE method_elect(VALUE self, VALUE size, VALUE input_fd, VALUE output_fd) {
  FILE *input = fdopen(NUM2INT(input_fd), "r");
  FILE *output = fdopen(NUM2INT(output_fd), "w");

  Result result = result_init(NUM2INT(size));

  Bignum bignum = { .len = 0 };
  bignum_zerify(&bignum);

  int c;
  do {
    c = getc(input);

    if('0' < c && c < '9' && bignum.len < BN_SIZE) {
      bignum.digits[bignum.len++] = c;
    } else if(bignum.len > 0) {
      result_add(&result, &bignum);
      bignum_zerify(&bignum);
    }
  } while(c != EOF);

  for(int i = 0; i < result.size; i++) {
    if(result.bignums[i].len) {
      fprintf(output, "%s\n", result.bignums[i].digits);
    }
  }

  fclose(input);
  fflush(output);
  fclose(output);

  return size;
}


#include "result.h"

Result result_init(int size) {
  Result result = { .min_index = 0, .size = size};
  result.bignums = (Bignum *)malloc(sizeof(Bignum) * size);
  memset(result.bignums, 0, sizeof(Bignum) * size);
  return result;
}

void result_set_min_index(Result *result) {
  int min_index = 0;
  for(int i = 0; i < result->size; i++) {
    if(bignum_compare(&result->bignums[i], &result->bignums[min_index]) == -1) {
      min_index = i;
    }
  }
  result->min_index = min_index;
}

void result_add(Result *result, Bignum *bignum) {
  if(bignum_compare(&result->bignums[result->min_index], bignum) == 1) return;
  bignum_copy(&result->bignums[result->min_index], bignum);
  result_set_min_index(result);
}

void bignum_zerify(struct Bignum *bignum) {
  bignum->len = 0;
  memset(bignum->digits, 0, BN_SIZE);
}

void bignum_copy(Bignum *target, Bignum *bignum) {
  target->len = bignum->len;
  strcpy(target->digits, bignum->digits);
}

int bignum_compare(Bignum *bignum, Bignum *another_bignum) {
  if(bignum->len < another_bignum->len) return -1;
  if(bignum->len > another_bignum->len) return 1;

  for(int i = 0; i < bignum->len; i++) {
    if(bignum->digits[i] < another_bignum->digits[i]) return -1;
    if(bignum->digits[i] > another_bignum->digits[i]) return 1;
  }

  return 0;
}
