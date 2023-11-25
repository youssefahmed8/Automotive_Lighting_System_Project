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
/* !File            : mode_int.h                                              */
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


#ifndef MODE_INT_H_
#define MODE_INT_H_

/******************************************************************************/

typedef enum
{
    IDLE = 0,
    RIGHT_BLINK,
    LEFT_BLINK,
    HAZZARD_BLINK
} MODE_enutModeState;

/******************************************************************************/
/*! \Description Initialize the MODE driver variables                         */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
extern void MODE_vidInit(void);

/******************************************************************************/
/*! \Description The MODE driver task, should be called periodically.         
				 This service update the state of all configured push
                 buttons.                                                     */
/*! \return      None                                                         */
/*! \Trace_To                                                                 */
/******************************************************************************/
extern void MODE_vidTask(void);
#endif // MODE_INT_H_
