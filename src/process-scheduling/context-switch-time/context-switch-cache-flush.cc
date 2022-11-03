#include <chrono>
#include <thread>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <semaphore>


#define CACHE_LINE_SIZE 64

typedef struct cache_line_t {
    cache_line_t *next;
    uint8_t padding [CACHE_LINE_SIZE - sizeof (void *)];
} cache_line_t;

static_assert (sizeof (cache_line_t) == CACHE_LINE_SIZE);


// Experiment dimensions

int loops = 16;
size_t memory = 16*1024*1024;

// Workload related variables

cache_line_t *ping_area, *pong_area;

std::binary_semaphore ping_semaphore (0);
std::binary_semaphore pong_semaphore (0);


// Memory area walk functions

cache_line_t *do_mem_alloc () {
    size_t count = memory / CACHE_LINE_SIZE;
    auto chain = new size_t [count];
    for (size_t index = 0 ; index < count ; index ++) {
        chain [index] = index;
    }
    std::random_shuffle (chain, chain + count);
    cache_line_t *block = new cache_line_t [count];
    auto current = block + chain [count - 1];
    for (size_t index = 0 ; index < count ; index ++) {
        current->next = block + chain [index];
        current = block + chain [index];
    }
    delete [] chain;
    return (block);
}

cache_line_t *do_mem_walk (cache_line_t *area) {
    size_t count = memory / CACHE_LINE_SIZE;
    cache_line_t *current = area;
    for (size_t index = 0 ; index < count ; index ++) {
        current = current->next;
    }
    return (current);
}


// Thread bodies

void ping_thread_body () {
    for (int i = 0 ; i < loops ; i ++) {
        ping_semaphore.release ();
        pong_semaphore.acquire ();
        ping_area = do_mem_walk (ping_area);
    }
}

void pong_thread_body () {
    for (int i = 0 ; i < loops ; i ++) {
        ping_semaphore.acquire ();
        pong_area = do_mem_walk (pong_area);
        pong_semaphore.release ();
    }
}


// Mainline

int main (int argc, char *argv []) {
    if (argc == 3) {
        // Number of times to iterate over memory area.
        loops = std::atoi (argv [1]);
        assert (loops > 0);
        // Size of memory area to iterate over.
        memory = std::atoi (argv [2]);
        assert (memory >= CACHE_LINE_SIZE);
    }

    std::cout << std::fixed << std::setprecision (0);

    // Initialize the memory walk chains.
    ping_area = do_mem_alloc ();
    pong_area = do_mem_alloc ();

    // Prime cache.
    ping_area = do_mem_walk (ping_area);

    // Perform single thread measurement.
    auto solo_time_before = std::chrono::steady_clock::now ();
    for (int i = 0 ; i < 2 * loops ; i ++) {
        ping_area = do_mem_walk (ping_area);
    }
    auto solo_time_after = std::chrono::steady_clock::now ();
    auto solo_time_delta = std::chrono::duration <double, std::nano> (solo_time_after - solo_time_before);;
    std::cout << "Solo time is " << solo_time_delta.count () << " ns, " << solo_time_delta.count () / loops / memory / 2 * 1000 << " ps per byte." << std::endl;

    // Perform double thread mesurement.
    auto thread_time_before = std::chrono::steady_clock::now ();
    auto ping_thread = new std::thread (ping_thread_body);
    auto pong_thread = new std::thread (pong_thread_body);
    ping_thread->join ();
    pong_thread->join ();
    auto thread_time_after = std::chrono::steady_clock::now ();
    auto thread_time_delta = std::chrono::duration <double, std::nano> (thread_time_after - thread_time_before);
    std::cout << "Thread time is " << thread_time_delta.count () << " ns, " << thread_time_delta.count () / loops / memory / 2 * 1000 << " ps per byte." << std::endl;

    std::cout << "Difference per ping pong is " << (thread_time_delta - solo_time_delta).count () / loops << " ns." << std::endl;

    return (0);
}
