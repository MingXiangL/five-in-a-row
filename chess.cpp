#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "chess.h"
#include <stdint.h>
#include <stdio.h>
chess::chess()
{
//	init chess board

	int i, j; //i＝行，j＝列

	this->Board[0][0] = 1;
	this->Board[0][14] = 2;
	this->Board[14][14] = 3;
	this->Board[14][0] = 4;

	for (i = 1; i <= 13; i++)
	{
		this->Board[i][0] = 5;
	}

	for (i = 1; i <= 13; i++)
	{
		this->Board[i][14] = 7;
	}

	for (j = 1; j <= 13; j++)
	{
		this->Board[0][j] = 6;
	}
	for (j = 1; j <= 13; j++)
	{
		this->Board[14][j] = 8;
	}

	for (i = 1; i <= 13; i++)
	{
		for (j = 1; j <= 13; j++)
		{
			this->Board[i][j] = 9;
		}
	}
// init Players
	this->Player = true; // true->black, false->white

}

void chess::PrintBoard()
{
	int i, j;
	system("cls");
	for (i = 0; i <= 14; i++)
	{
		printf("%3d ", 15-i);
		for (j = 0; j <= 14; j++)
		{
			switch (this->Board[i][j] % 100)//%100为了适应将来有分值的情形
			{
			case 1:
				printf("┏ ");
				break;	   
						   
			case 2:		   
				printf(" ┓ ");
				break;	   
						   
			case 3:		   
				printf(" ┛ ");
				break;	   
						   
			case 4:		   
				printf("┗ ");
				break;	   
						   
			case 5:		   
				printf("┠ ");
				break;	   
						   
			case 6:		   
				printf(" ┯ ");
				break;	   
						   
			case 7:		   
				printf(" ┨ ");
				break;	    
						    
			case 8:		    
				printf(" ┷ ");
				break;	    
						    
			case 9:		    
				printf(" ┼ ");
				break;	    
						    
			case 10:
				if (j == 0)
					printf("●");
				else
					printf(" ●");
				break;	    
						    
			case 11:	
				if (j == 0)
					printf("▲");
				else
					printf(" ▲");
				break;	    
						    
			case 20:	    
				if (j == 0)
					printf("◎");
				else
					printf(" ◎");
				break;	    
						    
			case 21:	
				if (j == 0)
					printf("△");
				else
					printf(" △");
				break;
			}
			if (j == 14)
			{
				printf("\n");
			}
		}
	}
	printf("  ");
	for (j = 0; j <= 14; j++)
	{
		int C = 'A';
		printf("  ");
		printf("%c", C+j);
	}
	printf("\n");

}

bool chess::GetInput()
{
	int tmp[2], tmp_t[2], tmp_ex;
	char y;
	bool stop = false;
	bool BadPoint;
	bool PlayerWin = false;
	bool input_correct = true;
	while (true)
	{
		this->PrintBoard();
		if (!input_correct)
			std::cout << "输入错误，第1位请输入A-O，第2位请输入1-15，停止请输入\"!16\"" << std::endl;

		std::cout << "请落" << (this->Player? "黑子" : "白子") << "\n" << std::endl;
		scanf("%c %d", &y, &tmp[0]);
		tmp_t[0] = int(y);
		tmp_t[1] = tmp[0];
		tmp[1] = int(y);

		if (tmp_t[0] == int('!') && tmp_t[1] == 16)
		{
			stop = true;
			break;
		}

		tmp[0] -= 1;
		if (tmp[1] >= 97 && tmp[1] <= 122)
			tmp[1] -= ('a' - 'A');
		input_correct = (tmp[0] >= 0 && tmp[0] <= 14) & (tmp[1] >= 'A' && tmp[1] <= 'O');
		if (input_correct)
		{
			tmp[1] -= 'A';
			tmp[0] = 14 - tmp[0];
			BadPoint = this->CheckBoard(tmp);
			if (BadPoint)
			{
				printf("位置%c%d已有落子，请选择其他位置！\n", tmp_t[0], tmp_t[1]);
			}
			else
				break;
		}
	}
	if (!stop)
	{
		this->UpdateBoard(tmp);
		this->judge.FreshScore(this->Board, tmp, this->Player);
	}
	return stop;
}

void chess::ChangePlayer()
{
	this->Player = !this->Player;
}

int chess::GetPlayerId()
{
	return this->Player;
}

void chess::UpdateBoard(int* input)
{
	this->DealLatest();
	this->Board[input[0]][input[1]] = this->Player ? 21 : 11;	
	
}

void chess::DealLatest()
{
	int i, j;
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			if (this->Board[i][j] == 11 || this->Board[i][j] == 21)
				this->Board[i][j] -= 1;
		}
	}
}

void chess::PlayGame()
{
	std::cout << "游戏开始\n" << std::endl;
	this->Player = true;
	bool stop, PlayerWin;
	do
	{
		stop = this->GetInput();
		PlayerWin = this->judge.JudgeWin(this->Player);
		if (PlayerWin)
		{
			this->PrintBoard();
			std::cout << (this->Player ? "黑方" : "白方") << "获胜！\n" << std::endl;
			stop = true;
			
		}
		this->ChangePlayer();
	} while (!stop);
	
}

bool chess::CheckBoard(int* input)
{
	return (this->Board[input[0]][input[1]] == 10) || (this->Board[input[0]][input[1]] == 11) \
		|| (this->Board[input[0]][input[1]] == 20) || (this->Board[input[0]][input[1]] == 21);
}

void Judge::FreshScore(int Board[15][15], int* input, bool Black)
{
	int i = input[0], j = input[1];
	this->AddScore(Black, i, j, Board);
}

void Judge::AddScore(bool Player, int i, int j, int Board[15][15])
{
	this->score[i][j][Player][0] = this->AddScoreDirection(Player, i, j, Board, -1, 0) + this->AddScoreDirection(Player, i, j, Board, 1, 0) -1;
	this->score[i][j][Player][1] = this->AddScoreDirection(Player, i, j, Board, 0, -1) + this->AddScoreDirection(Player, i, j, Board, 0, 1) -1;
	this->score[i][j][Player][2] = this->AddScoreDirection(Player, i, j, Board, -1, -1) + this->AddScoreDirection(Player, i, j, Board, 1, 1) - 1;
	this->score[i][j][Player][3] = this->AddScoreDirection(Player, i, j, Board, -1, 1) + this->AddScoreDirection(Player, i, j, Board, 1, -1) - 1;
}

int Judge::AddScoreDirection(int Player, int i, int j, int Board[15][15], int d_i, int d_j)
{
	int count;
	bool extreme = (i + d_i < 0) | (i + d_i > 14) | (j + d_j < 0) | (j + d_j > 14);
	if (this->IsPlayer(Board[i][j], Player))
		count = 1;
	else
		return 0;

	if (!extreme && this->IsPlayer(Board[i + d_i][j + d_j], Player))
		count += this->AddScoreDirection(Player, i + d_i, j + d_j, Board, d_i, d_j);
	
	return count;
}

bool Judge::IsPlayer(int member, bool Black)
{
	if (!Black)
		return member == 11 || member == 10;
	else
		return member == 21 || member == 20;
}

int Judge::GetMaxScore(bool Player)
{
	int max_score = 0;
	for (int i = 0; i <= 14; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			for (int k = 0; k <= 3; k++)
			{
				if (this->score[i][j][Player][k] > max_score)
					max_score = this->score[i][j][Player][k];
			}
		}
	}
	return max_score;
}

bool Judge::JudgeWin(bool Player)
{
	int player_score = this->GetMaxScore(Player);
		if (player_score >= 5)
		return true;
	else
		return false;
}

