// #include "result.h"

// extern Result* result_init(int size) {
//   Result *result;
//   return *result;
// }

// void bignum_zerify(Bignum *bignum) {
//   memset(bignum->digits, 0, BN_SIZE);
//   bignum->len = 0;
// }

// void result_add(Result *result, Bignum *bignum) {
//   if(bignum_compare(*bignum, *result->bignums[min_index]) == -1) return;
//   bignum_copy(*result->bignums[min_index], *bignum);
// }

// void bignum_copy(Bignum *target, Bignum *bignum) {
//   target->len = bignum->len;
//   strcpy(target->digits, bignum->digits);
// }

// int bignum_compare(Bignum *bignum, Bignum *another_bignum) {
//   if(bignum->len < another_bignum->len) return -1;
//   if(bignum->len > another_bignum->len) return 1;

//   for(int i = 0; i < bignum->len; i++) {
//     if(bignum->digits[i] < another_bignum->digits[i]) return -1;
//     if(bignum->digits[i] > another_bignum->digits[i]) return 1;
//   }

//   return 0;
// }
