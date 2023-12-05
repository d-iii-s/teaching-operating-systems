#include <chrono>
#include <random>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>


// Experiment dimensions

int loops = 16;
size_t step = 16;
size_t count = 1024*1024;

// Global area to avoid optimization.

void **area = NULL;


// Memory area walk functions

void **do_mem_alloc () {
    auto chain = new size_t [count];
    for (size_t index = 0 ; index < count ; index ++) {
        chain [index] = index;
    }
    auto generator = std::default_random_engine ();
    std::shuffle (chain, chain + count, generator);
    uintptr_t block = (uintptr_t) malloc (step * count);
    void **current = (void **) (block + chain [count - 1] * step);
    for (size_t index = 0 ; index < count ; index ++) {
        uintptr_t follows = block + chain [index] * step;
        (*current) = (void *) (follows);
        current = (void **) follows;
    }
    delete [] chain;
    return (void **) (block);
}

void **do_mem_walk (void **area) {
    void **current = area;
    for (size_t index = 0 ; index < count ; index ++) {
        current = (void **) (*current);
    }
    return (current);
}


int main (int argc, char *argv []) {
    if (argc == 4) {
        // Number of times to iterate over memory area.
        loops = std::atoi (argv [1]);
        assert (loops > 0);
        // Size of memory area to iterate over.
        count = std::atoi (argv [2]);
        assert (count > 0);
        // Step size to use.
        step = std::atoi (argv [3]);
        assert (step >= sizeof (void *));
    }

    // Beautiful output :-) ...
    std::cout << std::fixed << std::setprecision (0);

    // Initialize the memory chain.
    area = do_mem_alloc ();

    // Perform single thread measurement.
    auto solo_time_before = std::chrono::steady_clock::now ();
    for (int i = 0 ; i < loops ; i ++) {
        area = do_mem_walk (area);
    }
    auto solo_time_after = std::chrono::steady_clock::now ();
    auto solo_time_delta = std::chrono::duration <double, std::nano> (solo_time_after - solo_time_before);;

    std::cout << "Solo time is " << solo_time_delta.count () << " ns, " << solo_time_delta.count () / loops / count * sizeof (void *) * 1000 << " ps per byte." << std::endl;

    return (0);
}
