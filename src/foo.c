#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "..\inc/foo.h"

typedef struct chisl
{
    uint8_t razr1;
    struct chisl *next;
}chisl;
chisl *head1 = NULL;
chisl *head2 = NULL;
chisl *head_summ = NULL;


typedef bool (*Tcheck) (chisl*);

//Добавление новых узлов списка
void Path(chisl **head, uint32_t chislo){  
    chisl*tmp = ( chisl*) malloc(sizeof( chisl));
    tmp->razr1 = chislo;
    tmp->next = *head;
    (*head) = tmp;
}

//Ввод чисел
void Insert_numbers(uint32_t *number){
    printf("number: \n");
    scanf("%i", &(*number));
    printf("chisl %i\n", (*number));
    int n = (*number);
    (*number) = Flip(n);
}

// Переворот числа
int Flip(uint32_t flip_num){
    uint32_t rev=0,rem = 0;
    while(flip_num>0)
    {
    rem=flip_num%10; 
    rev=rev*10+rem;         
    flip_num=flip_num/10; 
    }
    return rev;
}


//Заполнение счетчиков
void Counter_number(uint8_t *counter, uint32_t number){
    while(number != 0)       
    {
        number = number / 10;
        (*counter)++;
    } 
}

//Определение является ли цифра больше 9
bool Check_number(chisl *head_summ_check){
    if (head_summ_check->razr1 == 3 ){
        return true;
    }
    else{return false;}
}

//Выборка узлов списка
void Pop_checker(Tcheck ch){
    bool ret = ch(head_summ);
    if (ret==true){
    Pop(&head_summ);
    printf("#");
    }
    else if (ret==false) {
        printf("%i", head_summ->razr1); 
        Pop(&head_summ);
    }
}

//Удаление узла списка
void Pop(chisl **head) {
    chisl* prev = NULL;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
}

//Разложение на цифры и запись в список
void Decomposition(uint8_t counter, uint32_t number,chisl **head){
for( uint8_t i = 0 ; i<(counter) ;i++)
    {
        uint8_t number_number;
        number_number = (number)%10;      
        number = (number) / 10; 
        Path(head, number_number); 
        printf("number first spisok %i: %i\n",i, (*head)->razr1);      
    }
}

//Разложение целого числа на цифры, по разрядам
void Razlojeniye(void)
{
    uint8_t counter_one=0, counter_two=0;
    uint32_t number_one =0, number_two = 0;
    Insert_numbers(&number_one);
    Insert_numbers(&number_two);
    Counter_number(&counter_one, number_one); 
    Counter_number(&counter_two, number_two);  
    Decomposition(counter_one, number_one, &head1);
    Decomposition(counter_two, number_two, &head2);
    Slojenie();
    printf("Summ chisel\n");
    while (head_summ)
    {
        Pop_checker(Check_number);
    }
    printf("\n");    
}

//Сумма с пустым списком
void Summ_void_title(chisl *head, chisl **summ){
    uint8_t sum = 0;
    sum = 0 + head->razr1;   
    Path(summ, sum);
}

//Сложение разрядов из списков и запись в новый список
void Slojenie(void)
{
    
    uint8_t sum = 0;
    uint8_t ostatok = 0;
    while (head1 || head2)
    {
        if (head1 == NULL && head2)
        {
            Summ_void_title(head2, &head_summ);
            Pop(&head2);
            
        }
        else if (head2 == NULL && head1)
        {
            Summ_void_title(head1, &head_summ);
            Pop(&head1);
        }
        else
        {
            sum = head1->razr1 + head2->razr1;
            if (ostatok > 0){
                sum = sum + 1;
                ostatok = 0;
            }
            if (sum > 9){
                sum = sum%10;
                ostatok = 1;
            }
            Pop(&head1); Pop(&head2);
            Path(&head_summ, sum);  
        } 
        }
        if (ostatok > 0){
            Path(&head_summ, ostatok);
        }
    }
         
