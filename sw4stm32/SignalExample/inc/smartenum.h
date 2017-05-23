/*
 * smartenum.h
 *
 *  Created on: May 22, 2017
 *      Author: chinm_000
 */

#ifndef SMARTENUM_H_
#define SMARTENUM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "string.h"

#define SMARTENUM_VALUE(typeName, value) value,
#define SMARTENUM_STRING(typeName, value) #value,

#define SMARTENUM_DEFINE_ENUM(typeName, values) enum typeName { values(SMARTENUM_VALUE) e##typeName##_Count, };

#define SMARTENUM_DECLARE_NAMES(typeName, values) extern const char* typeName##Array [e##typeName##_Count];

#define SMARTENUM_DEFINE_NAMES(typeName, values) const char* typeName##Array [e##typeName##_Count] = { values(SMARTENUM_STRING) };

//#define SMARTENUM_DEFINE_NAMES(typeName, values) const char* typeName##Array [] = { values(SMARTENUM_STRING) };
#define SMARTENUM_DECLARE_GET_VALUE_FROM_STRING(typeName, name)	typeName get##typeName##FromString(const char* str);

#define SMARTENUM_DEFINE_GET_VALUE_FROM_STRING(typeName, name)	\
	typeName get##typeName##FromString(const char* str) 					\
	{				                      																\
		for (int i = 0; i < e##typeName##_Count; ++i)       				\
		if (!strcmp(typeName##Array[i], str))											\
			return (typeName)i;																		\
		return e##typeName##_Count;																	\
	}

#define getStringFromEnumValue(typeName, value) typeName##Array[##value]
#define getEnumValueFromString(typeName, name)	get##typeName##FromString(##name)


#ifdef __cplusplus
}
#endif

#endif /* SMARTENUM_H_ */
