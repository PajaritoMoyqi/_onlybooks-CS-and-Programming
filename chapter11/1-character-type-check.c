int
isdigit(int c)
{
  return (c >= '0' && c <= '9');
}

int
ishexdigit(int c)
{
  return (c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f');
}

int
isalpha(int c)
{
  return (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z');
}

int
isupper(int c)
{
  return (c >= 'A' && c <= 'Z');
}