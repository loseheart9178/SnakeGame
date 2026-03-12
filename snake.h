#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// 定义游戏相关的常量
#define MAP_HEIGHT 20                             // 定义地图高度
#define MAP_WIDTH 40                              // 定义地图宽度
#define UP 'w'                                    // 定义向上移动的按键
#define DOWN 's'                                  // 定义向下移动的按键
#define LEFT 'a'                                  // 定义向左移动的按键
#define RIGHT 'd'                                 // 定义向右移动的按键
#define INITIAL_SNAKE_LENGTH 3                    // 定义初始蛇的长度
#define Max_SNAKE_LENGTH (MAP_HEIGHT * MAP_WIDTH) // 定义蛇的最大长度为地图面积
#define B_FOOD_CHAR '*'                            // 定义B级食物的显示字符
#define A_FOOD_CHAR 'x'                            // 定义A级食物的显示字符
#define S_FOOD_CHAR '$'                            // 定义S级食物的显示字符
#define SSR_FOOD_CHAR '?'                           // 定义SSR级食物的显示字符

#define SNAKE_HEAD_CHAR '@' // 定义蛇头的显示字符
#define SNAKE_BODY_CHAR 'o' // 定义蛇身的显示字符
#define MAP_CHAR '|'        // 定义地图的显示字符`

#define MAX_RANKING_COUNT 10
#define RANKING_FILE "rankings.txt"

// 障碍物相关
#define OBSTACLE_CHAR '#' // 定义障碍物的显示字符
#define OBSTACLE_COUNT 10 // 定义地图中障碍物数量

// 定义游戏相关的结构体
typedef struct SnakeNode
{
    int x;
    int y;
    struct SnakeNode *prev;
    struct SnakeNode *next;
} SnakeNode;

typedef struct
{
    int x;
    int y;
    int value; // 价值不同，得分不同
} Food;

// 障碍物结构体
typedef struct
{
    int x;
    int y;
} Obstacle;

typedef struct
{
    SnakeNode *head;   // 指向蛇头的指针
    SnakeNode *tail;   // 指向蛇尾的指针
    int length;        // 蛇的长度
    int speed;         // 蛇的速度
    int pendingGrowth; // 额外未消耗的增长次数（用于特殊食物）
} Snake;

typedef struct {
    int score;
    char date[20];
} RankEntry;

// 定义游戏相关的函数
void GotoXY(int x, int y); // 定义函数用于设置光标位置
void HideCursor();         // 定义函数用于隐藏光标
int InitMenu();            // 定义函数用于显示菜单并获取用户选择
void Helper();             // 定义函数用于显示帮助信息

// 更新帮助文本以说明特殊食物
void About();             // 定义函数用于显示关于信息
void InitMap();           // 定义函数用于绘制游戏地图
void InitSnake();         // 定义函数用于初始化蛇
int MoveSnake();          // 定义函数用于移动蛇
void GenerateFood();      // 定义函数用于生成食物
void GenerateObstacles(); // 定义函数用于生成障碍物

SnakeNode *CheckCollision();         // 定义函数用于检查碰撞
int IsPositionBlocked(int x, int y); // 检查坐标是否为障碍或蛇身

void SpeedControl(); // 定义函数用于控制蛇的速度
void FreeSnake();    // 定义函数用于释放蛇的内存
void GameOver();     // 定义函数用于显示游戏结束信息
void SaveScore(int score);
void ShowRankings();
