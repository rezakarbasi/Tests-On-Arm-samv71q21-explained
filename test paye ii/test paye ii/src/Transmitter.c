/*
 * Transmitter.c
 *
 * Created: 2/7/2016 4:28:50 PM
 *  Author: Reza_pc
 */ 



#include <Transmitter.h>


// receiving data for 9 robots(SIB = 104 ),why? should be 12 robots !!
// running time : about 560 clk
// time for receiving all packet : 560 * 104 clk = 58240 clk = 1.82 ms
void GetNewData(uint8_t data,int side)
{
	if (PCK_Num[side]<HEADER_LENGHT)
	{
		switch(PCK_Num[side])
		{

			case 0:
			if (data == START_BYTE0)
			{
				PCK_Num[side]++;
			}
			break;

			case 1:
			if (data == START_BYTE1)
			PCK_Num[side]++;
			else
			{
				PCK_Num[side] = 0;
			}
			break;

			case 2:
			PCK_H[side].SIB = data;
			PCK_Num[side]++;
			break;

			case 3:
			PCK_H[side].CHK = data;
			PCK_Num[side]++;
			break;
		}
	}
	else
	{
		if (PCK_Num[side] < PCK_H[side].SIB-1)
		{
			uint8_t id = (PCK_Num[side]-HEADER_LENGHT) / Data_Length ;

			switch((PCK_Num[side]-HEADER_LENGHT) % Data_Length)
			{
				case 0:
				Robot_D_tmp[side][id].RID=data;
				PCK_H[side].CHK -= data;
				break;

				case 1:
				Robot_D_tmp[side][id].Vx_sp.byte[high]=data;
				PCK_H[side].CHK -= data;
				break;

				case 2:
				Robot_D_tmp[side][id].Vx_sp.byte[low]=data;
				PCK_H[side].CHK -= data;
				break;

				case 3:
				Robot_D_tmp[side][id].Vy_sp.byte[high]=data;
				PCK_H[side].CHK -= data;
				break;

				case 4:
				Robot_D_tmp[side][id].Vy_sp.byte[low]=data;
				PCK_H[side].CHK -= data;
				break;

				case 5:
				Robot_D_tmp[side][id].Wr_sp.byte[high]=data;
				PCK_H[side].CHK -= data;
				break;

				case 6:
				Robot_D_tmp[side][id].Wr_sp.byte[low]=data;
				PCK_H[side].CHK -= data;
				break;

				case 7:
				Robot_D_tmp[side][id].Vx.byte[high]=data;
				PCK_H[side].CHK -= data;
				break;

				case 8:
				Robot_D_tmp[side][id].Vx.byte[low]=data;
				PCK_H[side].CHK -= data;
				break;

				case 9:
				Robot_D_tmp[side][id].Vy.byte[high]=data;
				PCK_H[side].CHK -= data;
				break;

				case 10:
				Robot_D_tmp[side][id].Vy.byte[low]=data;
				PCK_H[side].CHK -= data;
				break;

				case 11:
				Robot_D_tmp[side][id].Wr.byte[high]=data;
				PCK_H[side].CHK -= data;
				break;

				case 12:
				Robot_D_tmp[side][id].Wr.byte[low]=data;
				PCK_H[side].CHK -= data;
				break;

				case 13:
				Robot_D_tmp[side][id].alpha.byte[high]=data;
				PCK_H[side].CHK -= data;
				break;

				case 14:
				Robot_D_tmp[side][id].alpha.byte[low]=data;
				PCK_H[side].CHK -= data;
				break;

				case 15:
				Robot_D_tmp[side][id].KICK=data;
				PCK_H[side].CHK -= data;
				break;

				case 16:
				Robot_D_tmp[side][id].CHIP=data;
				PCK_H[side].CHK -= data;
				break;

				case 17:
				Robot_D_tmp[side][id].SPIN=data;
				PCK_H[side].CHK -= data;
				break;

			}
			PCK_Num[side]++;
		}
		else
		{
			if (PCK_H[side].CHK == 0 && data == STOP_BYTE)           //// !!!!!!!???????
			{
				uint8_t number_of_robots = (PCK_H[side].SIB - HEADER_LENGHT - STOP_BYTE_SIZE)/Data_Length ;          ////////  !!!!!!!!!????
				for (uint8_t i=0;i<number_of_robots;i++)      ////////////////    !!!!!!!!?????????
				{

					if (Robot_D_tmp[side][i].RID != 255)
					{
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 0] = Robot_D_tmp[side][i].RID ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 1] = Robot_D_tmp[side][i].Vx_sp.byte[high] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 2] = Robot_D_tmp[side][i].Vx_sp.byte[low] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 3] = Robot_D_tmp[side][i].Vy_sp.byte[high] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 4] = Robot_D_tmp[side][i].Vy_sp.byte[low] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 5] = Robot_D_tmp[side][i].Wr_sp.byte[high] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 6] = Robot_D_tmp[side][i].Wr_sp.byte[low] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 7] = Robot_D_tmp[side][i].Vx.byte[high] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 8] = Robot_D_tmp[side][i].Vx.byte[low] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][ 9] = Robot_D_tmp[side][i].Vy.byte[high] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][10] = Robot_D_tmp[side][i].Vy.byte[low] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][11] = Robot_D_tmp[side][i].Wr.byte[high] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][12] = Robot_D_tmp[side][i].Wr.byte[low] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][13] = Robot_D_tmp[side][i].alpha.byte[high] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][14] = Robot_D_tmp[side][i].alpha.byte[low] ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][15] = Robot_D_tmp[side][i].KICK ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][16] = Robot_D_tmp[side][i].CHIP ;
						Buf_Tx[side][Robot_D_tmp[side][i].RID][17] = Robot_D_tmp[side][i].SPIN ;

						pck_timeout[side][Robot_D_tmp[side][i].RID]=0;

					}
				}
			}
			PCK_Num[side] = 0;
		}
	}
}