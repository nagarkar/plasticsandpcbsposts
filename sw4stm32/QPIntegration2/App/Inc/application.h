/*
 * application.h
 *
 *  Created on: Apr 24, 2017
 *      Author: chinm_000
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

// POINT OF NOTE on the '_cplusplus' syntax below: https://goo.gl/azTck5, https://goo.gl/0cdm8
#ifdef __cplusplus
extern "C" {
#endif

void App_Init(void);
void App_InitComplete(void);
void App_Printf(char const *format, ...);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class Application {
public:
	static void Init(void);
	static void InitComplete(void);
};
#endif

#endif /* APPLICATION_H_ */
