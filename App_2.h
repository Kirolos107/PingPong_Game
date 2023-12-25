#ifndef APP_H
#define APP_H

void PP_voidRocketDirection(uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus);

uint8 PP_voidBallMove_MCU2(uint8 Copy_u8BallPos, uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus);

void INT0_Func(void);


#endif
