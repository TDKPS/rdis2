#ifndef map_HEADER
#define map_HEADER

// a 1-to-1 mapping of uint64_t to values

#include <inttypes.h>

#include "object.h"
#include "tree.h"

struct _map_node {
    const struct _object * object;
    uint64_t key;
    void   * value;
};


struct _map {
    const struct _object * object;
    size_t size;
    struct _tree * tree;
};


struct _map_it {
    struct _tree_it * it;
};


// returns 0 on success, -1 on error (key already exists)
int      map_insert        (struct _map *, uint64_t key, const void * value);
void *   map_fetch         (const struct _map *, uint64_t key);
void *   map_fetch_max     (const struct _map *, uint64_t key);
uint64_t map_fetch_max_key (const struct _map *, uint64_t key);
int      map_remove        (struct _map *, uint64_t key);


struct _map * map_create      ();
void          map_delete      (struct _map *);
struct _map * map_copy        (const struct _map *);

struct _map_node * map_node_create      (uint64_t key, const void * value);
void               map_node_delete      (struct _map_node *);
struct _map_node * map_node_copy        (const struct _map_node *);
int                map_node_cmp         (const struct _map_node *, const struct _map_node *);

struct _map_it * map_iterator  (const struct _map * map);
struct _map_it * map_it_next   (struct _map_it * map_it);
void *           map_it_data   (const struct _map_it * map_it);
uint64_t         map_it_key    (const struct _map_it * map_it);
void             map_it_delete (struct _map_it * map_it);


#endif