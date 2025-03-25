// SPDX-FileCopyrightText: 2025 Oswald Buddenhagen <ossi@users.sf.net>
// SPDX-License-Identifier: GPL-2.0-or-later
//
// isync test suite
//

#include "common.h"

static void
test( const char *name, const char *out, const char *fmt, ... )
{
	va_list va;

	printf( "Test %s ...\n", name );
	va_start( va, fmt );
	char *rslt = xvasprintf( fmt, va );
	va_end( va );
	if (strcmp( rslt, out )) {
		printf( "Mismatch, got \"%s\", want \"%s\"\n", rslt, out );
		exit( 1 );
	}
}

int
main( void )
{
	test( "empty", "", "" );
	test( "plain", "string", "string" );
	test( "char", "c", "%c", 'c' );
	test( "string", "string", "%s", "string" );
	test( "cut string", "str", "%.*s", 3, "string" );
	test( "uncut string", "string", "%.*s", 10, "string" );
	test( "double-quoted string", "foo \\\"\\\\\x1b\t\a\b\v\f\r\n bar",
	      "%\\s", "foo \"\\\x1b\t\a\b\v\f\r\n bar" );
	test( "cut double-quoted string", "quote \\\" back", "%.*\\s", 12, "quote \" backslash" );
	test( "uncut double-quoted string", "quote \\\" backslash", "%.*\\s", 20, "quote \" backslash" );
	test( "double-quoted w/ escapes", "foo \\\"\\\\\\x1b\\t\\a\\b\\v\\f\\r\\n",
	      "%!s", "foo \"\\\x1b\t\a\b\v\f\r\n" );
	test( "double-quoted w/ escapes & linebreak", "foo \\\"\\\\\\x1b\\t\\a\\b\\v\\f\\r\\n\n",
	      "%!&s", "foo \"\\\x1b\t\a\b\v\f\r\n" );
	test( "unsigned", "4123567890", "%u", 4123567890U );
	test( "positive signed", "13", "%d", 13 );
	test( "negative signed", "-17", "%d", -17 );
	test( "mixed format", "hello world 123 once more", "hello %s %u%smore", "world", 123, " once " );

	return 0;
}
