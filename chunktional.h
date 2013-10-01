#ifndef CHUNKTIONAL_H
#define CHUNKTIONAL_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

struct datatype_struct {
	int type;
	bool onHeap;
};

#define datatype(dataname, ...) enum dataname { __VA_ARGS__ }; typedef struct { enum dataname type; bool onHeap; } dataname;
#define datatypedefine(dataname, option, structure) struct option { enum dataname type; bool onHeap; struct structure; }; \
	static inline dataname *mk ## option () { \
		void *v = allocdatatype(option); \
		((struct option *)v)->type = option; \
		((struct option *)v)->onHeap = true; \
		return v; \
	} \
	static inline dataname *init ## option (dataname *value, struct option *raw) { \
		*((struct option *)value) = *raw; \
		((struct option *)value)->onHeap = true; \
		return value; \
	}
#define datatypeempty(dataname, option) datatypedefine(dataname, option, {})

#define allocdatatype(option) ((void *)calloc(1, sizeof(struct option)))
#define __mkdatatype(option, ...) (&((struct option) {option, false, {__VA_ARGS__}}))
#define mkdatatype(option, ...) init ## option (mk ## option (), __mkdatatype(option, ## __VA_ARGS__))
#define freedata(value) if (((struct datatype_struct *)value)->onHeap) free(value)

#define caseof(value) { void *___VALUE___ = value; switch((int)value->type) { case -99: {
#define endcaseof ;} break; }}
#define where(option, result) ;} break; case option: { struct option *result = (struct option *)___VALUE___;
#define whereatom(option) ;} break; case option: {
#define otherwise ;} break; default: {

#endif