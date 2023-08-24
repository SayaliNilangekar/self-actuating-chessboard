/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
////////GAME LOGIC//////////
#include <stdio.h>
#define EN_PASSANT 'p'
#define CASTLES_KINGSIDE 'k'
#define CASTLES_QUEENSIDE 'q'
#define CAPTURE 'c'
#define SELF_CAPTURE 'x'
#define PAWN_FIRSTMOVE 'f'
#define JUMPING 'j'
////////GAME LOGIC/////////
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// players LEDs
#define WHITE_ON() HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
#define WHITE_OFF() HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
#define WHITE_TOGG() HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);

#define BLACK_ON() HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
#define BLACK_OFF() HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
#define BLACK_TOGG() HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);

// electromagnet
#define MAG_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
#define MAG_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
#define MAG_TOGG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);

// hall effect sensor
#define HES_VAL() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);

// LED arrays
#define SER3_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); // blue2
#define SER3_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
#define SER3_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);

#define SER2_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET); // red2
#define SER2_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
#define SER2_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);

#define SER1_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); // blue1
#define SER1_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
#define SER1_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);

#define SER0_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); // red1
#define SER0_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
#define SER0_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

#define SCLK_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
#define SCLK_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
#define SCLK_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);

#define RCLK_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
#define RCLK_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
#define RCLK_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);

#define OE_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
#define OE_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
#define OE_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

// motors
#define STEP0_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
#define STEP0_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
#define STEP0_TOGG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);

#define DIR0_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
#define DIR0_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
#define DIR0_TOGG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);

#define STEP1_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
#define STEP1_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
#define STEP1_TOGG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);

#define DIR1_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
#define DIR1_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
#define DIR1_TOGG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);

#define MTR_SLP_ON() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
#define MTR_SLP_OFF() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
#define MTR_SLP_TOGG() HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);

#define M0_ON() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
#define M0_OFF() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
#define M0_TOGG() HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

#define M1_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
#define M1_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
#define M1_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);

#define M2_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
#define M2_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
#define M2_TOGG() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

// player controller buttons
#define WHITE_SND() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
#define WHITE_CLR() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
#define BLACK_SND() HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
#define BLACK_CLR() HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);

// side panel
#define DRAW() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
#define RST_GAME() HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
#define STRT_BTN() HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim14;

/* USER CODE BEGIN PV */
uint32_t wait;
uint32_t mode;
uint32_t start_lett;
uint32_t start_num;
uint32_t end_lett;
uint32_t end_num;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */
uint32_t WHT_X_VAL();
uint32_t WHT_Y_VAL();
uint32_t PROMOTION();
uint32_t BLK_X_VAL();
uint32_t BLK_Y_VAL();
void check_wait();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void ledArray(int s0, int s1, int s2, int s3);
void display(char *ddd,int length);
void clearDisplay();
void dispLine1();
void dispLine2();
void setBacklightRed(int on);
void setBacklightGreen(int on);
void setBacklightBlue(int on);
void setBacklightOff();
void setBacklight(int r, int g, int b);
void lcdInit();
void lcdSetSplash();
void waitPlayerMove();
void waitStartPosP1();
void waitEndPosP1();
int potToNum(int pot);
int numToSer0(int pot);
int numToSer1(int pot);
int numToSer2(int pot);
int numToSer3(int pot);
char numToSpace(int lett, int num);
void waitStartPosP2();
void waitEndPosP2();

//GAME LOGIC//
void nuke_castle_flags(char);
int convert_move(int start_x, int end_x, int start_y, int end_y);
int print_board();
int castle_check(char, char);
int self_capture_check(char piece, int x, int y);
int capture_check(char color, int x, int y);
int validate_move(int start_x, int end_x, int start_y, int end_y);
int jump_check(int start_x, int end_x, int start_y, int end_y);
int en_passant_check();
void set_rook_flags(int, int);
int exec_move(int start_x, int end_x, int start_y, int end_y);
int translate_input(int* start_x, int* end_x, int* start_y, int* end_y);
int gt(char, char);
int lt(char, char);
int undo_move();
char check_check(char, int, int);
int fix_castling();
char check_checkmate(char color, int king_x, int king_y);
char check_stalemate(char color);
char has_valid_moves(int x, int y);
int check_color(int, int, char);
int toggle_turn();
void convert_FEN();
int move[2];
int checking_piece[2];
int kingpos[4];
int lastmove[4];
char removed_piece;
char turn;
int movecounter;
char FEN[100];
char checking;
char board_array[8][8] = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    { 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },
    { 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },
    { 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },
    { 0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 },
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};
char line1[10] = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
char line2[10] = {' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
//char nums[9] = {'8', '7', '6', '5', '4', '3', '2', '1', ' '};
char nums[9] = {'1', '2', '3', '4', '5', '6', '7', '8', ' '};


char black_queenside;
char black_kingside;
char white_queenside;
char white_kingside;
char en_passant = '-';
int moveflag = 0;
int castling = 0;
static char input[2];

//GAME LOGIC//

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart){
    uint8_t i;
    /*if(huart -> Instance == USART1){
        if(index == 0){
            for(i = 0; i < 100; i++){
                data[i] = 0;
            }
        }

        if(input[0] != 13 && input[0] != 10){
            data[index] = input[0];
            index++;

        }

        else{
            index = 0;
            flag = 1;

        }
    }*/
	/*
    HAL_UART_Receive_IT(&huart1, input, 1);
}

void transmitString(UART_HandleTypeDef * huart, char * output){
    int length = strlen(output);
    HAL_UART_Transmit(huart, output, length, 1000);
}

*/

uint32_t WHT_X_VAL() // for letters
{
   HAL_StatusTypeDef stat;
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   uint32_t val = HAL_ADC_GetValue(&hadc); // ADC0
   HAL_ADC_Stop(&hadc);

   return val;
}

uint32_t WHT_Y_VAL() // for numbers
{
   HAL_StatusTypeDef stat;
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   uint32_t val = HAL_ADC_GetValue(&hadc); // ADC0
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC1
   HAL_ADC_Stop(&hadc);

   return val;
}

uint32_t PROMOTION()
{
   HAL_StatusTypeDef stat;
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   uint32_t val = HAL_ADC_GetValue(&hadc); // ADC0
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC1
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC4
   HAL_ADC_Stop(&hadc);

   return val;
}

uint32_t BLK_X_VAL() // for letters
{
   HAL_StatusTypeDef stat;
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   uint32_t val = HAL_ADC_GetValue(&hadc); // ADC0
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC1
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC4
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC5
   HAL_ADC_Stop(&hadc);

   return val;
}

uint32_t BLK_Y_VAL() // for numbers
{
   HAL_StatusTypeDef stat;
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   uint32_t val = HAL_ADC_GetValue(&hadc); // ADC0
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC1
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC4
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC5
   stat = HAL_ADC_Start(&hadc);
   while(stat == HAL_BUSY);
   val = HAL_ADC_GetValue(&hadc); // ADC7
   HAL_ADC_Stop(&hadc);

   return val;
}

void check_wait()
{
    if(wait < 300)
    {
        wait++;
    }
    else
    {
        wait = 0;

        if(mode > 7)
        {
            mode = 0;
        }
        else
        {
            mode++;
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM14) // every 1000us = 1ms
    {
        check_wait();

        if((mode % 2) == 0)
        {
            MTR_SLP_OFF(); // sleep
        }
        else
        {
            //MTR_SLP_ON();

            if(mode == 1)
            {
                DIR0_ON();
                //DIR1_ON();
                STEP0_TOGG();
                //STEP1_TOGG();
            }
            else if (mode == 3)
            {
                //DIR0_OFF();
                DIR1_OFF();
                //STEP0_TOGG();
                STEP1_TOGG();
            }
            else if (mode == 5)
            {
                //DIR0_OFF();
                DIR1_ON();
                //STEP0_TOGG();
                STEP1_TOGG();
            }
            else if (mode == 7)
            {
                DIR0_OFF();
                //DIR1_OFF();
                STEP0_TOGG();
                //STEP1_TOGG();
            }
        }
    }
}

void ledArray(int s0, int s1, int s2, int s3)
{
    for(int i = 0; i < 8; i++)
    {
        if(s0 == i)
        {
            SER0_ON();
        }
        else
        {
            SER0_OFF();
        }

        if(s1 == i)
        {
            SER1_ON();
        }
        else
        {
            SER1_OFF();
        }

        if(s2 == i)
        {
            SER2_ON();
        }
        else
        {
            SER2_OFF();
        }

        if(s3 == i)
        {
            SER3_ON();
        }
        else
        {
            SER3_OFF();
        }

        SCLK_ON();
        HAL_Delay(50);
        SCLK_OFF();
        HAL_Delay(50);
    }

    RCLK_ON();
    HAL_Delay(50);
    RCLK_OFF();
    HAL_Delay(50);
}

void display(char *ddd,int length)
{
    for (int j = 0;j<length;j++)
    {
        HAL_SPI_Transmit(&hspi1,&ddd[j], sizeof(ddd[j]), 100);
        int x = 30000;
        while (x!=0)
        {
            x--;
        }
    }
}

void clearDisplay()
{
    char ch1 = 0x7C;
    char ch2 = 0x2D;
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch1,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch2,1,1000);
}

void dispLine1()
{
    char ch1 = 0xFE;
    char ch2 = 0x80;
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch1,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch2,1,1000);
}

void dispLine2()
{
    char ch1 = 0xFE;
    char ch2 = 0xC0;
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch1,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch2,1,1000);
}

void setBacklightRed(int on)
{
    char ch0 = 0x7C;
    char ch2;

    if(on == 1)
    {
        ch2 = 0x9D; // red 100%
    }
    else
    {
        ch2 = 0x80; // red 0%
    }

    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch0,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch2,1,1000);
}

void setBacklightGreen(int on)
{
    char ch0 = 0x7C;
    char ch3;

    if(on == 1)
    {
        ch3 = 0xBB; // green 100%
    }
    else
    {
        ch3 = 0x9E; // green 0%
    }

    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch0,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch3,1,1000);
}

void setBacklightBlue(int on)
{
    char ch0 = 0x7C;
    char ch4;

    if(on == 1)
    {
        ch4 = 0xD9; // blue 100%
    }
    else
    {
        ch4 = 0xBC; // blue 0%
    }

    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch0,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch4,1,1000);
}

void setBacklightOff()
{
    char ch0 = 0x7C;
    char ch2 = 0x80; // red 0%
    char ch3 = 0x9E; // green 0%
    char ch4 = 0xBC; // blue 0%
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch0,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch2,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch0,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch3,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch0,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch4,1,1000);
}

void setBacklight(int r, int g, int b)
{
    setBacklightRed(r);
    setBacklightGreen(g);
    setBacklightBlue(b);
}

void lcdInit()
{
    char ch1 = 0xFE;
    char ch2 = 0x0C; // C for no cursor, E for cursor
    char ch4 = 0x06;
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch1,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch2,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch1,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch4,1,1000);
    clearDisplay();
    HAL_Delay(100);
}

void lcdSetSplash()
{
    clearDisplay();
    display("Deep Gold       Team 3", 22);
    char ch1 = 0x7C;
    char ch2 = 0x0A;
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch1,1,1000);
    HAL_Delay(50);
    HAL_SPI_Transmit(&hspi1,&ch2,1,1000);
}

void waitPlayerMove()
{
    ledArray(-1, -1, -1, -1);

    //clearDisplay();
    //display("In WPM",6);

    if(turn == 'w')
    {
        waitStartPosP1();

        HAL_Delay(500); // give time so dont skip second loop

        waitEndPosP1();
    }
    else // P2
    {
        waitStartPosP2();

        HAL_Delay(500); // give time so dont skip second loop

        waitEndPosP2();
    }
}

//clearDisplay();
//display("Received: ",10);
//display(numToSpace(1,start_num),1);
//display(numToSpace(0,start_lett),1);


void waitStartPosP1()
{
    uint32_t send_btn = WHITE_SND();
    clearDisplay();
    display("Waiting StPos1",14);
    while(send_btn == 1) // not pressed
    {
    	//INVERTED
        start_num = potToNum(WHT_X_VAL());
        start_lett = potToNum(WHT_Y_VAL());

        ledArray(numToSer0(start_lett), -1, numToSer2(start_num), -1);
        //to see input
        char sx1[1] = {numToSpace(0,start_lett)};
		char sy1[1] = {numToSpace(1,start_num)};
		clearDisplay();
		display("Received: ",10);
		display(sy1,1);
		display(sx1,1);
		//
        send_btn = WHITE_SND();
    }
}

void waitEndPosP1()
{
    uint32_t send_btn = WHITE_SND();
    clearDisplay();
	display("Waiting EnPos1",14);
	HAL_Delay(500);
    while(send_btn == 1) // not pressed
    {
        uint32_t clr_btn = WHITE_CLR();

        if(clr_btn == 0) // pressed
        {
            waitStartPosP1();
        }
        //inverted
        end_num = potToNum(WHT_X_VAL());
        end_lett = potToNum(WHT_Y_VAL());

        ledArray(numToSer0(start_lett), numToSer1(end_lett), numToSer2(start_num), numToSer3(end_num));

        //to see input
		char ex1[1] = {numToSpace(0,end_lett)};
		char ey1[1] = {numToSpace(1,end_num)};
		clearDisplay();
		display("Received: ",10);
		display(ey1,1);
		display(ex1,1);
		//
        send_btn = WHITE_SND();
    }
}

void waitStartPosP2()
{
    uint32_t send_btn = BLACK_SND();
    clearDisplay();
	display("Waiting StPos2",14);
    while(send_btn == 1) // not pressed
    {
    	//inverted
        start_num = potToNum(BLK_X_VAL());
        start_lett = potToNum(BLK_Y_VAL());

        ledArray(numToSer0(start_lett), -1, numToSer2(start_num), -1);

        //to see input
		char sx2[1] = {numToSpace(0,start_lett)};
		char sy2[1] = {numToSpace(1,start_num)};
		clearDisplay();
		display("Received: ",10);
		display(sy2,1);
		display(sx2,1);

		//

        send_btn = BLACK_SND();
    }
}

void waitEndPosP2()
{
    uint32_t send_btn = BLACK_SND();
    clearDisplay();
	display("Waiting EnPos2",14);
    while(send_btn == 1) // not pressed
    {
        uint32_t clr_btn = BLACK_CLR();

        if(clr_btn == 0) // pressed
        {
            waitStartPosP2();
        }
        //inverted
        end_num = potToNum(BLK_X_VAL());
        end_lett = potToNum(BLK_Y_VAL());

        ledArray(numToSer0(start_lett), numToSer1(end_lett), numToSer2(start_num), numToSer3(end_num));

        //to see input
		char ex2[1] = {numToSpace(0,end_lett)};
		char ey2[1] = {numToSpace(1,end_num)};
		clearDisplay();
		display("Received: ",10);
		display(ey2,1);
		display(ex2,1);

		//

        send_btn = BLACK_SND();
    }
}


int potToNum(int pot)
{
    int ser;

    if(pot < 511)
    {
        ser = 0;
    }
    else if(pot < 1022)
    {
        ser = 1;
    }
    else if(pot < 1533)
    {
        ser = 2;
    }
    else if(pot < 2044)
    {
        ser = 3;
    }
    else if(pot < 2555)
    {
        ser = 4;
    }
    else if(pot < 3066)
    {
        ser = 5;
    }
    else if(pot < 3577)
    {
        ser = 6;
    }
    else
    {
        ser = 7;
    }

    return ser;
}

int numToSer0(int pot)
{
    int ser;

    if(pot == 0)
    {
        ser = 1;
    }
    else if(pot == 1)
    {
        ser = 0;
    }
    else if(pot == 2)
    {
        ser = 3;
    }
    else if(pot == 3)
    {
        ser = 2;
    }
    else if(pot == 4)
    {
        ser = 5;
    }
    else if(pot == 5)
    {
        ser = 4;
    }
    else if(pot == 6)
    {
        ser = 7;
    }
    else
    {
        ser = 6;
    }

    return ser;
}

int numToSer1(int pot)
{
    int ser;

    if(pot == 0)
    {
        ser = 0;
    }
    else if(pot == 1)
    {
        ser = 1;
    }
    else if(pot == 2)
    {
        ser = 2;
    }
    else if(pot == 3)
    {
        ser = 3;
    }
    else if(pot == 4)
    {
        ser = 5;
    }
    else if(pot == 5)
    {
        ser = 4;
    }
    else if(pot == 6)
    {
        ser = 7;
    }
    else
    {
        ser = 6;
    }

    return ser;
}

int numToSer2(int pot)
{
    int ser;

    if(pot == 0)
    {
        ser = 6;
    }
    else if(pot == 1)
    {
        ser = 7;
    }
    else if(pot == 2)
    {
        ser = 4;
    }
    else if(pot == 3)
    {
        ser = 5;
    }
    else if(pot == 4)
    {
        ser = 3;
    }
    else if(pot == 5)
    {
        ser = 2;
    }
    else if(pot == 6)
    {
        ser = 1;
    }
    else
    {
        ser = 0;
    }

    return ser;
}

int numToSer3(int pot)
{
    int ser;

    if(pot == 0)
    {
        ser = 0;
    }
    else if(pot == 1)
    {
        ser = 1;
    }
    else if(pot == 2)
    {
        ser = 2;
    }
    else if(pot == 3)
    {
        ser = 3;
    }
    else if(pot == 4)
    {
        ser = 4;
    }
    else if(pot == 5)
    {
        ser = 5;
    }
    else if(pot == 6)
    {
        ser = 6;
    }
    else
    {
        ser = 7;
    }

    return ser;
}

char numToSpace(int lett, int num)
{
    char space;

    if(lett == 1)
    {
        if(num == 0)
        {
            space = 'A';
        }
        else if(num == 1)
        {
            space = 'B';
        }
        else if(num == 2)
        {
            space = 'C';
        }
        else if(num == 3)
        {
            space = 'D';
        }
        else if(num == 4)
        {
            space = 'E';
        }
        else if(num == 5)
        {
            space = 'F';
        }
        else if(num == 6)
        {
            space = 'G';
        }
        else
        {
            space = 'H';
        }
    }
    else
    {
        if(num == 0)
        {
            space = '1';
        }
        else if(num == 1)
        {
            space = '2';
        }
        else if(num == 2)
        {
            space = '3';
        }
        else if(num == 3)
        {
            space = '4';
        }
        else if(num == 4)
        {
            space = '5';
        }
        else if(num == 5)
        {
            space = '6';
        }
        else if(num == 6)
        {
            space = '7';
        }
        else
        {
            space = '8';
        }
    }

    return space;
}


//////GAME LOGIC FUNCTIONS///////
void convert_FEN()
{
	//clearDisplay();
	//display("In FEN",6);
    int i;
    int j;
    int fencount = 0;
    int strcount = 0;
    int hold;
    int moves_made = movecounter;
    for (i = 7; i > -1; i--)
    {
        for (j = 0; j < 8; j++)
        {
            if(board_array[i][j] != 0)
            {
                if(fencount > 0)
                {
                    //printf("%d", fencount);
                    FEN[strcount] = fencount + 0x30;
                    strcount++;
                    fencount = 0;
                }
                //printf("%c", board_array[i][j]);
                FEN[strcount] = board_array[i][j];
                strcount++;
            }
            else
            {
                fencount++;
            }
        }
        if(fencount > 0)
        {
            //printf("%d", fencount);
            FEN[strcount] = fencount + 0x30;
            strcount++;
            fencount = 0;
        }
        if(i != 0)
        {
            //printf("/");
            FEN[strcount] ='/';
            strcount++;
        }
    }
    //printf("\n");
    FEN[strcount] = ' ';
    strcount++;
    FEN[strcount] = turn;
    strcount++;
    FEN[strcount] = ' ';
    strcount++;
    hold = strcount;
    if(white_kingside)
    {
        FEN[strcount] = white_kingside;
        strcount++;
    }
    if(white_queenside)
    {
        FEN[strcount] = white_queenside;
        strcount++;
    }
    if(black_kingside)
    {
        FEN[strcount] = black_kingside;
        strcount++;
    }
    if(black_queenside)
    {
        FEN[strcount] = black_queenside;
        strcount++;
    }
    if(hold == strcount)
    {
        FEN[strcount] = '-';
        strcount++;
    }
    FEN[strcount] = ' ';
    strcount++;
    FEN[strcount] = en_passant;
    strcount++;
    if(en_passant != '-')
    {
        if(turn == 'w')
        {
            FEN[strcount] = '6';
        }
        else
        {
            FEN[strcount] = '3';
        }
        strcount++;
    }

    FEN[strcount] = ' ';
    strcount++;
    FEN[strcount] = '0';
    strcount++;
    FEN[strcount] = ' ';
    strcount++;
    if(moves_made > 100)
    {
        FEN[strcount] = moves_made/100+0x30;
        moves_made /= 100;
        strcount++;
    }
    if(moves_made > 10)
    {
        FEN[strcount] = moves_made/10+0x30;
        moves_made /= 10;
        strcount++;
    }
    FEN[strcount] = moves_made+0x30;
    strcount++;
    FEN[99] = '\0';
    //printf("\n%s\n", FEN);
}

int toggle_turn()
{
    if(turn == 'w')
    {
        turn = 'b';
        return 2;
    }
    else
    {
        turn = 'w';
        return 0;
    }
}
/*
 * char color: 'b' for black, 'w' for white. The color of king whose state is checked.
 * king_x, king_y: King's coordinates
 * Attempts to determine if there a valid move from white pieces to capture black king (or vice versa), the definition of check.
 * Brute force mechanism - checks every space for valid piece, then attempts to capture king.
 */

char check_check(char color, int king_x, int king_y)
{
    int i;
    int j;
    int adjust;
    int check;
    int (*comp)(char, char);
    //printf("checking check...\n");
    toggle_turn();
    if(color == 'w') //cases inverted, white pieces enabled to check the black king
    {
        comp = gt;
    }
    else
    {
        comp = lt;
    }
    for (i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(comp(board_array[i][j], 97))
            {
                if(board_array[i][j] == 'q' || board_array[i][j] == 'Q')
                {
                    //printf("Queen checked at %d,%d, type = %c\n", i, j, board_array[i][j]);
                	//LCD Display:
					//clearDisplay();
					//display("Queen checked at ",17);
					//display(i,1);
					//display(",",1);
					//display(j,1);
					//display(",",1);
					//display(" type = ",8);
					//display(board_array[i][j],1);
                }
                check = validate_move(i, king_x, j, king_y);
                if(check)
                {
                    /*if(color == 'w' && king_x == kingpos[0] && king_y == kingpos[1])
                    {
                        checking_piece[0] = i;
                        checking_piece[1] = j;
                    }
                    if(color == 'b' && king_x == kingpos[2] && king_y == kingpos[3])
                    {
                        checking_piece[0] = i;
                        checking_piece[1] = j;
                    }*/
                    //printf("%c is in check from %d, %d to  %d, %d,  %c\n", color, i, j, king_x, king_y, board_array[i][j]);
                	//LCD Display:
					//clearDisplay();
					//display(color,1);
					//display(" is in check from ",18);
					//display(i,1);
					//display(", ",2);
					//display(j,1);
                    toggle_turn();
                    return i*10 + j;
                }
            }
        }
    }
    toggle_turn();
    return 0;
}


char check_stalemate(char color)
{
    int move;
    int i;
    int j;
    int (*comp)(char, char);
    //printf("checking stalemate...\n");
    toggle_turn();
    if(color == 'w') //cases inverted, white pieces enabled to check the black king
    {
        comp = gt;
    }
    else
    {
        comp = lt;
    }
    for (i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(comp(board_array[i][j], 97) && board_array[i][j] != 0)
            {
                move = has_valid_moves(i, j);
                if(move)
                {
                    toggle_turn();
                    return 0;
                }
            }
        }
    }
    toggle_turn();
    return 1;
}

char check_checkmate(char color, int king_x, int king_y)
{
    int i;
    int j;
    int (*comp)(char, char);
    int check;
    int valid;
    int net_x;
    int net_y;
    char nc;
    //printf("checking checkmate...\n");
    //clearDisplay();
    //display("In check_checkmate",18);
    HAL_Delay(500);
    if(color == 'b') //cases inverted, white pieces enabled to check the black king
    {
        nc = 'w';
        comp = gt;
    }
    else
    {
        nc = 'b';
        comp = lt;
    }
    for (i = -1; i < 2; i++)
    {
        for(j = -1; j < 2; j++)
        {
            toggle_turn();
            //clearDisplay();
			//display("validate_move call",18);
            valid = validate_move(king_x, king_x + i, king_y, king_y + j);
            //clearDisplay();
			//display("validate_move done",18);
            toggle_turn();
            //clearDisplay();
			//display("check_check call",16);
            check = check_check(color, king_x + i, king_y + j);
            if(!check && valid)
            {
                //printf("escape to %d, %d\n", i, j);
                return 0;
            }
        }
    }
    for (i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            //if(comp(board_array[i][j], 97))  ////changed 16 apr for checkmate
        	if(comp(board_array[i][j], 97) && board_array[i][j] != 0)
            {
                check = validate_move(i, checking_piece[0], j, checking_piece[1]);
                if(check )
                {
                    if(!(board_array[i][j] == 'k' || board_array[i][j] == 'K'))
                    {
                        //printf("capture with %d, %d\n", i, j);
                        return 0;
                    }
                    else
                    {
                        toggle_turn();
                        check = check_check(nc, checking_piece[0], checking_piece[1]);
                        toggle_turn();
                        if(check)
                        {
                            continue;
                        }
                        else
                        {
                            //printf("capture with %d, %d\n", i, j);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    net_x = checking_piece[0] - king_x;
    net_y = checking_piece[1] - king_y;
    if (net_x == 1 || net_y == 1 || net_x == -1 || net_y == -1)
    {
        return 1;
    }
    else
    {
        if(net_x == 0)
        {
            for(i = 0; i < net_y; i++)
            {
                if(check_check(color, checking_piece[0], checking_piece[1]+i))
                {
                    return 0;
                }
            }
        }
        else if(net_y == 0)
        {
            for(i = 0; i < net_x; i++)
            {
                if(check_check(color, checking_piece[0]+i, checking_piece[1]))
                {
                    return 0;
                }
            }
        }
        else if(net_y == net_x)
        {
            if(net_x > 0)
            {
                for(i = 0; i < net_x; i++)
                {
                    if(check_check(color, checking_piece[0]+i, checking_piece[1]+i))
                    {
                        return 0;
                    }
                }
            }
            else
            {
                for(i = 0; i < -net_x; i++)
                {
                    if(check_check(color, checking_piece[0]-i, checking_piece[1]-i))
                    {
                        return 0;
                    }
                }
            }
        }
        else if(net_y == -net_x)
        {
            if(net_x > 0)
            {
                for(i = 0; i < net_x; i++)
                {
                    if(check_check(color, checking_piece[0]+i, checking_piece[1]-i))
                    {
                        return 0;
                    }
                }
            }
            else
            {
                for(i = 0; i < -net_x; i++)
                {
                    if(check_check(color, checking_piece[0]-i, checking_piece[1]+i))
                    {
                        return 0;
                    }
                }
            }
        }
    }
    //clearDisplay();
	//display("End check_checkmate",19);
    return 1;
    //do the piece blocking now
}

char has_valid_moves(int x, int y)
{
    char type;
    int i;
    int j;
    type = board_array[x][y];
    switch(type)
    {
        case 'p':
        if(validate_move(x, x - 1, y, y))
        {
            return 1;
        }
        if(validate_move(x, x - 1, y, y - 1))
        {
            return 1;
        }
        if(validate_move(x, x - 1, y, y + 1))
        {
            return 1;
        }
        break;
        case 'P':
         if(validate_move(x, x - 1, y, y))
        {
            return 1;
        }
        if(validate_move(x, x - 1, y, y - 1))
        {
            return 1;
        }
        if(validate_move(x, x - 1, y, y + 1))
        {
            return 1;
        }
        break;
        case 'n':
        case 'N':
        if(validate_move(x, x - 1, y, y + 2))
        {
            return 1;
        }
        if(validate_move(x, x + 1, y, y + 2))
        {
            return 1;
        }
        if(validate_move(x, x - 1, y, y - 2))
        {
            return 1;
        }
        if(validate_move(x, x + 1, y, y - 2))
        {
            return 1;
        }
        if(validate_move(x, x - 2, y, y + 1))
        {
            return 1;
        }
        if(validate_move(x, x + 2, y, y + 1))
        {
            return 1;
        }
        if(validate_move(x, x - 2, y, y - 1))
        {
            return 1;
        }
        if(validate_move(x, x + 2, y, y - 1))
        {
            return 1;
        }
        break;
        case 'b':
        case 'B':
        for (i = -7; i < 8; i ++)
        {
            if(validate_move(x, x + i, y, y - i))
            {
                return 1;
            }
            if(validate_move(x, x + i, y, y + i))
            {
                return 1;
            }
        }
        break;
        case 'q':
        case 'Q':
        for (i = -7; i < 8; i ++)
        {
            if(validate_move(x, x + i, y, y - i))
            {
                return 1;
            }
            if(validate_move(x, x + i, y, y + i))
            {
                return 1;
            }
            if(validate_move(x, x + i, y, y))
            {
                return 1;
            }
            if(validate_move(x, x, y, y + i))
            {
                return 1;
            }
        }
        break;
        case 'r':
        case 'R':
        for (i = -7; i < 8; i ++)
        {
            if(validate_move(x, x + i, y, y))
            {
                return 1;
            }
            if(validate_move(x, x, y, y + i))
            {
                return 1;
            }
        }
        break;
        case 'k':
        case 'K':
        for (i = -1; i < 2; i++)
        {
            for(j = -1; j < 2; j++)
            {
                if(validate_move(x, x + i, y, y + j))
                {
                    return 1;
                }
            }
        }
        break;
        default:
		return 0;
		break;
    }
    return 0;

}

int gt(char a, char b)
{
    return a > b;
}

int lt(char a, char b)
{
    return a < b;
}
//turns human input into a parsable move
int translate_input(int* start_x, int* end_x, int* start_y, int* end_y)
{

    char in[15];
    int *pointers[4];
    int i;
    pointers[0] = start_y;
    pointers[1] = start_x;
    pointers[2] = end_y;
    pointers[3] = end_x;

////Commenting following stmts because moves will be function inputs anyway
////    printf("Put in a move in UCI format: e.g. e2e4, d7d5, etc. Turn: %c. ", turn);
////    fgets(in, 10, stdin);
    in[4] = 0;
    for (i = 0; i < 4; i++)
    {
        switch(in[i])
        {
            case 'a':
                *pointers[i] = 0;
                break;
            case 'b':
                *pointers[i] = 1;
                break;
            case 'c':
                *pointers[i] = 2;
                break;
            case 'd':
                *pointers[i] = 3;
                break;
            case 'e':
                *pointers[i] = 4;
                break;
            case 'f':
                *pointers[i] = 5;
                break;
            case 'g':
                *pointers[i] = 6;
                break;
            case 'h':
                *pointers[i] = 7;
                break;
            case '1':
                *pointers[i] = 0;
                break;
            case '2':
                *pointers[i] = 1;
                break;
            case '3':
                *pointers[i] = 2;
                break;
            case '4':
                *pointers[i] = 3;
                break;
            case '5':
                *pointers[i] = 4;
                break;
            case '6':
                *pointers[i] = 5;
                break;
            case '7':
                *pointers[i] = 6;
                break;
            case '8':
                *pointers[i] = 7;
                break;
        }
    }
    fflush(stdin);
}
//prints board array into human readable format
int print_board()
{

	/*
    int i = 0;
    int row = 7;
    //printf("    --------\n");
    clearDisplay();
    display("    --------",12);  //12 with 4 spaces in the beginning
    dispLine2();
    while (row > -1)
    {
      //printf("%d | ", row + 1);
      display(row + 1,1);
      display(" | ",3);
      //dispLine2();
      for(i = 0; i < 8; i ++)
      {
          if(board_array[row][i] == '\0')
          {
              //printf(" ");
        	  display(" ",1);
          }
          else
          {
              //printf("%c", board_array[row][i]);
        	  display(board_array[row][i],1);
          }
      }
      //printf("\n");
      dispLine2();
      row--;
    }
    //printf("    --------\n");
    display("    --------",12);
    dispLine2();
    //printf("    abcdefgh\n");
    display("    abcdefgh",12);
    dispLine2();
	*/
	char l[10] = {' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	for(int f = 0; f < 10; f++)
	{
		line2[f] = l[f];
	}

	for(int k = 7; k >= 0; k--)  //was k=0, k<8, k++
	  {
		  HAL_Delay(750);
		  clearDisplay();

		  for(int j = 0; j < 10; j++)
		  {
			  line1[j] = line2[j];
		  }

		  line2[0] = nums[k];
		  line2[1] = ' ';

		  for(int j = 0; j < 8; j++)
		  {
			  line2[j + 2] = board_array[k][j];
		  }

		  display(line1, 10);
		  dispLine2();
		  display(line2, 10);
	  }


}

/*
int start_x, end_x, start_y, end_y - start and end positions of pieces
char type - piece. P - pawn, B - Bishop, N - Knight, Q - Queen, K - King. Lowercase pieces are black. Uppercase are white.
------
Primary move validation function.
CAN:
Validate pieces move correctly.
Prevents pieces from moving through or on top of each other.
Enforce check.
CANNOT:
King pins, en passant, castling
*/


int validate_move(int start_x, int end_x, int start_y, int end_y)
{
	//clearDisplay();
	//display("In Validate",11);
    int valid = 0;
    int x, y;
    int selfcap = 0;
    int jump = 0;
    char type;
    convert_move(start_x, end_x, start_y, end_y);
    type = board_array[start_x][start_y];
    //printf("validating...");
    x = move[0];
    y = move[1];
    //if((end_x < -1 || end_y < -1 || end_x > 7 || end_y > 7))
    if(end_x < 0 || end_y < 0 || end_x > 7 || end_y > 7)
    {
        //printf("out of bounds\n");
    	//LCD:
    	if(moveflag)
    	{
    		clearDisplay();
    		display("out of bounds",13);
    	}
    	return valid;
    }
    selfcap = self_capture_check(type, end_x, end_y);
    jump = (jump_check(start_x, end_x, start_y, end_y) && !(type == 'N' || type == 'n'));
    if(!check_color(start_x, start_y, turn))
    {
        //printf("wrong color piece!\n");
    	//LCD:
    	if(moveflag)
    	{
    		clearDisplay();
    		display("wrong color piece!",18);
    	}
        return valid;
    }
    if(selfcap || jump || (x == 0 && y == 0))
    {
        //printf("self capture or jump failure! %d %d \n", selfcap, jump);
    	//LCD:
    	if(moveflag)
    	{
    		clearDisplay();
    		display("self capture or jump failure!",29);
    	}
        return valid;
    }
    switch(type)
    {
    	char type1[1] = {numToSpace(0,type)};
    	clearDisplay();
    	display(type1,1);
        case 'p':
        if(x == -2 && start_x == 6 && !capture_check('b', end_x, end_y)) //add condition for pawn start
        {
            valid = 1;
        }
        if(x == -1 && !capture_check('b', end_x, end_y)) //pawns cannot capture forward
        {
            valid = 1;
        }
        if(x == -1 && (y == 1 || y == -1) && (capture_check('b', end_x, end_y) || en_passant_check('b', start_y)))
        {
            valid = 1;
        }
        break;
        case 'P':
        if(x == 2 && start_x == 1  && !capture_check('w', end_x, end_y)) //add condition for pawn start
        {
            valid = 1;
        }
        if(x == 1 && !capture_check('w', end_x, end_y))
        {
            valid = 1;
        }
        if(x == 1 && (y == 1 || y == -1) && (capture_check('w', end_x, end_y) || en_passant_check('w', start_y)))
        {
            valid = 1;
        }
        break;
        case 'n':
        case 'N':
        if (((x == -2 || x == 2) && (y == 1 || y == -1)) || ((x == -1 || x == 1) && (y == 2 || y == -2)))
        {
            //printf("N: %d %d\n", x, y);
            valid = 1;
        }
        break;
        case 'b':
        case 'B':
        if (x == y || -x == y)
        {
            valid = 1;
        }
        break;
        case 'q':
        case 'Q':
        if ((x == 0 || y == 0) || (x == y || -x == y))
        {
            valid = 1;
        }
        break;
        case 'r':
        case 'R':
        if (x == 0 || y == 0)
        {
            valid = 1;
            //set_rook_flags(start_x, start_y);
        }
        break;
        case 'k':
        case 'K':
        if ((x <= 1 && y <= 1) && (x >= -1 && y >= -1))
        {
            //printf("king moving %d, %d\n", x, y);
    		clearDisplay();
    		display("King move! ",9);
            valid = 1;
        }
        else
        {
            //printf("%d", end_y);
            if(end_y == 6 && x == 0)
            {
                valid = castle_check(type, 'k');
                castling = valid;
            }
            else if(end_y == 2 && x == 0)
            {
                valid = castle_check(type, 'q');
                castling = valid;
            }
        }
        //if(castle_check(type == 'k' ? castle_check('b',x) : castle_check('w',x))) //Handle castling here
        //{
        //    valid = 1;
        //}
        break;
        default:
    		//clearDisplay();
    		//display("Move fail! ",9);
        break;
    }
    /*if(type > 97)
    {
        if(type != 'k')
        {
            if(check_check('b', end_x, end_y))
            {
                valid = 0;
            }
        }
        else if(check_check('b', kingpos[2], kingpos[3]))
        {
            valid = 0;
        }
    }
    else
    {
        if(type != 'K')
        {
            if(check_check('w', end_x, end_y))
            {
                valid = 0;
            }
        }
        if(check_check('w', kingpos[0], kingpos[1]))
        {
            valid = 0;
        }
    }*/
    if(valid && (type == 'k' || type == 'K'))
    {
		clearDisplay();
		display("KingPos updated",15);
        if(type == 'k')
        {
            kingpos[2] = end_x;
            kingpos[3] = end_y;
        }
        else
        {
            kingpos[0] = end_x;
            kingpos[1] = end_y;
        }
    }
    //clearDisplay();
    //display("Valid: ",7);
    //display(valid,1);
    if(valid)
    {
        //printf("valid! %c to %d,%d \n", type, end_x, end_y);
    	//LCD:
    	if(moveflag)
    	{
    		char t[1] ={type};
    		char ex[1] = {numToSpace(0,end_x)};
    		char ey[1] = {numToSpace(1,end_y)};
    		clearDisplay();
    		display("valid! ",7);
    		//display(type,1); //"=" instead of type
    		display(t, 1);
    		display(" to ",4);
    		//display(numToSpace(0,end_x),1);  //space
    		display(ey, 1);
    		display(ex, 1);
    		//display(",",1);
    		//display(numToSpace(1,end_y),1); //space
    		HAL_Delay(1500);
    	}
    }
    else
    {
        //printf("not valid?\n");
        //LCD:
    	if(moveflag)
    	{
    		char t[1] ={type};
			char ex[1] = {numToSpace(0,end_x)};
			char ey[1] = {numToSpace(1,end_y)};
    		clearDisplay();
    		display("not valid",9);
    		display(t, 1);
    		display(" to ",4);
    		display(ey, 1);
			display(ex, 1);
    		HAL_Delay(1500);
    	}
    }
    return valid;
}



//if king moves, nuke the castling flags
void nuke_castle_flags(char type)
{
    if(type == 'r' || type == 'R')
    {
        set_rook_flags(lastmove[0], lastmove[2]);
    }
    else if(type == 'k')
    {
        black_kingside = 0;
        black_queenside = 0;
    }
    else
    {
        white_kingside = 0;
        white_queenside = 0;
    }
}

int check_color(int start_x, int start_y, char color)
{
    if(color == 'w')
    {
        return board_array[start_x][start_y] < 97;
    }
    else
    {
        return board_array[start_x][start_y] > 97;
    }
}


int exec_move(int start_x, int end_x, int start_y, int end_y)
{
    int net_x;
    int net_y;
    net_x = end_x - start_x;
    net_y = end_y - start_y;
    //printf("Processing move x: %d, y: %d\n", net_x, net_y);
    if(check_color(start_x, start_y, 'b'))
    {
        movecounter += 1;
    }
    //printf("(%d, %d) to (%d, %d)\n", start_x, start_y, end_x, end_y);
    removed_piece = board_array[end_x][end_y];
    board_array[end_x][end_y] = board_array[start_x][start_y];
    board_array[start_x][start_y] = 0;
    lastmove[0] = start_x;
    lastmove[1] = end_x;
    lastmove[2] = start_y;
    lastmove[3] = end_y;
    return 0;
}

int fix_castling()
{
    if(lastmove[1] == 0)
    {
        if(lastmove[3] == 6)
        {
            board_array[0][7] = 0;
            board_array[0][5] = 'R';
        }
        if(lastmove[3] == 2)
        {
            board_array[0][0] = 0;
            board_array[0][3] = 'R';
        }
    }
    if(lastmove[1] == 7)
    {
        if(lastmove[3] == 6)
        {
            board_array[7][7] = 0;
            board_array[7][5] = 'r';
        }
        if(lastmove[3] == 2)
        {
            board_array[7][0] = 0;
            board_array[7][3] = 'r';
        }
    }
    return 0;
}

int undo_move()
{
    if(board_array[lastmove[1]][lastmove[3]] == 'k')
    {

        //printf("black king reset!\n");
        kingpos[2] = lastmove[0];
        kingpos[3] = lastmove[2];
    }
    if(board_array[lastmove[1]][lastmove[3]] == 'K')
    {
        //printf("white king reset!\n");
        kingpos[0] = lastmove[0];
        kingpos[1] = lastmove[2];
    }
    board_array[lastmove[0]][lastmove[2]] = board_array[lastmove[1]][lastmove[3]];
    board_array[lastmove[1]][lastmove[3]] = removed_piece;

    if(check_color(lastmove[0], lastmove[2], 'b'))
    {
        movecounter -= 1;
    }
}

int capture_check(char color, int x, int y)
{
    if(board_array[x][y] == 0)
    {
        return 0;
    }
    if(board_array[x][y] != '\0' && color == 'w' ? board_array[x][y] > 97 : board_array[x][y] < 97)
    {
        return 1;
    }
    return 0;
}
int self_capture_check(char piece, int x, int y)
{
    if(board_array[x][y] == 0)
    {
        return 0;
    }
    if(board_array[x][y] != '\0' && (piece > 97 ? board_array[x][y] > 97 : board_array[x][y] < 97))
    {
        return 1;
    }
    return 0;
}
int castle_check(char king, char side)
{
    //printf("checking castle...\n");
    if(king == 'k')
    {
        if(side == 'k' && (!black_kingside || board_array[7][5] || board_array[7][6]))
        {
            //printf("black king crossing through pieces kingside\n");
            return 0;
        }
        else if(side == 'k')
        {

            return !check_check('b', 7, 4) && !check_check('b', 7, 5) && !check_check('b', 7, 6);
        }

        else if(side == 'q' && (!black_queenside || board_array[7][3] || board_array[7][2] || board_array[7][1]))
        {
            //printf("black king crossing through pieces queenside\n");
            return 0;
        }
        else
        {
            return !check_check('b', 7, 4) && !check_check('b', 7, 3) && !check_check('b', 7, 2);
        }
    }
    if(king == 'K')
    {
        if(side == 'k' && (!white_kingside || board_array[0][5] || board_array[0][6]))
        {

            //printf("black king crossing through pieces kingside\n");
            return 0;
        }
        else if(side == 'k')
        {
            return !check_check('b', 0, 4) && !check_check('b', 0, 5) && !check_check('b', 0, 6);
        }

        else if(side == 'q' && (!white_queenside || board_array[0][3] || board_array[0][2] || board_array[0][1]))
        {

            //printf("white king crossing through pieces queenside, %d %d %d %d\n", white_queenside, board_array[0][3], board_array[0][2], board_array[0][1]);
            return 0;
        }
        else
        {
            return !check_check('b', 7, 4) && !check_check('b', 7, 3) && !check_check('b', 7, 2);
        }
    }

}
int en_passant_check()
{
    return 0;
}
void set_rook_flags(int start_x, int start_y)
{
    if(start_x == 7 && start_y == 7)
    {
        black_kingside = 0;
    }
    else if(start_x == 7 && start_y == 0)
    {
        black_queenside = 0;
    }
    else if(start_x == 0 && start_y == 7)
    {
        white_queenside = 0;
    }
    else if(start_x == 0 && start_y == 0)
    {
        white_queenside = 0;
    }
    return;
}
int jump_check(int start_x, int end_x, int start_y, int end_y)
{
    int x;
    int y;
    int dirx;
    int diry;
    int i;
    x = move[0];
    y = move[1];
    if (x == y)
    {
        if(x > 0)
        {
            for(i = 1;  i < x; i ++)
            {
                if(board_array[start_x + i][start_y + i] != 0)
                {
                    return 1;
                }
            }
        }
        else
        {
            for(i = 1 ; i < -x; i ++)
            {
                if(board_array[start_x - i][start_y - i] != 0)
                {
                    return 1;
                }
            }
        }
    }
    else if (-x == y)
    {
        if(x > 0)
        {
            for(i = 1; i < x; i ++)
            {
                //printf("%d, %d\n", start_x + i, start_y - i);
                if(board_array[start_x + i][start_y - i] != 0)
                {
                    return 1;
                }
            }
        }
        else
        {
            for(i = 1 ; i < -x; i ++)
            {
                //printf("%d, %d\n", start_x - i, start_y + i);
                if(board_array[start_x - i][start_y + i] != 0)
                {
                    return 1;
                }
            }
        }
    }
    else if (x == 0)
    {
        if(y > 0)
        {
            for (i = 1; i < y; i++)
            {
                if(board_array[start_x][start_y+i] != 0)
                {
                    return 1;
                }
            }
        }
        else
        {
            for (i = 1; i < -y ; i++)
            {
                if(board_array[start_x][start_y-i] != 0)
                {
                    return 1;
                }
            }

        }
    }
    else if (y == 0)
    {
        if(x > 0)
        {
            for (i = 1; i < x; i++)
            {
                if(board_array[start_x+i][start_y] != 0)
                {
                    //printf("%c at %d, %d\n", board_array[start_x+i][start_y], start_x+i, start_y);
                    return 1;
                }
            }
        }
        else
        {
            for (i = 1; i < -x ; i++)
            {
                if(board_array[start_x - i][start_y] != 0)
                {
                    return 1;
                }
            }

        }
    }
    return 0;
}
int convert_move(int start_x, int end_x, int start_y, int end_y)
{
    move[0] = end_x-start_x;
    move[1] = end_y-start_y;
}
//////GAME LOGIC FUNCTIONS///////



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  ///GAME LOGIC///
	int start_x;
	int end_x;
	int start_y;
	int end_y;
	int valid;
	int adjust = 0;
	int check  = 0;
	int stale  = 0;
	int transient = 0;
	checking = 0;
	turn = 'w';
	movecounter = 1;
	black_queenside = 'q';
	black_kingside = 'k';
	white_queenside = 'Q';
	white_kingside = 'K';
	en_passant = '-';
	kingpos[0] = 0;
	kingpos[1] = 4;
	kingpos[2] = 7;
	kingpos[3] = 4;
	checking_piece[0] = -1;
	checking_piece[1] = -1;
  ///GAME LOGIC///


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_SPI1_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
  // motor controls
  wait = 0;
  mode = 0;
  DIR0_ON();
  DIR1_ON();
  STEP0_OFF();
  STEP1_OFF();
  M0_OFF();
  M1_OFF();
  M2_OFF();
  MTR_SLP_OFF(); // !!!!!! change back to ON to let motors move

  // player led
  WHITE_OFF();
  BLACK_OFF();

  HAL_TIM_Base_Start_IT(&htim14);

  // led array controls
  OE_OFF();
  SCLK_OFF();
  RCLK_OFF();

  // magnet
  MAG_ON();

  // lcd
  HAL_Delay(1000);
  lcdInit();

  char board[72] = {'r', 'n', 'b', 'k', 'q', 'b', 'n', 'r',
                    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                    '.', '.', '.', '.', '.', '.', '.', '.',
                    '.', '.', '.', '.', '.', '.', '.', '.',
                    '.', '.', '.', '.', '.', '.', '.', '.',
                    '.', '.', '.', '.', '.', '.', '.', '.',
                    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                    'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R',
                    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  char line1[10] = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
  char line2[10] = {' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  //char nums[9] = {'8', '7', '6', '5', '4', '3', '2', '1', ' '};
  char nums[9] = {'1', '2', '3', '4', '5', '6', '7', '8', ' '};

  //display(line1, 10);
  //dispLine2();
  //display(line2, 10);

  uint32_t send_btn;
  /*SER0_OFF();
  SER1_ON();
  SER2_OFF();
  SER3_ON();
  for(int i = 0; i < 8; i++)
  {
      SCLK_ON();
      HAL_Delay(50);
      SCLK_OFF();
      HAL_Delay(50);
  }
  RCLK_ON();
  HAL_Delay(50);
  RCLK_OFF();
  HAL_Delay(50);*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


      ////PUTTING IN PIECE_VALIDATION CODE BEFORE PIECE MOVEMENT CODE>>>>>////// (GAME LOGIC)
      //toggle_turn();
	  //convert_FEN();
	  //transmitString(&huart1, FEN);
	  check = check_check(turn, kingpos[adjust], kingpos[adjust+1]);
	  checking_piece[0] = check / 10;
	  checking_piece[1] = check % 10;
	  //clearDisplay();
	  //display("check checked2!",15);
	  if(check)
	  {
		  //printf("king at %d,%d \n", kingpos[adjust], kingpos[adjust+1]);
		  if(check_checkmate(turn, kingpos[adjust], kingpos[adjust+1]) == 1)
		  {
			  //printf("%c is checkmated!\n", turn);
			  //LCD
			  clearDisplay();
			  char turn_ar[1] ={turn};
			  display(turn_ar,1);
			  display(" is checkmated!",16);
			  break;
		  }
		  else
		  {
			  //printf("check!\n");
			  //LCD Display:
			  clearDisplay();
			  display("check!",6);
		  }
	  }
	  else
	  {
		  stale = 0;
		  //stale = check_stalemate(turn);
		  if(stale)
		  {
			  //printf("Stalemate!\n");
			  //LCD Display:
			  clearDisplay();
			  display("Stalemate!",10);
			  break;
		  }
	  }

	  transient = 1;
	  while(transient)
	  {
		  print_board(); //works
		  //convert_FEN();
		  //translate_input(&start_x, &end_x, &start_y, &end_y);
		  waitPlayerMove(); //>>>REPLACES TRANSLATE_INPUT
		  //set flag here
		  moveflag = 1;
		  valid = validate_move(start_lett, end_lett, start_num, end_num);
		  ///clear flag here
		  moveflag = 0;
		  if(valid)
		  {
			  exec_move(start_lett, end_lett, start_num, end_num);
			  clearDisplay();
			  display("move executed!",14);
			  check = check_check(turn, kingpos[adjust], kingpos[adjust+1]);
			  clearDisplay();
			  display("check checked!",14);
			  if(check)
			  {
				  /*if(check_checkmate(turn, kingpos[adjust], kingpos[adjust+1]))
				  {
					  printf("%c is checkmated!\n");
					  break;
				  }
				  else*/
				  //printf("king at %d,%d \n", kingpos[adjust], kingpos[adjust+1]);
				  //printf("\nKing still in check!\n");
				  //LCD Display:
				  clearDisplay();
				  display("King still in check!",20);
				  //adjust = toggle_turn();
				  undo_move();
				  continue;
			  }
			  transient = 0;
			  if(castling)
			  {
				  fix_castling();
				  castling = 0;
			  }
			  if(board_array[lastmove[1]][lastmove[3]] == 'k' || board_array[lastmove[1]][lastmove[3]] == 'K' || board_array[lastmove[1]][lastmove[3]] == 'R' || board_array[lastmove[1]][lastmove[3]] == 'r')
			  {
				  //printf("nuking flags\n");
				  nuke_castle_flags(board_array[lastmove[1]][lastmove[3]]);
			  }
			  adjust = toggle_turn();
		  }
	  }

      ////<<<<<<PIECE_VALIDATION CODE///// (GAME LOGIC)

  	  /*
      // move piece
      board[8*(7-end_num) + end_lett] = board[8*(7-start_num) + start_lett];
      board[8*(7-start_num) + start_lett] = '.';    */ //<<CODE SHIFTED TO BETWEEN PIECE VALIDATION CODE
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_7;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 8;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 999;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8 
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB14 PB3 PB4 
                           PB5 PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 
                           PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PF6 PF7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
