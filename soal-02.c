/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 8 - Advanced Algorithms
*Percobaan        : -
*Hari dan Tanggal : Selasa, 12 April 2022
*Nama (NIM)       : -
*Asisten (NIM)    : -
*Nama File        : soal-02.c
*Deskripsi        : -
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *environment;    // pointer untuk matriks 2 dimensi
static int columnSize = 5;  // ukuran kolom dari environment
static int rowSize = 5; // ukuran baris dari environment
int *visitedState; // pointer untuk array dari state yang telah dikunjungi (inisial nilai elemen-elemennya adalah -1)

// =========================================================================
// Fungsi : initEnvironment
// Deskripsi : inisialisasi environment
void initEnvironment(){
	environment = (char*)calloc(columnSize*columnSize, sizeof(char));

	for(int i = 0; i < rowSize; i++){
		if(i == 0){
			*(environment+i*columnSize+0) = '0';
			*(environment+i*columnSize+1) = 'x';
			*(environment+i*columnSize+2) = '0';
			*(environment+i*columnSize+3) = 'x';
			*(environment+i*columnSize+4) = '0';
		}
		else if(i == 1){
			*(environment+i*columnSize+0) = '0';
			*(environment+i*columnSize+1) = '0';
			*(environment+i*columnSize+2) = '0';
			*(environment+i*columnSize+3) = '0';
			*(environment+i*columnSize+4) = '0';
		}
		else if(i == 2){
			*(environment+i*columnSize+0) = 'x';
			*(environment+i*columnSize+1) = 'x';
			*(environment+i*columnSize+2) = '0';
			*(environment+i*columnSize+3) = 'x';
			*(environment+i*columnSize+4) = 'x';
		}
		else if(i == 3){
			*(environment+i*columnSize+0) = '0';
			*(environment+i*columnSize+1) = '0';
			*(environment+i*columnSize+2) = '0';
			*(environment+i*columnSize+3) = '0';
			*(environment+i*columnSize+4) = '0';
		}
		else if(i == 4){
			*(environment+i*columnSize+0) = '0';
			*(environment+i*columnSize+1) = 'x';
			*(environment+i*columnSize+2) = '0';
			*(environment+i*columnSize+3) = 'x';
			*(environment+i*columnSize+4) = '0';
		}
	}

	// ---------------- UNTUK TEST -------------------------------
	// for(int i = 0; i < columnSize; i++){
	//     for(int j = 0; j < columnSize; j++){
	//         printf("Test: %c", *(environment + i*columnSize + j));
	//     }
	//     printf("\n");
	// }
	// -----------------------------------------------------------
}

// =========================================================================
// Fungsi : isNotVisited
// Deskripsi : Menentukan apakah state tertentu sudah dikunjungi atau belum
// Parameter:
//     state : state yang ingin dicek
//     *visitedState : array yang berisi state-state yang telah dikunjungi
int isNotVisited(int state, int *visitedState){
	for(int i = 0; i<columnSize*rowSize; i++){
		if(*(visitedState+i) == state){
			return 0;
		}
	}
	
	return 1;
}

// =================================================================================================================
// Fungsi : isMoveValid
// Deskripsi : Menentukan apakah pergerakan ke kanan, atas, kiri, atau bawah dari sebuah state tidak menabrak tembok
// Parameter:
//     currentState : posisi state yang ingin dicek
//     action : pergerakan yang dicek ( 0: kanan, 1: atas, 2: kiri, 3: bawah )
//     output : 1 : tidak menabrak tembok, 0 : menabrak tembok
int isMoveValid(int currentState, int action){
	int rowState;
	int columnState;

	rowState = currentState/columnSize; // Menentukan posisi baris
	columnState = currentState%columnSize; // Menentukan posisi kolom
	
	// Action ke kanan
	if(action == 0){
		if(columnState != columnSize-1){
			if(*(environment+currentState+1) == '0'){
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	// Action ke atas
	else if(action == 1){
		if(rowState != 0){
			if(*(environment+currentState-columnSize) == '0'){
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	// Action ke kiri
	else if(action == 2){
		if(columnState != 0){
			if(*(environment+currentState-1) == '0'){
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	// Action ke bawah
	else if(action == 3){
		if(rowState != rowSize-1){
			if(*(environment+currentState+columnSize) == '0'){
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
		
}

// =========================================================================
// Fungsi : deepFirstSearch
// Deskripsi : mencari path dengan algoritma DFS
// Parameter:
// 
// 
int deepFirstSearch(..., ..., ...){
	// ------------ Tulis kode anda pada bagian ini ----------------------- //
}

// =========================================================================
// Fungsi : searchPath
// Deskripsi : sebagai wrapper fungsi deepFirstSearch dan inisialisasi array visitedState
// Parameter:
//     *currentState : posisi state robot saat ini
//     *destinationState : posisi state tujuan
void searchPath(int *currentState, int *destinationState){
	// Mengalokasikan memori
	visitedState = (int*)malloc(columnSize*rowSize*sizeof(int));

	// Inisialisasi array visitedState
	for(int i = 0; i<columnSize*rowSize; i++){
		*(visitedState + i) = -1;
	}

	// Mencari path dengan algoritma DFS
	deepFirstSearch(..., ..., ...);
}

int main(){
	int start;
	int dest;

	// Inisialisasi environment
	initEnvironment();

	// Memasukkan input
	printf("State mulai: ");
	scanf("%d",&start);
	printf("State tujuan: ");
	scanf("%d",&dest);
	
	// Mencari jalan
	searchPath(&start, &dest);

	// Dealokasi dynamic array
	free(environment);
	free(visitedState);

	return 0;
}
