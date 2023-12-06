#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

volatile bool startBoth = false;
volatile bool finishedT1 = false;
volatile bool finishedT2 = false;

volatile bool X = false;
volatile bool Y = false;

volatile bool sawTrueY = false;
volatile bool sawTrueX = false;

void *ThreadOne (void *)
{
  while (true)
  {
    while (!startBoth) { };

    // X = 1
    X = true;
    // READ Y
    sawTrueY = Y;

    finishedT1 = true;
    while (startBoth) { };
    finishedT1 = false;
  }
}

void *ThreadTwo (void *)
{
  while (true)
  {
    while (!startBoth) { };

    // Y = 1
    Y = true;
    // READ X
    sawTrueX = X;

    finishedT2 = true;
    while (startBoth) { };
    finishedT2 = false;
  }
}

int main (int iArgC, char *apArgV [])
{
  pthread_t oThreadOne, oThreadTwo;

  pthread_create (&oThreadOne, NULL, ThreadOne, NULL);
  pthread_create (&oThreadTwo, NULL, ThreadTwo, NULL);

  int countT1Faster = 0;
  int countT2Faster = 0;
  int countImpossible = 0;

  while (true)
  {
    X = false;
    Y = false;
    startBoth = true;
    while (!finishedT1) { };
    while (!finishedT2) { };
    if (!sawTrueY && !sawTrueX) countImpossible ++;
    else
    {
      countT1Faster += sawTrueX;
      countT2Faster += sawTrueY;
    };
    if ((countT1Faster + countT2Faster + countImpossible) % 1000 == 0)
    {
      printf ("T1 faster %d times - T2 faster %d times - Impossible result %d times.\n", countT1Faster, countT2Faster, countImpossible);
    }
    startBoth = false;
    while (finishedT1) { };
    while (finishedT2) { };
  }
}
