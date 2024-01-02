#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "basic.h"

int main(void)
{
	str world = str_from_cstr("World!");
	str hello = str_from_cstr("Hello,");
	println(hello, world);

	str ap = str_append(hello, world);
	println(ap);

	str* v = str_split(ap, ',');
	foreach (str, v) {
		print(*it);
	}
	putcstr("");

	str join = str_join(str_from_cstr(","), v[0], v[1]);
	println(join);

	str build = str_new_from_file("build.c");
	//println(build);

	str_delete(build);
	str_delete(join);
	str_delete(ap);
	vec_delete(v);
	return 0;
}
