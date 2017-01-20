/**
 *  @file    malloc.c
 *  @brief   Functions dynamic memory allocation.
 *  @author  Gerasimov A.S., Sudak I.
 *  @date    2013-04-12 14:45:55 +0400
 */
#include <stddef.h>
#include "typedef.h"
#include "math.h"
#include "malloc.h"


/**
 *  Возвращает кэш для выделения указанного
 *  размера памяти.
 */
struct __memcache* __get_cache ( memmap_t *mmap, size_t size, uint align )
{
	struct __memcache*  cache;
	struct __memcache*  cache_bfit;
	   register size_t  cache_size;


	cache_bfit = (struct __memcache *)0;
	cache_size = (ulong)(-1);
	/* 
	 *  Ищем среди существующих кэшей по принципу
	 *  первого идентичного и параллельно подбираем
	 *  наиболее подходящий.
	 */
	for( cache = mmap->cachelist; cache; cache = cache->next )
	{
		if( (cache->obj_size >= size) &&
		    (cache->obj_align >= align)
		)
		{
			if( cache->obj_size < cache_size )
			{
				cache_size = cache->obj_size;
				cache_bfit = cache;
			}

			if( (cache->obj_size == size) &&
			    (cache->obj_align == align)
			)
			return cache;
		}
	}


	/*
	 *  Нужный кэш не найден, создаем новый кэш
	 *  для указанного объекта.
	 */
	if( (mmap->end - mmap->ptr) > ( offsetof(struct __memobject, data) + sizeof(*cache) + size ) )
	{
		cache = (struct __memcache *)( memmap_block( mmap, sizeof(*cache), MF_ALIGN ) );

		cache->obj_size  = size;
		cache->obj_align = align;
		cache->obj_list  = (void *)NULL;
		cache->list_len  = 0;
		cache->total_len = 0;
		cache->next = mmap->cachelist;
		mmap->cachelist = cache;

		return  cache;
	}


	/* 
	 *  Если идентичный кэш не найден и создать новый неудалось,
	 *  то возвращаем результат наиболее подходящего кэша.
	 */
	return  cache_bfit;
}


/**
 *  Возвращает объект из кэш для размещения
 *  указанного размера памяти.
 */
struct __memobject* __get_object ( memmap_t *mmap, struct __memcache* cache )
{
	struct __memobject*  obj;

	/*
	 *  Берем объект из кэша.  */
	if( (obj = cache->obj_list) )
	{
		cache->obj_list = obj->next;
		cache->list_len--;
		return  obj;
	}
	/*
	 *  Кэш пуст -> создаем новый объект.  */
	uint    align   = cache->obj_align;
	size_t  obhsize = ALIGNe_HI( offsetof(struct __memobject, data), align );
	size_t  obdsize = ALIGNe_HI( cache->obj_size, align );

	void *ptr = memmap_block( mmap, obhsize + obdsize, align );

	if( ptr )
	{
		obj = ptr;
		obj->cache = cache;
		cache->total_len++;
	}

	return  obj;
}


/**
 *  @brief   Выделяет указанный размер памяти в указанной карте памяти.
 *
 *  @param   mmap  : [in] карта памяти (куча).
 *  @param   size  : [in] размер выделяемого блока из карты (кучи).
 *  @param   align : [in] выравнивание выделяемого блока.
 *
 *  @return  Возвращает адрес выделенного в указанной памяти (куче)
 *           буфера данных. В случае ошибки возвращает "0".
 */
void* map_alloc ( memmap_t *mmap, size_t size, unsigned int align )
{
	struct __memobject *object;
	struct __memcache  *cache;


	if( !( cache = __get_cache(mmap, size, align) ) )
		return  (void *)0;

	if( ( object = __get_object(mmap, cache) ) )
		return  (void *)object->data;


	return  (void *)0;
}


/**
 *  @brief   Освобождает ранее выделенный блок памяти.
 *  @param   ptr  : [in] адрес ранее выделенного блока.
 */
void free ( void *ptr )
{
	struct __memobject *object;
	struct __memcache  *cache;

	object = (struct __memobject *)( ((ulong)(ptr)) - offsetof(struct __memobject, data) );
	cache  = object->cache;

	object->next = cache->obj_list;
	cache->obj_list = object;
	cache->list_len++;
}
