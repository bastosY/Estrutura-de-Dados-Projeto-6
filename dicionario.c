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
        return 1;
    }
    else{
        return root->height;
    }
}

void calcultatorBalacing(word *root){
    root->height = getHeight(root->left) - getHeight(root->right);
    
}
/*
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
*/

void add(word *root, char name[31]){


    if(strcmp(root->name, "aaaaF") == 0){
        
        root = initWord(name);
    }

    else if(strcmp(root->name, name) < 0){
        if(root->right != NULL){
            add(root->right, name);
        }     
        else{
            root->right = initWord(name);
            calcultatorBalacing(root);
            //balacing(root);
            
        }
    }

    else if(strcmp(root->name, name) > 0){
        if(root->left != NULL){
            add(root->left, name);
            
        }
        else{
            root->left = initWord(name); 
            calcultatorBalacing(root);
            //balacing(root);
            
        }
    }
}


void PED(word *root){

    if(root == NULL){
        return;
    }
    else{
        printf("%s\n", root->name);
        PED(root->left);
        PED(root->right);
    }
}

int main(int argc, char const *argv[])
{
    word *root = (word*)malloc(sizeof(word));
    

    add(root, "a");
    PED(root);
    
    //printf("%s", root->name);
    
   
    return 0;
}



