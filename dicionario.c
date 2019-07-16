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
    root->right = eixo->left;
    eixo->left = root;
    root = eixo;
}

void rotationRight(word *root){
    word *eixo = root->left;
    root->left = eixo->right;
    eixo->right = root;
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
        return -1;
    }
    else{
        return root->height;
    }
}

int calcultatorBalacing(word *root){
    return getHeight(root->left) - getHeight(root->right);
    
}

void balacing(word *root){
    if(calcultatorBalacing(root) == 2){
        if(calcultatorBalacing(root->right) == -1){
            rotationRightLeft(root);
        }
        else{
            rotationLeft(root);
        }
    }
    else if(calcultatorBalacing(root) == -2){
        if(calcultatorBalacing(root->left) == 1){
            rotationLeftRight(root);
        }
        else{
            rotationRight(root);
        }
    }
    else{
        root->height = comparation(getHeight(root->left), getHeight(root->right));
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
            root[0]->height = comparation(getHeight(root[0]->left), getHeight(root[0]->right) + 1);
            
            balacing(root[0]);
            
        }
    }

    else if(strcmp(root[0]->name, name) > 0){
        if(root[0]->left != NULL){
            aux[0] = root[0]->left;
            add(aux, name);
            
        }
        else{
            root[0]->left = initWord(name); 
    
            root[0]->height = comparation(getHeight(root[0]->left), getHeight(root[0]->right) + 1);
            
            balacing(root[0]);
            
        }
    }

    PED(aux[0]);

}


int main(int argc, char const *argv[])
{
    word **root = (word**)malloc(sizeof(word*));
    root[0] = NULL;

    add(root, "a");
    add(root, "b");
    add(root, "c");
    
  
    
   
    return 0;
}



