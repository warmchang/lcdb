/*!
 * crc32c.h - crc32c for rdb
 * Copyright (c) 2022, Christopher Jeffrey (MIT License).
 * https://github.com/chjj/rdb
 */

#ifndef RDB_CRC32C_H
#define RDB_CRC32C_H

#include <stddef.h>
#include <stdint.h>

/* Return the crc32c of concat(A, data[0,n-1]) where init_crc is the
 * crc32c of some string A. extend() is often used to maintain the
 * crc32c of a stream of data.
 */
uint32_t
rdb_crc32c_extend(uint32_t z, const uint8_t *xp, size_t xn);

/* Return the crc32c of data[0,n-1]. */
uint32_t
rdb_crc32c_value(const uint8_t *xp, size_t xn);

/* Return a masked representation of crc.
 *
 * Motivation: it is problematic to compute the CRC of a string that
 * contains embedded CRCs. Therefore we recommend that CRCs stored
 * somewhere (e.g., in files) should be masked before being stored.
 */
uint32_t
rdb_crc32c_mask(uint32_t crc);

/* Return the crc whose masked representation is masked_crc. */
uint32_t
rdb_crc32c_unmask(uint32_t masked_crc);

#endif /* RDB_CRC32C_H */
