#ifndef APPLICATIONTASK_CORE0_H
#define APPLICATIONTASK_CORE0_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                             INCLUDES                                       */
/******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
/*                             MACROS & CONSTANTS                             */
/******************************************************************************/
#define APPLICATIONTASK_CORE0_SUCCESS 0
#define APPLICATIONTASK_CORE0_ERROR   (-1)

/******************************************************************************/
/*                             DATA TYPES                                     */
/******************************************************************************/

/******************************************************************************/
/*                             GLOBAL FUNCTION DECLARATIONS                   */
/******************************************************************************/
int ApplicationTask_Core0_Init(void);
int ApplicationTask_Core0_Start(void);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATIONTASK_CORE0_H */
