#include "snake.h"

int main()
{
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
            InitMap();      // 初始化游戏地图
            InitSnake();    // 初始化蛇
            GenerateFood(); // 生成食物
            while (MoveSnake() )
                ;

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