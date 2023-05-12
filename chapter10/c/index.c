#include <stdio.h> // 표준 I/O
#include <stdlib.h> // exit와 malloc 제공
#include <string.h> // 문자열 처리

// 노드 구조체 선언
struct node {
  struct node *no; // '아니오'에 대응하는 노드를 참조
  struct node *yes; // '예'에 대응하는 노드를 참조
  char string[1]; // 질문이나 동물 이름
};

struct node *
make_node(char, *string)
{
  struct node *memory; // 새로 할당할 메모리를 가리키는 포인터

  if((memory = (struct node *)malloc(sizeof (struct node) + strlen(string))) == (struct node *)0) {
    (void)fprintf(stderr, "gta: out of memory.\n"); // 오류 메시지 출력
    // (void)는 강제 타입 변환 연산자
    // 깜빡하고 return 값을 처리하지 않은 게 아니라 의도적으로 그랬다는 걸 컴파일러에게 알려야 함.
    exit(-1); // 프로그램 종료. 메모리가 부족하니깐 ㅜ
  }

  (void)strcpy(memory->string, string);
  memory->yes = memory->no = (struct node *)0;

  return (memory);
}