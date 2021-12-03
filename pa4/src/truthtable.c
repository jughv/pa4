#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum {
    AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER
} kind_t;
struct gate {
    kind_t kind; // indicates size of DECODER and MULTIPLEXER
    int size;// length determined by kind and size;
    int *params; // includes inputs and outputs, indicated by variable numbers

};

struct node { // nodes for linked list
    char name[10];
    int ind;
    struct node *next;
};

struct circuit { // stores each circuit
    int *values;
    struct gate *gates;
};


int newInd(struct node *root, char *name, int numVar) { //creates an index for use
    while (root->next != NULL) {
        root = root->next;
    }
    root->next = malloc(sizeof(struct node));
    root = root->next;
    strcpy(root->name, name);
    root->ind = numVar++;
    root->next = NULL;
    return root->ind;
}


int findInd(struct node *root, char *name) { // finds the index
    while (root != NULL) {
        if (strcmp(root->name, name) == 0) {
            return root->ind;
        }
        root = root->next;
    }
    return -1;
}





int main(int argc, char **argv) {

    struct node *root = malloc(sizeof(struct node));
    struct node *ptr = root;
    struct circuit *cirq = malloc(sizeof(struct circuit));
    cirq->gates = malloc(sizeof(struct gate));

    int i =0, numGates = 0, numOut = 0 , NumIn = 0, totalVar = 2, numVar =2;
    char input[17];

    FILE *f = fopen(argv[1], "r");
    fscanf(f, "%6s ", input);

    if (strcmp(input, "INPUT") == 0) { //reads input
        int num = 0;
        fscanf(f, " %d", &num);
        NumIn = num;
        totalVar += num;
        fscanf(f, " %s", root->name);
        root->ind = numVar++;
        for (i = 1; i < num; i++) {
            ptr->next = malloc(sizeof(struct node));
            ptr = ptr->next;

            fscanf(f, " %s", ptr->name);
            ptr->next = NULL;
            ptr->ind = numVar++;
        }
    }

    fscanf(f, " %6s", input);
    if (strcmp(input, "OUTPUT") == 0) { //reads output
        int num = 0;
        fscanf(f, " %d", &num);     
        numOut = num;
        totalVar += num;
        ptr->next = malloc(sizeof(struct node));
        ptr = ptr->next;
        fscanf(f, " %s", ptr->name);
        ptr->ind = numVar++;
        for (i = 1; i < num; i++) {
            ptr->next = malloc(sizeof(struct node));
            ptr = ptr->next;
            fscanf(f, " %16s", ptr->name);
            ptr->ind = numVar++;

        }
        ptr->next = NULL;
        ptr = root;


    }

    while (fscanf(f, " %16s", input) != EOF) { //create and gate

        if (strcmp(input, "AND") == 0) {
            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);

            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }
            
            int index = 0;
            free(cirq->gates);
            cirq->gates = temp;
            cirq->gates[numGates - 1].size = 0;
            cirq->gates[numGates - 1].kind = AND;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * 3);
            
            for (int i = 0; i < 3; i++) {
                fscanf(f, " %16s", input);
                if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;   
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;
            }

        } else if (strcmp(input, "OR") == 0) { //create or gate
            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }    

            int index = 0;
            free(cirq->gates);
            cirq->gates = temp;
            cirq->gates[numGates - 1].size = 0;
            cirq->gates[numGates - 1].kind = OR;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * 3);
            
            for (int i = 0; i < 3; i++) {
                fscanf(f, "%s", input);
               if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                        
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;
            }

        } else if (strcmp(input, "NOR") == 0) { //create nor gate
            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }

            int index = 0;
            free(cirq->gates);
            cirq->gates = temp;
            cirq->gates[numGates - 1].size = 0;
            cirq->gates[numGates - 1].kind = NOR;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * 3);

            for (int i = 0; i < 3; i++) {
                fscanf(f, "%s", input);
                if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;
            }

        } else if (strcmp(input, "XOR") == 0) { //create xor gate
            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }

            int index = 0;
            free(cirq->gates);
            cirq->gates = temp;
            cirq->gates[numGates - 1].size = 0;
            cirq->gates[numGates - 1].kind = XOR;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * 3);

            for (int i = 0; i < 3; i++) {
                fscanf(f, "%s", input);
               if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;
            }
            
        } else if (strcmp(input, "NAND") == 0) { //create nand gate
            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }

            int index = 0;
            free(cirq->gates);
            cirq->gates = temp;
            cirq->gates[numGates - 1].size = 0;
            cirq->gates[numGates - 1].kind = NAND;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * 3);

            for (int i = 0; i < 3; i++) {
                fscanf(f, "%s", input);
                if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                }else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;
            }
        
        } else if (strcmp(input, "PASS") == 0) { //create pass gate
            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }

            int index = 0;
            free(cirq->gates);
            cirq->gates = temp;
            cirq->gates[numGates - 1].size = 0;
            cirq->gates[numGates - 1].kind = PASS;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * 3);

            for (int i = 0; i < 2; i++) {
                fscanf(f, "%s", input);
                if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;
            }
        } else if (strcmp(input, "NOT") == 0) { //create not gate
                        numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }

            int index = 0;
            free(cirq->gates);
            cirq->gates = temp;
            cirq->gates[numGates - 1].size = 0;
            cirq->gates[numGates - 1].kind = NOT;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * 3);

            for (int i = 0; i < 2; i++) {
                fscanf(f, "%s", input);
                if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;
            }
        } else if (strcmp(input, "DECODER") == 0) { //create decoder gate
            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }
            
            int index = 0;
            int num = 0;
            fscanf(f, "%d", &num);
            free(cirq->gates);
            cirq->gates = temp;  
            cirq->gates[numGates - 1].size = num;
            cirq->gates[numGates - 1].kind = DECODER;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * (num + pow(2, num)));
            
            for (int i = 0; i < num + pow(2, num); i++) {
                fscanf(f, "%s", input);
                if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                } else if (strcmp(input, "_") == 0){
                    index = -99;
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;

            }
        } else if (strcmp(input, "MULTIPLEXER") == 0) { //create multiplexer gate

            numGates++;
            struct gate *temp = malloc(sizeof(struct gate) * numGates);
            for (i = 0; i < numGates - 1; i++){
                temp[i] = cirq->gates[i];
            }
            
            int index = 0;
            int num = 0;
            fscanf(f, "%d", &num);
            free(cirq->gates);
            cirq->gates = temp;  
            cirq->gates[numGates - 1].size = num;
            cirq->gates[numGates - 1].kind = MULTIPLEXER;
            cirq->gates[numGates - 1].params = malloc(sizeof(int) * (num + pow(2, num) + 1));
            for (int i = 0; i < num + pow(2, num) + 1; i++) {
                fscanf(f, "%s", input);
                if (strcmp(input, "1") == 0){
                    index = 1;
                } else if (strcmp(input, "0") == 0){
                    index = 0;
                } else {
                    index = findInd(root, input);
                    if (index == -1) {
                        index = newInd(root, input, numVar);
                        totalVar++;
                        numVar++;
                    }

                }
                cirq->gates[numGates - 1].params[i] = index;

            }
        }
        
    }


    cirq->values = (int *) malloc(totalVar * sizeof(int));
    cirq->values[0] = 0;
    cirq->values[1] = 1;


    int n = pow(2, NumIn);

    for (int j = 0; j < n; j++) {
        int num = j;
        for (i = NumIn + 1; i >= 2; i--) {
            if (num != 0) {
                cirq->values[i] = num % 2;
                num /= 2;
            } else
                cirq->values[i] = 0;
        }

        for (i = 2; i < NumIn + 2; i++) {
            printf("%d ", cirq->values[i]);
        }

        for (i = NumIn + 2; i < totalVar; i++) {
            cirq->values[i] = -1;
        }

        printf("|");
        for (i = 0; i < numGates; i++) {
            int j = 0;
            struct gate g = cirq->gates[i];

            if (g.kind == AND) {
                if (cirq->values[g.params[0]] == -1 || cirq->values[g.params[1]] == -1) {
                    struct gate temp = g;
                    for (int k = i; k < numGates - 1; k++) {
                        cirq->gates[k] = cirq->gates[k+1];
                    }
                    i--;
                    cirq->gates[numGates-1] = temp;
                    continue;
                }
                cirq->values[g.params[2]] = (cirq->values[g.params[0]] == 1 && cirq->values[g.params[1]] == 1);

            } else if (g.kind == OR) {
                if (cirq->values[g.params[0]] == -1 || cirq->values[g.params[1]] == -1) {
                    struct gate temp = g;
                    for (int k = i; k < numGates - 1; k++) {
                        cirq->gates[k] = cirq->gates[k+1];
                    }
                    i--;
                    cirq->gates[numGates-1] = temp;
                    continue;
                }
                cirq->values[g.params[2]] = (cirq->values[g.params[0]] == 1 || cirq->values[g.params[1]] == 1);

            } else if (g.kind == XOR) {
                if (cirq->values[g.params[0]] == -1 || cirq->values[g.params[1]] == -1) {
                    struct gate temp = g;
                    for (int k = i; k < numGates - 1; k++) {
                        cirq->gates[k] = cirq->gates[k+1];
                    }
                    i--;
                    cirq->gates[numGates-1] = temp;
                    continue;
                }
                cirq->values[g.params[2]] = (cirq->values[g.params[0]] != cirq->values[g.params[1]]);
               
            } else if (g.kind == NOR) {
                if (cirq->values[g.params[0]] == -1 || cirq->values[g.params[1]] == -1) {
                    struct gate temp = g;
                    for (int k = i; k < numGates - 1; k++) {
                        cirq->gates[k] = cirq->gates[k+1];
                    }
                    i--;
                    cirq->gates[numGates-1] = temp;
                    continue;
                }
                cirq->values[g.params[2]] = (cirq->values[g.params[0]] == 0 && cirq->values[g.params[1]] == 0);

            } else if (g.kind == NAND) {
                if (cirq->values[g.params[0]] == -1 || cirq->values[g.params[1]] == -1) {
                    struct gate temp = g;
                    for (int k = i; k < numGates - 1; k++) {
                        cirq->gates[k] = cirq->gates[k+1];
                    }
                    i--;
                    cirq->gates[numGates-1] = temp;
                    continue;
                }
                cirq->values[g.params[2]] = !((cirq->values[g.params[0]] == cirq->values[g.params[1]]) &&
                                           (cirq->values[g.params[0]] == 1));
               
            } else if (g.kind == PASS) {
                if (cirq->values[g.params[0]] == -1) {
                    struct gate temp = g;
                    for (int k = i; k < numGates - 1; k++) {
                        cirq->gates[k] = cirq->gates[k+1];
                    }
                    i--;
                    cirq->gates[numGates-1] = temp;
                    continue;
                }
                cirq->values[g.params[1]] = cirq->values[g.params[0]];
            } else if (g.kind == NOT) {
                if (cirq->values[g.params[0]] == -1) {
                    struct gate temp = g;
                    for (int k = i; k < numGates - 1; k++) {
                        cirq->gates[k] = cirq->gates[k+1];
                    }
                    i--;
                    cirq->gates[numGates-1] = temp;
                    continue;
                }
                if (cirq->values[g.params[0]] == 1){
                    cirq->values[g.params[1]] = 0;
                } else{
                    cirq->values[g.params[1]] = 1;
                }
            } else if (g.kind == DECODER) {
                num = 0;
                for (j = 0; j < g.size; j++) {
                    if (cirq->values[g.params[j]] == 1)
                        num += pow(2, g.size - j - 1);
                }
                while (j < g.size + pow(2, g.size)) {
                    if (g.params[j] == -99){
                        continue;
                    } else if (j - g.size == num) {
                        cirq->values[g.params[j]] = 1;
                    } else{
                        cirq->values[g.params[j]] = 0;
                    }
                    j++;    
                }

            } else if (g.kind == MULTIPLEXER) {
                num = 0;
                for (j = pow(2, g.size); j < pow(2, g.size) + g.size; j++) {
                    if (cirq->values[g.params[j]] == -1) {
                        struct gate temp = g;
                        for (int k = i; k < numGates - 1; k++) {
                            cirq->gates[k] = cirq->gates[k + 1];
                        }
                        i--;
                        cirq->gates[numGates - 1] = temp;
                        
                        continue;
                    }
                    if (cirq->values[g.params[j]] == 1)
                        num += pow(2, g.size - j + pow(2, g.size) - 1);
                }
                for (j = 0; j < pow(2, g.size); j++) {
                    if (j == num) {
                        cirq->values[g.params[g.size + (int) pow(2, g.size)]] = cirq->values[g.params[j]];
                        break;
                    }
                }

            }

        }

        for (i = NumIn + 2; i < NumIn + 2 + numOut; i++) {
            printf(" %d", cirq->values[i]);
        }
        printf("\n");
    }


    while (numGates != 0){
        free(cirq->gates[numGates-1].params); // free parameters
        numGates --;
    }
    ptr = root;
    while (ptr != NULL){ //free linked list
        ptr = ptr->next;
        free(root);
        root = ptr;
    }
    free(cirq->gates); //free gates
    free(cirq->values); //free values
    free(cirq); // free circuit
    return EXIT_SUCCESS;
}