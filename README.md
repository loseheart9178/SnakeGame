# SnakeGame

一个基于 C 语言的控制台贪吃蛇小游戏，支持：
- 普通食物与特殊食物
- 障碍物
- 游戏结束结算
- 积分排行榜（Top 10）

## 环境要求

请确保本机已安装并配置以下工具：
- GCC（建议 MinGW-w64）
- GDB
- VS Code（已安装 C/C++ 扩展）

## Windows 快速准备

1. 安装 MinGW-w64。
2. 将 MinGW 的 `bin` 目录加入系统 PATH。
3. 在终端验证：

```powershell
gcc --version
gdb --version
```

若命令可执行，说明环境配置成功。

## 运行方式

### 方式一：VS Code（推荐）

1. 打开本项目根目录。
2. 运行默认生成任务：`C/C++: gcc.exe 生成活动文件`。
3. 生成后运行：
   - 调试启动配置：`(gdb) 启动`，或
   - 直接执行 `run.bat`。

### 方式二：命令行

在项目根目录执行：

```powershell
gcc -fdiagnostics-color=always -finput-charset=utf-8 -fexec-charset=GBK -g *.c -o snake.exe
.\snake.exe
```

说明：项目中的 VS Code 任务已配置为默认编译全部 `.c` 源文件，新增源文件后通常无需再手动修改任务参数。

## 排行榜说明

- 排行榜文件为 `rankings.txt`（在程序运行目录生成）。
- 每局结束会尝试写入排行榜。
- 仅保留 Top 10 高分；当已满 10 条时，只有新分数高于当前第 10 名才会更新。
- `rankings.txt` 属于运行时数据，已在 `.gitignore` 中忽略，不建议提交到仓库。

## 仓库提交说明

- 已建议提交以下 VS Code 配置文件（便于他人拉取后直接构建/调试）：
   - `.vscode/tasks.json`
   - `.vscode/launch.json`
- `.gitignore` 已配置为：忽略 `.vscode` 目录下其他文件，仅放行上述两个 JSON 文件。

## 常见问题

### 1) 提示 `undefined reference to SaveScore`

原因：未使用项目根目录的一体化源码进行编译，或编译命令未包含 `snake.c`。

解决：使用 README 中的完整编译命令，或直接执行 VS Code 默认构建任务。

### 2) VS Code 可以编译，命令行不行

原因：终端 PATH 未生效或未重启。

解决：重开终端后再次执行 `gcc --version`、`gdb --version` 检查。
