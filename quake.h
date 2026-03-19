/*

        QUAKE

  Chunked arena allocator

*/

#ifndef UTILS_H_QUAKE_H
#define UTILS_H_QUAKE_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_QUAKE) //Avoid defining if module was turned off
//Define types/macros here

#ifndef quake_size_t
  #include <stddef.h>
  #define quake_size_t size_t
#endif

#ifndef quake_byte
  #define quake_byte unsigned char
#endif

#include <stdarg.h>

typedef struct quake_chunk {
  struct quake_chunk* next;
  quake_size_t cap;
  quake_size_t used;
  quake_byte data[];
} quake_chunk;

typedef struct quake {
  quake_chunk* head;
  quake_chunk* tail;
  quake_size_t chunk_cap;
} quake;

#define quake_default_chunk_cap 1024

#define quake_new(...) ({ \
  struct { quake_size_t chunk_cap; } _opt = { \
    .chunk_cap = quake_default_chunk_cap, \
    ##__VA_ARGS__ \
  }; \
  quake _arena; \
  quake_init(&_arena, _opt.chunk_cap); \
  _arena; \
})

void quake_init(quake* arena, quake_size_t chunk_cap);
void quake_reset(quake* arena);
void quake_free(quake* arena);
void* quake_alloc(quake* arena, quake_size_t bytes);
void* quake_calloc(quake* arena, quake_size_t count, quake_size_t bytes);
char* quake_strdup(quake* arena, const char* src);
int quake_vasprintf(quake* arena, char** out, const char* format, va_list ap);
int quake_asprintf(quake* arena, char** out, const char* format, ...);
char* quake_strus_newf(quake* arena, const char* fmt, ...);

#define quake_new_darr(A, T, ...) ({ \
    struct { quake_size_t cap; quake_size_t len; void* src; } _opt = { \
        .cap = darr_default_cap, \
        .len = 0, \
        .src = NULL, \
        ##__VA_ARGS__ \
    }; \
    T* _result = NULL; \
    if (_opt.cap < _opt.len) _opt.cap = _opt.len; \
    size_t _total_sz = darr_prefix_sz + (sizeof(T) * _opt.cap); \
    darr_header* _raw = (darr_header*)quake_alloc((A), _total_sz); \
    if (_raw) { \
      _raw->len = _opt.len; \
      _raw->cap = _opt.cap; \
      T* _data_ptr = (T*)((char*)_raw + darr_prefix_sz); \
      if (_opt.src) memcpy(_data_ptr, _opt.src, sizeof(T) * _opt.len); \
      _result = _data_ptr; \
    } \
    _result; \
})

//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_QUAKE_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static quake_size_t _quake_align_up(quake_size_t value, quake_size_t alignment) {
  quake_size_t mask = alignment - 1;
  return (value + mask) & ~mask;
}

static quake_chunk* _quake_new_chunk(quake_size_t cap) {
  quake_chunk* chunk = (quake_chunk*)malloc(sizeof(quake_chunk) + cap);
  if (!chunk) return NULL;
  chunk->next = NULL;
  chunk->cap = cap;
  chunk->used = 0;
  return chunk;
}

void quake_init(quake* arena, quake_size_t chunk_cap) {
  if (!arena) return;
  arena->head = NULL;
  arena->tail = NULL;
  arena->chunk_cap = chunk_cap ? chunk_cap : quake_default_chunk_cap;
}

void quake_reset(quake* arena) {
  if (!arena) return;
  for (quake_chunk* chunk = arena->head; chunk; chunk = chunk->next)
    chunk->used = 0;
  arena->tail = arena->head;
}

void quake_free(quake* arena) {
  if (!arena) return;
  quake_chunk* chunk = arena->head;
  while (chunk) {
    quake_chunk* next = chunk->next;
    free(chunk);
    chunk = next;
  }
  arena->head = NULL;
  arena->tail = NULL;
}

void* quake_alloc(quake* arena, quake_size_t bytes) {
  if (!arena || bytes == 0) return NULL;

  quake_size_t alignment = sizeof(max_align_t);
  quake_size_t required = bytes + alignment;

  if (!arena->tail) {
    quake_size_t first_cap = arena->chunk_cap > required ? arena->chunk_cap : required;
    quake_chunk* first = _quake_new_chunk(first_cap);
    if (!first) return NULL;
    arena->head = first;
    arena->tail = first;
  }

  quake_chunk* chunk = arena->tail;
  quake_size_t aligned_used = _quake_align_up(chunk->used, alignment);

  if (aligned_used + bytes > chunk->cap) {
    if (chunk->next) {
      arena->tail = chunk->next;
      chunk = arena->tail;
      aligned_used = _quake_align_up(chunk->used, alignment);
    } else {
      quake_size_t new_cap = arena->chunk_cap;
      if (new_cap < required) new_cap = required;
      quake_chunk* next = _quake_new_chunk(new_cap);
      if (!next) return NULL;
      chunk->next = next;
      arena->tail = next;
      chunk = next;
      aligned_used = 0;
    }

    if (aligned_used + bytes > chunk->cap) return NULL;
  }

  void* ptr = chunk->data + aligned_used;
  chunk->used = aligned_used + bytes;
  return ptr;
}

void* quake_calloc(quake* arena, quake_size_t count, quake_size_t bytes) {
  if (!count || !bytes) return NULL;
  if (count > ((quake_size_t)-1) / bytes) return NULL;
  quake_size_t total = count * bytes;
  void* ptr = quake_alloc(arena, total);
  if (!ptr) return NULL;
  memset(ptr, 0, total);
  return ptr;
}

char* quake_strdup(quake* arena, const char* src) {
  if (!src) return NULL;
  quake_size_t len = strlen(src) + 1;
  char* out = (char*)quake_alloc(arena, len);
  if (!out) return NULL;
  memcpy(out, src, len);
  return out;
}

int quake_vasprintf(quake* arena, char** out, const char* format, va_list ap) {
  if (!arena || !out || !format) return -1;

  va_list ap_copy;
  va_copy(ap_copy, ap);
  int len = vsnprintf(NULL, 0, format, ap_copy);
  va_end(ap_copy);
  if (len < 0) {
    *out = NULL;
    return -1;
  }

  char* buffer = (char*)quake_alloc(arena, (quake_size_t)len + 1);
  if (!buffer) {
    *out = NULL;
    return -1;
  }

  int written = vsnprintf(buffer, (quake_size_t)len + 1, format, ap);
  if (written < 0) {
    *out = NULL;
    return -1;
  }

  *out = buffer;
  return written;
}

int quake_asprintf(quake* arena, char** out, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  int written = quake_vasprintf(arena, out, format, ap);
  va_end(ap);
  return written;
}

char* quake_strus_newf(quake* arena, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  va_list ap_copy;
  va_copy(ap_copy, ap);
  int len = vsnprintf(NULL, 0, fmt, ap_copy);
  va_end(ap_copy);
  if (len < 0) {
    va_end(ap);
    return NULL;
  }

  char* out = (char*)quake_alloc(arena, (quake_size_t)len + 1);
  if (!out) {
    va_end(ap);
    return NULL;
  }

  if (vsnprintf(out, (quake_size_t)len + 1, fmt, ap) < 0) {
    va_end(ap);
    return NULL;
  }

  va_end(ap);
  return out;
}

//end of variables
#endif //UTILS_H_QUAKE_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_QUAKE

#endif //UTILS_H_QUAKE_H
