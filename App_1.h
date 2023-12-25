#ifndef APP_H
#define APP_H

void PP_voidRocketDirection(uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus);

void PP_voidBallMove_1_MCU1(uint8 Copy_u8BallPos, uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus);

uint8 PP_voidBallMove_2_MCU1(uint8 Copy_u8BallPos, uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus);

void INT0_Func(void);


#endif
