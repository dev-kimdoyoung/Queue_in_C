#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "boolean.h"
/*
    목표 : 연결리스트(LinkedList)를 이용하여 큐를 구현
    queue.h : 추상자료형(ADT) 명세
    boolean.h : 프로젝트 구현 편의를 위해 TRUE / FALSE를 정의
    선입선출(FIFO) 구조를 띈다.
 */

int main() {
    Queue* queue;
    queue = createQueue(queue);
    printf("큐 생성 완료\n");

    queue = addNode(queue, 5);
    queue = addNode(queue, 4);
    queue = addNode(queue, 3);

    peek(queue);

    removeNode(queue);
    peek(queue);

    removeNode(queue);
    peek(queue);

    removeNode(queue);
    peek(queue);

    if(deleteQueue(queue)) {
        printf("큐 메모리 반환 완료\n");
    }
    else {
        printf("큐 메모리 반환 실패..\n");
    }

    return 0;
}


// 큐 생성 : front, rear 노드를 생성하고 노드를 초기화
Queue* createQueue(Queue* queue) {
    // 큐 메모리 할당
    queue = (Queue*)malloc(sizeof(Queue));

    // 큐에 메모리 할당 실패 시
    if(queue == NULL) {
        printf("queue에 메모리 할당 실패\n");
        return FALSE;
    }

    queue->front = (queueData*)malloc(sizeof(queueData));

    // 가장 처음 노드에 메모리 할당 실패 시
    if(queue->front == NULL) {
        printf("queue->front에 메모리 할당 실패\n");
        memset(queue, 0xFF, sizeof(queue));
        free(queue);
        queue = NULL;
        return NULL;
    }

    queue->rear = (queueData*)malloc(sizeof(queueData));

    // 마지막 노드에 메모리 할당 실패 시
    if(queue->rear == NULL) {
        printf("queue->rear에 메모리 할당 실패\n");
        memset(queue->front, 0xFF, sizeof(queue->front));
        free(queue->front);
        queue->front = NULL;

        memset(queue, 0xFF, sizeof(queue));
        free(queue);
        queue = NULL;
        return NULL;
    }

    // 노드 초기화
    queue->current = queue->rear;

    // 처음(front) 노드 설정
    queue->front->previous = NULL;
    queue->front->next = queue->rear;

    // 마지막(rear) 노드 설정
    queue->rear->next = NULL;
    queue->rear->previous = queue->front;

    return queue;
}


// 큐 제거 : 동적 할당한 모든 노드의 메모리를 반환
_Bool deleteQueue(Queue* queue) {
    // 임시로 데이터를 저장할 노드 메모리 할당
    struct queueData* temp = (struct queueData*)malloc(sizeof(struct queueData));

    // 현재 가리키는 노드는 처음 노드
    queue->current = queue->front;

    // 전체 데이터 노드 순차적으로 순회
    while (queue->current == NULL) {
        temp = queue->current->next;
        memset(queue->current, 0xFF, sizeof(queue->current));
        free(queue->current);
        queue->current = temp;
    }

    // 포인터 반환 작업
    queue->current = NULL;
    queue->rear = NULL;
    queue->front = NULL;

    // 큐(queue) 메모리 반환
    memset(queue, 0xFF, sizeof(queue));
    free(queue);
    queue = NULL;

    // 임시 노드 메모리 반환
    memset(temp, 0xFF, sizeof(temp));
    free(temp);
    temp = NULL;

    return TRUE;
}


// 큐 추가(enqueue) : 큐의 가장 마지막에 데이터를 추가
Queue* addNode(Queue* queue, const int number) {

    // 데이터 노드 메모리 할당
    queueData* newData = (queueData*)malloc(sizeof(queueData));

    // 노드에 매개변수로 받아온 데이터 저장
    newData->number = number;

    // 연결된 데이터 노드가 존재하지 않는다면
    if(isEmpty(queue)) {
        // 처음(front) 노드와 추가할 노드 연결
        queue->front->next = newData;
        newData->previous = queue->front;

        // 추가할 노드와 마지막(rear) 노드 연결
        newData->next = queue->rear;
        queue->rear->previous = newData;
    }
    // 기존에 1개 이상의 연결되어 있는 데이터 노드가 존재하면
    else {
        // 가장 처음 데이터 노드를 추가할 노드와 연결
        queue->current = queue->front->next;
        queue->current->previous = newData;

        // 추가할 노드 설정
        newData->previous = queue->front;
        newData->next = queue->current;

        // 처음(front) 노드의 다음(next) 노드는 추가할 노드
        queue->front->next = newData;
    }
    return queue;
}


// 큐 제거(dequeue) : 큐의 가장 처음 데이터를 제거
Queue* removeNode(Queue* queue) {
    // 임시로 저장할 노드
    queueData* temp;
    // underflow 예외 처리
    if(isEmpty(queue)) {
        printf("큐에 데이터가 존재하지 않습니다\n");
        return FALSE;
    }
    else {
        // 현재 가리키는 노드는 삭제할 노드
        queue->current = queue->rear->previous;

        // temp에 삭제할 노드 이전(previous) 노드의 레퍼런스를 복사
        temp = queue->rear->previous->previous;

        // 삭제할 노드를 제외한 노드 연결
        temp->next = queue->rear;
        queue->rear->previous = temp;

        // 삭제할 노드 메모리 반환
        memset(queue->current, 0xFF, sizeof(queue->current));
        free(queue->current);
        queue->current->next = NULL;
        queue->current->previous = NULL;
    }
    return queue;
}

// 데이터 출력(peek) : 가장 처음 데이터 노드의 데이터 출력
void peek(Queue* queue) {
    // 만약 데이터 노드가 존재하지 않는다면
    if(isEmpty(queue)) {
        printf("데이터가 존재하지 않습니다\n");
        return;
    }
    // 현재 가리킬 노드는 마지막 노드의 이전 노드
    queue->current = queue->rear->previous;
    printf("%d\n", queue->current->number);
}


// 공백 여부
_Bool isEmpty(Queue* queue) {
    if(queue->front->next == queue->rear) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}