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

void balacing(word *root);
int getHeight(word *root);


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

void rotationLeft(word *root){
    word *eixo = root->right;
    word *aux = eixo->left;
    eixo->left = root;
    root->right = aux;
    root->height = comparation(getHeight(root->left), getHeight(root->right)) + 1;
    eixo->height = comparation(getHeight(eixo->left), getHeight(eixo->right)) + 1;
    root = eixo;
}

void rotationRight(word *root){
    word *eixo = root->left;
    word *aux = eixo->right;
    eixo->right = root;
    root->left = aux;
    root->height = comparation(getHeight(root->left), getHeight(root->right)) + 1;
    eixo->height = comparation(getHeight(eixo->left), getHeight(eixo->right)) + 1;
    root = eixo;
    
}

void rotationLeftRight(word *root){
    rotationLeft(root->left);
    rotationRight(root);
}


void rotationRightLeft(word *root){
    rotationLeft(root->right);
    rotationRight(root);
}

int getHeight(word *root){
    if(root == NULL){
        return 0;
    }
    else{
        return root->height;
    }
}

int calcultatorBalacing(word *root){
    return getHeight(root->left) - getHeight(root->right);
}

void balacing(word *root){
    
    if(getHeight(root) == 2){        
        if(getHeight(root->right) == -1){
            rotationRightLeft(root);
        }
        else{
            rotationLeft(root);
        }
    }
    else if(getHeight(root) == -2){
        
        if(getHeight(root->left) == 1){
            rotationLeftRight(root);
        }
        else{
            rotationRight(root);
        }
    }
    else{
        //root->height = comparation(getHeight(root->left), getHeight(root->right));
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
        //printf("%d",comparation(getHeight(root[0]->left), getHeight(root[0]->right) + 1) );
        root[0]->height = comparation(getHeight(root[0]->left), getHeight(root[0]->right) + 1);
        int balacing = calcultatorBalacing(root[0]);    
        printf("%d\n", balacing);   
}


int main(int argc, char const *argv[])
{
    word **root = (word**)malloc(sizeof(word*));
    root[0] = NULL;

    add(root, "d");
    add(root, "c");
    add(root, "b");
    add(root, "a");

    
    
    return 0;
}



