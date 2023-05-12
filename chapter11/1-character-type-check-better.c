unsigned char table[128] = [ ... ];

#define isdigit(c) (table[(c) & 0x7f] & DIGIT)
#define ishexdigit(c) (table[(c) & 0x7f] & HEXADECIMAL)
#define isalpha(c) (table[(c) & 0x7f] & (UPPER | LOWER))
#define isupper(c) (table[(c) & 0x7f] & UPPER)