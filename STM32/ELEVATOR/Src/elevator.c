#include "main.h"
#include "button.h"
#include "i2c_lcd.h"
#include <stdio.h>

void cds_led(void);
void elevator_main(void);
void elevator_init();

extern void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
extern void delay_us(unsigned long us);
extern uint16_t adcValue[4];

extern void stepmotor_drive(int direction);
extern void set_rpm(int rpm);

//extern void init_dotmatrix(void);
extern void i2c_lcd_init(void);

extern int dotmatrix_main_up(void);
extern int dotmatrix_main_down(void);
extern void init_dotmatrix_up(void);
extern void init_dotmatrix_down(void);

int button_1_flag = 0;
int button_2_flag = 0;
int button_3_flag = 0;
int button_4_flag = 0;


void elevator_init()
{
//	i2c_lcd_init();
	init_dotmatrix();
}


void cds_led(void)
{
//	uint16_t adcValue[4];
	printf("cds sensor : %d\n", adcValue[0]);
	if (adcValue[0] < 3900 )
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, 1);	// LED0 on
	}
	else
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, 0);	// LED0 off
	}
	HAL_Delay(50); 	//50ms
}


int current_floor = 0;
void elevator_main(void)
{
	int direction = 0;
	int input_floor = 0;
	char lcd_buff[40];

//	i2c_lcd_init();
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, 1);	// LED0 on

	move_cursor(0,0);
	sprintf(lcd_buff, "=== ELEVATOR ===");
	lcd_string(lcd_buff);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);

	while (1)
	{

		// 버튼 1
		if (get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)	// 버튼1 : 1층으로
		{
			button_1_flag++;
			button_1_flag %= 2;

			input_floor = 1;	// 입력층

			if (button_1_flag == 1)
			{
				direction = 2;	// 역방향 down

				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, 1);	// LED0 on

				move_cursor(1,0);
				sprintf(lcd_buff, "   Move to 1F");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_6, GPIO_PIN_RESET);	//on
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);	//off
			}
			else if (button_1_flag == 0)
			{
				direction = 0;	// 취소

				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, 0);	// LED0 off

				move_cursor(1,0);
				sprintf(lcd_buff, "     Cancel  ");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
			}
		}

		// 버튼 2
		if (get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)	// 버튼2 : 2층으로
		{
			button_2_flag++;
			button_2_flag %= 2;

			input_floor = 2;	// 입력층

			if (button_2_flag == 1)
			{
				if (current_floor < 2) direction = 1;	// 정방향 up
				else if (current_floor > 2) direction = 2;	// 역방향 down

				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 1);	// LED0 on

				move_cursor(1,0);
				sprintf(lcd_buff, "   Move to 2F");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_10, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_11, GPIO_PIN_SET);
			}
			else if (button_2_flag == 0)
			{
				direction = 0;	// 취소

				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, 0);	// LED0 off

				move_cursor(1,0);
				sprintf(lcd_buff, "     Cancel  ");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
			}

		}


		// 버튼 3
		if (get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS) 	// 버튼3 : 3층으로
		{
			button_3_flag++;
			button_3_flag %= 2;

			input_floor = 3;

			if (button_3_flag == 1)
			{
				if (current_floor < 3) direction = 1;	// 정방향 up
				else if (current_floor > 3) direction = 2;	// 역방향 down

				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, 1);	// LED0 on

				move_cursor(1,0);
				sprintf(lcd_buff, "   Move to 3F");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_10, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_11, GPIO_PIN_SET);
			}
			else if (button_3_flag == 0)
			{
				direction = 0;	// 취소

				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, 0);	// LED0 off

				move_cursor(1,0);
				sprintf(lcd_buff, "     Cancel  ");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
			}
		}

		// 버튼 4
		if (get_button(BUTTON4_GPIO_Port, BUTTON4_Pin, 4) == BUTTON_PRESS)	// 버튼4 : 4층으로
		{
			button_4_flag++;
			button_4_flag %= 2;

			input_floor = 4;

			if (button_4_flag == 1)
			{
				direction = 1;	// 정방향 up

				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 1);	// LED0 on

				move_cursor(1,0);
				sprintf(lcd_buff, "   Move to 4F");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_10, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11, GPIO_PIN_SET);
			}
			else if (button_4_flag == 0)
			{
				direction = 0;	// 취소

				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 0);	// LED0 on

				move_cursor(1,0);
				sprintf(lcd_buff, "     Cancel  ");
				lcd_string(lcd_buff);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
			}
		}
/*
		// 버튼 0 (일시정지)
		if (get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)	// 버튼0(취소)
		{
			direction = 0;	// 취소

			move_cursor(1,0);
			sprintf(lcd_buff, "    Cancel ");
			lcd_string(lcd_buff);

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
		}
*/
		if (current_floor == input_floor) direction = 0;

		stepmotor_drive(direction);
		set_rpm(13);

	}
}

