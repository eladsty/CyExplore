#ifndef __UTILS_SHANI_H__
#define __UTILS_SHANI_H__
#include "vsa.h"


extern size_t vsa_start;
extern size_t vsa_end;



#ifdef NDEBUG
#define NULLERROR(pointer) (void)
#define OUTBOUNDERROR(pointer) (void)
#define BLOCKERROR(pointer) (void)
#define DOUBLEFREELERROR(pointer) (void)
#define VALIDATOR ((void)0)
#endif /* NDEBUG */

#ifndef NDEBUG
#define VALIDATOR (11443) /* prime number to validate the freed pointer given by user */
#define NULLERROR(pointer) ({\
                    if(NULL == (pointer))\
                    {\
                        printf("program: %s:%d: main: Null pointer was given.\n", __FILE__, __LINE__);\
                        exit(1);\
                    }\ 
                            })
#define OUTBOUNDERROR(pointer) ({\
                    if((vsa_start) > ((size_t)pointer) || (vsa_end) < ((size_t)pointer))\
                    { \
                        printf("program: %s:%d: main: out of bounds pointer was given.\n", __FILE__, __LINE__);\
                        exit(1);\
                    } \
                    
                })
#define BLOCKERROR(pointer) ({\
                    if((0) != ((*(vsa_t *)pointer) / (VALIDATOR)))\
                    {\
                        printf("program: %s:%d: main: pointer was given that was not previously allocated.\n", __FILE__, __LINE__);\
                        exit(1);\
                    }\
                })
#define DOUBLEFREELERROR(pointer) ({\
                    if((0) > (*(vsa_t *)pointer))\
                    {\
                        printf("program: %s:%d: main: pointer was given that was previously freed.\n", __FILE__, __LINE__);\
                        exit(1);\
                    }\
                })
#endif /* NDEBUG */
#endif /* __UTILS_SHANI_H__ */