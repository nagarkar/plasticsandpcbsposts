/*
 * application.h
 *
 *  Created on: Apr 24, 2017
 *      Author: chinm_000
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#define LESS(a_, b_) (((a_) < (b_)) ? (a_) : (b_))
#define COUNTOF(v)  (sizeof(v)/sizeof(v[0]))

void App_Init(void);
void App_Printf(char const *format, ...);



#endif /* APPLICATION_H_ */
