/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                          (c) Copyright 2009-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          APPLICATION CODE
*
*                                          Microsoft Windows
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : JJL
*                 FGK
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/
/*=====================================================================
my task definition
*/
#define TASK_STACK_SIZE 512
#define TASK1_PRIORITY 21
#define TASK2_PRIORITY 22
#define TASK1_ID 1
#define TASK2_ID 2
/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
/*==============================================================
os stack declaration
edf data declaration
*/
OS_STK TASK1STK[TASK_STACK_SIZE];
OS_STK TASK2STK[TASK_STACK_SIZE];
EDF_DATA edf_datas[] =
{
	{ 1,3,1,4,1 },
	{ 3,5,3,6,1 }
};


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart(void  *p_arg);
/*===========================================================
FUNCTION DECLARATION
*/
static void task1(void* p);
static void task2(void* p);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

int  main (void)
{
    OSInit();                                                   /* Init uC/OS-II.                                       */

	OSTaskCreateExt((void(*)(void *))task1,
		(void          *)0,
		(OS_STK		   *)&TASK1STK[TASK_STACK_SIZE - 1],
		(INT8U          )TASK1_PRIORITY,
		(INT16U         )TASK1_ID,
		(OS_STK        *)&TASK1STK[0],
		(INT32U         )TASK_STACK_SIZE,
		(void          *)&edf_datas[0],
		(INT16U         )0);

	OSTaskCreateExt((void(*)(void *))task2,
		(void          *)0,
		(OS_STK		   *)&TASK2STK[TASK_STACK_SIZE - 1],
		(INT8U          )TASK2_PRIORITY,
		(INT16U         )TASK2_ID,
		(OS_STK        *)&TASK2STK[0],
		(INT32U         )TASK_STACK_SIZE,
		(void          *)&edf_datas[1],
		(INT16U         )0);

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg       is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    OS_ERR  err;


   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();                                                 /* Initialize uC/CPU services                           */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

    APP_TRACE_DBG(("uCOS-II is Running...\n\r"));

    while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */
        OSTimeDlyHMSM(0, 0, 1, 0);

        APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet(&err)));
    }
}

/*================================================================
my tasks
*/
static void task1(void* p) {
	OSTimeDly(1);
	for (;;) {
		while (((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->remain_time>0) {
			//do nothing
		}
	}
}
static void task2(void* p) {
	OSTimeDly(1);
	for (;;) {
		while (((EDF_DATA*)OSTCBCur->OSTCBExtPtr)->remain_time>0) {
			//do nothing
		}
	}
}
