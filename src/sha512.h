/*
 * sha512 - Implementation of SHA512 hash function.
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

#ifndef __LIBHIBOX_SHA512_H
#define __LIBHIBOX_SHA512_H

#include <stdint.h>
#include <stdio.h>

typedef struct
{
    uint64_t    length;
    uint64_t    state[8];
    uint32_t    curlen;
    uint8_t     buf[128];
} Sha512Context;

#define SHA512_DIGEST_SIZE            (512/8)

#ifdef __cplusplus
extern "C" {
#endif

/*
 * sha512_init
 *
 * Initialises a SHA512 ctxt. Use this to initialise/reset a context.
 */
void sha512_init (Sha512Context* ctxt);

/*
 * sha512_update
 *
 * Adds data to the SHA512 context. This will process the data and update
 * the internal state of the context.
 * Keep on calling this function until all the data has been added.
 * Then call sha512_finalize to calculate the hash.
*/
void sha512_update (Sha512Context* ctxt, const void* buff, uint32_t buff_sz);

/*
 * sha512_finalize
 *
 * Performs the final calculation of the hash and returns the digest
 * (64 byte buffer containing 512bit hash).
 * After calling this, Sha512Initialised must be used to reuse the context.
 */
void sha512_finalize (Sha512Context* ctxt, uint8_t* digest);

/*
 * sha512_calc_digest
 *
 * Combines sha512_init, sha512_update, and sha512_finalize into one function.
 * Calculates the SHA512 hash of the buffer.
 */
void sha512_calc_digest (const void* buff, uint32_t buff_sz, uint8_t* digest);

#ifdef __cplusplus
}
#endif

#endif  /* __LIBHIBOX_SHA512_H */
