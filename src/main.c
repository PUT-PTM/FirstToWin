/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"



int main(void)
{
	int stage = 0;
		int P1 = 0, P2 = 0, P3 = 0, P4 = 0;
		int win_round = 0;

		 //Obsulga wyœwieltacza----------------------------------------------
		    // means doesn't care, lower 5 bits are important for LCD
		    uint8_t customChar[] = {
		        0x1F,    //  11111
		        0x11,    //  10001
		        0x11,    // 10001
		        0x11,    //  10001
		        0x11,    // 10001
		        0x11,    // 10001
		        0x11,    // 10001
		        0x1F    //  11111
		    };
		    //Initialize system
		    SystemInit();

		    //Initialize LCD 20 cols x 4 rows
		    TM_HD44780_Init(16, 2);

		    //Save custom character on location 0 in LCD
		    TM_HD44780_CreateChar(0, &customChar[0]);
		    //Obsulga wyœwieltacza ---------------------------------------------



	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


		int press_any_key()
		{
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0)) return 1;
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)) return 1;
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)) return 1;
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)) return 1;
			return 0;
		};

		void ResetDiodes()
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		};

		void SetDiodes()
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
		};


		void blink(int player,int times)
		{
			switch(player)
			{//switch
			case 1:
			{
				for (int j=0;j<times;j++)
				{
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_12);
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_12);
				}
				break;
			}
			case 2:
			{
				for (int j=0;j<times;j++)
				{
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_13);
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_13);
				}
				break;
			}
			case 3:
			{
				for (int j=0;j<times;j++)
				{
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_14);
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_14);
				}
				break;
			}
			case 4:
			{
				for (int j=0;j<times;j++)
				{
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_15);
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_15);
				}
				break;
			}
			case 5:
			{
				for (int j=0;j<times;j++)
				{
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_12);
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_13);
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_14);
					for (int k = 0;k<1000000;k++)GPIO_SetBits(GPIOD, GPIO_Pin_15);
					///
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_12);
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_13);
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_14);
					for (int k = 0;k<1000000;k++)GPIO_ResetBits(GPIOD, GPIO_Pin_15);
				}
				break;
			}
			default:
				stage = 1;
				break;

			}//switch
		};

		void Punktacja(){

					if (P1 == 0) TM_HD44780_Puts(0, 1, "A=0" );
					if (P1 == 1) TM_HD44780_Puts(0, 1, "A=1" );
					if (P1 == 2) TM_HD44780_Puts(0, 1, "A=2" );
					if (P1 == 3) TM_HD44780_Puts(0, 1, "A=3" );
					if (P1 == 4) TM_HD44780_Puts(0, 1, "A=4" );
					if (P1 == 5) TM_HD44780_Puts(0, 1, "A=5" );
								if (P1 == -1) TM_HD44780_Puts(0, 1, "A=-1" );
								if (P1 == -2) TM_HD44780_Puts(0, 1, "A=-2" );
								if (P1 == -3) TM_HD44780_Puts(0, 1, "A=-3" );
								if (P1 == -4) TM_HD44780_Puts(0, 1, "A=-4" );
								if (P1 == -5) TM_HD44780_Puts(0, 1, "A=-5" );
								if (P1 < -5) {TM_HD44780_Puts(0, 1, "A=--" );P1=-1000;}

								if (P2 == 0) TM_HD44780_Puts(4, 1, "B=0" );
								if (P2 == 1) TM_HD44780_Puts(4, 1, "B=1" );
								if (P2 == 2) TM_HD44780_Puts(4, 1, "B=2" );
								if (P2 == 3) TM_HD44780_Puts(4, 1, "B=3" );
								if (P2 == 4) TM_HD44780_Puts(4, 1, "B=4" );
								if (P2 == 5) TM_HD44780_Puts(4, 1, "B=5" );
														if (P2 == -1) TM_HD44780_Puts(4, 1, "B=-1" );
														if (P2 == -2) TM_HD44780_Puts(4, 1, "B=-2" );
														if (P2 == -3) TM_HD44780_Puts(4, 1, "B=-3" );
														if (P2 == -4) TM_HD44780_Puts(4, 1, "B=-4" );
														if (P2 == -5) TM_HD44780_Puts(4, 1, "B=-5" );
														if (P2 < -5) {TM_HD44780_Puts(4, 1, "B=--" );P2=-1000;}

											if (P3 == 0) TM_HD44780_Puts(8, 1, "C=0" );
											if (P3 == 1) TM_HD44780_Puts(8, 1, "C=1" );
											if (P3 == 2) TM_HD44780_Puts(8, 1, "C=2" );
											if (P3 == 3) TM_HD44780_Puts(8, 1, "C=3" );
											if (P3 == 4) TM_HD44780_Puts(8, 1, "C=4" );
											if (P3 == 5) TM_HD44780_Puts(8, 1, "C=5" );
													if (P3 == -1) TM_HD44780_Puts(8, 1, "C=-1" );
													if (P3 == -2) TM_HD44780_Puts(8, 1, "C=-2" );
													if (P3 == -3) TM_HD44780_Puts(8, 1, "C=-3" );
													if (P3 == -4) TM_HD44780_Puts(8, 1, "C=-4" );
													if (P3 == -5) TM_HD44780_Puts(8, 1, "C=-5" );
													if (P3 < -5) {TM_HD44780_Puts(8, 1, "C=--" );P3=-1000;}

														if (P4 == 0) TM_HD44780_Puts(12, 1, "D=0" );
														if (P4 == 1) TM_HD44780_Puts(12, 1, "D=1" );
														if (P4 == 2) TM_HD44780_Puts(12, 1, "D=2" );
														if (P4 == 3) TM_HD44780_Puts(12, 1, "D=3" );
														if (P4 == 4) TM_HD44780_Puts(12, 1, "D=4" );
														if (P4 == 5) TM_HD44780_Puts(12, 1, "D=5" );
																	if (P4 == -1) TM_HD44780_Puts(12, 1, "D=-1" );
																	if (P4 == -2) TM_HD44780_Puts(12, 1, "D=-2" );
																	if (P4 == -3) TM_HD44780_Puts(12, 1, "D=-3" );
																	if (P4 == -4) TM_HD44780_Puts(12, 1, "D=-4" );
																	if (P4 == -5) TM_HD44780_Puts(12, 1, "D=-5" );
																	if (P4 < -5) {TM_HD44780_Puts(12, 1, "D=--" );P4=-1000;}
				};

		void ToFast()
		{
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))
						{
						P1--;
						Punktacja();
						ResetDiodes();
						blink(5,1);
						stage = 1;
						}
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1))
						{
						P2--;
						Punktacja();
						ResetDiodes();
						blink(5,1);
						stage = 1;
						}
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2))
						{
						P3--;
						Punktacja();
						ResetDiodes();
						blink(5,1);
						stage = 1;
						}
			if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3))
						{
						P4--;
						Punktacja();
						ResetDiodes();
						blink(5,1);
						stage = 1;
						}

		};



		TM_HD44780_Puts(0, 0, "First 2 Win");
		Delayms(2000);
		TM_HD44780_Clear();

	for(;;)
		{



		switch(stage)
		{
			case 0:
			{

				TM_HD44780_Puts(0, 0, "Nacisnij by ");
				TM_HD44780_Puts(0, 1, "rozpoczac");
				if(press_any_key())
				{
					for (int x=0;x<= 5000000;x++);
					stage = 1;
				}
				break;
			}

			case 1:
			{
				TM_HD44780_Clear();
				TM_HD44780_Puts(0, 0, "Jeszcze nie...");
				Punktacja();
				int time = rand()%4+1;
				for (int z = 0;z<1000000+time*500000;z++)
					{
					SetDiodes();
					ToFast();
					if(stage == 6) break;
					}
				if (stage != 6) {stage = 2;TM_HD44780_Clear();}
				break;
			}
			case 2:
			{

				TM_HD44780_Puts(0, 0, "Teraz!!!");
				Punktacja();
				ResetDiodes();
				if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0)) {stage = 3; win_round = 1; break;}
				if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)) {stage = 3; win_round = 2; break;}
				if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)) {stage = 3; win_round = 3; break;}
				if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)) {stage = 3; win_round = 4; break;}
				break;
			}
			case 3:
			{
				TM_HD44780_Clear();
				if(win_round == 1) {TM_HD44780_Puts(0, 0, "Wygrywa gracz A");P1++; Punktacja(); blink(1,5); stage = 4;}
				if(win_round == 2) {TM_HD44780_Puts(0, 0, "Wygrywa gracz B");P2++;Punktacja();blink(2,5);  stage = 4;}
				if(win_round == 3) {TM_HD44780_Puts(0, 0, "Wygrywa gracz C");P3++;Punktacja();blink(3,5);  stage = 4;}
				if(win_round == 4) {TM_HD44780_Puts(0, 0, "Wygrywa gracz D");P4++;Punktacja();blink(4,5);  stage = 4;}
				Punktacja();
				stage = 4;
				break;
			}
			case 4:
			{
				win_round = 0;
				if (P1>= 5 || P2>= 5 ||P3>= 5 ||P4>= 5) stage = 5;
				else stage = 1;
				break;
			}
			case 5:
			{
				if(P1>= 5) {TM_HD44780_Clear();TM_HD44780_Puts(0, 0, "Gracz A wygrywa gre! Gratulacje!"); blink(1,20);}
				if(P2>= 5) {TM_HD44780_Clear();TM_HD44780_Puts(0, 0, "Gracz B wygrywa gre! Gratulacje!");blink(2,20);}
				if(P3>= 5) {TM_HD44780_Clear();TM_HD44780_Puts(0, 0, "Gracz C wygrywa gre! Gratulacje!");blink(3,20);}
				if(P4>= 5) {TM_HD44780_Clear();TM_HD44780_Puts(0, 0, "Gracz D wygrywa gre! Gratulacje!");blink(4,20);}
				break;
			}

			default:
				stage = 1;
				break;

		}// switch end


		}



}
