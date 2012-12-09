#ifndef BITWISE_H
#define BITWISE_H

/* a=target variable, b=bit number to act upon 0-n, c=condition */
#define BIT_RISE(a,b)   ((a) |=  (1<<(b)))
#define BIT_CLEAR(a,b)  ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b)   ((a) ^=  (1<<(b)))
#define BIT_CHECK(a,b)  ((a) &   (1<<(b)))
#define BIT_SET(a,b,c)  ((c)?BIT_RISE((a),(b)):BIT_CLEAR((a),(b)))

#endif // BITWISE_H
