#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
typedef struct tree
{
    uint8_t id;
    uint32_t data;
    struct tree*parent;
    struct tree*left;
    struct tree*right;
}Tree;
typedef struct list_of_count{
    struct tree*node;
    struct list_of_count*next;
}List_Of_Count;
typedef struct list_of_leveles{
    struct list_of_count*node;
    struct list_of_leveles*next;
}List_Of_Leveles;



void Main_foo(void);
Tree *CreateNode(uint32_t data);
void Push(Tree **tree, uint32_t data);

static void Path_Leveles(List_Of_Leveles **head, List_Of_Count *node){  
    List_Of_Leveles*tmp = ( List_Of_Leveles*) malloc(sizeof( List_Of_Leveles));
    tmp->node = node;
    tmp->next = *head;
    (*head) = tmp;
}
Tree *CreateNode(uint32_t data){
    Tree *newNode = (Tree*)malloc(sizeof(Tree));
    if (newNode == NULL){
        printf("Malloc returned NULL\n");
        exit(1);
    }
    newNode->data = data;
    newNode->id = 0;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void Push(Tree **tree, uint32_t data){
    Tree *newNode = CreateNode(data);
    Tree *tmp = *tree;
    if(tmp == NULL){
        *tree = newNode;
    }
    else if (data < tmp->data){
        if (tmp->left == NULL){
            tmp->left = newNode;
            newNode->parent = tmp;
        }else{
            Push(&(tmp->left), data);
        }
    }
    else if (data > tmp->data){
        if (tmp->right == NULL){
            tmp->right = newNode;
            newNode->parent = tmp;
        }else{
            Push(&(tmp->right), data);
        }
    }
    
}

int Max(Tree *tree, uint8_t max_right, uint8_t max_left){
    uint8_t max = 0;
    Tree *newNode = NULL;
    newNode = tree;
    if (newNode == NULL){
        return;
    }
    max_right = newNode->id;
    if(newNode->right!=NULL){        
       max_right = Max(newNode->right, max_right, max_left);
    }
    max_left = newNode->id;
    if( newNode->left!=NULL){
        max_left = Max(newNode->left, max_right, max_left);
    }
    if (max_left > max_right)
    {max = max_left;}
    else {max = max_right;}
    return max;
}

void PrintfNode(Tree *tree, uint8_t id_fu){
    if (tree == NULL){
        return;
    }
    else{
        tree->id = id_fu;
        printf("data - %i, id - %i\n", tree->data, tree->id);
        if(tree->left != NULL){
            id_fu ++;
            PrintfNode(tree->left, id_fu);
        }
        id_fu -= 1;
        if (tree->right != NULL){
            id_fu ++;
            PrintfNode(tree->right, id_fu);
        }
    }
}
void Input_nubers(Tree *tree, uint8_t id_fu, uint8_t max, List_Of_Leveles *head){
    if (tree == NULL){
        return;
    }
    else{
        if(tree->id == max){
        Path_Leveles(&head, head->node->node = tree);
        }
        if(tree->left != NULL){
            id_fu ++;
            PrintfNode(tree->left, id_fu);
        }
        id_fu -= 1;
        if (tree->right != NULL){
            id_fu ++;
            PrintfNode(tree->right, id_fu);
        }
    }
}  

int Input(void){
    uint32_t num = 0;
    scanf("%i", &num);
    return num;
}

void Main_foo(void){
    uint8_t id_fu = 0;
    uint8_t n;
    printf("count numbers\n");
    n = Input();
    n--;
    Tree *tree = NULL;
    List_Of_Leveles *head = NULL;
    List_Of_Count *node = NULL;
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

    Path_Count(&node, tree);
    for (int i = 0; i < max; i++){
        
        Path_Leveles(&head, node);
    }
    head->node->
}