#ifndef REACH_H
#define REACH_H

#include "../ast/ast.h"
#include "../../libponyrt/ds/hash.h"

PONY_EXTERN_C_BEGIN

typedef struct reachable_method_t reachable_method_t;
typedef struct reachable_method_name_t reachable_method_name_t;
typedef struct reachable_type_t reachable_type_t;

DECLARE_HASHMAP(reachable_methods, reachable_method_t);
DECLARE_HASHMAP(reachable_method_names, reachable_method_name_t);
DECLARE_HASHMAP(reachable_types, reachable_type_t);
DECLARE_HASHMAP(reachable_type_cache, reachable_type_t);

struct reachable_method_t
{
  const char* name;
  ast_t* typeargs;
  ast_t* r_fun;
  uint32_t vtable_index;
};

struct reachable_method_name_t
{
  const char* name;
  reachable_methods_t r_methods;
};

struct reachable_type_t
{
  const char* name;
  ast_t* type;
  reachable_method_names_t methods;
  reachable_type_cache_t subtypes;
  uint32_t vtable_size;
};

/// Allocate a new set of reachable types.
reachable_types_t* reach_new();

/// Add primitive types to the reachable set.
void reach_primitives(reachable_types_t* r, pass_opt_t* opt, ast_t* from);

/// Free a set of reachable types.
void reach_free(reachable_types_t* r);

/** Determine code reachability for a method in a type.
 *
 * The type should be a nominal, including any typeargs. The supplied method
 * typeargs can be NULL if there are none.
 */
void reach(reachable_types_t* r, ast_t* type, const char* name,
  ast_t* typeargs);

reachable_type_t* reach_type(reachable_types_t* r, const char* name);

reachable_method_name_t* reach_method_name(reachable_type_t* t,
  const char* name);

reachable_method_t* reach_method(reachable_method_name_t* n,
  const char* name);

size_t reach_method_count(reachable_type_t* t);

void reach_dump(reachable_types_t* r);

PONY_EXTERN_C_END

#endif
