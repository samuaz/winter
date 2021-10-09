//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-11-27.
//

#ifndef WINTERCPP_WINTER_MACRO_H
#define WINTERCPP_WINTER_MACRO_H
// Variable Argument Macro (VA_MACRO) upto 10 arguments
#define NUM_ARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, TOTAL, ...) TOTAL
#define NUM_ARGS(...) NUM_ARGS_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define CONCATE_(X, Y) X##Y  // Fixed the double '_' from previous code
#define CONCATE(MACRO, NUMBER) CONCATE_(MACRO, NUMBER)
#define VA_MACRO(MACRO, ...)            \
  CONCATE(MACRO, NUM_ARGS(__VA_ARGS__)) \
  (__VA_ARGS__)
#endif	// WINTERCPP_WINTER_MACRO_H
