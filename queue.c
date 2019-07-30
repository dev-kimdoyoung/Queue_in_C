#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "boolean.h"

int main() {
    Queue* queue;
    queue = createQueue(queue);
    printf("큐 생성 완료\n");

    if(deleteQueue(queue)) {
        printf("큐 메모리 반환 완료\n");
    }
    else {
        printf("큐 메모리 반환 실패..\n");
    }
}


// 큐 생성 : front, rear 노드를 생성하고 노드를 초기화
Queue* createQueue(Queue* queue) {
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

    // 큐 초기화
    queue->current = queue->rear;
    queue->front->next = NULL;
    queue->rear->next = NULL;
    return queue;
}

// 큐 제거 : 동적 할당한 모든 노드의 메모리를 반환
_Bool deleteQueue(Queue* queue) {
    // 마지막 노드 메모리 반환
    memset(queue->rear, 0xFF, sizeof(queue->rear));
    free(queue->rear);
    queue->rear = NULL;

    // 처음 노드 메모리 반환
    memset(queue->front, 0xFF, sizeof(queue->front));
    free(queue->front);
    queue->front = NULL;

    // 큐(queue) 메모리 반환
    memset(queue, 0xFF, sizeof(queue));
    free(queue);
    queue = NULL;

    return TRUE;
}

// 큐 추가(enqueue) : 큐의 가장 마지막에 데이터를 추가
Queue* addNode(Queue* queue, int number) {
    // 데이터 노드 동적 할당
    queueData* data = (queueData*)malloc(sizeof(queueData));

    // 데이터 노드에 데이터 update
    data->number = number;

    // 큐의 현재 노드 위치 초기화
    queue->current = queue->rear;
    // 만약 연결된 데이터 노드가 없으면
    if(queue->rear->next == NULL) {
        queue->rear->next = data;
        data->next = queue->front;
        return queue;
    }
    else {
        // 현재 노드가 front(처음) 노드가 되기 전까지 노드 순회
        while(queue->rear->next->next == NULL) {
            queue->current = queue->rear->next;
        }
        // 새로운 노드가 마지막 노드가 되도록 노드 연결
        data->next = queue->current->next;
        queue->current->next = data;
    }
}

// 큐 제거(dequeue) : 큐의 가장 처음 데이터를 제거
Queue* removeNode(Queue* queue);

// 데이터 출력(peek) : 가장 처음 데이터 노드의 데이터 출력
Queue* peek(Queue* queue);

// 공백 여부
_Bool isEmpty(Queue* queue);

// 데이터 추가 가능 여부
_Bool isFull(Queue* queue);