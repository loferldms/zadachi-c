#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "..\inc/foo.h"

typedef struct chisl
{
    int razr1;
    struct chisl *next;
}chisl;
chisl *head1 = NULL;
chisl *head2 = NULL;
chisl *head_summ = NULL;


typedef bool (*Tcheck) (chisl*);

//Добавление новых узлов списка
void Path(chisl **head, int chislo){  
    chisl*tmp = ( chisl*) malloc(sizeof( chisl));
    tmp->razr1 = chislo;
    tmp->next = *head;
    (*head) = tmp;
}

//Ввод чисел
void Insert_numbers(int *number){
    printf("number: \n");
    scanf("%i", &(*number));
    printf("chisl %i\n", (*number));
    int n = (*number);
    (*number) = Flip(n);
}

// Переворот числа
int Flip(int flip_num){
    int rev=0,rem = 0;
    while(flip_num>0)
    {
    rem=flip_num%10; 
    rev=rev*10+rem;         
    flip_num=flip_num/10; 
    }
    return rev;
}


//Заполнение счетчиков
void Counter_number(int *counter, int number){
    while(number != 0)       
    {
        number = number / 10;
        (*counter)++;
    } 
}

//Определение является ли цифра больше 9
bool Check_number(chisl *head_summ_check){
    if (head_summ_check->razr1 == 0 ){
        return true;
    }
    else{return false;}
}

//Выборка узлов списка
void Pop_checker(Tcheck ch){
    bool ret = ch(head_summ);
    if (ret==true){
    Pop(&head_summ);
    printf(" !(filtered out) ");
    }
    else if (ret==false) {
        printf("%i", head_summ->razr1);   
        head_summ = head_summ->next;
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
void Decomposition(int counter, int number,chisl **head){
for( int i = 0 ; i<(counter) ;i++)
    {
        int number_number;
        number_number = (number)%10;      
        number = (number) / 10; 
        Path(head, number_number); 
        printf("number first spisok %i: %i\n",i, (*head)->razr1);      
    }
}

//Разложение целого числа на цифры, по разрядам
void Razlojeniye(void)
{
    int counter_one=0, counter_two=0, number_one =0, number_two = 0;
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
    int sum = 0;
    sum = 0 + head->razr1;   
    Path(summ, sum);
}

//Сложение разрядов из списков и запись в новый список
void Slojenie(void)
{
    
    int sum = 0;
    int ostatok = 0;
    while (head1 || head2)
    {
        if (head1 == NULL && head2)
        {
            Summ_void_title(head2, &head_summ);
            head2 = head2->next;
        }
        else if (head2 == NULL && head1)
        {
            Summ_void_title(head1, &head_summ);
            head1 = head1->next;
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
            head1 = head1->next;
            head2 = head2->next;
            Path(&head_summ, sum);  
        } 
        }
        if (ostatok > 0){
            Path(&head_summ, ostatok);
        }
    }
         
