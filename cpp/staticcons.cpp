#include <iostream>

int f();  // forward declaration
int g();  // forward declaration

int x = f();
int y = g();

int f()
{
  return 3*y + 7;
}

int g()
{
  return 5;
}

int main()
{
}
