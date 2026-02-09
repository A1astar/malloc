# malloc

Educational implementation of a dynamic memory allocator in the spirit of `malloc`/`free`.
The goal of this project is to gain a deep understanding of how a memory allocator works (heap organization, allocation strategies, fragmentation, coalescing, etc.), rather than to provide a production-ready replacement for glibc’s `malloc(3)`.

---

## Project goals

- Reproduce the behavior of a user-space allocator (`malloc`/`realloc`/`free`).
- Handle fragmentation and coalescing of free blocks.
- Manipulate the heap directly `mmap`.

This project is primarily intended for educational use by students in systems programming, low-level C programming, or security.

---

## Build

```sh
git clone https://github.com/A1astar/malloc.git
cd malloc

make          # builds the library
make test     # builds test binary
make fclean    # cleanup
```

---

## Usage

#### As a library (LD_PRELOAD or explicit linking)

```sh
LD_PRELOAD=./libft_malloc.so ./my_prorgam
```

#### Explicit linking at compile time:

```sh
gcc -o program program.c -L. -lft_malloc
```

## Allocator architecture / design

- **Internal block structure**
  - Header: single `size_t` metadata (size + allocated flag in LSB)
  - Block alignment: 16 bytes
  - Payload immediately follows header (offset by `align16(sizeof(size_t))`)
  - No explicit prev/next pointers — blocks found by traversing via size
- **Heap management**
  - Uses `mmap` exclusively (no `sbrk`)
  - Three allocation strategies:
    - **TINY**: blocks ≤ 1024 bytes → pre-allocated arena
    - **SMALL**: blocks ≤ 4096 bytes → pre-allocated arena
    - **LARGE**: blocks > 4096 bytes → individual `mmap` per allocation
  - Arena size: 100 blocks × max_block_size + arena header, page-aligned
- **Free-block organization**
  - Implicit free list (no explicit links between free blocks)
  - Traversal by size field embedded in each block
  - Arena tracks `max_available` (largest free block) for quick fit checks
  - Circular doubly linked list of arenas per type (TINY/SMALL)
  - Separate circular doubly linked list for large `mmap` allocations
- **Allocation strategy**
  - First fit within arenas
  - Arena selection: search existing arenas for sufficient `max_available`, else create new arena
  - Block splitting: if found block > requested size, create new free block with remainder
- **Coalescing**
  - Triggered on `free()` after marking block as free
  - Forward coalescing only (merges consecutive free blocks)
  - Updates arena's `max_available` during merge
  - Empty arenas (nb_alloc == 0) are unmapped
- **Security / robustness**
  - Thread-safe: global `pthread_mutex_t` protects all operations
  - Validates pointers via `is_from_current_allocator()` before freeing
  - LSB flag prevents double-free (checks allocated bit)
  - Bounded arena traversal (stops at arena boundaries)

---

## Tests and validation

- Command to run tests:

  ```sh
  make test
  ./malloc_test
  ```
---

## References and documentation

- [Doug Lea – Malloc](https://gee.cs.oswego.edu/dl/html/malloc.html)
- [Malloc tutorial (EPITA)](https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf)
- [Malloc slides – IIT](https://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf)
- [Coursebook Malloc – UIUC CS 341](https://cs341.cs.illinois.edu/coursebook/Malloc)
- [Heap exploitation – Azeria Labs](https://azeria-labs.com/heap-exploitation-part-1-understanding-the-glibc-heap-implementation/)
- [glibc malloc internals (sourceware)](https://sourceware.org/glibc/wiki/MallocInternals)

> *One Heap to malloc them all, One Heap to free them, One Heap to coalesce, and in the memory bind them...*
