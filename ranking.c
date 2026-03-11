#include "ranking.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void SaveScore(int score) {
    RankEntry rankings[MAX_RANKING_COUNT];
    int count = 0;
    
    // 读取现有排名
    FILE *file = fopen(RANKING_FILE, "rb");
    if (file) {
        count = fread(rankings, sizeof(RankEntry), MAX_RANKING_COUNT, file);
        fclose(file);
    }
    
    // 获取当前时间
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char dateStr[20];
    strftime(dateStr, 20, "%Y-%m-%d %H:%M", tm_info);
    
    // 插入新分数
    int inserted = 0;
    if (count < MAX_RANKING_COUNT) {
        rankings[count].score = score;
        strcpy(rankings[count].date, dateStr);
        count++;
        inserted = 1;
    } else if (score > rankings[MAX_RANKING_COUNT - 1].score) {
        rankings[MAX_RANKING_COUNT - 1].score = score;
        strcpy(rankings[MAX_RANKING_COUNT - 1].date, dateStr);
        inserted = 1;
    }
    
    if (inserted) {
        // 排序 (简单冒泡排序)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (rankings[j].score < rankings[j + 1].score) {
                    RankEntry temp = rankings[j];
                    rankings[j] = rankings[j + 1];
                    rankings[j + 1] = temp;
                }
            }
        }
        
        // 写回文件
        file = fopen(RANKING_FILE, "wb");
        if (file) {
            fwrite(rankings, sizeof(RankEntry), count, file);
            fclose(file);
        }
    }
}

void ShowRankings() {
    system("cls");
    RankEntry rankings[MAX_RANKING_COUNT];
    int count = 0;
    
    FILE *file = fopen(RANKING_FILE, "rb");
    if (file) {
        count = fread(rankings, sizeof(RankEntry), MAX_RANKING_COUNT, file);
        fclose(file);
    }
    
    GotoXY(40, 5);
    printf("=== 积分排行榜 (Top %d) ===", MAX_RANKING_COUNT);
    
    if (count == 0) {
        GotoXY(43, 8);
        printf("暂无排名数据");
    } else {
        GotoXY(35, 7);
        printf("%-6s %-10s %-20s", "排名", "得分", "日期");
        for (int i = 0; i < count; i++) {
            GotoXY(35, 8 + i);
            printf("%-6d %-10d %-20s", i + 1, rankings[i].score, rankings[i].date);
        }
    }
    
    GotoXY(40, 22);
    printf("按任意键返回主菜单...");
    getch();
    system("cls");
}
