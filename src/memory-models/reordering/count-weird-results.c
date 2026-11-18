#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

atomic_bool startBoth = false;
atomic_bool finishedT1 = false;
atomic_bool finishedT2 = false;

atomic_bool X = false;
atomic_bool Y = false;

atomic_bool sawTrueY = false;
atomic_bool sawTrueX = false;

void *ThreadOne (void *)
{
    while (true)
    {
        while (!atomic_load (&startBoth)) { }

        // X = 1
        atomic_store_explicit (&X, true, memory_order_relaxed);
        // READ Y
        atomic_store (&sawTrueY, atomic_load_explicit (&Y, memory_order_relaxed));

        atomic_store (&finishedT1, true);
        while (atomic_load (&startBoth)) { }
        atomic_store (&finishedT1, false);
    }
}

void *ThreadTwo (void *)
{
    while (true)
    {
        while (!atomic_load (&startBoth)) { }

        // Y = 1
        atomic_store_explicit (&Y, true, memory_order_relaxed);
        // READ X
        atomic_store (&sawTrueX, atomic_load_explicit (&X, memory_order_relaxed));

        atomic_store (&finishedT2, true);
        while (atomic_load (&startBoth)) { }
        atomic_store (&finishedT2, false);
    }
}

int main (void)
{
    pthread_t oThreadOne, oThreadTwo;

    pthread_create (&oThreadOne, NULL, ThreadOne, NULL);
    pthread_create (&oThreadTwo, NULL, ThreadTwo, NULL);

    int countT1Faster = 0;
    int countT2Faster = 0;
    int countImpossible = 0;

    while (true)
    {
        atomic_store (&X, false);
        atomic_store (&Y, false);
        atomic_store (&startBoth, true);
        while (!atomic_load (&finishedT1)) { }
        while (!atomic_load (&finishedT2)) { }

        bool readY = atomic_load (&sawTrueY);
        bool readX = atomic_load (&sawTrueX);
        if (!readY && !readX) countImpossible ++;
        else
        {
            countT1Faster += readX;
            countT2Faster += readY;
        }
        if ((countT1Faster + countT2Faster + countImpossible) % 1000 == 0)
        {
            printf ("T1 faster %d times - T2 faster %d times - Impossible result %d times.\n", countT1Faster, countT2Faster, countImpossible);
        }
        atomic_store (&startBoth, false);
        while (atomic_load (&finishedT1)) { }
        while (atomic_load (&finishedT2)) { }
    }
}
