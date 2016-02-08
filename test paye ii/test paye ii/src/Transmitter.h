/*
 * Transmitter.h
 *
 * Created: 2/7/2016 4:28:29 PM
 *  Author: Reza_pc
 */ 


#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_


#include <stdio.h>


struct PCK_Header
{
	uint8_t SIB;  /// size in byte
	uint8_t CHK;  /// check sum
};

union Motor_Speed
{
	char Bytes[2];
	int16_t Speed;
};

typedef union High_Low{
	uint8_t byte[2] ;
	int16_t full ;
} HL;

struct Robot_Data
{
	uint8_t RID ;  //robot ID
	HL Vx_sp ;
	HL Vy_sp ;
	HL Wr_sp ;
	HL Vx ;
	HL Vy ;
	HL Wr ;
	HL alpha ;
	uint8_t KICK ;
	uint8_t CHIP ;
	uint8_t SPIN ;
};

struct PCK_Send_Header
{
	uint8_t SIB;
	uint8_t CHK;
	uint8_t RID;
};



#define _Buffer_Size 32
#define HEADER_LENGHT 4
#define STOP_BYTE_SIZE 1
#define Data_Length 18 // old length 11
#define Max_Robot 12
#define START_BYTE0 0xA5     /////////// it was 0xA5
#define START_BYTE1 0x5A     /////////// it was 0x5A
#define STOP_BYTE 0x80      /////////// it was 0x80
#define R 0
#define L 1
#define high 1
#define	low	 0



/////         transmitter
char Buf_Tx[2][Max_Robot][_Buffer_Size];
uint16_t pck_timeout[2][Max_Robot];
struct PCK_Header PCK_H[2];
struct Robot_Data Robot_D_tmp[2][Max_Robot];
uint8_t PCK_Num[2];


void GetNewData(uint8_t data,int side);

#endif /* TRANSMITTER_H_ */