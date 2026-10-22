#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/mman.h>

#define FILE_NAME "/dev/zero"
#define PAGE_SIZE 4096
#define DATA_SIZE (2 * PAGE_SIZE)

#define ENTRY_PRESENT_MASK (1ul << 63)
#define ENTRY_SWAPPED_MASK (1ul << 62)
#define ENTRY_FRAME_MASK ((1ul << 55) - 1)


void print_physical_addresses (void *data, size_t size) {
    int mapping = open ("/proc/self/pagemap", O_RDONLY);
    lseek (mapping, (uintptr_t) data / PAGE_SIZE * sizeof (uint64_t), SEEK_SET);
    for (size_t position = 0 ; position < size ; position += PAGE_SIZE) {
        uint64_t entry;
        read (mapping, &entry, sizeof (entry));
        printf (
            "P%" PRIu64 " S%" PRIu64 " frame %014" PRIx64 " ",
            (bool) (entry & ENTRY_PRESENT_MASK),
            (bool) (entry & ENTRY_SWAPPED_MASK),
            entry & ENTRY_FRAME_MASK
        );
    }
    printf ("\n");
    close (mapping);
}


int main (int argc, char *argv []) {

    int file = open (FILE_NAME, O_RDONLY);
    int *data_one = (int *) mmap (NULL, DATA_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, file, 0);
    int *data_two = (int *) mmap (NULL, DATA_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, file, 0);
    assert (data_one != MAP_FAILED);
    assert (data_two != MAP_FAILED);
    close (file);

    printf ("Before reading ...\n");

    print_physical_addresses (data_one, DATA_SIZE);
    print_physical_addresses (data_two, DATA_SIZE);

    volatile int one = data_one [0];
    volatile int two = data_two [PAGE_SIZE / sizeof (int)];

    printf ("After reading ...\n");

    print_physical_addresses (data_one, DATA_SIZE);
    print_physical_addresses (data_two, DATA_SIZE);

    data_one [0] = 0xBEEF;
    data_two [PAGE_SIZE / sizeof (int)] = 0xBAAD;

    printf ("After writing ...\n");

    print_physical_addresses (data_one, DATA_SIZE);
    print_physical_addresses (data_two, DATA_SIZE);

    return (0);
}
