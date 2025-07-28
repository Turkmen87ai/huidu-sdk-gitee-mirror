/**
 * @file   posixPortMemory.h
 * @brief  Huidu Memory management of the SDK
 * @author taixi
 * @date   2025/07/22
 */

#ifndef __POSIX_PORT_MEMORY_H__
#define __POSIX_PORT_MEMORY_H__

#include "stdbool.h"
#include "stdint.h"

/**
 * @brief Apply for memory.
 * @param size The size requested for the application.
 * @return Return the memory address.
 */
void *hdmalloc(uint32_t size);

/**
 * @brief Reapply for memory.
 * @param ptr Source Address
 * @param size Size of the reapplication
 * @return Return the memory address.
 */
void *hdrealloc(void *ptr, uint32_t size);

/**
 * @brief Release memory
 * @param The address released by ptr.
 */
void hdfree(void *ptr);

#endif // __POSIX_PORT_MEMORY_H__