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
//     *currentState : posisi state robot saat ini
//     *destinationState : posisi state tujuan
//     *counter : counter untuk menyimpan banyaknya perulangan yang telah terjadi
int deepFirstSearch(int *currentState, int *destinationState, int counter){
	// mengupdate state yang telah dikunjungi
	*(visitedState + counter) = *currentState;

	// Bila path ditemukan
	if(*currentState == *destinationState){
		for(int i = 0; i<counter; i++){
			printf("%d->", *(visitedState + i));
		}
		printf("%d Goal!", *currentState);
		printf("\n");
		return 1;
	}

	// Depth First Search
	// 1) bergerak ke kanan terus sampai mentok
	// 2) bergerak ke atas dan mengulang step pertama sampai tidak bisa bergerak ke atas lagi
	// 3) bergerak ke kiri dan mengulang step pertama dan kedua sampai tidak bisa bergerak ke kiri lagi
	// 4) bergerak ke bawah dan mengulang step pertama, kedua, dan ketiga sampai tidak bisa bergerak ke bawah lagi
	// 5) Apabila sudah mencapai ujung, kembali ke state sebelumnya 

	// Mengecek apakah bergerak ke kanan valid
	if(isMoveValid(*currentState, 0) && isNotVisited(*currentState+1, visitedState)){
		// Robot bergerak ke kanan
		*currentState += 1;
		deepFirstSearch(currentState, destinationState, counter+1);

		// Apabila sudah mentok, robot akan kembali
		*currentState -= 1;
	}

	// Mengecek apakah bergerak ke atas valid
	if(isMoveValid(*currentState, 1) && isNotVisited(*currentState-columnSize, visitedState)){
		// Robot bergerak ke atas
		*currentState -= columnSize;
		deepFirstSearch(currentState, destinationState, counter+1);
		
		// Apabila sudah mentok, robot akan kembali
		*currentState += columnSize;
	}

	// Mengecek apakah bergerak ke kiri valid
	if(isMoveValid(*currentState, 2) && isNotVisited(*currentState-1, visitedState)){
		// Robot bergerak ke kiri
		*currentState -= 1;
		deepFirstSearch(currentState, destinationState, counter+1);
		
		// Apabila sudah mentok, robot akan kembali
		*currentState += 1;
	}

	// Mengecek apakah bergerak ke bawah valid
	if(isMoveValid(*currentState, 3) && isNotVisited(*currentState+columnSize, visitedState)){
		// Robot bergerak ke bawah
		*currentState += columnSize;
		deepFirstSearch(currentState, destinationState, counter+1);
		
		// Apabila sudah mentok, robot akan kembali
		*currentState -= columnSize;
	}

	// Bila sudah tidak ada pergerakan yang memungkinkan, kembali ke state sebelumnya
	*(visitedState + counter) = -1;

	return 0;
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

	// Inisialisasi
	for(int i = 0; i<columnSize*rowSize; i++){
		*(visitedState + i) = -1;
	}

	// Mencari Path
	deepFirstSearch(currentState, destinationState, 0);
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

	// Mencari path kalau masukan benar. Ketika praktikum, input diasumsikan selalu benar
	if (*(environment+start) != 'x' && *(environment+dest) != 'x' ){
		searchPath(&start, &dest);
	}
	else{
		printf("State masukan tidak valid!");
	}

	// dealokasi dynamic array
	free(environment);
	free(visitedState);

	return 0;
}
