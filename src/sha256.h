/*
 * sha256 - Implementation of SHA256 hash function.
 *
 * Original author: Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 * Modified by WaterJuice retaining Public Domain license.
 *
 * This is free and unencumbered software released into the public domain
 *  - June 2013 waterjuice.org
 *
 * Modify the source code with Unix C style by Vincent Wei
 *  - Nov. 2020
 *
 * Copyright (C) 2020 FMSoft <https://www.fmsoft.cn>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef __LIBHIBOX_SHA256_H
#define __LIBHIBOX_SHA256_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint64_t    length;
    uint32_t    state[8];
    uint32_t    curlen;
    uint8_t     buf[64];
} Sha256Context;

#define SHA256_DIGEST_SIZE           (256 / 8)

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  sha256_init
 *
 *  Initialises a SHA256 Context. Use this to initialise/reset a context.
 */
void sha256_init (Sha256Context* ctxt);

/*
 * sha256_update
 *
 * Adds data to the SHA256 context. This will process the data and update
 * the internal state of the context. Keep on calling this function until
 * all the data has been added. Then call sha256_finalize to calculate the hash.
*/
void sha256_update (Sha256Context* ctxt, const void* buff, uint32_t buff_sz);

/*
 * sha256_finalize
 *
 * Performs the final calculation of the hash and returns the digest
 * (32 byte buffer containing 256bit hash).
 * After calling this, Sha256Initialised must be used to reuse the context.
 */
void sha256_finalize (Sha256Context* ctxt, uint8_t* digest);

/*
 * sha256_calc_digest
 *
 * Combines sha256_init, sha256_update, and sha256_finalize into one function.
 * Calculates the SHA256 hash of the buffer.
 */
void sha256_calc_digest (const void* buff, uint32_t buff_sz, uint8_t* digest);

#ifdef __cplusplus
}
#endif

#endif /* __LIBHIBOX_SHA256_H */

