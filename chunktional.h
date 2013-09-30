#ifndef CHUNKTIONAL_H
#define CHUNKTIONAL_H

#include <stdarg.h>

#define datatype(dataname, ...) enum dataname { ## __VA_ARGS__ };
#define datatypedefine(dataname, option) struct option { dataname type;
#define datatypeend }

#define mkdatatype(option, ...) ((struct option) {option, ## __VA_ARGS__})
#define allocdatatype(option) ((struct option *)calloc(1, sizeof(struct option)))
#define assigndatatype(value, option, ...) value = mkdatatype(option, ## __VA_ARGS__)

#define match(value) switch(value.type)
#define case(value, option, result) case option: { struct option result = (struct option)value;
#define caseend } break

#endif