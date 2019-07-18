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

word *rotationLeft(word **root){
     printf("Emtrada: %s ",root[0]->name);
    word *aux = root[0]->right;
    root[0]->right = aux->left;
    aux->left = root[0];
    root[0]->height = calcultatorBalacing(root[0]);
    aux->height = calcultatorBalacing(aux);
     printf("saida: %s ",aux->name);
    return aux;
}

word *rotationRight(word **root){
     printf("Entrada: %s ",root[0]->name);
    word *aux = root[0]->left;
    root[0]->left = aux->right;
    aux->right = root[0];
    root[0]->height = calcultatorBalacing(root[0]);
    aux->height = calcultatorBalacing(aux);
    printf("saida: %s ",aux->name);
    return aux;
    
}

void rotationLeftRight(word **root){
    word **aux = (word**)malloc(sizeof(word*));
    aux[0] = root[0]->left;
    rotationLeft(aux);
    rotationRight(root);
}


void rotationRightLeft(word **root){
    word **aux = (word**)malloc(sizeof(word*));
    aux[0] = root[0]->right;
    rotationLeft(aux);
    rotationRight(root);
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

word *balacing(word **root, int height);

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
        
    int heightNo = calcultatorBalacing(root[0]);
    root[0] = balacing(root, heightNo);

    if(root[0]->right != NULL && root[0]->left != NULL){
        if(root[0]->right->height == 1 && root[0]->left->height == 0){
            root[0]->height = root[0]->right->height;
        }
        else if(root[0]->right->height == 0 && root[0]->left->height == 1){
            root[0]->height = root[0]->left->height;
        }  
        else{
            root[0]->height = comparation(getHeight(root[0]->right), getHeight(root[0]->left))+1;
        }
    }
    else{
        root[0]->height = comparation(getHeight(root[0]->right), getHeight(root[0]->left))+1;
    }

    PED(root[0]);
    getchar();

}

word *balacing(word **root, int height){

    word *newRoot;

    if(height > 1){
        printf("ENTROU 1 ");
        if(calcultatorBalacing(root[0]->right) == -1){
             printf("ENTROU 3 ");
            rotationRightLeft(root);
        }
        else{
            //father->right = root[0];
            newRoot = rotationLeft(root);
            root[0] = newRoot;
        }
    }

    else if (height < -1){
        printf("ENTROU 2 ");
        if(calcultatorBalacing(root[0]->left) == 1){
             printf("ENTROU 4 ");
            rotationLeftRight(root);
        }
        else{
            printf("QQ: %s\n", root[0]->name);
            newRoot = rotationRight(root);
            printf("\nKK: %s\n", newRoot->name);
            printf("YY: %s\n", root[0]->name);
            return newRoot;
        }
    }
    else{
        return root[0];
    }

}


int main(int argc, char const *argv[])
{
    word **root = (word**)malloc(sizeof(word*));
    root[0] = NULL;

    add(root, "j");
    add(root, "i");
    add(root, "g");
    add(root,  "h");
    add(root, "c");
    add(root, "b");
    add(root, "a");
    PED(root[0]);

    return 0;
}