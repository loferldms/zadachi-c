#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "..\inc/foo.h"

//@brief: Объявление структуры
typedef struct chisl 
{
    uint8_t razr1;
    struct chisl *next;
}chisl;

//@brief: Объявление указателей на структуру
chisl *head1 = NULL;
chisl *head2 = NULL;
chisl *head_summ = NULL;

//@brief: создание ссылки на функцию
typedef bool (*Tcheck) (chisl*);

//@brief: Объявление-функций
static void Slojenie(void);
static void Path(chisl **head, uint32_t chislo);
static void Insert_numbers(uint32_t *number);
static int Flip(uint32_t flip_num);
static void Counter_number(uint8_t *counter, uint32_t number);
static bool Check_number(chisl *head_summ_check);
static void Pop_checker(Tcheck ch);
static void Pop(chisl **head);
static void Decomposition(uint8_t counter, uint32_t number,chisl **head);
void Razlojeniye(void);
static void Summ_void_title(chisl *head, chisl **summ);


//@brief: Функция добавления новых узлов списка
//@param: **head двойной указатель на структуру
//@param: chislo разряд числа
//@param: *tmp указатель на структуру
static void Path(chisl **head, uint32_t chislo){  
    chisl*tmp = ( chisl*) malloc(sizeof( chisl));
    tmp->razr1 = chislo;
    tmp->next = *head;
    (*head) = tmp;
}

//@brief: функция вывода сообщения и приема числа из консоли
//@param: *number указатель на число
static void Insert_numbers(uint32_t *number){
    printf("number: \n");
    scanf("%i", &(*number));
    printf("chisl %i\n", (*number));
    int n = (*number);
    (*number) = Flip(n);
}

//@brief: функция переворачивает число и возвращает его
//@param: flip_num число для переворота
//@param: rev конечный результат
static int Flip(uint32_t flip_num){
    uint32_t rev=0,rem = 0;
    while(flip_num>0)
    {
    rem=flip_num%10; 
    rev=rev*10+rem;         
    flip_num=flip_num/10; 
    }
    return rev;
}

//@brief: функция заполнения счетчика количества цифр в числе
//@param: *counter указатель на счетчик
//@param: number число для подсчета цифр в нем
static void Counter_number(uint8_t *counter, uint32_t number){
    while(number != 0)       
    {
        number = number / 10;
        (*counter)++;
    } 
}

//@brief: функция проверки цифры из узла структуры
//@param: *head_summ_check указатель на структуру
static bool Check_number(chisl *head_summ_check){
    if (head_summ_check->razr1 == 3 ){
        return true;
    }
    else{return false;}
}

//@brief: функция фильтрации цифр из узла структуры
//@param: ch указатель на функцию Check_number
static void Pop_checker(Tcheck ch){
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

//@brief: функция удаления узла из списка
//@param: **head двойной указатель на структуру
//@param: *prev указатель на структуру
static void Pop(chisl **head) {
    chisl* prev = NULL;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
}

//@brief: функция декомпозиции числа на цифры и их запись в узлы структуры
//@param: counter счетчик цифр в числе
//@param: number введенное число
//@param: **head двойной указатель на структуру
static void Decomposition(uint8_t counter, uint32_t number,chisl **head){
for( uint8_t i = 0 ; i<(counter) ;i++)
    {
        uint8_t number_number;
        number_number = (number)%10;      
        number = (number) / 10; 
        Path(head, number_number); 
        printf("number first spisok %i: %i\n",i, (*head)->razr1);      
    }
}

//@brief: основная функция вызова остальных функций
//@param: counter_one счетчик первого числа
//@param: counter_two счетчик второго числа
//@param: number_one первое число
//@param: number_two второе число
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

//@brief: функция сложения цифр из узлов чисел если одна из цифр равна 0
//@param: *head указатель на структуру
//@param: **summ двойной указатель на функцию
static void Summ_void_title(chisl *head, chisl **summ){
    uint8_t sum = 0;
    sum = 0 + head->razr1;   
    Path(summ, sum);
}

//@brief: функция сложения и записи в узлы структуры суммы цифр
//@param: sum сумма чисел
//@param: ostatok остаток от сложения для переноса в следующий разряд
static void Slojenie(void)
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
         
