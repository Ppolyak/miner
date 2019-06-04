#pragma once

class Game
{
public:
	Game();
	void Draw();
	void DrawGameOver(const char *text, int x);
	enum { FIELD_WIDTH = 15, FIELD_HEIGHT =15  };
	enum State { CLOSED, OPENED, FLAG };
	enum StateGame { PLAY, GAME_OVER, WIN };
	StateGame stateGame;
	static const int NUMBER_OF_MINES = 40;
	int points = 0;
	unsigned int startTime;
	unsigned int endTime;
	struct Cell
	{
		State state;
		bool HasMine;
		int MinesAround;
	};
	Cell Field[FIELD_WIDTH][FIELD_HEIGHT];
	void Open(int x, int y);
	void Mark(int x, int y);
	void OpenEmptyCells(int x, int y);
};