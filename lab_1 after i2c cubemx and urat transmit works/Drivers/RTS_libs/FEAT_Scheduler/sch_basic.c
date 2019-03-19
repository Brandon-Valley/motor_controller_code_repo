//#include "defs/esnl_pub.h"

//#ifdef _ENABLE_SCH_BASIC_

#include "sch_basic_prv.h"
#include "sch_basic_pub.h"
//#include "../.."





/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */








#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tasks_lab_1.h"
#include "../Drivers/RTS_libs/FEAT_Scheduler/sch_basic_pub.h"



long int DIFF = 0;


//
//static void MX_GPIO_Init(void)
//{
//	  GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//	  /* GPIO Ports Clock Enable */
//	  __HAL_RCC_GPIOC_CLK_ENABLE();
//	  __HAL_RCC_GPIOH_CLK_ENABLE();
//	  __HAL_RCC_GPIOA_CLK_ENABLE();
//	  __HAL_RCC_GPIOB_CLK_ENABLE();
//
//	  /*Configure GPIO pin Output Level */
//	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LD2_Pin, GPIO_PIN_RESET);
//
//	  /*Configure GPIO pin : B1_Pin */
//	  GPIO_InitStruct.Pin = B1_Pin;
//	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//	  GPIO_InitStruct.Pull = GPIO_NOPULL;
//	  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
//
//	  /*Configure GPIO pins : PA0 LD2_Pin */
//	  GPIO_InitStruct.Pin = GPIO_PIN_0|LD2_Pin;
//	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	  GPIO_InitStruct.Pull = GPIO_NOPULL;
//	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//}





//#include "API_frames.h"
//#include "tsp_common_pub.h"
//#include "Application.h"

//#include "sys_func.h"


//#define _SCH_DEBUG_ENABLE_
#undef _SCH_DEBUG_ENABLE_
#define _SCH_DEBUG_LEVEL_	0
//
//static void MX_GPIO_Init(void)
//{
//	  GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//	  /* GPIO Ports Clock Enable */
//	  __HAL_RCC_GPIOC_CLK_ENABLE();
//	  __HAL_RCC_GPIOH_CLK_ENABLE();
//	  __HAL_RCC_GPIOA_CLK_ENABLE();
//	  __HAL_RCC_GPIOB_CLK_ENABLE();
//
//	  /*Configure GPIO pin Output Level */
//	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LD2_Pin, GPIO_PIN_RESET);
//
//	  /*Configure GPIO pin : B1_Pin */
//	  GPIO_InitStruct.Pin = B1_Pin;
//	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//	  GPIO_InitStruct.Pull = GPIO_NOPULL;
//	  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
//
//	  /*Configure GPIO pins : PA0 LD2_Pin */
//	  GPIO_InitStruct.Pin = GPIO_PIN_0|LD2_Pin;
//	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	  GPIO_InitStruct.Pull = GPIO_NOPULL;
//	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//}


/****************************************************************************
**	Constants, definies and typedefs  (PUBLIC)
****************************************************************************/

/****************************************************************************
**	Variables definition (PRIVATE)
****************************************************************************/

//extern uint8_t		truck_state_test;
rtc_tick_t		sch_timeout_ticks[MAX_TIMEOUTS];
uint8_t			sch_timeout_state[MAX_TIMEOUTS];
list_size_t		sch_timeout_count;

list_index_t		sch_timeout_order[MAX_TIMEOUTS];
list_index_t		sch_tout_head;
list_index_t		sch_tout_free;
sch_cb_func_t		sch_callback_funcs[MAX_TIMEOUTS];
uint8_t			 *	sch_callback_context[MAX_TIMEOUTS];
char *	sch_callback_name[MAX_TIMEOUTS];

//sch_loop_func_t	xdata	sch_loop_funcs[MAX_LOOPS];
sch_loop_func_t sch_loop_funcs[MAX_LOOPS];
uint8_t sch_loop_funcs_on[MAX_LOOPS];

/****************************************************************************
**	Variables definition (PUBLIC)
****************************************************************************/

void sch_default_callback( uint8_t tid)
{
	//Do default handling HERE
}

/****************************************************************************
**	Functions implementation (PUBLIC)
****************************************************************************/

#define SCH_FUNC_OFF	0
#define SCH_FUNC_ON		1

char str_NONE[] = "NONE";

/**
  * sch_power_up () - power up (tasks/system) SCHEDULING module
  */
void sch_power_up ( void )
{
	uint8_t i;
	//sch_timeout_ticks[MAX_TIMEOUTS];
	for(i=0; i< MAX_TIMEOUTS; i++)
	{
		sch_timeout_state[i] = SCH_STATE_IDLE;
		sch_timeout_order[i] = (i+1)%MAX_TIMEOUTS;
		sch_callback_funcs[i] = (sch_cb_func_t)NULL; //sch_default_callback;
		sch_callback_name[i] = str_NONE;
	}
	sch_timeout_order[MAX_TIMEOUTS - 1] = SCH_NO_TIMEOUT_ID; // last points to nothing
	sch_timeout_count = MAX_TIMEOUTS; // initially all empty
	sch_tout_head = SCH_NO_TIMEOUT_ID; // empty
	sch_tout_free = 0; // first empty ID



	for(i=0; i< MAX_LOOPS; i++)
	{
		sch_loop_funcs[i] = SCH_NO_FUNC_ID;
		sch_loop_funcs_on[i] = SCH_FUNC_OFF;
	}
	sch_timeout_count = 0; // empty

}

/**
  * sch_init () - sets up (tasks/system) SCHEDULING module
  */
void sch_init ( void )
{
	// Any initializations - e.g. periodic scheduler job/task

}



/**
* sch_test() - tests SCHEDULING operation (e.g. RTC correctness)
*/
uint8_t sch_test()
{
	return 0;
}

uint8_t current_loop_idx;
uint8_t timeout_idx;
/**
  * sch_loop() - executes main loop block (BUT DOES NOT LOOP ITSELF!!!)
  */
void sch_loop( void )
{
	unsigned int test_num = 2;
//	MX_GPIO_Init();

	//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LD2_Pin, GPIO_PIN_SET);
	for(current_loop_idx=0; current_loop_idx< MAX_LOOPS; current_loop_idx++)
	{
		if (sch_loop_funcs_on[current_loop_idx] == SCH_FUNC_ON)
		{
			//set pin high befor func. runs
			if (current_loop_idx == test_num)
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LD2_Pin, GPIO_PIN_SET);

			(sch_loop_funcs[current_loop_idx])();

			//set pin low after func. done running
			if (current_loop_idx == test_num)
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LD2_Pin, GPIO_PIN_RESET);
		}
	}
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LD2_Pin, GPIO_PIN_RESET);
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	while ( (SCH_NO_TIMEOUT_ID != sch_tout_head )
		&& (sch_timeout_ticks[sch_tout_head ] < rtc_get_ticks()) )
	{
		//TESTING FOR DIFFERENCE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		DIFF =  sch_timeout_ticks[sch_tout_head ] - rtc_get_ticks();


		// Remove from head for the purpose of consistency
		ATOMIC(
			   	timeout_idx = sch_tout_head ;
				sch_tout_head  = sch_timeout_order[sch_tout_head ];
				sch_timeout_order[timeout_idx] = 0xEE;//sch_tout_free;
				sch_timeout_count--;
				)
		// Execute
		(sch_callback_funcs[timeout_idx ])(sch_callback_context[timeout_idx] );
		// Free the Timer slot for others to use
		sch_timeout_state[timeout_idx] = SCH_STATE_IDLE;
	}
}


void sch_remove_timeout(uint8_t tidx, char*name)
{
	uint8_t temp = sch_tout_head;
	if (SCH_NO_TIMEOUT_ID == temp) {printf("ERROR DELETING TO 255\n"); return;} // not found anything (maybe JUST executed)
	printf("SCH_TO_DEL= %d,%s (r=%s)\n", temp, sch_callback_name[temp], name);
	//print_timeouts();
	if (  sch_callback_name[tidx] != name ) 
	{
		printf("ERROR DELETING wrong name %d,%s (req=%s)\n", temp, sch_callback_name[temp], name); 
		return; // wrong removal
	}
	sch_timeout_count--;
	if (tidx == temp) // TIDX is the HEAD
	{
		sch_tout_head = sch_timeout_order[tidx]; // remove timeout from ORDERED list
		sch_timeout_order[tidx] = 0xEE;//sch_tout_free;
		sch_timeout_state[tidx] = SCH_STATE_IDLE; // free timeout record
		return;
	}
	// Find the previous item in the list to skip/remove the TIDX
	while (SCH_NO_TIMEOUT_ID != sch_timeout_order[temp])
	{
		if ( tidx == sch_timeout_order[temp])
		{
		// Remove from the list
			//		ATOMIC(
			   	sch_timeout_order[temp] = sch_timeout_order[tidx]; // skip the TIDX
				sch_timeout_order[tidx] = 0xEE;//sch_tout_free;
				sch_timeout_state[tidx] = SCH_STATE_IDLE; // free timeout record
//				)
				return;
		}
		temp = sch_timeout_order[temp]; // go to next
	}
	// NOT FOUND
	sch_timeout_count++; // revert to original count
}

/**
  * sch_correct_time_shift (offset) - updates schedule timeouts to accomodate
  *		for the RTC shift due to clock (re-)synchronization (e.g. from BEAM pkt)
  */
void sch_correct_time_shift ( int32_t offset)
{
	// TODO: handle case when the RTC has been set to a new value (large change)
	// 		this will require shift in all timeouts
}

/**
  * sch_create_timeout (timeout, callback_func) - sets a new timeout at "timoeut"
  *		RTC ticks (absolute value). When timeout expires, the "callback_func" is
  *		executed (function has to be REENTRANT and accept timeout ID as param)
  *	RETURNS: timeout ID or "SCH_NO_TIMEOUT_ID" if unsuccesful
  */
uint8_t sch_create_timeout( rtc_tick_t timeout, sch_cb_func_t callback_func, uint8_t* t_context, char*name)
{
	list_index_t tidx;
	list_index_t order_idx = sch_tout_head;
	// TODO: find a free timeout ID
	tidx = get_free_timeout();
// DEBUG
	printf("SCH_TO_SET= %d,%s #\n", tidx, name);
	if (SCH_NO_TIMEOUT_ID == tidx)
	{
		return SCH_NO_TIMEOUT_ID;
	}
	//		then, set the timeout
	sch_timeout_count++;
	sch_timeout_ticks[tidx] = timeout;
	sch_timeout_state[tidx] = SCH_STATE_PENDING;
	sch_callback_funcs[tidx] = callback_func;
	sch_callback_context[tidx] = t_context;
	sch_callback_name[tidx] = name;

	//		then, insert into the timeouts' list
	if ((SCH_NO_TIMEOUT_ID == sch_tout_head) || (timeout < sch_timeout_ticks[sch_tout_head]))
	{
		sch_timeout_order[tidx] = sch_tout_head; // put as first
		sch_tout_head = tidx;
	}
	else
	{
		// Until the current item is last (next is empty)
		//		OR until next item in the list is later than the new timeout
		while ((SCH_NO_TIMEOUT_ID != sch_timeout_order[order_idx])
			   && (timeout > sch_timeout_ticks[sch_timeout_order[order_idx]]))
		{
			order_idx = sch_timeout_order[order_idx];
		}
		sch_timeout_order[tidx] = sch_timeout_order[order_idx]; // inherit the next in list
		sch_timeout_order[order_idx] = tidx; // connect to the previous item (earlier event)
		
	}
	return tidx;
}




/**
  * sch_add_loop( sch_loop_func_t loop_func) - sets a new loop function to
  *		be executed every time in the main loop
  *	RETURNS: loop function ID or "SCH_NO_FUNC_ID" if unsuccesful
  */
uint8_t sch_add_loop( sch_loop_func_t loop_func)
{
	uint8_t i = SCH_NO_TIMEOUT_ID;
	for( i= 0; i < MAX_LOOPS; i++)
	{
		if (sch_loop_funcs_on[i] == SCH_FUNC_OFF)
		{
			break;
		}
	}
	if (MAX_LOOPS > i)
	{
		sch_loop_funcs[i] = loop_func;
		sch_loop_funcs_on[i] = SCH_FUNC_ON;
		return i;
	}
	// else not found free space
	return 	SCH_NO_TIMEOUT_ID;
}

/****************************************************************************
**	Functions implementation (PRIVATE)
****************************************************************************/


/**
*  sch_init_timeout_list () - (re)sets the timeout list
*/
void sch_init_timeout_list()
{

}

/**
*  get_free_timeout () - finds free slot in timeout tables,
*       RETURN: "index", or SCH_NO_TIMEOUT_ID if no space left
*		NOTE: Sets state of timer to SCH_STATE_BUSY
*/
list_index_t get_free_timeout()
{
	list_index_t i;
	for(i=0; i < MAX_TIMEOUTS; i++)
	{
		if ( SCH_STATE_IDLE == sch_timeout_state[i] )
		{
			sch_timeout_state[i]= SCH_STATE_BUSY;
			return i;
		}
	}
	printf("NO TIMEOUTS LEFT = %d\n", sch_timeout_count);
	return SCH_NO_TIMEOUT_ID;
}

/**
*  print_timeouts () - prints state of the timeout table,
*       uses STDOUT (mostly serial interface UART)
*/
void print_timeouts()
{
	list_index_t i;
	for(i=0; i < MAX_TIMEOUTS-20; i++)
	{
		printf(" %d/%d,/%s\n" 
			   , sch_timeout_state[i]
				   , sch_timeout_order[i]
				   , sch_callback_name[i]);
	}	
}

// ############################################################################
// ############################################################################




// ############################################################################
// ############################################################################
// Spacers
// ############################################################################
// ############################################################################



