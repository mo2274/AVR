/*
 * StdTypes.h
 *
 * Created: 11/05/2020 05:18:28
 *  Author: Mohamed Abo Raia
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char              uint8;
typedef signed char                int8;

typedef unsigned short int         uint16;
typedef signed short int           int16;

typedef unsigned long int		   uint32;
typedef signed long int            int32;

typedef unsigned long long int     uint64;
typedef signed long long int       int64;

typedef float                      float32;
typedef double                     float64;

typedef uint8                      bool;
#define TRUE                       1
#define FLASE                      0
#define SUCCESS                    0
#define ERROR                      1

typedef enum {
	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D
}Port_t;

/* type of data */
typedef uint8   Data_t;
typedef uint8   Pin_type;

#endif /* STDTYPES_H_ */