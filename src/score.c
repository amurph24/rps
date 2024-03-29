#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SCORECOUNT 2
#define SCOREFILE_PATH "/var/lib/rps/score.txt"

void read_scores(int* player_score, int* computer_score) {
    FILE *fp = fopen(SCOREFILE_PATH, "r");
    const char s[3] = ", ";
    char *token;
    int count = 0;
    int *scores = (int*) malloc(sizeof(int)*SCORECOUNT);
    // TODO: condense conditional
    if (fp != NULL)
    {
        char line[40];
        fgets(line, sizeof(line), fp);
        token = strtok(line, s);
        while (token != NULL)
        {
            *scores = atoi(token);
            scores++; count++;
            token = strtok(NULL, s);
        }
        scores -= count;
    } else {
        *scores = 0;
        *(scores + 1) = 0;
        fopen(SCOREFILE_PATH, "a");
    }

    *player_score = *scores;
    *computer_score = *(scores+1);
    free(scores);

    return;
}

int write_scores(int* player_score, int* computer_score) {
    FILE *fp = fopen(SCOREFILE_PATH, "r+");
    if (fp) {
        fprintf(fp, "%d, %d", *player_score, *computer_score);
    } else {
        printf("scores could not be saved, sorry\n");
        printf("errno: %s\n", strerror(errno));
    }
    return 0;
}