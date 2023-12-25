#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "CLCD_interface.h"


void PP_voidRocketDirection(uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus)
{
	/* The racket pattern on LCD */
	uint8 Local_au8Racket[8] = {0b00011100, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00011100, 0b00000000};

	DIO_u8ReadPinValue(DIO_u8PORTB, DIO_u8PIN0, &Copy_u8ButtStatus);

	if(Copy_u8ButtStatus == DIO_u8PIN_LOW)
	{
		_delay_ms(50); // Debouncing delay

		CLCD_voidGoToXY(0, *Copy_pu8RocketPos);
		CLCD_voidSendData(' ');

		*Copy_pu8RocketPos = !(*Copy_pu8RocketPos);
		CLCD_u8SendSpecialCharacter(1, Local_au8Racket, 0, *Copy_pu8RocketPos);
	}
}
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
void PP_voidBallMove_1_MCU1(uint8 Copy_u8BallPos, uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus)
{
	/* Simulates the first movement at the begining of game */
	uint8 Local_u8BallIterator = 0u;
	uint8 Local_au8Ball[8] = {0b00000000, 0b00001000, 0b00010100, 0b00010100, 0b00001000, 0b00000000, 0b00000000, 0b00000000};

	for(Local_u8BallIterator = 1u; Local_u8BallIterator < 16u; Local_u8BallIterator++)
	{
		PP_voidRocketDirection(Copy_pu8RocketPos, Copy_u8ButtStatus);

		CLCD_u8SendSpecialCharacter(2, Local_au8Ball, Local_u8BallIterator, Copy_u8BallPos);
		_delay_ms(75);

		CLCD_voidGoToXY(Local_u8BallIterator, Copy_u8BallPos);
		CLCD_voidSendData(' ');
	}
}
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
uint8 PP_voidBallMove_2_MCU1(uint8 Copy_u8BallPos, uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus)
{
	/* Simulates the movement when the ball comes from the MCU2 */
	uint8 Local_u8BallIterator = 0u;
	uint8 Local_u8ExitFlag = 0u;  // Exit flag to quite from the outer and the inner loop

	/* The ball pattern on LCD */
	uint8 Local_au8Ball[8] = {0b00000000, 0b00001000, 0b00010100, 0b00010100, 0b00001000, 0b00000000, 0b00000000, 0b00000000};

	for(Local_u8BallIterator = 15u; Local_u8BallIterator >= 1u; Local_u8BallIterator--)
	{
		PP_voidRocketDirection(Copy_pu8RocketPos, Copy_u8ButtStatus);

		CLCD_u8SendSpecialCharacter(2, Local_au8Ball, Local_u8BallIterator, Copy_u8BallPos);
		_delay_ms(75);

		CLCD_voidGoToXY(Local_u8BallIterator, Copy_u8BallPos);
		CLCD_voidSendData(' ');

		if(Local_u8BallIterator == 1u)
		{
			if(Copy_u8BallPos == (*Copy_pu8RocketPos))
			{
				for(Local_u8BallIterator = 2u; Local_u8BallIterator <= 15u; Local_u8BallIterator++)
				{
					PP_voidRocketDirection(Copy_pu8RocketPos, Copy_u8ButtStatus);

					CLCD_u8SendSpecialCharacter(2, Local_au8Ball, Local_u8BallIterator, Copy_u8BallPos);
					_delay_ms(75);

					CLCD_voidGoToXY(Local_u8BallIterator, Copy_u8BallPos);
					CLCD_voidSendData(' ');

					if(Local_u8BallIterator == 15u)
					{
						// Generate an interrupt to start the MCU2
						DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_HIGH);
						DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_LOW);

						// Turn of the start pin
						DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN3, DIO_u8PIN_LOW);

						Local_u8ExitFlag = 1u;
						return 1;
					}
				}
			}
			else
			{
				return 0;
			}
		}
	}
}
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
void INT0_Func(void)
{
	// Turn on the MCU2
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN3, DIO_u8PIN_HIGH);
}
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
