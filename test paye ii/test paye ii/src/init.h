/*
 * init.h
 *
 * Created: 2/6/2016 3:19:24 PM
 *  Author: Reza_pc
 */ 


#ifndef INIT_H_
#define INIT_H_

#include <asf.h>
#include "pio.h"
#include <string.h>
#include <stdio.h>



#define MY_LED    IOPORT_CREATE_PIN(PIOA, 23)
#define button    PIO_PA9_IDX

#endif /* INIT_H_ */


