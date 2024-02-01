#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


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
static void Push(Tree **tree, uint32_t data);
static void Path(List_Of_Leveles **head);
static List_Of_Count *Path_Counter(List_Of_Count **node, Tree *tree);
static int Max(Tree *tree, uint8_t max_right, uint8_t max_left);
static void PrintfNode(Tree *tree, uint8_t id_fu);
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
static List_Of_Count *Path_Counter(List_Of_Count **node, Tree *tree){
    List_Of_Count*tmp = ( List_Of_Count*) malloc(sizeof(List_Of_Count));
    tmp->tree_node = tree;
    tmp->next = *node;
    (*node) = tmp;
    return (*node);
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
static void Push(Tree **tree, uint32_t data){
    Tree *newNode = CreateNode(data);
    Tree *tmp = *tree;
    if(tmp == NULL){
        *tree = newNode;
    }
    else if (data < tmp->data){
        if (tmp->left == NULL){
            tmp->left = newNode;        ////тут нужно запихивать в списки
        }else{
            Push(&(tmp->left), data);
        }
    }
    else if (data > tmp->data){
        if (tmp->right == NULL){
            tmp->right = newNode;
        }else{
            Push(&(tmp->right), data);
        }
    }
    
}

//@brief: функция нахождения самого глубокого элемента 
//@param: *tree указатель на структуру
//@param: max_right глубочайший правый элемент
//@param: max_left глубочайший левый элемент
static int Max(Tree *tree, uint8_t max_right, uint8_t max_left){
    uint8_t max = 0;
    Tree *newNode = NULL;
    newNode = tree;
    if (newNode == NULL){
        return;
    }
    max_left-=1;
    if(newNode->right!=NULL){        
       max_right = Max(newNode->right, max_right, max_left);
       max_right++;
       
    }
    max_right-=1;
    if( newNode->left!=NULL){
        max_left = Max(newNode->left, max_right, max_left);
        max_left++;
    }
    if (max_left > max_right)
    {max = max_left;}
    else {max = max_right;}
    return max;
}

//@brief: функция вывода значений из древа обходом в глубину
//@param: *tree указатель на структуру
//@param: id_fu глубина элемента
static void PrintfNode(Tree *tree, uint8_t id_fu){
    if (tree == NULL){
        return;
    }
    else{
        printf("data - %i\n", tree->data);
        if(tree->left != NULL){
            PrintfNode(tree->left, id_fu);
        }
        if (tree->right != NULL){
            PrintfNode(tree->right, id_fu);
        }
    }
}

//@brief: функция заполнения списков из древа
//@param: *tree указатель на структуру
//@param: id_fu глубина элемента
//@param: *head указатель на структуру
//@param: max максимальное число
static void Input_nubers(Tree *tree, uint8_t id_fu,List_Of_Leveles *head, uint8_t max){
    if (tree == NULL){
        return;
    }
    else{
        if(id_fu == max){
            head->node = Path_Counter(&head->node, tree);
        }
        if(tree->left != NULL){
            id_fu ++;
            Input_nubers(tree->left, id_fu, head, max);
        }
        id_fu -= 1;
        if (tree->right != NULL){
            id_fu ++;
            Input_nubers(tree->right, id_fu, head, max);
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
       Push(&tree, array[i]);
    }
    printf("end.\n");
    PrintfNode(tree, id_fu);
    uint8_t max = Max(tree, 0, 0);
    printf("Max - %i", max);
    for (uint8_t i = 0; i <= max; i++){
        Path(&head);
        Input_nubers(tree, 0, head, i);
    }
    printf ("\n");
    Return_numbers_from_list(head);
    
}