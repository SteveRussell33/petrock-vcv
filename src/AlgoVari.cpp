#include "AlgoVari.h"
#include "jfunc.h"

void AlgoVari::init()
{
    /*

    if(weekday==0)
    {
        maxRepeats=8;
    } else {
        maxRepeats=weekday;
    }

    */

    switch (cyclePos)
    {
    case 0:
        seqMax = jrandom(3, 19 + 1);
        maxRepeats = 3;
        break;

    case 1:
    case 7:
        seqMax = jrandom(8, 12 + 1);
        maxRepeats = jrandom(3, 7);
        break;

    case 2:
    case 6:
        seqMax = 8;

        if (ID == 1)
        {
            maxRepeats = 4;
        }

        if (ID == 2)
        {
            maxRepeats = 8;
        }

        break;

    case 3:
        seqMax = 16;
        maxRepeats = 4;
        break;

    case 5:
        seqMax = 16;
        maxRepeats = 4;
        break;

    case 4:
        seqMax = 12;
        maxRepeats = 3;
        break;
    }

    // seqMax=6;
    // maxRepeats=5;

    for (int i = 0; i < seqMax; i++)
    {
        int val = jrandom(2);
        seqA[i] = val;
        seqB[i] = val;
    }

    // shuffle seqB

    for (int i = seqMax - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        // Swap the elements at indices i and j
        int temp = seqB[i];
        seqB[i] = seqB[j];
        seqB[j] = temp;
    }

    // curseq=seqA
    for (int i = 0; i < seqMax; i++)
    {
        curSeq[i] = seqA[i];
    }

    // for (int i = 0; i < seqMax; i++)
    // {
    //     printf("%d ", seqA[i]);
    // }
    // printf("sep\n");

    // for(int i=0; i<seqMax; i++){printf("%d ",seqB[i]);}
}

bool AlgoVari::shouldPlayGate()
{
    bool result = curSeq[seqInd] == 1;
    seqInd++;

    // Sequence is reset
    if (seqInd > seqMax - 1)
    {
        seqInd = 0;

        if (!bPlaying)
        {
            repeats++;

            // -1 is index compensation
            // other minus 1 is so that its one beat before the beat, so if max repeats =4, then you get 3 bars a, 1 bar b
            // nvm pretty sure-1 is actually right

            if (repeats == maxRepeats - 1)
            {
                // curSeq=seqB;
                for (int i = 0; i < seqMax; i++)
                {
                    curSeq[i] = seqB[i];
                }
                bPlaying = true;
            }

            // b playing
        }
        else
        {
            // curSeq=seqA;
            for (int i = 0; i < seqMax; i++)
            {
                curSeq[i] = seqA[i];
            }

            bPlaying = false;
            repeats = 0;

            isResetLightOn = true;
        }
    }

    return result;
}