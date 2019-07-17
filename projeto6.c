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

int getHeight(word *root){
    if(root == NULL){
        return -1;
    }
    else{
        return root->height;
    }
}

int comparation(int left, int right){
    if(left > right){
        return left;
    }
    else{
        return right;
    }
}

word *initWord(char name[31]){
    
    word *element = (word*)malloc(sizeof(word));
    element->left = NULL;
    element->right = NULL;
    strcpy(element->name, name);
    element->height = 0;

    return element;
}

int calcultatorBalacing(word *root){
    return getHeight(root->right) - getHeight(root->left);
}

word *rotationLeft(word *root){
    word *aux = root->right;
    root->right = aux->left;
    aux->left = root;
    root->height = calcultatorBalacing(root);
    aux->height = calcultatorBalacing(aux);
    return aux;
}

word *rotationRight(word *root){
    word *aux = root->left;
    root->left = aux->right;
    aux->right = root;
    root->height = calcultatorBalacing(root);
    aux->height = calcultatorBalacing(aux);
    return aux;
    /*
    printf("%s\n", root->name);
    printf("%s\n", root->left->name);
    printf("%s\n", root->right->name);

     */
    
}

void rotationLeftRight(word *root){
    rotationLeft(root->left);
    rotationRight(root);
}


void rotationRightLeft(word *root){
    rotationLeft(root->right);
    rotationRight(root);
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
        
    root[0]->height = comparation(getHeight(root[0]->right), getHeight(root[0]->left))+1;
    int balance = calcultatorBalacing(root[0]);
    printf("b: %d\n", balance);
    
    if(balance > 1){
        if(calcultatorBalacing(root[0]) == -1){
            
            rotationRightLeft(root[0]);
        }
        else{
            root[0] = rotationLeft(root[0]);

        }
 
    }
    else if (balance < -1){
        if(calcultatorBalacing(root[0]->left) == 1){
            rotationLeftRight(root[0]);
        }
        else{
            root[0] = rotationRight(root[0]);

        }
            
             
    }
    
    
    
    
    
}


void PED(word *root){

    if(root == NULL){
        return;
    }
    else{
        printf("%s\n", root->name);
        printf("%d\n", root->height);
        PED(root->left);
        PED(root->right);
    }
}

int main(int argc, char const *argv[])
{
    word **root = (word**)malloc(sizeof(word*));
    root[0] = NULL;

    add(root, "f");
    add(root, "e");
    add(root, "c");
    add(root, "d");
    add(root, "b");

    PED(root[0]);
    printf("C: %s", root[0]->left->left->right->name);
    
    return 0;
}