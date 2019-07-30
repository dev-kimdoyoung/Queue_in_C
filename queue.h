#ifndef QUEUE_H
#define QUEUE_H

typedef struct queueData {
    int number;
    struct queueData *next;
}queueData;

typedef struct Queue {
    struct queueData *front;
    struct queueData *rear;
    struct queueData *current;
}Queue;

// 큐 생성 : front, rear 노드를 생성하고 노드를 초기화
Queue* createQueue(Queue* queue);

// 큐 제거 : 동적 할당한 모든 노드의 메모리를 반환
_Bool deleteQueue(Queue* queue);

// 큐 추가(enqueue) : 큐의 가장 마지막에 데이터를 추가
Queue* addNode(Queue* queue, int number);

// 큐 제거(dequeue) : 큐의 가장 처음 데이터를 제거
Queue* removeNode(Queue* queue);

// 데이터 출력(peek) : 가장 처음 데이터 노드의 데이터 출력
Queue* peek(Queue* queue);

// 공백 여부
_Bool isEmpty(Queue* queue);

// 데이터 추가 가능 여부
_Bool isFull(Queue* queue);

#endif