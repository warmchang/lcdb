/*!
 * comparator.h - comparator for rdb
 * Copyright (c) 2022, Christopher Jeffrey (MIT License).
 * https://github.com/chjj/rdb
 */

#ifndef RDB_COMPARATOR_H
#define RDB_COMPARATOR_H

#include "types.h"

/*
 * Types
 */

/* A comparator object provides a total order across slices that are
 * used as keys in an sstable or a database. A comparator implementation
 * must be thread-safe since leveldb may invoke its methods concurrently
 * from multiple threads.
 */
typedef struct rdb_comparator_s {
  /* The name of the comparator. Used to check for comparator
   * mismatches (i.e., a DB created with one comparator is
   * accessed using a different comparator.
   *
   * The client of this package should switch to a new name whenever
   * the comparator implementation changes in a way that will cause
   * the relative ordering of any two keys to change.
   *
   * Names starting with "leveldb." are reserved and should not be used
   * by any clients of this package.
   */
  const char *name;

  /* Three-way comparison. Returns value:
   *   < 0 iff "a" < "b",
   *   == 0 iff "a" == "b",
   *   > 0 iff "a" > "b"
   */
  int (*compare)(const rdb_slice_t *, const rdb_slice_t *);

  /* Advanced functions: these are used to reduce the space requirements
     for internal data structures like index blocks. */

  /* If *start < limit, changes *start to a short string in [start,limit).
     Simple comparator implementations may return with *start unchanged,
     i.e., an implementation of this method that does nothing is correct. */
  void (*find_shortest_separator)(rdb_buffer_t *, const rdb_slice_t *);

  /* Changes *key to a short string >= *key.
     Simple comparator implementations may return with *key unchanged,
     i.e., an implementation of this method that does nothing is correct. */
  void (*find_short_successor)(rdb_buffer_t *);
} rdb_comparator_t;

/*
 * Globals
 */

/* RDB_EXTERN */ extern const rdb_comparator_t *rdb_bytewise_comparator;

#endif /* RDB_COMPARATOR_H */
