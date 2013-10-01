#ifndef CHUNKTIONAL_H
#define CHUNKTIONAL_H

#include <stdlib.h>
#include <stdarg.h>

#define datatype(dataname, ...) enum dataname { __VA_ARGS__ }; typedef struct { enum dataname type; } dataname;
#define datatypedefine(dataname, option, information) struct option { enum dataname type; struct information; }; \
	static inline dataname *mk ## option () { \
		void *v = allocdatatype(option); \
		((struct option *)v)->type = option; \
		return v; \
	} \
	static inline dataname *init ## option (dataname *value, struct option raw) { \
		*((struct option *)value) = raw; \
		return value; \
	}
#define datatypeempty(dataname, option) datatypedefine(dataname, option, {})

#define allocdatatype(option) ((void *)calloc(1, sizeof(struct option)))
#define __mkdatatype(option, ...) ((struct option) {option, {__VA_ARGS__}})
#define mkdatatype(option, ...) init ## option (mk ## option (), __mkdatatype(option, ## __VA_ARGS__))

#define caseof(value) { void *___VALUE___ = value; switch(value->type) {
#define endcaseof }}
#define where(option, result) case option: { struct option *result = (struct option *)___VALUE___;
#define whereis(option) case option: {
#define endwhere ;} break

#endif