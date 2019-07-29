#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct words{

    char name[31];
    char sinonimo[11][31];
    int8_t height;
    struct words *right;
    struct words *left; 

}word;


word *initWord(char name[31]){
    
    word *element = (word*)malloc(sizeof(word));
    element->left = NULL;
    element->right = NULL;
    strcpy(element->name, name);
    element->height = 0;

    return element;
}
void insert(word **root, char name[31]){

    word **aux = (word**)malloc(sizeof(word*));

    if(*root  == NULL){  
        *root  = initWord(name);   
    }
    else if(strcmp((*root)->name, name) < 0){
        if((*root)->right != NULL){
            aux[0] = (*root)->right;
            insert(aux, name);
        }     
        else{
            (*root)->right = initWord(name);
        }
    }
    else if(strcmp((*root)->name, name) > 0){
        if((*root)->left != NULL){
            aux[0] = (*root) ->left;
            insert(aux, name);

        }
        else{
            (*root)->left = initWord(name);      
        }
    } 

    *root = balance(*root );  
         
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
