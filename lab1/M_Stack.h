#include <iostream>
#include <ctime>
#include <random>
#include <stdexcept>

template <typename T> 
class M_Stack
{
public:
    typedef struct link
    {
        T data;
        struct link *next;
    }LINK;
private:    
    LINK *head;
    int num;
public:
    M_Stack(){
        head = new LINK;
        head->next = nullptr;
        this->num = 0;
    }
    
    ~M_Stack()
    {
        LINK *p = head,*pr = nullptr;
        while(p!=nullptr)
        {
            pr = p->next;
            delete p;
            p = pr;
        }
    }
    void Push(T value)
    {
        LINK *t = head;
        LINK *p = new LINK;
        while(t->next!=nullptr) t = t->next;
        t->next = p;
        p->next = nullptr;
        p->data = value;
        this->num ++;
    }
    T Pop()
    {
        if(IsEmpty())
        { 
          throw std::runtime_error("The stack is Empty");
          return T();
        }
        LINK *p = head;
        while(p->next->next != nullptr) p = p->next;
        T value = p->next->data;
        delete p->next;
        p->next = nullptr;
        this->num--;
        return value;
    }

    T Get_Top()
    {
        if(IsEmpty())
        { 
          throw std::runtime_error("The stack is Empty");
          return T();
        }
        LINK *p = head;
        while(p->next!= nullptr) p = p->next;
        return p->data;
    }

    bool IsEmpty()
    {
       return head->next == nullptr ? true : false;
    }

    T Random_Select()
    {
  
        if(IsEmpty()) throw std::runtime_error("The stack is Empty");
        std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<int> distribution(1,num);
        int random_number = distribution(generator);
        int count = 1;
        
        LINK *p = head,*pr = p->next;
        while(pr!=nullptr)
        {
            if(count == random_number)
            {
               p->next = pr->next;
               T value = pr->data;
               delete pr;
               pr = p->next;
               this->num--;
               return value;
            }
            else
            {
                p = p->next;
                pr = p->next;
                count ++;
            }
        }
        return T();
    }

    void Display()
    {
        LINK *p = head->next;
        while(p!=nullptr)
        {
            std::cout<<p->data<<" ";
            p = p->next;
        }
        std::cout<<std::endl;
    }

    void Clear()
    {
        LINK *p = head->next,*pr = nullptr;
        while(p!=nullptr)
        {
            pr = p->next;
            delete p;
            p = pr;
        }
    }
};

