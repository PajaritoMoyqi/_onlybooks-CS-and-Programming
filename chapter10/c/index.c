#include <stdio.h> // 표준 I/O
#include <stdlib.h> // exit와 malloc 제공
#include <string.h> // 문자열 처리

// 노드 구조체 선언
struct node {
  struct node *no; // '아니오'에 대응하는 노드를 참조
  struct node *yes; // '예'에 대응하는 노드를 참조
  char string[1]; // 질문이나 동물 이름
};