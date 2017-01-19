#ifndef MALLOC_H_
#define MALLOC_H_
/**
 *  @file    malloc.h
 *  @brief   Header file for malloc.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */
enum {
	MF_ALIGN = sizeof(long)
};

struct __memcache {
	struct __memobject *obj_list;
	struct __memcache  *next;

	size_t  obj_size;
	size_t  obj_align;
	size_t  list_len;
	size_t  total_len;
};

struct __memobject {
	struct __memcache *cache;
	union {
		struct __memobject *next;
		char  data[0];
	};
};

typedef struct {
	struct __memcache *cachelist;

	void    *start;
	void    *ptr;
	void    *end;

} memmap_t;

#ifdef  __cplusplus
extern "C" {
#endif

 void  heap_init    ( void *, void * );
void*  memmap_block ( memmap_t *, size_t, unsigned int );
void*  map_alloc    ( memmap_t *, size_t, unsigned int );
void*  malloc       ( size_t );
void*  calloc       ( size_t, size_t );
 void  free         ( void * );

#ifdef  __cplusplus
}
#endif

#endif  /*  MALLOC_H_  */

