#ifndef RANKING_H
#define RANKING_H

#define MAX_RANKING_COUNT 10
#define RANKING_FILE "rankings.dat"

typedef struct {
    int score;
    char date[20];
} RankEntry;

void SaveScore(int score);
void ShowRankings();

#endif
