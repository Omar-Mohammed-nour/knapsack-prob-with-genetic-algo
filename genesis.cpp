#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <cstring>

//#include "geneH.h"

using namespace std;

#define newline cout << "\n"

#define space " "
//value for parent
#define value_p "Value :"
//weight for parent
#define weight_p "Weight :"

//generate random float number between 0 and 1
float random_float() {
    srand(time(NULL));
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

//how or what to add to our vector
struct parentel {
    int val;
    int weight;
};

//our actual parents and their sum values
struct parents {
    int parentNumber;
    int uniValue;
    int uniWeight;
};

int main() {
    srand(time(NULL));

    int randro = 4;

	const int PBrows = 4;
    const int Pcolms = 4;
    const int Bcolms = 2;

    //our boxes
	int boxes[PBrows][Bcolms] = {
	{4, 2},
	{8, 1},
	{9, 9},
	{7, 3}
	};

    int binariesP[PBrows][Pcolms] = {};
    

	for (int i = 0; i <= PBrows; i++) {
		//for each cell
		for (int k = 0; k <= Pcolms; k++) {
			int randNum = rand() % 2;
			//cout << "rand nums : " << randNum << endl;
			binariesP[i][k] = randNum;
		}
	}

    int generations = 3, gene = 0;

while (gene < generations) {
    cout << "Generation :" << gene;
    newline;

    //our vector
	vector<parentel> parent;

    const int Piter = 3, Biter = 3;
    //adding values to vector
    for (int i = 0; i <= Piter; i++) {
        parent.push_back({boxes[i][0], boxes[i][1]});
    }

    const int parent_vect_num = 3;
    //printing vector values and how to acces them
    /*
    for (int i = 0; i <= parent_vect_num; i++)
	    cout << value_p << parent[i].val << space << weight_p << parent[i].weight << "\n";
	*/
	
    vector<parents> ParentValu;

        for (int i = 0; i <= parent_vect_num; i++) {
        int tempVal = 0, tempWeight = 0;
        for (int k = 0; k <= 3; k++) {
            if (binariesP[i][k] == 1) {
                tempVal += parent[k].val;
                tempWeight += parent[k].weight;
            }
        }
        if (tempWeight >= 15) {
            tempVal = 0;
        }
        ParentValu.push_back({i, tempVal, tempWeight});
        cout << "Parent[" << ParentValu[i].parentNumber + 1 << 
        "] :\n" << value_p << ParentValu[i].uniValue << "\n" << weight_p << ParentValu[i].uniWeight << "\n";


    }

    //tournament selection
    
    int children[PBrows][Pcolms] = {};
    
    int x, y;

    for (int z = 0; z <= 2; z++) {//this runs for 4 times 
        x = rand() % randro, y = rand() % randro;
        if (x == y) {
            if (x == 3 & y == 3) {
                x -= 1;
                y -= 2;
            }
            else if (x == 0 & y == 0) {
                y += 1;
            }
            else {
                x += 1;
                y -= 1;
            }
        }

        if (ParentValu[x].uniValue > ParentValu[y].uniValue) {
            for (int i = 0; i <= Pcolms; i++) {
                children[z][i] = binariesP[x][i];
            }
        }
        else if (ParentValu[x].uniValue < ParentValu[y].uniValue) {
            for (int i = 0; i <= Pcolms; i++) {
                children[z][i] = binariesP[y][i];
            }
        }
    cout << "parent X :" << ParentValu[x].parentNumber << space << "parent Y :" << ParentValu[y].parentNumber << space << "X Val :" << ParentValu[x].uniValue << space << "Y Val :" << ParentValu[y].uniValue << space << "X weight :" << ParentValu[x].uniWeight << space << "Y weight :" << ParentValu[y].uniWeight;
    newline;
    }
    
    for (int i = 0; i <= 3; i++) {
        for (int k = 0; k <= 3; k++) {
            cout << binariesP[i][k] << ", ";
        }
        newline;
    }
        
    memcpy(binariesP, children, sizeof(children));

    //all the side tasks and cross over, mutation
    bool isCrossed = false;
    float xR = random_float();
    const float crossover_rate = 0.5;//this should be 0.5 but its whatever it is for testing 

    if (x <= crossover_rate) {//this shoulf be x < crossover_rate but it is whatever it is for testing
        isCrossed = true;
        
        binariesP[0][1] = binariesP[1][0];
        binariesP[0][0] = binariesP[1][1];

        binariesP[1][1] = binariesP[0][2];
        binariesP[1][0] = binariesP[0][3];

    
        binariesP[2][1] = binariesP[3][0];
        binariesP[2][0] = binariesP[3][1];

        binariesP[3][1] = binariesP[2][2];
        binariesP[3][0] = binariesP[2][3];

        cout  << "after crossover";
        
        newline;
        for (int i = 0; i <= 3; i++) {
            for (int k = 0; k <= 3; k++) {
                cout << binariesP[i][k] << ", ";
            }
            newline;
        }
    }
        

if (isCrossed) {
    const float mutation_rate = 0.1;//this should be 0.2 but it is whatever it is for testing
    
    for (int i = 0;  i <= 2; i++) {
        for (int k = 0; k <= 3; k++) {
            float xre = random_float();
            if (xre <= mutation_rate) {//this should be xre < mutation_rate but it is whatever it is for testing
                if (binariesP[i][k] == 0) {
                    binariesP[i][k] = 1;
                }
                else if (binariesP[i][k] == 1) {
                    binariesP[i][k] = 0;
                }
                cout << "We Mutated!!!";
            }
        }
    }
}


    newline;
    
    //copy all items back to parents to do the genereations loop
    //memcpy(binariesP, children, sizeof(children));
    //     ^^ destination
    //                ^^ source
    //                          ^^ size of source
    

    newline;newline;


    
        for (int i = 0; i <= 3; i++) {
            for (int k = 0; k <= 3; k++) {
                cout << children[i][k] << ", ";
            }
            newline;
        }
    
        cout << "^^source array^^:";
        newline;


        for (int i = 0; i <= 3; i++) {
            for (int k = 0; k <= 3; k++) {
                cout << binariesP[i][k] << ", ";
            }
            newline;
        }

        cout << "^^destination array^^";

    
        int checker = 0;
        for (int i = 0; i <= 3; i++) {
            for (int k = 0; k <= 3; k++) {
                checker += binariesP[i][k];
            }
        }

        if (checker == 0) {
            newline;
            cout << "this generation is 'infertile' no more generations possible";
            break;
        }


    newline;
    newline;
    gene++;
}
}
