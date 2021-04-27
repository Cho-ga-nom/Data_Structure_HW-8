/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {                         // 리스트 노드. 값을 저장하는 key 변수와 왼쪽 링크, 오른쪽 링크 포이터가 있음.
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);           // 리스트 초기화 함수
int freeList(listNode* h);             // 리스트 해제 함수
int insertLast(listNode* h, int key);    // 리스트 마지막에 노드를 삽입하는 함수
int deleteLast(listNode* h);             // 마지막 노드 삭제 함수
int insertFirst(listNode* h, int key);   // 리스트 첫번째 위치에 노드를 삽입하는 함수
int deleteFirst(listNode* h);            // 첫번째 노드 삭제 함수
int invertList(listNode* h);             // 리스트를 역순으로 재배치하는 함수

int insertNode(listNode* h, int key);    // 노드 삽입 함수
int deleteNode(listNode* h, int key);    // 노드 삭제 함수

void printList(listNode* h);           // 리스트 출력 함수



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;           // 리스트의 시작과 끝을 가리킬 헤드노드

	printf("[----- [2018038084 조수현] -----]\n\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h)
{
	listNode* p = h;
	listNode* prev = NULL;

	while(p->rlink != h)         // 리스트를 한 바퀴 돌면서 p의 위치를 prev에 저장하여 prev를 해제
	{
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);      // 마지막에 헤드 노드 메모리도 해제
	return 0;
}


void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) 
{
	listNode* temp;                        // 현재 리스트에서 어느 위치인지 저장할 포인터
	temp = h;                             // 처음에 헤드 노드 위치를 넣어줌

	listNode* newnode = (listNode*)malloc(sizeof(listNode));    // 새로 삽입할 노드 동적할당
	newnode->key = key;

	if(temp->rlink == h)                // temp가 마지막 노드면 다음 노드가 헤드 노드
	{
		newnode->rlink = h;             // 새로 삽입한 노드의 오른쪽 링크가 헤드 노드를 가리키도록 링크
		newnode->llink = temp;          // 왼쪽 링크가 원래 마지막 노드였던 temp를 가리키도록 링크
		temp->rlink = newnode;          // 마지막 노드였던 temp의 오른쪽 링크를 새로운 노드에 연결
		h->llink = newnode;             // 헤드노드의 왼쪽 링크가 마지막 노드가 된 newnode를 가리키도록 변경
		return 0;
	}
	else
	{
		while(temp->rlink != h)         // temp가 마지막 노드까지 이동
		{
			temp = temp->rlink;
		}

		newnode->rlink = h;            // 위와 동일한 방식으로 새로운 노드 삽입
		newnode->llink = temp;
		temp->rlink = newnode;
		h->llink = newnode;
		return 0;
	}
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) 
{
	if((h->rlink == h) && (h->llink == h))       // 리스트가 비어있을 경우 검사
	{
		printf("삭제할 노드가 없습니다.\n\n");
		return 0;
	}

	listNode* temp;                     // 위치를 저장할 temp선언 및 헤드 노드로 초기화
	temp = h;

	temp->llink = temp->llink->llink;     // temp가 헤드노드이므로 마지막 노드를 가리키고 있던 왼쪽 링크를 마지막에서 두번째 노드로 변경
	temp->llink->rlink = h;               // 바로 윗줄에서 마지막 노드가 변경 됐으므로 새로 마지막 노드가 된 노드의 오른쪽 링크를 헤드 노드에 연결
	free(temp);               // temp 메모리 해제
	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key)
{
	listNode* newnode = (listNode*)malloc(sizeof(listNode));    // 새로 삽입할 노드 동적할당
	newnode->key = key;

	if(h == NULL)                     // 아직 리스트에 노드가 하나도 없다면
	{
		newnode->rlink = h;             // 새로 삽입한 노드의 오른쪽 링크가 헤드 노드를 가리킴
		h->rlink = newnode;             // 헤드 노드의 오른쪽 링크와 왼쪽 링크 모두 첫번째이자 하나뿐인 newnode를 가리킴
		h->llink = newnode;
		return 0;
	}
	else                              // 리스트에 노드가 존재한다면
	{
		newnode->rlink = h->rlink;     // 새로 삽입한 newnode의 오른쪽 링크를 헤드 노드의 오른쪽 링크가 가리키고 있던 원래 첫번째 노드에 연결
		newnode->llink = h;           // newnode의 왼쪽 링크를 헤드 노드에 연결
		h->rlink = newnode;          // 헤드 노드의 오른쪽 링크를 newnode에 연결
		return 0;
	}
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) 
{
	listNode* temp;
	temp = h;

	if((h->rlink == h) && (h->llink == h))          
	{
		printf("삭제할 노드가 없습니다.\n\n");
		return 0;
	}

	if(h->rlink == h->llink)          // 헤드의 오른쪽 링크와 왼쪽 링크가 가리키는 노드가 같음. 노드가 하나뿐인 경우
	{
		temp->rlink = h;           // 헤드 노드의 양쪽 링크가 자기 자신을 가리키도록 초기화
		temp->llink = h;
		free(temp);                
		return 0;
	}
	else                                   // 나머지 경우
	{
		temp->rlink = temp->rlink->rlink;    // 헤드 노드의 오른쪽 링크가 첫번째 노드의 다음 노드를 가리키도록 변경
		free(temp);
		return 0;
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h)
{
	listNode* lead;                   // 선행 노드를 가리킬 포인터
	listNode* trail;                   // 뒤에서 따라갈 노드를 가리킬 포인터
	lead = h;                         // 선행 포인터를 헤드 노드로 초기화
	h->llink = h->rlink;             // 마지막 노드를 가리키던 왼쪽 링크가 첫번째 노드를 가리키도록 변경

	while(lead->rlink != h)          // 선행 포인터가 리스트를 한 바퀴 다 돌때까지
	{
		trail = lead;                  // trail이 lead를 따라감
		lead = lead->rlink;            // lead 이동
		lead->llink = lead->rlink;     // lead의 왼쪽 링크를 오른쪽 링크로 바꿔줌
		lead->rlink = trail;           // lead의 오른쪽 링크를 이전 노드인 trail에 연결
	}

	h->rlink = lead;               // 헤드노드의 오른쪽 링크를 마지막 노드까지 이동한 lead에 연결
	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key)
{
	listNode* temp;
	temp = h;

	if(h->rlink == h)            // 리스트가 비어있으면
	{
		insertFirst(h, key);      // insertFirst를 호출하여 첫번째 노드 삽입       
		return 0;
	}
	else
	{
		while(temp->rlink != h)           // 리스트 한 바퀴 돌때까지 반복
		{
			if(key < temp->rlink->key)         // 다음 노드의 key보다 작으면
			{
				listNode* newnode = (listNode*)malloc(sizeof(listNode));
				newnode->key = key;
				newnode->llink = temp;                // 새로운 노드의 왼쪽 링크가 현재 노드를 가리키도록 연결
				newnode->rlink = temp->rlink;         // 새로운 노드의 오른쪽 링크가 현재 노드의 다음 노드를 가리키도록 연결
				temp->rlink->llink = newnode;         // 현재 노드의 다음 노드의 왼쪽 링크가 새로운 노드를 가리키도록 연결
				temp->rlink = newnode;                // 현재 노드의 오른쪽 링크가 새로운 노드를 가리키도록 연결
				return 0;
			}
			temp = temp->rlink; 
		}

		if(temp->rlink == h)           // 마지막 노드에 갈 때까지 삽입을 완료하지 못했으면
		{
			insertLast(h, key);        // insertLast 호출
			return 0;
		}
	}
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) 
{
	listNode* temp;
	temp = h;

	while(temp->rlink != h)          // 리스트 한 바퀴 돌때까지 반복
	{
		if(temp->key == key)        // 입력받은 키와 같은 값을 찾으면
		{
			if(temp == h)             // temp가 헤드 노드라면 즉, 찾은 노드가 첫번째 노드라면
			{
				deleteFirst(h);          // deleteFirst 호출
				return 0;
			}

			temp->llink->rlink = temp->rlink;   // 현재 노드의 이전 노드의 오른쪽 링크가 현재 노드의 다음 노드를 가리키도록 연결
			temp->rlink->llink = temp->llink;   // 현재 노드의 다음 노드의 왼쪽 링크가 현재 노드의 이전 노드를 가리키도록 연결
			free(temp);                        // 메모리 해제
			return 0;
		}
		temp = temp->rlink;
	}

	if(temp->rlink == h)                // 마지막 노드에 갈 때까지 못 찾았다면
	{
		temp->llink->rlink = h;          // 마지막 노드의 이전 노드의 오른쪽 링크를 헤드 노드에 연결
		h->llink = temp->llink;         // 헤드 노드의 왼쪽 링크를 마지막 노드의 이전 노드에 연결
		free(temp);
		return 0;
	}
}