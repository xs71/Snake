#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <queue>
#include "config.h"
typedef struct Body
{
	int x;
	int y;
	Body() {};
	Body(int x, int y) :x(x), y(y) {};
}Body,Food;
/*
 * 贪吃蛇类
 */
class Snake
{
public:
	Snake();
protected:
		void move();
		void turn(const char flag);
		void eat();
		std::queue<Body> body;	// 蛇身队列
		Body head;				// 蛇头
		char flag;				// 运动方向
		bool addflag;			// 进食标记
		int size;				// 蛇身长度
		int speed;				// 移动速度
};
/*
 * 游戏棋盘类
 */
class Game:public Snake
{
	public:
		Game();
		void mainLoop();

	private:
		void creatFood();
		void isImpact();
		void display();
		Food food;//食物
		bool over;//结束标记
		char gameboard[BOARD_SIZE][BOARD_SIZE];//棋盘
};
#endif // !

