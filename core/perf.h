#pragma once

#include <stddef.h>

#ifdef _WIN32
# ifdef PERF_BUILD
#  define PERF_C_EXPORT __declspec(dllexport)
# else
#  define PERF_C_EXPORT __declspec(dllimport)
# endif
#else
# define PERF_C_EXPORT
#endif

/// \defgroup C_API
/// This module exposes the perf api to C, useful for C only
/// applications and importing perf into other languages.

extern "C"
{

struct perf_config;
struct perf_context;
struct perf_identity;
struct perf_meta_event;
struct perf_event;

/// @addtogroup C_API
/// @{

/// Allocation function
/// \param size The size to allocate
/// \note Accepts malloc
typedef void *(*perf_alloc)(size_t size);
/// Deallocation function
/// \param memory The memory to free
/// \note Accepts free
typedef void (*perf_free)(void *memory);

/// \name Config management
/// @{

/// \brief Create a performance testing config
///
/// The config should be created before anything else in perf.
PERF_C_EXPORT perf_config *perf_init_config(perf_alloc, perf_free, const char *binding);

/// \brief Create a default performance testing config
///
/// This helper internally calls perf_init_config with malloc and free.
PERF_C_EXPORT perf_config *perf_init_default_config(const char *binding);

/// \brief Terminate the performance testing config.
PERF_C_EXPORT void perf_term_config(perf_config *ctx);


/// \brief Find the identity of the context
///
/// The identity describes the machine hardware, and is used in
/// graphing to identify threads of tests.
///
/// \note The identity memory is managed by the config, it should not be freed.
PERF_C_EXPORT const perf_identity *perf_find_identity(perf_config *ctx);

/// \brief Transform the identity into a readable description.
///
/// \note The description memory is managed by the config, it should not be freed.
PERF_C_EXPORT const char *perf_identity_description(const perf_identity *id);

/// @}


/// \name Context management
/// @{

/// \brief Init a performance testing context.
PERF_C_EXPORT perf_context *perf_init_context(perf_config *cfg, const char *name);

/// \brief Terminate a performance testing context.
PERF_C_EXPORT void perf_term_context(perf_context *ctx);

/// @}

/// \name Context output
/// @{

/// \brief Write the context to disk.
PERF_C_EXPORT void perf_write_context(perf_context *ctx, const char *filename);

/// \brief Return the context as a string.
PERF_C_EXPORT const char *perf_dump_context(perf_context *ctx);

/// @}

/// \name Recording events
/// @{

/// \brief Create a meta event which can be fired multiple times.
PERF_C_EXPORT perf_meta_event *perf_init_meta_event(perf_context *ctx, const char *name);

/// \brief destroy an meta event
PERF_C_EXPORT void perf_term_meta_event(perf_meta_event *ctx);

/// \brief create an event
PERF_C_EXPORT perf_event *perf_init_event(perf_meta_event *meta);

/// \brief destroy an event
PERF_C_EXPORT void perf_term_event(perf_event *ctx);

/// @}
/// @}

}
