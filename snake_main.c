#include "snake.h"
#include <locale.h>
#include <windows.h>

int main()
{  
   
    setlocale(LC_ALL, "");     // 设置本地化以支持中文显示
    srand((unsigned int)time(0)); // 使用当前时间作为随机数生成的种子
    int end = 1;                  // 定义一个变量用于控制游戏循环
    int choice;                   // 定义一个变量用于存储用户的选择
    while (end)
    {                        // 游戏循环
        choice = InitMenu(); // 显示菜单并获取用户选择
        switch (choice)
        { // 根据用户选择执行相应的操作
        case 1:
            // 开始游戏
            system("cls");  // 清屏，移除菜单文字
            InitMap();      // 初始化游戏地图
            InitSnake();    // 初始化蛇
            // 生成障碍物（放在蛇初始化后以避免冲突）
            GenerateObstacles();
            GenerateFood(); // 生成食物
            while (MoveSnake()); // 移动蛇，直到游戏结束
            GameOver();          // 显示游戏结束信息
            break;
        case 2:
            // 显示帮助
            Helper();
            break;
        case 3:
            // 显示关于
            About();
            break;
        case 0:
            // 退出游戏
            end = 0;
            break;
        }
    }
    return 0;
}