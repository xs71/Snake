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
 * �������ƶ�
 */
void Snake::move()
{
	// ��ȡ��ͷ����
	int x = head.x;
	int y = head.y;
	// ��ȡ��֡��ͷλ��
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
	// ��������ͷ
	body.push(head);
	head = Body(x, y);
	// �ж������Ƿ��ʳ����
	if (addflag)
		addflag = false;
	else
		body.pop();
}

/*
 * @param char ch �û�����wasd֮һ
 * @������ͷ����
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
 * ��ʳͬʱ����
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
 * ��Ϸ��ѭ��
 */
void Game::mainLoop()
{
	while (!over)
	{
		// ����������
		if(_kbhit())
			turn(_getch());
		move();
		memset(gameboard, ' ', BOARD_SIZE*BOARD_SIZE);
		isImpact();
		system("cls"); // �����һ֡����
		display();
		Sleep(speed);
	}
}
/*
 * ������ʳ��
 */
void Game::creatFood()
{
	int x = rand() % (BOARD_SIZE - 1);
	int y = rand() % (BOARD_SIZE - 1);
	food = Body(x, y);
}
/*
 * ��ʳ����ײ���
 */
void Game::isImpact()
{
	// ����ʳ
	if (head.x == food.x&&head.y == food.y)
	{
		eat();
		creatFood();
		addflag = true;
	}
	// ���ײǽ
	if (head.x == BOARD_SIZE - 1 || head.y == BOARD_SIZE - 1||head.x == -1||head.y==-1)
		over = true;
	int len = body.size();
	// ���ײ������
	for (int i = 0; i < len; i++)
	{
		Body b = body.front();
		gameboard[b.y][b.x] = '*';// ���������
		if (head.x == b.x&&head.y == b.y)
			over = true;
		body.pop();
		body.push(b);
	}
}
/*
 * ��Ⱦ��Ϸ����
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