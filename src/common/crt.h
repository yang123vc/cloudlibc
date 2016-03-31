// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#ifndef COMMON_CRT_H
#define COMMON_CRT_H

#include <cloudabi_types.h>
#include <link.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <threads.h>

// Markers for sections.
extern void (*__ctors_start[])(void);
extern void (*__ctors_stop[])(void);
extern void (*__dtors_start[])(void);
extern void (*__dtors_stop[])(void);

// DSO handle. Not used, as we only support static linkage.
extern void *__dso_handle;

// Stack protection: stack smashing and LLVM SafeStack.
extern unsigned long __stack_chk_guard;
extern thread_local void *__safestack_unsafe_stack_ptr;

// Values preserved from the auxiliary vector.
extern const void *__at_base;         // Process base address.
extern uint32_t __at_ncpus;           // Number of CPUs.
extern uint32_t __at_pagesz;          // Page size.
extern const ElfW(Phdr) * __at_phdr;  // ELF program headers.
extern ElfW(Half) __at_phnum;         // Number of ELF program headers.

// Values preserved from the ELF program headers.
extern const void *__pt_tls_vaddr_abs;  // Initial TLS data (absolute address).
extern size_t __pt_tls_filesz;          // Size of initial TLS data.
extern size_t __pt_tls_memsz_aligned;   // Size of full TLS data (aligned).
extern size_t __pt_tls_align;           // Alignment of TLS data.

// Executable entry point.
noreturn void _start(const cloudabi_auxv_t *);

// Dynamic TLS handler. If object files that use TLS are compiled with
// -fPIC, access to TLS is replaced by calls to __tls_get_addr(). This
// function may then be used to dynamically allocate TLS if needed. We
// don't support dynamic allocation, but still need this function to
// keep code happy.
#if defined(__x86_64__)
struct tls_index {
  size_t module;
  size_t offset;
};

void *__tls_get_addr(const struct tls_index *);
#endif

// Multi-threading: pthread_t handle and thread ID.
struct __pthread {
  _Atomic(cloudabi_lock_t) join;  // Join queue used by pthread_join().
  void *return_value;             // Value returned by pthread_join().
  void *safe_stack;               // Safe stack buffer used by this thread.
  void *unsafe_stack;             // Unsafe stack buffer used by this thread.
  size_t unsafe_stacksize;        // Size of the unsafe stack buffer.

  _Atomic(unsigned int) detachstate;  // Flags related to thread detaching.
#define DETACH_DETACHED 0x1
#define DETACH_TERMINATING 0x2

  void *(*start_routine)(void *);  // User-supplied startup routine.
  void *argument;                  // Argument for startup routine.
};

extern thread_local pthread_t __pthread_self_object;
extern thread_local cloudabi_tid_t __pthread_thread_id;

#endif
