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
make_node(char *string)
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

int
main(int argc, char *argv[])
{
  char  animal[50]; // 새 동물 이름이 들어갈 버퍼
  char  buffer[3]; // 사용자 입력(y or n)이 들어갈 버퍼
  int   c; // 버퍼의 현재 문자
  struct node **current; // 현재 순회 중인 트리 노드
  FILE  *in; // 훈련 데이터나 타이핑 입력 파일
  struct node *new; // 새로 만든 노드
  FILE  *out; // 훈련 데이터를 저장할 출력 파일
  char  *p; // 새 줄 문자를 지우기 위한 포인터
  char  question[100]; // 새로운 질문이 들어갈 버퍼
  struct node *root; // 지식 트리의 루트

  // 명령줄 인자 처리

  in = out = (FILE *)0;

  for (argc--, argv++; argc > 1 && argc % 2 == 0; argc -= 2, argv += 2) {
    if (strcmp(argv[0], "-i") == 0 && in == (FILE *)0) {
      if ((in = fopen(argv[1], "r")) == (FILE *)0) {
        (void)fprintf(stderr, "gta: can't open input file `%s'.\n", argv[1]);
        exit(-1);
      }
    }

    else if (strcmp(argv[0], "-o") == 0 && out == (FILE *)0) {
      if((out = fopen(argv[1], "w")) == (FILE *)0) {
        (void)fprintf(stderr, "gta: can't open output file `%s'.\n", argv[1]);
        exit(-1);
      }
    }

    else
      break;
  }

  if (argc > 0) {
    (void)fprintf(stderr, "usage: gta [-i input-file-name] [-o output-file-name]\n");
    exit(-1);
  }

  // 명령줄에서 입력 파일을 지정하지 않으면 표준 입력에서 입력을 읽는다.

  if (in == (FILE *)0)
    in = stdin;

  // 초기 지식 트리를 만든다.

  root = make_node("Does it bark?");
  root->yes = make_node("dog");
  root->no = make_node("cat");

  for (;;) { // 사용자가 끝낼 때까지 게임이 지속된다.
    if (in == stdin)
      (void)printf("Think of an animal.\n");

    current = &root; // 루트 노드부터 트리를 순회한다.

    for (;;) { // game start
      for (;;) { // 올바른 사용자 입력을 받는다.
        if (in == stdin) {
          if((*current)->yes == (struct node *)0)
            (void)printf("Is it a "); // ~ 입니까?

          (void)printf("%s?[ynq] ", (*current)->string);
        }

        if (fgets(buffer, sizeof (buffer), in) == (char *)0 || strcmp(buffer, "q\n") == 0) {
          if (in != stdin) {
            (void)fclose(in);
            in = stdin;
          }
          else {
            if (in == stdin)
              (void)printf("\nThanks for playing. Bye.\n");
            
            exit(0);
          }
        }
        else if (strcmp(buffer, "y\n") == 0) {
          if (out != (FILE *)0)
            fputs("y\n", out);

          current = &((*current)->yes);

          if (*current == (struct node *)0) {
            (void)printf("I knew it!\n");
            break;
          }
        }
        else if (strcmp(buffer, "n\n") == 0) {
          if (out != (FILE *)0)
            fputs("n\n", out);

          if ((*current)->no == (struct node *)0) {
            if (in == stdin)
              (void)printf("I give up. What is it? ");

            fgets(animal, sizeof (animal), in);

            if (out != (FILE *)0)
              fputs(animal, out);

            if ((p = strchr(animal, '\n')) != (char *)0)
              *p = '\0';

            if (in == stdin)
              (void)printf(
                "What's a good question that I could use to tell a %s from a %s? ",
                animal, (*current)->string
              );

            fgets(question, sizeof (question), in); // 새로운 질문 입력

            if (out != (FILE *)0)
              fputs(question, out);

            if ((p = strchr(question, '\n')) != (char *)0)
              *p = '\0';

            new = make_node(question);
            new->yes = make_node(animal);
            new->no = *current;
            *current = new;

            if (in == stdin)
              (void)printf("Thanks! I'll remember that.\n");

            break;
          }

          else
            current = &((*current)->no);
        }
        else {
          if (in == stdin) // y, n, q 중 하나만 받아들이기
            (void)printf("Huh? Please answer y for yes, n for no, o q for quit.\n");

          while ((c = getc(in)) != '\n' && c != EOF)
            ;
        }
      }

      break;
    }

    if (in == stdin)
      (void)printf("Let's play again.\n\n");
  }
}