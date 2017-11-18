/* libpex - C library for reading and writing compiled Papyrus scripts (PEX files)
 * Copyright (c) 2017 Oskar Sveinsen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * #include <stdint.h>
 * #include <stdio.h>
 */

typedef struct Pex_string {
	uint16_t len;
	char	*c; /* null-terminated */
} Pex_string;

typedef struct Pex_debug_func {
	Pex_string	*object;
	Pex_string	*state;
	Pex_string	*name;
	uint8_t	type; /* TODO */
	uint16_t	linec;
	uint16_t	*linev;
} Pex_debug_func;

typedef struct Pex_debug_group {
	Pex_string	*object;
	Pex_string	*name;
	Pex_string	*docstring;
	uint32_t	userflags;
	uint16_t	propc;
	Pex_string	**propv;
} Pex_debug_group;

typedef struct Pex_debug_struct {
	Pex_string	*object;
	Pex_string	*name;
	uint16_t	memberc;
	Pex_string	**memberv;
} Pex_debug_struct;

typedef struct Pex_debug {
	uint64_t	modifytime;
	uint16_t	funcc;
	Pex_debug_func	*funcv;
	uint16_t	groupc;
	Pex_debug_group	*groupv;
	uint16_t	structc;
	Pex_debug_struct	*structv;
} Pex_debug;

typedef struct Pex_userflag {
	Pex_string	*name;
	uint8_t	id;
} Pex_userflag;

typedef struct Pex_object_var {
	Pex_string	*name;
	Pex_string	*type;
} Pex_object_var;

typedef struct Pex_object_value {
	uint8_t type; /* TODO */
	union {
		Pex_string	*s;
		int32_t	n;
	}	value;
} Pex_object_value;

typedef struct Pex_object_var_global {
	Pex_object_var	var;
	uint32_t	userflags;
	Pex_object_value	initialvalue;
	uint8_t	flags;
} Pex_object_var_global;

typedef struct Pex_object_struct_member {
	Pex_object_var_global	var;
	Pex_string	*docstring;
} Pex_object_struct_member;

typedef struct Pex_object_struct {
	Pex_string	*name;
	uint16_t	memberc;
	Pex_object_struct_member	*memberv;
} Pex_object_struct;

typedef struct Pex_object_func_code {
	uint8_t op;
	uint16_t	argc;
	Pex_object_value	*argv;
} Pex_object_func_code;

typedef struct Pex_object_func {
	Pex_string	*returntype;
	Pex_string	*docstring;
	uint32_t	userflags;
	uint8_t	flags;
	uint16_t	paramc;
	Pex_object_var	*paramv;
	uint16_t	localc;
	Pex_object_var	*localv;
	uint16_t	codec;
	Pex_object_func_code	*codev;
} Pex_object_func;

typedef struct Pex_object_prop {
	Pex_object_var	var;
	Pex_string	*docstring;
	uint32_t	userflags;
	uint8_t	flags;
	Pex_string	*autovar;
	Pex_object_func	*getter;
	Pex_object_func	*setter;
} Pex_object_prop;

typedef struct Pex_object_state_func {
	Pex_string	*name;
	Pex_object_func	func;
} Pex_object_state_func;

typedef struct Pex_object_state {
	Pex_string	*name;
	uint16_t	funcc;
	Pex_object_state_func	*funcv;
} Pex_object_state;

typedef struct Pex_object {
	Pex_string	*name;
	Pex_string	*parent;
	Pex_string	*docstring;
	uint8_t	flags;
	uint32_t	userflags;
	Pex_string	*autostate;
	uint16_t	structc;
	Pex_object_struct *structv;
	uint16_t	varc;
	Pex_object_var	*varv;
	uint16_t	propc;
	Pex_object_prop	*propv;
	uint16_t	statec;
	Pex_object_state	*statev;
} Pex_object;

typedef struct Pex {
	uint8_t	version_major;
	uint8_t	version_minor;
	uint16_t	game;
	uint64_t	compiletime;
	uint16_t	stringc;
	Pex_string	*stringv;
	uint16_t	debugc;
	Pex_debug	*debugv;
	uint16_t	userflagc;
	Pex_userflag	*userflagv;
	uint16_t	objectc;
	Pex_object	*objectv;
} Pex;

int pex_read(Pex *, FILE *);
int pex_write(Pex *, FILE *);
int pex_free(Pex *); /* does not free the root Pex object */
