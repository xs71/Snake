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
 * ̰������
 */
class Snake
{
public:
	Snake();
protected:
		void move();
		void turn(const char flag);
		void eat();
		std::queue<Body> body;	// �������
		Body head;				// ��ͷ
		char flag;				// �˶�����
		bool addflag;			// ��ʳ���
		int size;				// ������
		int speed;				// �ƶ��ٶ�
};
/*
 * ��Ϸ������
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
		Food food;//ʳ��
		bool over;//�������
		char gameboard[BOARD_SIZE][BOARD_SIZE];//����
};
#endif // !

