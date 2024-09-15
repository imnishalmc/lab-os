#include <stdio.h>

int search(int key, int frame_items[], int frame_occupied)
{
    for (int i = 0; i < frame_occupied; i++)
        if (frame_items[i] == key)
            return 1;
    return 0;
}

void printOuterStructure(int max_frames)
{
    printf("Stream ");
    for (int i = 0; i < max_frames; i++)
        printf("\t\tFrame%d ", i + 1);
}

void printCurrFrames(int item, int frame_items[], int frame_occupied, int max_frames)
{
    printf("\n%d \t\t", item);
    for (int i = 0; i < max_frames; i++)
    {
        if (i < frame_occupied)
            printf("%d \t\t", frame_items[i]);
        else
            printf("- \t\t");
    }
}

int predict(int ref_str[], int frame_items[], int refStrLen, int index, int frame_occupied)
{
    int result = 0, farthest = index;
    for (int i = 0; i < frame_occupied; i++)
    {
        int j;
        for (j = index; j < refStrLen; j++)
        {
            if (frame_items[i] == ref_str[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == refStrLen)
            return i;
    }
    return result;
}

void optimalPage(int ref_str[], int refStrLen, int frame_items[], int max_frames)
{
    int frame_occupied = 0;
    printOuterStructure(max_frames);
    int hits = 0;
    for (int i = 0; i < refStrLen; i++)
    {
        if (search(ref_str[i], frame_items, frame_occupied))
        {
            hits++;
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
            continue;
        }
        if (frame_occupied < max_frames)
        {
            frame_items[frame_occupied] = ref_str[i];
            frame_occupied++;
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
        }
        else
        {
            int pos = predict(ref_str, frame_items, refStrLen, i + 1, frame_occupied);
            frame_items[pos] = ref_str[i];
            printCurrFrames(ref_str[i], frame_items, frame_occupied, max_frames);
        }
    }
    printf("\n\nHits: %d\n", hits);
    printf("Misses: %d", refStrLen - hits);
}

int main()
{
    printf("lab 7.2(optimal page refreshment algorithm:)\n");
    printf("Name:Nisha Lamichhane\n");
    printf("Roll no:21 \t\t\t section:'A:\n");
    int ref_str[] = {9, 5, 1, 2, 6, 3, 2, 3, 2, 3, 0, 9, 2, 1, 2, 0, 5, 8, 0, 1};
    int refStrLen = sizeof(ref_str) / sizeof(ref_str[0]);
    int max_frames = 4;
    int frame_items[max_frames];

    optimalPage(ref_str, refStrLen, frame_items, max_frames);
    return 0;
}