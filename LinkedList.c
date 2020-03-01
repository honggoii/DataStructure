#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int data;
	struct _node* next;
} Node;

int main(void)
{
	Node* head = NULL;	// 리스트의 머리를 가리키는 포인터 변수
	Node* tail = NULL;	// 리스트의 꼬리를 가리키는 포인터 변수
	Node* cur = NULL;	// 리스트 내부를 돌아다니는 포인터 변수

	Node* newNode = NULL;
	int readData;

	// 데이터 입력
	while (1)
	{
		printf("자연수 입력: ");
		scanf("%d", &readData);
		if (readData < 1)
			break;

		// 노드 추가과정
		newNode = (Node*)malloc(sizeof(Node));	// 노드 생성
		newNode->data = readData;				// 노드에 데이터 저장
		newNode->next = NULL;					// 노드의 next를 NULL로 초기화

		if (head = NULL)	// 첫 번째 노드라면
			head = newNode;	// 첫 번째 노드가 head를 가리키게 함
		else
			tail->next = newNode;

		tail = newNode;		// 노드의 끝을 tail이 가리키게 함
	}
	printf("\n");

	// 데이터 출력
	printf("입력 받은 데이터 전체출력! \n");
	if (head == NULL)
	{
		printf("저장된 자연수가 존재하지 않습니다.\n");
	}
	else
	{
		cur = head;	// cur이 리스트의 첫 번째 노드를 기리킴
		printf("%d ", cur->data);	// 첫 번째 데이터 출력

		while (cur->next != NULL)	// 연결된 노드가 존재하면
		{
			cur = cur->next;		// cur이 다음 노드를 가리키게 함
			printf("%d ", cur->data);	// cur이 가리키는 노드 출력
		}
	}
	printf("\n\n");

	// 데이터 삭제
	if (head == NULL)
	{
		return 0;	// 해제할 노드가 없다
	}
	else
	{
		Node* delNode = head;
		Node* delNextNode = head->next;

		printf("%d을(를) 삭제합니다.\n", head->data);
		free(delNode);	// 첫 번째 노드 삭제

		while (delNextNode != NULL)	// 두 번째 노드 이후 삭제
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			printf("%d을(를) 삭제합니다.\n", delNode->data);
			free(delNode);
		}
	}

	return 0;
}