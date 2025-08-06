#ifndef APPLICATIONTASK_CORE1_H
#define APPLICATIONTASK_CORE1_H

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
#define APPLICATIONTASK_CORE1_SUCCESS 0
#define APPLICATIONTASK_CORE1_ERROR   (-1)

/******************************************************************************/
/*                             DATA TYPES                                     */
/******************************************************************************/

/******************************************************************************/
/*                             GLOBAL FUNCTION DECLARATIONS                   */
/******************************************************************************/
int ApplicationTask_Core1_Init(void);
int ApplicationTask_Core1_Start(void);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATIONTASK_CORE1_H */
