#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Definisi tipe data wajib Dobby
typedef uintptr_t addr_t;
typedef uintptr_t zsize_t;

#ifdef __cplusplus
extern "C" {
#endif
    // Masukkan deklarasi fungsi standar di sini biar aman
    void *memcpy(void *dest, const void *src, size_t n);
    size_t strlen(const char *s);
#ifdef __cplusplus
}
#endif
