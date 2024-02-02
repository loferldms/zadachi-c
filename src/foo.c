#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>


//@brief: Объявленние структур
typedef struct tree
{
    uint32_t data;
    struct tree*left;
    struct tree*right;
}Tree;
typedef struct list_of_count{
    struct tree*tree_node;
    struct list_of_count*next;
}List_Of_Count;
typedef struct list_of_leveles{
    struct list_of_count*node;
    struct list_of_leveles*next;
}List_Of_Leveles;


//@brief: Объявление функций
void Main_foo(void);
static Tree *CreateNode(uint32_t data);
static void Push(Tree **tree, uint32_t data, List_Of_Leveles *head, List_Of_Count *node);
static void Path(List_Of_Leveles **head);
static void Path_Counter(List_Of_Count **node, Tree *tree);
static int Max(Tree *tree, uint8_t max_right, uint8_t max_left);
static void PrintfNode(Tree *tree);
static void Input_nubers(Tree *tree, uint8_t id_fu,List_Of_Leveles *head, uint8_t max);
static int Input(void);
void Return_numbers_from_list(List_Of_Leveles *head);

//@brief: Функция добавления новых узлов списка
//@param: **head двойной указатель на структуру
//@param: node указатель на вторую структуру
//@param: *tmp указатель на структуру
static void Path(List_Of_Leveles **head){  
    List_Of_Leveles*tmp = (List_Of_Leveles*) malloc(sizeof(List_Of_Leveles));
    tmp->node = NULL;
    tmp->next = *head;
    (*head) = tmp;
}

//@brief: Функция добавления новых узлов списка
//@param: **node двойной указатель на структуру
//@param: *tree указатель на вторую структуру
//@param: *tmp указатель на структуру
static void Path_Counter(List_Of_Count **node, Tree *tree){
    List_Of_Count*tmp = ( List_Of_Count*) malloc(sizeof(List_Of_Count));
    tmp->tree_node = tree;
    tmp->next = *node;
    (*node) = tmp;
}

//@brief: функция добавления новых ветвей древа
//@param: data число вводимое в консоль
static Tree *CreateNode(uint32_t data){
    Tree *newNode = (Tree*)malloc(sizeof(Tree));
    if (newNode == NULL){
        printf("Malloc returned NULL\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//@brief: функция распределение чисел по ветвям древа
//@param: **tree двойной указатель на структуру
//@param: data число вводимое в консоль
static void Push(Tree **tree, uint32_t data, List_Of_Leveles *head, List_Of_Count *node){
    Tree *newNode = CreateNode(data);
    Tree *tmp = *tree;
    if(tmp == NULL){
        *tree = newNode;
    }
    else if (data < tmp->data){
        if (tmp->left == NULL){
            tmp->left = newNode;        ////тут нужно запихивать в списки
        }else{
            Push(&(tmp->left), data, head, node);
        }
    }
    else if (data > tmp->data){
        if (tmp->right == NULL){
            tmp->right = newNode;
        }else{
            Push(&(tmp->right), data, head, node);
        }
    }
    
}

List_Of_Leveles *Insert_in_to_list(List_Of_Leveles *head, List_Of_Count *node, Tree *tree){
    Tree *newNode = tree;
    List_Of_Leveles *Sklad = NULL;
    uint8_t i = 0;
    if (head == NULL){
        Path(&head);
        Path_Counter(&head->node, newNode);
    } 
    List_Of_Leveles *head_one = NULL;
    while (head != NULL){
        head_one = head;
        Path(&head);
        while (head_one->node != NULL){
            if (head_one->node->tree_node->left !=NULL){
            Path_Counter(&head->node, head_one->node->tree_node->left);
            }
            if(head_one->node->tree_node->right != NULL){
            Path_Counter(&head->node, head_one->node->tree_node->right);
            }
            if(head_one->node->next)
            {
                head_one->node = head_one->node->next;
            }
            else{
                break;
            }
        }
        if(head->node == NULL){
            head = head->next;
            return head;
        }
    }
    

}


//@brief: функция вывода значений из древа обходом в глубину
//@param: *tree указатель на структуру
//@param: id_fu глубина элемента
static void PrintfNode(Tree *tree){
    if (tree == NULL){
        return;
    }
    else{
        printf("data - %i\n", tree->data);
        if(tree->left != NULL){
            PrintfNode(tree->left);
        }
        if (tree->right != NULL){
            PrintfNode(tree->right);
        }
    }
}


//@brief: функция приема данных с консоли
static int Input(void){
    uint32_t num = 0;
    scanf("%i", &num);
    return num;
}


//@brief: функция возврата чисель из списков в консоль
//@param: *head указатель на структуру
void Return_numbers_from_list(List_Of_Leveles *head){
    while(head->node && head){
        printf("%i", head->node->tree_node->data);
        if(head->node){
           head->node = head->node->next; 
        }
        if (head->node == NULL && head!=NULL){
            head = head->next;
            if (head==NULL){
                break;
            }
        }
    }
}

//@brief: основная функция вызова функций и объявления переменных
void Main_foo(void){
    uint8_t id_fu = 0;
    uint8_t n;
    Tree *tree = NULL;
    List_Of_Leveles *head = NULL;
    List_Of_Count *node = NULL;
    printf("count numbers\n");
    n = Input();
    n--;
    uint32_t array[n];
    printf("numbers: \n");
    for (uint8_t i = 0; i <= n; i++){
       array[i] = Input();
       Push(&tree, array[i], head, node);
    }
    printf("end.\n");
    PrintfNode(tree);
    head = Insert_in_to_list(head,node,tree);
    printf ("\n");
    Return_numbers_from_list(head);
    
}