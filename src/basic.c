#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include "basic.h"

void* memalloc(size_t len)
{
	void* mem = malloc(len);

	assert(mem);

	return mem;
}

char* shift(int* argc, char*** argv)
{
	assert(*argc > 0);

	*argc -= 1;
	*argv += 1;

	return *argc > 0 ? **argv : "";
}

void* vec_new_impl(size_t size, size_t len)
{
	vec* v = memalloc(sizeof(vec) - sizeof(uintmax_t) + size * len);
	v->size = size;
	v->len = len;
	v->append = 0;

	return &v->data;
}

vec* vec_get(void* v)
{
	return (void*) (((char*) v) - offsetof(vec, data));
}

void vec_delete(void* this)
{
	free(vec_get(this));
}

void* vec_resize(void* this, size_t n)
{
	vec* v = vec_get(this);
	vec* new = memalloc(sizeof(vec) - sizeof(uintmax_t) + v->size * n);

	size_t meta = offsetof(vec, data);
	memcpy(new, v, meta);

	size_t copied = v->len > n ? n : v->len;
	memcpy(&new->data, this, copied * v->size);

	free(v);

	new->len = n;

	return &new->data;
}

str str_from_cstr(char* cstr)
{
	return (str){ cstr, strlen(cstr) };
}

str str_new(size_t len)
{
	return (str){
		.ptr = memalloc(len),
		.len = len
	};
}

str str_new_dup(str other)
{
	str this = {
		.ptr = memalloc(other.len),
		.len = other.len,
	};

	memcpy(this.ptr, other.ptr, this.len);

	return this;
}

str str_new_from_file(char* file)
{
	FILE* f = fopen(file, "rb");

	assert(f);

	assert(fseek(f, 0, SEEK_END) >= 0);

	str new = str_new(ftell(f));

	assert(fseek(f, 0, SEEK_SET) >= 0);

	fread(new.ptr, 1, new.len, f);

	assert(ferror(f) == 0);

	fclose(f);

	return new;
}

str str_append(str this, str other)
{
	str new = str_new(this.len + other.len);

	memcpy(new.ptr, this.ptr, this.len);
	memcpy(new.ptr + this.len, other.ptr, other.len);

	return new;
}

str str_with_null(str this)
{
	str new = str_new(this.len + 1);

	memcpy(new.ptr, this.ptr, this.len);
	new.ptr[this.len] = '\0';

	return new;
}

str str_join_v(str sep, str strs[])
{
	size_t len = 0;

	for (str* s = strs; s->len > 0; ++s) {
		len += s->len + sep.len;
	}

	len -= sep.len;

	str this = str_new(len);

	size_t idx = 0;

	for (str* s = strs; s->len > 0; ++s) {
		memcpy(this.ptr + idx, s->ptr, s->len);
		idx += s->len;

		if (idx < len) {
			memcpy(this.ptr + idx, sep.ptr, sep.len);
			idx += sep.len;
		}
	}

	return this;
}

void str_delete(str this)
{
	free(this.ptr);
}

bool str_eq(str this, str other)
{
	return memcmp(this.ptr, other.ptr, this.len) == 0;
}

bool str_contains(str this, str other)
{
	if (other.len > this.len)
		return false;

	size_t match = 0;

	for (size_t i = 0; i < this.len; ++i) {
		if (this.ptr[i] == other.ptr[match]) {
			++match;
		} else {
			match = this.ptr[i] == other.ptr[0] ? 1 : 0;
		}

		if (match == other.len)
			return true;
	}

	return false;
}

size_t str_count(str this, char c)
{
	size_t count = 0;

	for (size_t i = 0; i < this.len; ++i) {
		if (this.ptr[i] == c)
			++count;
	}

	return count;
}

str* str_split(str this, char sep)
{
	size_t n_sep = str_count(this, sep);
	size_t start = 0;
	str* v = vec_new(str, n_sep + 1);

	for (size_t i = 0; i < this.len; ++i) {
		if (this.ptr[i] == sep) {
			vec_append(v, ((str){this.ptr + start, i - start}));
			start = i + 1;
		}

		if (i + 1 == this.len) {
			vec_append(v, ((str){this.ptr + start, this.len - start}));
		}
	}

	return v;
}

int str_to_int(str this)
{
	str cstr = str_with_null(this);

	int res = atoi(cstr.ptr);

	str_delete(cstr);

	return res;
}

void print(str s)
{
	assert(write(STDOUT_FILENO, s.ptr, s.len) >= 0);
	assert(write(STDOUT_FILENO, " ", 1) >= 0);
}

void println_v(str strs[])
{
	for (str* s = strs; s->len > 0; ++s) {
		print(*s);
	}

	assert(write(STDOUT_FILENO, "\n", 1) >= 0);
}

void cmd_run_v(char* cmd[])
{
	// pid_t parent = getpid();
	pid_t pid = fork();

	assert(pid >= 0);

	if (pid == 0) {
		execvp(cmd[0], cmd);
		assert(false);
	} else {
		int status;
		waitpid(pid, &status, 0);
	}
}

void cmd_run_file_v(char* cmd[])
{
	char path[255];
	assert(getcwd(path, 255) != NULL);
	strcat(path, "/");
	strcat(path, cmd[0]);

	// pid_t parent = getpid();
	pid_t pid = fork();

	assert(pid >= 0);

	if (pid == 0) {
		execv(path, cmd);
		assert(false);
	} else {
		int status;
		waitpid(pid, &status, 0);
	}
}
