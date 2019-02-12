#ifndef __json_h__
#define __json_h__

#include "general.h"

typedef enum jnode_type_e jnode_type_e;

enum jnode_type_e {
	JNODE_VAL,
	JNODE_ARRAY,
	JNODE_OBJECT,
	JNODE_STRING,
	JNODE_NUMBER,
	JNODE_TRUE,
	JNODE_FALSE,
	JNODE_NULL
};

typedef struct jnode_s jnode_s;
typedef struct jobject_s jobject_s;
typedef struct jarray_s jarray_s;
typedef struct jstring_s jstring_s;
typedef struct jtrue_s jtrue_s;
typedef struct jfalse_s jfalse_s;
typedef struct jnull_s jnull_s;

struct jnode_s {
	jnode_type_e type;
};

struct jobject_s {
	jnode_s base;
	map_s table;
};

struct jarray_s {
	jnode_s base;
	jnode_s *children[];
};

struct jstring_s {	
	jnode_s base;
	char data[];
};

struct jtrue_s {
	jnode_s base;
};

struct jfalse_s {
	jnode_s base;
};

struct jnull_s {
	jnode_s base;
};

extern jnode_s *jnode_parse(char *src);

#endif

