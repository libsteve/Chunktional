// Chunktional.h
// Steven Brunwasser, altece.com
// A collection of C Macros for making functional-style programming more intuitive in C.

#ifndef CHUNKTIONAL_H
#define CHUNKTIONAL_H

#include <stdlib.h>
#include <stdarg.h>


////
// datatype declarations

// define a datatype and all it's concrete types
#define datatype(dataname, ...) enum dataname { __VA_ARGS__ }; typedef struct { enum dataname type; } dataname;

// define the structure for a concrete type of a datatype
// will create "private" allocation and initialization static inline functions for the concrete type
#define datatypedefine(dataname, option, structure) struct option { enum dataname type; struct structure; }; \
	static inline dataname *mk ## option () { \
		void *v = allocdatatype(option); \
		((struct option *)v)->type = option; \
		return v; \
	} \
	static inline dataname *init ## option (dataname *value, struct option raw) { \
		*((struct option *)value) = raw; \
		return value; \
	}

// define a concrete type of a datatype as being an atom
#define datatypeatom(dataname, option) datatypedefine(dataname, option, {})


////
// datatype creation and initialization

// allocate the raw space for the concrete type
#define allocdatatype(option) ((void *)calloc(1, sizeof(struct option)))

// "private" stack constructor for the concrete type
#define __mkdatatype(option, ...) ((struct option) {option, {__VA_ARGS__}})

// allocate and initialize a new instance of the concrete type
#define mkdatatype(option, ...) init ## option (mk ## option (), __mkdatatype(option, ## __VA_ARGS__))


////
// caseof statement

// open a new caseof statement for a given datatype instance
#define caseof(value) { void *___VALUE___ = value; switch((int)value->type) { case -99: {

// close a caseof statement
#define endcaseof ;} break; }}

// define a case for an instance of the specified concrete type assigned to the given value symbol
#define where(option, result) ;} break; case option: { struct option *result = (struct option *)___VALUE___;

// define a case for an atom instance of the specified concrete type
#define whereatom(option) ;} break; case option: {

// define a default case for the caseof statement
#define otherwise ;} break; default: {


////
// closures

// define a closure of the given type, for the given symbol name, 
// whose closure would follow the given structure, and that takes the given parameters
#define closure(type, fn, context, ...) struct _ ## fn ## _context context; type fn (struct _ ## fn ## _context closure, ## __VA_ARGS__)

// call a closure function with the given context structure and parameters
#define call(fn, context, ...) fn((struct _ ## fn ## _context)context, ## __VA_ARGS__)

#endif