/*-
 * Copyright (c) 2002 Thomas Moestl <tmm@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: releng/10.1/sys/sys/endian.h 208331 2010-05-20 06:16:13Z phk $
 */

#ifndef _ENDIAN_UTIL_H_
#define _ENDIAN_UTIL_H_

#include "pkg_config.h"

#include <sys/types.h>
#include <inttypes.h>

/* Alignment-agnostic encode/decode bytestream to/from little/big endian. */

#if defined(HAVE_DECL_BE16DEC) && !HAVE_DECL_BE16DEC
static __inline uint16_t
be16dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return ((p[0] << 8) | p[1]);
}
#endif

#if defined(HAVE_DECL_BE32DEC) && !HAVE_DECL_BE32DEC
static __inline uint32_t
be32dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return (((unsigned)p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}
#endif

#if defined(HAVE_DECL_BE64DEC) && !HAVE_DECL_BE64DEC
static __inline uint64_t
be64dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return (((uint64_t)be32dec(p) << 32) | be32dec(p + 4));
}
#endif

#if defined(HAVE_DECL_LE16DEC) && !HAVE_DECL_LE16DEC
static __inline uint16_t
le16dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return ((p[1] << 8) | p[0]);
}
#endif

#if defined(HAVE_DECL_LE32DEC) && !HAVE_DECL_LE32DEC
static __inline uint32_t
le32dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return (((unsigned)p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0]);
}
#endif

#if defined(HAVE_DECL_LE64DEC) && !HAVE_DECL_LE64DEC
static __inline uint64_t
le64dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return (((uint64_t)le32dec(p + 4) << 32) | le32dec(p));
}
#endif

#if defined(HAVE_DECL_BE16ENC) && !HAVE_DECL_BE16ENC
static __inline void
be16enc(void *pp, uint16_t u)
{
	uint8_t *p = (uint8_t *)pp;

	p[0] = (u >> 8) & 0xff;
	p[1] = u & 0xff;
}
#endif

#if defined(HAVE_DECL_BE32ENC) && !HAVE_DECL_BE32ENC
static __inline void
be32enc(void *pp, uint32_t u)
{
	uint8_t *p = (uint8_t *)pp;

	p[0] = (u >> 24) & 0xff;
	p[1] = (u >> 16) & 0xff;
	p[2] = (u >> 8) & 0xff;
	p[3] = u & 0xff;
}
#endif

#if defined(HAVE_DECL_BE64ENC) && !HAVE_DECL_BE64ENC
static __inline void
be64enc(void *pp, uint64_t u)
{
	uint8_t *p = (uint8_t *)pp;

	be32enc(p, (uint32_t)(u >> 32));
	be32enc(p + 4, (uint32_t)(u & 0xffffffffU));
}
#endif

#if defined(HAVE_DECL_LE16ENC) && !HAVE_DECL_LE16ENC
static __inline void
le16enc(void *pp, uint16_t u)
{
	uint8_t *p = (uint8_t *)pp;

	p[0] = u & 0xff;
	p[1] = (u >> 8) & 0xff;
}
#endif

#if defined(HAVE_DECL_LE32ENC) && !HAVE_DECL_LE32ENC
static __inline void
le32enc(void *pp, uint32_t u)
{
	uint8_t *p = (uint8_t *)pp;

	p[0] = u & 0xff;
	p[1] = (u >> 8) & 0xff;
	p[2] = (u >> 16) & 0xff;
	p[3] = (u >> 24) & 0xff;
}
#endif

#if defined(HAVE_DECL_LE64ENC) && !HAVE_DECL_LE64ENC
static __inline void
le64enc(void *pp, uint64_t u)
{
	uint8_t *p = (uint8_t *)pp;

	le32enc(p, (uint32_t)(u & 0xffffffffU));
	le32enc(p + 4, (uint32_t)(u >> 32));
}
#endif

#endif	/* _ENDIAN_UTIL_H_ */
