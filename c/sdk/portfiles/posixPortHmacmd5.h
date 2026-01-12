/**
 * @file   posixPortHmacmd5.h
 * @brief  Huidu HMAC-MD5 module
 * @author taixi
 * @date   2024/05/23
 */

#ifndef __POSIX_PORT_HMACMD5_H__
#define __POSIX_PORT_HMACMD5_H__

#include "stdint.h"

void hdinitmd5(void);
void hdmd5(const void* data, uint32_t datLen, uint8_t output[16]);
void hdmd5Hex(const void* data, uint32_t datLen, uint8_t result[32]);
void hdhmacmd5(const void* data, uint32_t dataLen, const void* key, uint32_t keyLen, uint8_t out[16]);
void hdhmacmd5Hex(const void* data, uint32_t dataLen, const void* key, uint32_t keyLen, uint8_t result[32]);
#endif // __POSIX_PORT_HMACMD5_H__
