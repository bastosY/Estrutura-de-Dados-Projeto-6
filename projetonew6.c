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


int getHeight(word *root){
    if(root == NULL){
        return -1;
    }
    else{
        return root->height;
    }
}

int getBalacing(word *root){
    return getHeight(root->right) - getHeight(root->left);
}

int comparation(int right, int left){
    if(right > left){
        return right;
    }
    else if(left == right){
        return -1;
    }
    else{
        return left;
    }
}

word *rotationLeft(word *root){
    //printf("Emtrada: %s ",root->name);
    word *aux = root->right;
    root->right = aux->left;
    aux->left = root;
    root->height = comparation(getHeight(root->right), getHeight(root->left))+1;;
    aux->height = comparation(getHeight(aux->right), root->height)+1;
    //printf("saida: %s ",aux->name);
    return aux;
}

word *rotationRight(word *root){
    //printf("Entrada: %s ",root->name);
    word *aux = root->left;
    root->left = aux->right;
    aux->right = root;
    root->height = comparation(getHeight(root->right), getHeight(root->left))+1;
    aux->height = comparation(getHeight(aux->left), root->height)+1;
    //printf("saida: %s ",aux->name);
    return aux;
    
}

void rotationLeftRight(word *root){
    //word **aux = (word**)malloc(sizeof(word*));
    //aux[0] = *root ->left;
    rotationLeft(root->left);
    rotationRight(root);
}


void rotationRightLeft(word *root){
    //word **aux = (word**)malloc(sizeof(word*));
    //aux[0] = *root ->right;
    rotationLeft(root->right);
    rotationRight(root);
}


word *balance(word *root){

    root->height = getBalacing(root);
    
    if(root->height > 1){
        if(getBalacing(root->right) == -1){
            rotationRightLeft(root);
            
        }
        else{
            root = rotationLeft(root);
        }
    }
    else if(root->height < -1){
        if(getBalacing(root->left) == 1){
            rotationLeftRight(root);
        }
        else{
            root = rotationRight(root);
        }
    }
    root->height = comparation(getHeight(root->right), getHeight(root->left))+1;
    return root;
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
void PED(word *root){

    if(root == NULL){
        return;
    }
    else{
        printf("%s::%d\n", root->name,root->height);
    
        PED(root->left);
        PED(root->right);
    }
}

int main(int argc, char const *argv[])
{
    word **root = (word**)malloc(sizeof(word*));
    *root  = NULL;

    insert(root, "d");
    //*root = balance(*root );  
    insert(root, "c");
    //*root = balance(*root );  
    insert(root, "b");
    //*root = balance(*root );  
    insert(root,  "a");
    //*root = balance(*root );  
    //insert(root, "c");
    //insert(root, "b");
    //insert(root, "a");
   
    PED(*root );
    return 0;


}
