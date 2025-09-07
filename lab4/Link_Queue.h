// #pragma once
// #include "utils.h"

// struct ListNode {
//     int data;
//     struct ListNode *next;
// };
// typedef struct ListNode Node;

// class Queue{
// public:
//     Queue():front(nullptr),rear(nullptr){}
//     ~Queue(){
//         Clear();
//     }
// private:
//     Node *front;
//     Node *rear;
// public:
//     bool Is_Empty()const{
//         return front == nullptr;
//     }
//     void EnQueue(int value){
//         Node *p = new Node;
//         p->data = value;
//         if(Is_Empty()){
//             front = rear = p;
//         }else{
//             rear->next = p;
//             rear = p;
//         }
//     }

//     int DeQueue(){
//         if(Is_Empty()) std::cerr<<"Error";
//         Node *temp = front;
//         int value = temp->data;
//         front = front->next;
//         if(front == nullptr) rear = front;
//         delete temp;
//         return value;
//     }

//     void Concentrate(Queue &son){
//         if(!son.Is_Empty()){
//             if(Is_Empty()){
//                 front = son.front;
//                 rear = son.rear;
//             }else{
//                 rear->next = son.front;
//                 rear = son.rear;
//                 rear->next = nullptr;
//             }

//         }
//     }
//     inline void Clear(){
//         while(!Is_Empty()) DeQueue();
//     }

// };

// // int main(void){

// //     Queue Q,P;
// //     for(int i = 0;i<10;i++){
// //         Q.EnQueue(i);
// //         P.EnQueue(i+20);
// //     }
// //     Q.Concentrate(P);
// //     while(!Q.Is_Empty())std::cout<<Q.DeQueue()<<" ";
// //     return 0;
// // }
#pragma once
#include <iostream>
#include <stdexcept>

struct ListNode {
    int data;
    ListNode *next;
    ListNode(int val) : data(val), next(nullptr) {}
};
typedef ListNode Node;

class Queue{
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue(){
        Clear();
    }

    bool IsEmpty() const {
        return front == nullptr;
    }

    void EnQueue(int value){
        Node *p = new Node(value);
        if(IsEmpty()){
            front = rear = p;
        }else{
            rear->next = p;
            rear = p;
        }
    }

    int DeQueue(){
        if(IsEmpty()){
            std::cerr << "Error: Attempt to dequeue from an empty queue." << std::endl;
            throw std::underflow_error("Queue is empty");
        }
        Node *temp = front;
        int value = temp->data;
        front = front->next;
        if(front == nullptr) rear = nullptr;
        delete temp;
        return value;
    }

    void Concentrate(Queue &son){
        if(!son.IsEmpty()){
            if(IsEmpty()){
                front = son.front;
                rear = son.rear;
            }else{
                rear->next = son.front;
                rear = son.rear;
            }
            son.front = son.rear = nullptr;
        }
    }

    void Clear(){
        while(!IsEmpty()) DeQueue();
    }

private:
    Node *front;
    Node *rear;
};
