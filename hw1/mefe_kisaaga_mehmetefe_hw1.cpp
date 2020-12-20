// Mehmet Efe Kisaaga		25255		mefe@sabanciuniv.edu		CS 300 - HW1

#include <iostream>
#include <vector>
#include "stack.h"
#include "stack.cpp"
#include "randgen.h"
#include <string>
#include <fstream>

using namespace std;

struct cell { // cell to keep coordiantes, broken down walls and visiteing situation
	int y;
	int x;

	bool isVisited;

	int lWall;
	int rWall;
	int uWall;
	int dWall;

	~cell() {};
	cell() {};
	cell(int y, int x) : y(y), x(x) {
		lWall = 1;
		rWall = 1;
		uWall = 1;
		dWall = 1;
		isVisited = false;
	};
};

Stack<cell> stack;

string findWay(cell c, vector<vector<cell>> m) { // eleminate unavailable directions and select random one proper direction
	RandGen rand;
	vector<string> dir;
	if (c.y + 1 < m.size() && !m[c.y + 1][c.x].isVisited)//up
	{
		dir.push_back("up");
	}
	if (c.y - 1 > 0 && !m[c.y - 1][c.x].isVisited)//down
	{
		dir.push_back("down");
	}
	if (c.x + 1 < m[0].size() && !m[c.y][c.x + 1].isVisited)//right
	{
		dir.push_back("right");
	}
	if (c.x - 1 > 0 && !m[c.y][c.x - 1].isVisited)//left
	{
		dir.push_back("left");
	}
	if (dir.size() == 0)
		return "NA";
	int index = rand.RandInt(0, dir.size() - 1);
	return dir[index];
}

void createMaze(vector<vector<cell>>& maze) { // create maze by breaking down the walls randomly
	/*
		2-Push (0,0) cell to your stack.
		3-Use the top element (currentCell) in the stack to choose the next cell to be added to your maze.
		4-Choose a random wall of the currentCell to add a new unvisited cell to the maze.
		5-Knock down the wall and add the new cell to the stack.
		6-If no wall exists to knock down for the currentCell, backtrack using the stack until you find a cell which has an unvisited neighbour cell.
		7-Continue steps 3-6 until no cell remains unvisited.

	*/
	cell curr;
	string movingDir;
	stack.push(maze[0][0]);

	while (!stack.isEmpty())
	{
		curr = stack.top();
		maze[curr.y][curr.x].isVisited = true;
		movingDir = findWay(curr, maze);
		if (movingDir == "up")
		{
			maze[curr.y][curr.x].uWall = 0;
			maze[curr.y + 1][curr.x].dWall = 0;
			stack.push(maze[curr.y + 1][curr.x]);
		}
		else if (movingDir == "down")
		{
			maze[curr.y][curr.x].dWall = 0;
			maze[curr.y - 1][curr.x].uWall = 0;
			stack.push(maze[curr.y - 1][curr.x]);
		}
		else if (movingDir == "right")
		{
			maze[curr.y][curr.x].rWall = 0;
			maze[curr.y][curr.x + 1].lWall = 0;
			stack.push(maze[curr.y][curr.x + 1]);
		}
		else if (movingDir == "left")
		{
			maze[curr.y][curr.x].lWall = 0;
			maze[curr.y][curr.x - 1].rWall = 0;
			stack.push(maze[curr.y][curr.x - 1]);
		}
		else
		{
			stack.pop(); // if no directions left to go -> go back
		}
	}
}

void clearVisit(vector<vector<cell>>& maze) { // clear the cells' isVisited before discovering
	for (int a = 0; a < maze.size(); a++)
	{
		for (int b = 0; b < maze[a].size(); b++)
		{
			maze[a][b].isVisited = false;
		}
	}
}

void discover(vector<vector<cell>>& maze, int enx, int eny, int exx, int exy, string mazeID) {
	/*
		1- Start with an initially empty stack.
		2- Push the entry cell to your stack (will be entered by the user).
		3- Use the top element in the stack to choose the next cell to visit.
		4- If you cannot find any cell to go, backtrack using the stack until you find an unvisited cell to go.
		5- Continue steps 3-4 until you reach the exit point.

	*/
	clearVisit(maze);
	cell curr;
	stack.push(maze[enx][eny]); // start with entry cell
	curr = stack.top();
	while (curr.y != exy || curr.x != exx) // until reach the exit point
	{
		curr = stack.top();
		maze[curr.y][curr.x].isVisited = true;
		if (curr.y + 1 < maze.size() && !maze[curr.y + 1][curr.x].isVisited && curr.uWall == 0) //up
		{
			stack.push(maze[curr.y + 1][curr.x]);
		}
		else if (curr.y - 1 >= 0 && !maze[curr.y - 1][curr.x].isVisited && curr.dWall == 0) //down
		{
			stack.push(maze[curr.y - 1][curr.x]);
		}
		else if (curr.x + 1 < maze[curr.y].size() && !maze[curr.y][curr.x + 1].isVisited && curr.rWall == 0) //right
		{
			stack.push(maze[curr.y][curr.x + 1]);
		}
		else if (curr.x - 1 >= 0 && !maze[curr.y][curr.x - 1].isVisited && curr.lWall == 0) //left
		{
			stack.push(maze[curr.y][curr.x - 1]);
		}
		else
		{
			stack.pop();
		}
	}
	Stack<cell> temp;
	ofstream out;
	out.open("maze_" + mazeID + "_path_" + to_string(enx) + "_" + to_string(eny) + "_" + to_string(exx) + "_" + to_string(exy) + ".txt"); // write output to the file cell by cell
	while (!stack.isEmpty()) // to make reverse of stack
	{
		temp.push(stack.top());
		stack.pop();
	}
	while (!temp.isEmpty())
	{
		out << temp.top().x << " " << temp.top().y << "\n";
		temp.pop();
	}
	out << exx << " " << exy << "\n";
}

int main()
{
	int mazeCnt, M_rows, N_cols;

	cout << "Enter the number of mazes: ";
	cin >> mazeCnt;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> M_rows >> N_cols;

	vector<vector<cell>> maze;
	for (int i = 0; i < M_rows; i++) // put default cells to the maze depend on proper coordinates
	{
		vector<cell> temp;
		for (int j = 0; j < N_cols; j++)
		{
			temp.push_back(cell(i, j));
		}
		maze.push_back(temp);
	}

	vector<vector<vector<cell>>> mazeArr(mazeCnt, maze);
	for (int i = 0; i < mazeArr.size(); i++)
	{
		createMaze(mazeArr[i]);
	}
	string mazeID;
	cout << "Enter a maze ID between 1 to " << mazeCnt << " inclusive to find a path: ";
	cin >> mazeID;

	ofstream outs;
	outs.open("maze_" + mazeID + ".txt"); // write selected maze's information to the file
	outs << M_rows << " " << N_cols << "\n";
	for (int a = 0; a < M_rows; a++)
	{
		for (int b = 0; b < N_cols; b++)
		{
			cell c = mazeArr[stoi(mazeID) - 1][a][b];
			outs << "x=" << b << " y=" << a << " l=" << c.lWall << " r=" << c.rWall << " u=" << c.uWall << " d=" << c.dWall << "\n";
		}
	}
	outs.close();
	int enPx, enPy, exPx, exPy;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> enPx >> enPy;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exPx >> exPy;

	discover(mazeArr[stoi(mazeID) - 1], enPx, enPy, exPx, exPy, mazeID); // find the solution of the maze


	return 0;
}
