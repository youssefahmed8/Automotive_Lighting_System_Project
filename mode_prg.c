/******************************************************************************/
/*                                                                            */
/* !Layer           : Application Abstraction Layer                           */
/*                                                                            */
/* !Component       : MODE                                                    */
/* !Description     : Hazzard Indicator Function module                       */
/*                                                                            */
/* !Module          : MODE                                                    */
/* !Description     : MODE Module interface                                   */
/*                                                                            */
/* !File            : mode_prg.c                                              */
/*                                                                            */
/* !Scope           : Private                                                 */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Induction training exercise project                     */
/*                                                                            */
/* !Target          : ATMega32                                                */
/*                                                                            */
/* !Compiler        : AVR GCC Cross Compiler                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Coded by        : Youssef Ahmed                   !Date : 25/11/2023      */
/*                                                                            */
/******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SW_interface.h"
#include "SSD_interface.h"
#include "CLCD_interface.h"


#include "mode_int.h"

/******************************************************************************/

/* Global Variables Definition */
MODE_enutModeState Type,PreviousType;

/*****************************************************************************************/
extern SSD_Type R_SSD ;
extern SSD_Type L_SSD ;

extern SW_Type R_SW ;
extern SW_Type L_SW ;
extern SW_Type H_SW ;
/*****************************************************************************************/

/******************************************************************************/
/*! \Description Helper Functions                                             */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
void APP_vidSetMode(MODE_enutModeState enutSetMode)
{
	/*
 IDLE = 0,
    RIGHT_BLINK,
    LEFT_BLINK,
    HAZZARD_BLINK

**/
	switch(enutSetMode)
	{
		case IDLE:
		CLCD_voidSendString((u8*)"IDEL MODE");
		SSD_voidDisable(L_SSD);
		SSD_voidDisable(R_SSD);
		break;

		case RIGHT_BLINK:
		CLCD_voidSendString((u8*)"RIGHT_BLINK MODE");
		SSD_voidDisable(L_SSD);
		SSD_voidEnable(R_SSD);
		SSD_voidSendNumber(R_SSD,0);
		break;
		case LEFT_BLINK:
			CLCD_voidSendString((u8*)"LEFT_BLINK MODE");
			SSD_voidEnable(L_SSD);
			SSD_voidDisable(R_SSD);
			SSD_voidSendNumber(L_SSD,0);

			break;
		case HAZZARD_BLINK:
		CLCD_voidSendString((u8*)"HAZZARD_BLINK MODE");
		SSD_voidEnable(L_SSD);
		SSD_voidEnable(R_SSD);
		SSD_voidSendNumber(R_SSD,0);
		SSD_voidSendNumber(L_SSD,0);

		break;

	}

}

/***************************************/
void MODE_vidIdle (void)
{
	/* Set Mode to IDLE */
	APP_vidSetMode(IDLE);
	/* Check the SWs */
	if(SW_u8GetPressed(L_SW))
	{
		Type=LEFT_BLINK;
	}
	else if(SW_u8GetPressed(R_SW))
	{
		Type=RIGHT_BLINK;
	}
	else if(SW_u8GetPressed(H_SW))
	{
		PreviousType=IDLE;
		Type=HAZZARD_BLINK;
	}
}
void MODE_vidRightBlink (void)
{
	/* Set Mode to RIGHT_BLINK */
	APP_vidSetMode(RIGHT_BLINK);

	/* Check the SWs */
	if(SW_u8GetPressed(L_SW))
	{
		Type=IDLE;
	}

	else if(SW_u8GetPressed(H_SW))
	{
		PreviousType=RIGHT_BLINK;
		Type=HAZZARD_BLINK;
	}
}
void MODE_vidLeftBlink (void)
{
	/* Set Mode to LEFT_BLINK */
	APP_vidSetMode(LEFT_BLINK);

	/* Check the SWs */

		if(SW_u8GetPressed(R_SW))
		{
			Type=IDLE;
		}
		else if(SW_u8GetPressed(H_SW))
		{
			PreviousType=LEFT_BLINK;
			Type=HAZZARD_BLINK;
		}
}
void MODE_vidHazardBlink (void)
{
	/* Set Mode to HAZZARD_BLINK */
	APP_vidSetMode(HAZZARD_BLINK);

	/* Check the SWs */
	if(SW_u8GetPressed(L_SW))
	{
		Type=HAZZARD_BLINK;
	}
	else if(SW_u8GetPressed(R_SW))
	{
		Type=HAZZARD_BLINK;
	}
	else if(SW_u8GetPressed(H_SW))
	{

		Type=PreviousType;
	}

}


/*****************************************************************************************/

/******************************************************************************/
/*! \Description Initialize the MODE driver variables                         */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
void MODE_vidInit(void)
{
	/* Set Mode to Default (IDLE) */
	MODE_vidIdle();
}

/******************************************************************************/
/*! \Description The MODE driver task, should be called periodically.
				 This service update the state of all configured push
                 buttons.                                                     */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
void MODE_vidTask(void)
{
	/* Check the global enum then call Mode API According to it */
	if(Type==IDLE)
	{
		MODE_vidIdle();
	}
	else if(Type==LEFT_BLINK)
	{
		MODE_vidLeftBlink();
	}
	else if(Type==RIGHT_BLINK)
	{
		MODE_vidRightBlink();
	}
	else if(Type==HAZZARD_BLINK)
	{
		MODE_vidHazardBlink();
	}
}

/**********************************************************************************************/
