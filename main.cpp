#include <iostream>

using namespace std;

using i16 = short;
using i32 = int;
using i64 = long long;

using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

const char ICONS[] = {'.', 'X', 'O'};
const u16 WIDTH = 7;
const u16 HEIGHT = 6;

u16 display[HEIGHT][WIDTH] = {0};
u16 display_map[HEIGHT][WIDTH] = {0};
u16 height[WIDTH] = {0};

void print_display ()
{
  for (int i = HEIGHT - 1; i >= 0; i--)
    {
      for (int j = 0; j < WIDTH; j++)
        {
          cout << ICONS[display[i][j]];
        }
      cout << '\n';
    }
}

bool is_inside_display (i16 x, i16 y)
{
  return (
          x >= 0
      and x < WIDTH
      and y >= 0
      and y < HEIGHT
    );
}

u16 update_map (u16 column)
{
  // directions down-right,  down-left, down, right
  i16 dx[4] = {1, -1, 0, 1};
  i16 dy[4] = {-1, -1, -1, 0};

  u16 largest = 1;

  cout << "UPDATE MAP\n";
  print_display ();

  // for each direction
  for (int i = 0; i < 4; i++)
    {
      u16 size = 1;
      i16 x = (i16) column;
      i16 y = height[column] - 1;
      const i16 x2 = x, y2 = y;

      // first one direction
      while (is_inside_display(x+=dx[i], y+=dy[i]) and display[x][y] == display[x2][y2])
        size += 1;

      x = x2;
      y = y2;

      // then the other
      while (is_inside_display(x-=dx[i], y-=dy[i]) and display[x][y] == display[x2][y2])
        size += 1;

      // update the largest size
      largest = max(largest, size);
    }

  return largest;
}

void put_coin (u16 column, bool turn)
{
  display[height[column]][column] = turn ? 1 : 2;
  height[column] += 1;
}

u16 read_column ()
{
  u16 column;

  while (true)
    {
      cout << "Where do you want to put the coin? ";

      cin >> column;

      column -= 1;

      if (column >= WIDTH)
        continue;

      if (height[column] >= HEIGHT)
        continue;

      return column;
    }
}

int main ()
{
  bool turn = true; // Player 1 turn

  // There can only be 42 moves in the game
  for (int i = 0; i < 42; i++)
    {
      print_display ();

      u16 column = read_column ();

      put_coin (column, turn);

      if (update_map (column) >= 4)
        {
          cout << "Player " << (turn ? 1 : 2) << " wins!\n";
          return 0;
        }

      turn = !turn;
    }

  cout << "It's a tie\n";

  return 0;
}