#include <iostream>

class Judge
{
public:
	int GetMaxScore(bool Player);
	bool JudgeWin(bool Player);
	void FreshScore(int Board[15][15], int* input, bool Black);

private:
	int score[15][15][2][4] = { 0 }; //15x15:chess board size, 2 players: black, white, 4 directions: | - \ /
	void AddScore(int Player, int i, int j, int Board[15][15]);
	int AddScoreDirection(int Player, int i, int j, int Board[15][15], int d_x, int d_y);
	bool IsPlayer(int, bool);
	
};

class chess
{
public:
	void PrintBoard();
	
	void PlayGame();
	chess();

private:
	int Board[15][15];
	bool Player;
	Judge judge;
	void ChangePlayer();
	int GetPlayerId();
	void UpdateBoard(int*);
	void DealLatest();
	bool GetInput();
	bool CheckBoard(int*);
};

