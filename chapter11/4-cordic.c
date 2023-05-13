const int angles[] = {
  0x3243f6a8, 0x1dac6705, 0x0fadbafc, 0x07f56ea6, 0x03feab76, 0x01ffd55b, 0x00fffaaa, 0x007fff55,
  0x003fffea, 0x001ffffd, 0x000fffff, 0x0007ffff, 0x0003ffff, 0x0001ffff, 0x0000ffff, 0x00007fff,
  0x00003fff, 0x00001fff, 0x00000fff, 0x000007ff, 0x000003ff, 0x000001ff, 0x000000ff, 0x0000007f,
  0x0000003f, 0x0000001f, 0x0000000f, 0x00000008, 0x00000004, 0x00000002, 0x00000001, 0x00000000
};

int angle = (desired_angle_in_degrees / 360 * 2 * 3.14159265358979323846) * 0x40000000;

int x = (int)(0.6072529350088812561694 * 0x40000000);
int y = 0;

for (int index = 0; index < 32; index++) {
  int x_prime;
  int y_prime;

  if (angle < 0) {
    x_prime = x + (y >> index);
    y_prime = y - (x >> index);
    angle += angles[index];
  }
  else {
    x_prime = x - (y >> index);
    y_prime = y + (x >> index);
    angle -= angles[index];
  }

  x = x_prime;
  y = y_prime;
}