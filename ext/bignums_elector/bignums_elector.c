#include <ruby.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bignums_elector.h"

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

  int bf_size = 1024 * 1024;
  char *buffer = (char*)malloc(sizeof(char) * bf_size);
  while(fgets(buffer, bf_size, input) != NULL) {
    for(int i = 0; i < bf_size; i++) {
      if('0' <= buffer[i] && buffer[i] <= '9' && bignum.len < BN_SIZE) {
        bignum.digits[bignum.len++] = buffer[i];
      } else if(bignum.len > 0) {
        result_add(&result, &bignum);
        bignum_zerify(&bignum);
      }
    }
  }

  for(int i = 0; i < result.size; i++) {
    if(result.bignums[i].len) {
      result.bignums[i].digits[result.bignums[i].len] = 0;
      fprintf(output, "%s\n", result.bignums[i].digits);
    }
  }

  fclose(input);
  fflush(output);
  fclose(output);

  return size;
}

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
  memset(bignum->digits, 0, bignum->len);
  bignum->len = 0;
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
