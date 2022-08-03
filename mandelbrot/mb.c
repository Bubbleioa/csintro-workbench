#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#define W 1000
#define H 1000
char *IMG_FILE;
double scale = 8e-9;
int x[W][H];

void display(FILE *fp, int step)
{
  static int rnd = 1;
  int w = W / step, h = H / step;
  fprintf(fp, "P6\n%d %d 255\n", w, h);
  for (int j = 0; j < H; j += step)
  {
    for (int i = 0; i < W; i += step)
    {
      int n = x[i][j];
      // If you want to change color, change here.
      int r = 255 * pow((n - 80) / 800.0, 3);
      int g = 255 * pow((n - 80) / 800.0, 0.7);
      int b = 255 * pow((n - 80) / 800.0, 0.5);
      fputc(r, fp);
      fputc(g, fp);
      fputc(b, fp);
    }
  }
}

void draw()
{
  for (int i = 0; i < W; i++)
    for (int j = 0; j < H; j++)
    {
      // TODO: Add your code here, please use 'scale' to control view scope
    }
}

int main(int argc, char *argv[])
{
  assert(argc == 3);
  IMG_FILE = argv[1];
  char *ptr;
  scale = strtod(argv[2], &ptr);
  FILE *fp = fopen(IMG_FILE, "wb");
  draw();
  display(fp, 2);
  fclose(fp);
  return 0;
}
