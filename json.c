#include "json.h"
#include <stdio.h>
#include <ctype.h>

typedef enum jtok_type_e jtok_type_e;

enum jtok_type_e {
	JTOK_STRING,
	JTOK_NUM,
	JTOK_TRUE,
	JTOK_FALSE,
	JTOK_NULL,
	JTOK_LBRACE,
	JTOK_RBRACE,
	JTOK_LBRACKET,
	JTOK_RBRACKET,
	JTOK_COMMA,
	JTOK_COLON,
	JTOK_EOF
};

typedef struct jtok_s jtok_s;

struct jtok_s {
	jtok_type_e type;
	char *lex;
	size_t len;
};

static int lex(jtok_s *t, char **ptr);
static void jtok_make(jtok_s *t, char *lex, size_t len, jtok_type_e type);

static jnode_s *jparse_value(char **ptr);
static jnode_s *jparse_object(char **ptr);
static jnode_s *jparse_array(char **ptr);
static jnode_s *jparse_string(jtok_s *str);
static jnode_s *jparse_number(jtok_s *num);
static jnode_s *jparse_true(jtok_s *tval);
static jnode_s *jparse_false(jtok_s *fval);
static jnode_s *jparse_null(jtok_s *null);

jnode_s *jnode_parse(char *src) {
	char **ptr = &src;
	return jparse_value(ptr);
}

int lex(jtok_s *t, char **src) {
	char *fptr = *src, *bptr;	

	while(*fptr) {
		switch(*fptr) {
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				fptr++;
				break;
			case '{':
				*src = fptr + 1;	
				jtok_make(t, fptr, 1, JTOK_LBRACE);
				return 0;
			case '}':
				*src = fptr + 1;
				jtok_make(t, fptr, 1, JTOK_RBRACE);
				return 0;
			case '[':
				*src = fptr + 1;
				jtok_make(t, fptr, 1, JTOK_LBRACKET);
				return 0;
			case ']':
				*src = fptr + 1;
				jtok_make(t, fptr, 1, JTOK_RBRACKET);
				return 0;
			case ',':
				*src = fptr + 1;
				jtok_make(t, fptr, 1, JTOK_COMMA);
				return 0;
			case ':':
				*src = fptr + 1;
				jtok_make(t, fptr, 1, JTOK_COLON);
				return 0;
			default:
				if(isdigit(*fptr) || *fptr == '-' || *fptr == '+') {
					if(!isdigit(*(fptr + 1)) && *fptr == '-' || *fptr == '+') {
						return -1;
					}
					bptr = fptr;
					do {
						fptr++;
					} while(isdigit(*fptr));
					if(*fptr == '.') {
						fptr++; 	
					}
					if(*fptr == 'e' || *fptr == 'E') {
						fptr++;
						if(*fptr == '+' || *fptr == '-') {
							fptr++;
						}
						else {
							return -1;
						}
						if(isdigit(*fptr)) {
							do {
								fptr++;
							} while(isdigit(*fptr));
						}
					}
					jtok_make(t, bptr, fptr-bptr, JTOK_NUM);
				}
				break;
		}
	}
}

jnode_s *jparse_value(char **ptr) {
	jtok_s t;
	jnode_s *n;

	lex(&t, ptr);
	switch(t.type) {
		case JTOK_LBRACE:
			n = jparse_object(ptr);
			break;
		case JTOK_LBRACKET:
			n = jparse_array(ptr);
			break;
		case JTOK_STRING:
			n = jparse_string(&t);	
			break;
	}
	return n;
}

jnode_s *jparse_object(char **ptr) {
	jtok_s t;
	jtok_s *key;
	jnode_s *node;

	lex(&t, ptr);
	if(t.type == JTOK_STRING) {
		//key = t;
		lex(&t, ptr);
		if(t.type == JTOK_COLON) {
			node = jparse_value(ptr);
		}
	}
	else {
		return NULL;
	}
	return node;
}

jnode_s *jparse_array(char **ptr) {
}

jnode_s *jparse_string(jtok_s *ptr) {
	
}

jnode_s *jparse_number(jtok_s *num) {
}

jnode_s *jparse_true(jtok_s *tval) {
}

jnode_s *jparse_false(jtok_s *fval) {
}

jnode_s *jparse_null(jtok_s *null) {
}

void jtok_make(jtok_s *t, char *lex, size_t len, jtok_type_e type) {	
	t->type = type;
	t->len = len;
	t->lex = lex;
}

