#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"

#include "App.h"

//void PP_voidRocketDirection(uint8* Copy_pu8RocketPos, uint8 Copy_u8ButtStatus);

void main(void)
{
	/* A0 To A6 (LCD) are Output */
	/* C0 Pin (MCU1 signal To EXTI pin in MCU2) are Output Low */
	/* C3 Pin (Start pin in MCU1) is Output Low */
	/* D2(INT0) is Input-PullUp */
	/* B0(Button) is Input-PullUp */
	PORT_voidInit();

	/* Initilization the LCD */
	CLCD_voidInit();

	/* Enable the global interrupt */
	GIE_voidEnableGlobal();

	/* INT0 is Enabled with RisingEdge sense ctrl */
	/* INT1 is Disabled */
	/* INT2 is Disabled */
	EXTI_voidInit();

	/* Call back INT0 function by its address */
	EXTI_u8SetCallBack(INT0, &INT0_Func);



	/* The racket pattern on LCD */
	uint8 Local_au8Racket[8] = {0b00011100, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00010100, 0b00011100, 0b00000000};

	uint8 Local_u8RocketPos = 0u;     // For determining the position of the rocket
	uint8 Local_u8ButtStatus = 0u;	  // For storing the value of button reading
	uint8 Local_u8State2 = 0u;        // For storing the value of button reading
	uint8 Local_PositionCounter = 0u; // Using for generating random moving for the ball

	uint8 Local_GameStatus = 1u; // Using for generating random moving for the ball


	while(1)
	{
		CLCD_u8SendSpecialCharacter(1, Local_au8Racket, 15, Local_u8RocketPos);

		Local_PositionCounter++;  // To generate random movment for the ball

		do
		{
			PP_voidRocketDirection(&Local_u8RocketPos, Local_u8ButtStatus);
			_delay_ms(50);
			DIO_u8ReadPinValue(DIO_u8PORTC, DIO_u8PIN3, &Local_u8State2);

		}while(Local_u8State2 == 0u);

		// Generate random movment for the ball depend on the condition
		if(Local_PositionCounter % 2 == 0u)
		{
			Local_GameStatus = PP_voidBallMove_MCU2(0, &Local_u8RocketPos, Local_u8ButtStatus);

			if(Local_GameStatus == 0u)
			{
				CLCD_voidSendCmd(1);
				CLCD_u8SendString("You Lose :(");
				break;
			}
			else
			{
				continue;
			}
		}
		else
		{
			Local_GameStatus = PP_voidBallMove_MCU2(1, &Local_u8RocketPos, Local_u8ButtStatus);

			if(Local_GameStatus == 0u)
			{
				CLCD_voidSendCmd(1);
				CLCD_u8SendString("You Lose :(");
				break;
			}
			else
			{
				continue;
			}
		}
	}
}




