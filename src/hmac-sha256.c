/*
 * hmac-sha256 - Implementation of HMAC-SHA256 algrithoms.
 *
 * Modify the source code with Unix C style by Vincent Wei
 *  - Nov. 2020
 *
 * Copyright (C) 2020 FMSoft <https://www.fmsoft.cn>
 * Copyright (C) 2017 Adrian Perez <aperez@igalia.com>
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


#include "hmac.h"

/*
 * HMAC(H, K) == H(K ^ opad, H(K ^ ipad, text))
 *
 *    H: Hash function (sha256)
 *    K: Secret key
 *    B: Block byte length
 *    L: Byte length of hash function output
 *
 * https://tools.ietf.org/html/rfc2104
 */

#define B 64
#define L (SHA256_DIGEST_SIZE)
#define K (SHA256_DIGEST_SIZE * 2)

#define I_PAD 0x36
#define O_PAD 0x5C

void
hmac_sha256 (Sha256Digest* out,
             const uint8_t *data, size_t data_len,
             const uint8_t *key, size_t key_len)
{
    Sha256Context ss;
    Sha256Digest kh;

    /*
     * If the key length is bigger than the buffer size B, apply the hash
     * function to it first and use the result instead.
     */
    if (key_len > B) {
        sha256_init (&ss);
        sha256_update (&ss, key, key_len);
        sha256_finalize (&ss, &kh);
        key_len = SHA256_DIGEST_SIZE;
        key = kh.bytes;
    }

    /*
     * (1) append zeros to the end of K to create a B byte string
     *     (e.g., if K is of length 20 bytes and B=64, then K will be
     *     appended with 44 zero bytes 0x00)
     * (2) XOR (bitwise exclusive-OR) the B byte string computed in step
     *     (1) with ipad
     */
    uint8_t kx[B];
    for (size_t i = 0; i < key_len; i++) kx[i] = I_PAD ^ key[i];
    for (size_t i = key_len; i < B; i++) kx[i] = I_PAD ^ 0;

    /*
     * (3) append the stream of data 'text' to the B byte string resulting
     *     from step (2)
     * (4) apply H to the stream generated in step (3)
     */
    sha256_init (&ss);
    sha256_update (&ss, kx, B);
    sha256_update (&ss, data, data_len);
    sha256_finalize (&ss, out);

    /*
     * (5) XOR (bitwise exclusive-OR) the B byte string computed in
     *     step (1) with opad
     *
     * NOTE: The "kx" variable is reused.
     */
    for (size_t i = 0; i < key_len; i++) kx[i] = O_PAD ^ key[i];
    for (size_t i = key_len; i < B; i++) kx[i] = O_PAD ^ 0;

    /*
     * (6) append the H result from step (4) to the B byte string
     *     resulting from step (5)
     * (7) apply H to the stream generated in step (6) and output
     *     the result
     */
    sha256_init (&ss);
    sha256_update (&ss, kx, B);
    sha256_update (&ss, out, SHA256_DIGEST_SIZE);
    sha256_finalize (&ss, out);
}

