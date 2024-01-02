// TODO: fix magic numbers
// TODO: standard code style
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "src/basic.h"

#define CFLAGS "-std=c99", "-Wall", "-Wextra", "-Wshadow", "-pedantic", "-D_DEFAULT_SOURCE", "-Isrc"
#define LDFLAGS "-lm"

char* cflags[] = { CFLAGS, NULL };
char* ldflags[] = { LDFLAGS, NULL };

typedef struct {
	char* bin;
	char** deps;
} prog;

int main(int argc, char* argv[])
{
	char* type = argc > 1 ? argv[1] : "self";

	char* srcs[] = { "tui", "mesh", "canvas", "audio", "basic", NULL };

	prog examples[] = {
		{ "snake", (char*[]){ "tui.o", NULL } },
		{ "mines", (char*[]){ "tui.o", NULL } },
		{ "sort", (char*[]){ "tui.o", NULL } },
		{ "wave", (char*[]){ "audio.o", NULL } },
		{ "shapes", (char*[]){ "mesh.o", "canvas.o", "tui.o", NULL } },
		{ "basics", (char*[]){ "basic.o", NULL } },
	};

	if (strcmp(type, "self") == 0) {
		printf("Recompiling build.c...\n");
		cmd_run("cc", CFLAGS, "build.c", "src/basic.c", "-o", "build");

		cmd_run_file("build", "all");
	} else if (strcmp(type, "all") == 0) {
		for (char** src = srcs; *src; ++src) {
			char file[16] = "src/";
			strcat(file, *src);
			strcat(file, ".c");

			printf("Compiling %s...\n", file);
			cmd_run("cc", CFLAGS, "-c", file);
		}

		for (size_t i = 0; i < sizeof(examples) / sizeof(examples[0]); ++i) {
			prog ex = examples[i];
			char src[32] = "examples/";
			strcat(src, ex.bin);
			strcat(src, ".c");

			printf("Compiling %s...\n", src);
			cmd_run("cc", CFLAGS, "-c", src);

			char obj[32] = {0};
			strcpy(obj, ex.bin);
			strcat(obj, ".o");

			char** cmd = vec_new(char*, 32);

			vec_append(cmd, "cc");

			for (char** flag = cflags; *flag; ++flag)
				vec_append(cmd, *flag);

			for (char** dep = ex.deps; *dep; ++dep)
				vec_append(cmd, *dep);

			vec_append(cmd, obj);
			vec_append(cmd, "-o");
			vec_append(cmd, ex.bin);

			for (char** f = ldflags; *f; ++f)
				vec_append(cmd, *f);

			vec_append(cmd, NULL);

			cmd_run_v(cmd); // TODO
		}
	} else {
		printf("Unknown build type");
	}

	return 0;
}
