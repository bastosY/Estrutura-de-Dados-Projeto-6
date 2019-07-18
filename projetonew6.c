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

void add(word **root, char name[31]){

    word **aux = (word**)malloc(sizeof(word*));

    if(root[0] == NULL){  
        root[0] = initWord(name);   
    }
    else if(strcmp(root[0]->name, name) < 0){
        if(root[0]->right != NULL){
            aux[0] = root[0]->right;
            add(aux, name);
        }     
        else{
            root[0]->right = initWord(name);
        }
    }
    else if(strcmp(root[0]->name, name) > 0){
        if(root[0]->left != NULL){
            aux[0] = root[0]->left;
            add(aux, name);

        }
        else{
            root[0]->left = initWord(name);      
        }
    }   
         
}