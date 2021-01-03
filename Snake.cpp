#include "Snake.h"
#include <Windows.h>
#include <conio.h>
#include <time.h>
Snake::Snake()
{
	body = std::queue<Body>();
	flag = 'd';
	head = Body(BOARD_SIZE / 2, BOARD_SIZE / 2);
	size = 1;
	addflag = false;
	speed = GAME_SPEED;
}
/*
 * 控制蛇移动
 */
void Snake::move()
{
	// 获取蛇头坐标
	int x = head.x;
	int y = head.y;
	// 获取下帧蛇头位置
	switch (flag)
	{
	case 'd':
		x++;
		break;
	case 'a':
		x--;
		break;
	case 'w':
		y--;
		break;
	case 's':
		y++;
		break;
	default:
		break;
	}
	// 生成新蛇头
	body.push(head);
	head = Body(x, y);
	// 判断蛇身是否进食增长
	if (addflag)
		addflag = false;
	else
		body.pop();
}

/*
 * @param char ch 用户输入wasd之一
 * @调整蛇头方向
 */
void Snake::turn(const char ch)
{
	if (ch != 'w'&&ch != 'a'&&ch != 'd'&&ch != 's')
		return;
	if (ch == 'w'&&flag == 's')
		return;
	if (ch == 's'&&flag == 'w')
		return;
	if (ch == 'a'&&flag == 'd')
		return;
	if (ch == 'd'&&flag == 'a')
		return;
	flag = ch;
}
/*
 * 进食同时加速
 */
void Snake::eat()
{
	addflag = true;
	size++;
	speed = GAME_SPEED + size * 10;
}

Game::Game()
{
	srand((unsigned)time(NULL));
	creatFood();
	speed = GAME_SPEED;
	over = false;
	memset(gameboard, ' ', BOARD_SIZE*BOARD_SIZE);
}
/*
 * 游戏主循环
 */
void Game::mainLoop()
{
	while (!over)
	{
		// 非阻塞输入
		if(_kbhit())
			turn(_getch());
		move();
		memset(gameboard, ' ', BOARD_SIZE*BOARD_SIZE);
		isImpact();
		system("cls"); // 清除上一帧内容
		display();
		Sleep(speed);
	}
}
/*
 * 生成新食物
 */
void Game::creatFood()
{
	int x = rand() % (BOARD_SIZE - 1);
	int y = rand() % (BOARD_SIZE - 1);
	food = Body(x, y);
}
/*
 * 进食，碰撞检测
 */
void Game::isImpact()
{
	// 检测进食
	if (head.x == food.x&&head.y == food.y)
	{
		eat();
		creatFood();
		addflag = true;
	}
	// 检测撞墙
	if (head.x == BOARD_SIZE - 1 || head.y == BOARD_SIZE - 1||head.x == -1||head.y==-1)
		over = true;
	int len = body.size();
	// 检测撞到身子
	for (int i = 0; i < len; i++)
	{
		Body b = body.front();
		gameboard[b.y][b.x] = '*';// 将蛇身放入
		if (head.x == b.x&&head.y == b.y)
			over = true;
		body.pop();
		body.push(b);
	}
}
/*
 * 渲染游戏画面
 */
void Game::display()
{
	gameboard[food.y][food.x] = '0';
	gameboard[head.y][head.x] = '#';
	for (int i = 0; i < BOARD_SIZE-1; i++)
	{
		for (int j = 0; j < BOARD_SIZE-1; j++)
			printf("%c", gameboard[i][j]);
		printf("\n");
	}
	for (int i = 0; i < BOARD_SIZE; i++)
		printf("#");
}