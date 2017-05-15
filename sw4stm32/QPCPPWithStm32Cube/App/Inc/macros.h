#ifndef MACROS_H_
#define MACROS_H_

#define LESS(a_, b_) (((a_) < (b_)) ? (a_) : (b_))
#define COUNTOF(v)  (sizeof(v)/sizeof(v[0]))
#define ROUND_UP_DIV(a_, d_)        (((a_) + (d_) - 1) / (d_))
#define ROUND_UP_DIV_4(a_)          ROUND_UP_DIV((a_), 4)
#define ROUND_UP_DIV_8(a_)          ROUND_UP_DIV((a_), 8)

#endif
