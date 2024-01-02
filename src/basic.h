typedef struct {
	size_t size;
	size_t len;
	size_t append;
	uintmax_t data;
} vec;

typedef struct {
	char* ptr;
	size_t len;
} str;

void* memalloc(size_t len);

char* shift(int* argc, char*** argv);

void* vec_new_impl(size_t size, size_t len);

vec* vec_get(void* this);

void vec_delete(void* this);

void* vec_resize(void* this, size_t n);

str str_from_cstr(char* cstr);

str str_new(size_t len);

str str_new_dup(str other);

str str_new_from_file(char* file);

str str_append(str this, str other);

str str_with_null(str this);

str str_join_v(str sep, str strs[]);

str* str_split(str this, char sep);

void str_delete(str this);

bool str_eq(str this, str other);

bool str_contains(str this, str other);

size_t str_count(str this, char c);

int str_to_int(str this);

// TODO: str_fmt

void print(str s);

void println_v(str strs[]);

void cmd_run_v(char* cmd[]);

void cmd_run_file_v(char* cmd[]);

#define vec_new(T, n) vec_new_impl(sizeof(T), n)

#define vec_append(v, x) v[vec_get(v)->append++] = x

#define foreach(T, v) for (T* it = v; it - v < (long) vec_get(v)->len; ++it)

#define str_join(sep, ...) str_join_v(sep, (str[]){ __VA_ARGS__, (str){0} })

#define println(...) println_v((str[]){ __VA_ARGS__, (str){0} })

#define putcstr(s) println(str_from_cstr(s))

#define cmd_run(...) cmd_run_v((char*[]){ __VA_ARGS__, NULL })

#define cmd_run_file(...) cmd_run_file_v((char*[]){ __VA_ARGS__, NULL })
