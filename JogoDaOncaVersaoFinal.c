#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

short int mapa[7][5];
long int timer[3] = {0,0,0};

void MostrarMapa(int y, int x);

int Possiveis(int PosY,int PosX, int Animal, bool printar);

int ValidarJogada(int y, int x, int posY, int posX);

void cpu(int *OncaY, int *OncaX, short int mortes);

void movimentoOnca(int *OncaY, int *OncaX, short int mortes);

void movCachorro(int *y,int *x, int posY, int posX, bool bot, short int mortes);

void movimentoCacho(int *y, int *x, bool bot, short int mortes);

int dica(int y, int x, int animal, bool bot, int posYo, int posXo){
	short int guardarY, guardarX, z = 0;
	
	if(animal == 1 && bot == true && Possiveis(posYo, posXo, 2, false) == 2){
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				if(ValidarJogada(i,j,y,x) == 0){
					mapa[y + i][x + j] = 1;
					if(Possiveis(posYo, posXo, 2, false) != 2){
						mapa[y + i][x + j] = 0;
						printf("\nA posicao da Linha:%d e Coluna:%d voce evita uma captura.\n", y + i + 1, x + j + 1);
						return 0;
					}
					mapa[y + i][x + j] = 0;
				}
			}
		}
	}
	
	if(animal == 1){
		for(int i = -1; i < 2; i++)
			for(int j = -1; j < 2; j++){
				if(ValidarJogada(i, j, y, x) == 0){
					for(int l = -1; l < 2; l++){
						for(int p = -1; p < 2; p++){
							if(mapa[y + i + l][x + j + p] == 2){
								z = 1;
								}
						}
					}
					if(z == 0){
						printf("\nA posicao da Linha:%d e Coluna:%d eh possivelmente a melhor escolha.\n",y+i+1,x+j+1);
						return 0;
					}
					else{
						z = 0;
					}
					
				}
			}
		for(int i = -1; i < 2; i++)
			for(int j = -1; j < 2; j++)
				if(ValidarJogada(i, j, y, x) == 0){
					printf("\nA posicao da Linha:%d e Coluna:%d eh possivelmente a melhor escolha.\n",y+i+1,x+j+1);
					return 0;
				}
	}
	else{
		if(animal == 2){
			for(int i = -1; i < 2; i++){
				for(int j = -1; j < 2; j++){
					if(mapa[y + i][x + j] == 1 && ValidarJogada(i, j, y, x) == 1 && z == 0){
						printf("\nNa posicao da Linha:%d e Coluna:%d voce pode capturar um cachorro.\n",y+i+1,x+j+1);
						return 0;
					}
					if(i == 1 && j == 1 && z == 0){
						i = -1; j = -1; z = 1;
					}
					if(z == 1){
						for(int l = -1; l < 2; l++){
							for(int p = -1; p < 2; p++){
								if(mapa[y + i + l][x + j + p] == 0 && ValidarJogada(l, p, y + i + l, x + j + p) == 0 && ValidarJogada(i,j,y,x) == 0){
									printf("\nA posicao da Linha:%d e Coluna:%d eh possivelmente a melhor escolha.\n",y+i+1,x+j+1);
									return 0;
								}
						}
					}
					}
				}
			}
		}
}
	return 0;
}

void VitoriaC(){
	system("cls");
	printf("\n===============================================\n");
	printf("\n\tVitoria dos cachorros!\n");
	printf("\n\t%d segundos passados.\n\n", ((clock() - timer[3])/ 1000));
	printf("\n===============================================\n");
	system("pause");
	return;
}

void VitoriaO(){
	system("cls");
	printf("\n===============================================\n");
	printf("\n\tVitoria da Onca!\n");
	printf("\n\t%d segundos passados.\n\n", ((clock() - timer[3])/ 1000));
	printf("\n===============================================\n");
	system("pause");
	return;
}

void pause(){
	system("cls");
	timer[0] = clock() - timer[1];
	timer[1] = 0;
	printf("======================================");
	printf("\n\n\t    JOGO PAUSADO\n\n");
	printf("\n\t%d segundos passados.\n\n", (timer[0] / 1000));
	printf("======================================\n");
	system("pause");
	timer[1] = clock() - timer[0];
	timer[2] += timer[1];
	system("cls");
	MostrarMapa(6, 5);
	return;
}

int Possiveis(int PosY,int PosX, int Animal, bool printar){
	int valido = 0;
	
	
	if(mapa[PosY][PosX] != 1 && Animal == 1)
		return 2;
	
	if(printar == true)
		printf("\n\nJogadas Possiveis:");
	
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(ValidarJogada(i, j, PosY, PosX) == 0){
				if(valido != 2)
					valido = 1;
				if(printar == true){
				if(i == (-1)){
					if(j == (-1)){
						printf("7 ");
					}
					else{
						if(j == 0)
								printf("8 ");
							else{
								if(j == 1)
									printf("9 ");
								}
						}
				}
				if(i == 0){
					if(j == (-1))
						printf("4 ");
						else
							if(j == 1)
								printf("6 ");
					}
				if(i == 1){
					if(j == (-1))
						printf("1 ");
					else
						if(j == 0)
							printf("2 ");
						else
							if(j == 1)
								printf("3 ");
							}
				}
			}
			if(ValidarJogada(i, j, PosY, PosX) == 1 && Animal == 2){
				valido = 2;
				if(printar == true){
				if(i == (-1)){
					if(j == (-1))
						printf("\033[0;31m7 \033[0m");
					else
						if(j == 0)
								printf("\033[0;31m8 \033[0m");
							else
								if(j == 1)
									printf("\033[0;31m9 \033[0m");
				}
				if(i == 0){
					if(j == (-1))
						printf("\033[0;31m4 \033[0m");
					else
						if(j == 0)
							printf("\033[0;31m5 \033[0m");
						else
							if(j == 1)
								printf("\033[0;31m6 \033[0m");
					}
				if(i == 1){
					if(j == (-1))
						printf("\033[0;31m1 \033[0m");
					else
						if(j == 0)
							printf("\033[0;31m2 \033[0m");
						else
							if(j == 1)
								printf("\033[0;31m3 \033[0m");
				}
			}
		}
		}
	}
	if(valido == 1)
		return 1;
	else
		if(valido == 0)
			return 0;
			else
			return 2;
	
}

void MostrarMapa(int y, int x){
	char capa[7][5];
	    
    system("cls");
    
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 5; j++){
            if(mapa[i][j]== 0)
                capa[i][j] = 'o';
            else
                if(mapa[i][j] == 1)
                    capa[i][j] = 'Z';
                else
                    if(mapa[i][j] == 2)
                        capa[i][j] = 'X';
        }
    }
    
    capa[y][x] = '@';
    
    printf("==========================================\n");
    printf("\t(d)DICA   (p)PAUSE   (s)SAIR");
    printf("\n\n");
    printf("\t    1   2   3   4   5\n\n");
    printf("\t1   %c---%c---%c---%c---%c\n", capa[0][0],capa[0][1],capa[0][2],capa[0][3],capa[0][4]);
    printf("\t    | \\ | / | \\ | / | \n");
    printf("\t2   %c---%c---%c---%c---%c\n", capa[1][0], capa[1][1], capa[1][2], capa[1][3], capa[1][4]);
    printf("\t    | / | \\ | / | \\ |\n");
    printf("\t3   %c---%c---%c---%c---%c\n", capa[2][0], capa[2][1], capa[2][2], capa[2][3], capa[2][4]);
    printf("\t    | \\ | / | \\ | / | \n");
    printf("\t4   %c---%c---%c---%c---%c\n", capa[3][0], capa[3][1], capa[3][2], capa[3][3], capa[3][4]);
    printf("\t    | / | \\ | / | \\ |\n");
    printf("\t5   %c---%c---%c---%c---%c\n", capa[4][0], capa[4][1], capa[4][2], capa[4][3], capa[4][4]);
    printf("\t           /|\\ \n");
    printf("\t6         %c-%c-%c\n", capa[5][1], capa[5][2], capa[5][3]);
    printf("\t         /  |  \\\n");
    printf("\t7       %c---%c---%c", capa[6][1], capa[6][2], capa[6][3]);
    
    return;
}

int ValidarJogada(int y, int x, int posY, int posX){
    
    if(posY + y > 6 || posX + x > 4 || posY + y < 0 || posX + x < 0)
        return 2;
        
    if(posY > 4  && (posX + x > 3 || posX + x < 1))
    	return 2;
    
    if((posY + y == 5 && posX + x == 0) || (posY + y == 5 && posX + x == 4)) 
        return 2;

    if((posY + y == 5) && (posX + x == 1 || posX + x == 3)){
        if((posY == 4 && posX == 1) || (posY == 4 && posX == 3)){
            return 2;
        }
    }    
    
    if((posY == 5) && (posX != 2) && (y == (-1)))
    	return 2;
    
    if((posY == 6 && posX >= 1) && (fabs(y) == 1) && (fabs(x) == 1))
    	return 2;
    	
    if((posY == 6 && posX >= 1 && posX != 2) && (fabs(y) == 1))
    	if(mapa[posY + y][posX + x] != 0)
    		return 2;
    
	if(mapa[posY + y][posX + x] == 3)
		return 2;
	 
    if((posY + y == 6) && (posX + x == 2)) 
        if((posY == 5 && posX == 1) || (posY == 5 && posX == 3))
            return 2;
    
    if(posY == 4 && posX == 4)
    	if(posY + y == 5 && posX + x == 3)
    	 return 2;
    
    if(fabs(y) == 1 && fabs(x) == 1)
        if((posY + posX) % 2 != 0)
            return 2;
    
    if(mapa[posY + y][posX + x] == 0)
        return 0;
    else
        if(mapa[posY + y + y][posX + x + x] == 0 && posY + y + y >= 0 && posX + x + x >= 0 && posY + y + y < 7 && posX + x + x <= 4 && mapa[posY + y][posX + x] == 1){
        	if(!(posY == 3 && (posX < 2 || posX > 2) && (y == 1) && (fabs(x) == 0))){
        		return 1;
        	}
        }
    
    return 2;
}

void movCachorro(int *y,int *x, int posY, int posX, bool bot, short int mortes){
	char mov; 
	long int p;
	
	if(mortes >= 5){
		VitoriaO();
		return;
	}
	
	printf("\n\n=============Turno dos Cachorros=============\n");
	
	Possiveis(posY, posX, 1, true);
		
    printf("\n\nDigite a direcao: ");
    scanf("%c", &mov);
    
    if(mov == '\n')
    	scanf("%c", &mov);
    
    switch(mov){
        case '7':
            if(ValidarJogada(-1 , -1, posY, posX) != 0){
                printf("\n Jogada Invalida, tente novamente");
                movCachorro(y, x, posY, posX, bot, mortes);
                return;
            }
            else{
                    mapa[posY][posX] = 0;
                    posY -= 1; posX -= 1;
                    mapa[posY][posX] = 1;
                }
            break;
            
        case '8':
            if(ValidarJogada(-1 , 0, posY, posX) != 0){
                printf("\n Jogada Invalida, tente novamente");
                movCachorro(y, x, posY, posX, bot, mortes);
                return;
            }
            else{
                mapa[posY][posX] = 0;
                posY -= 1; 
                mapa[posY][posX] = 1;
                }
            break;
            
        case '9':
            if(ValidarJogada(-1 , 1,posY, posX) != 0){
                printf("\n Jogada Invalida, tente novamente");
                movCachorro(y, x, posY, posX, bot, mortes);
                return;
            }
                else{
                    mapa[posY][posX] = 0;
                    posY -= 1; posX += 1;
                    mapa[posY][posX] = 1;
                }
            break;
        case '4':
            if(ValidarJogada(0 , -1, posY, posX) != 0){
                    printf("\n Jogada Invalida, tente novamente");
                    movCachorro(y, x, posY, posX, bot, mortes);
                    return;
                }
                    else{
                        mapa[posY][posX] = 0;
                        posX -= 1;
                        mapa[posY][posX] = 1;
                    }
                break;
        case '6':
            if(ValidarJogada(0 , 1, posY, posX) != 0){
                    printf("\n Jogada Invalida, tente novamente");
                    movCachorro(y, x, posY, posX, bot, mortes);
                    return;
                }
                    else{
                        mapa[posY][posX] = 0;
                        posX += 1;
                        mapa[posY][posX] = 1;
                    }
                break;
        case '1':
            if(ValidarJogada(1 , -1,posY, posX) != 0){
                    printf("\n Jogada Invalida, tente novamente");
                    movCachorro(y, x, posY, posX, bot, mortes);
                    return;
                }
                    else{
                        mapa[posY][posX] = 0;
                        posY += 1; posX -= 1;
                        mapa[posY][posX] = 1;
                    }
                break;
        case '2':
            if(ValidarJogada(1 , 0, posY, posX) != 0){
                    printf("\n Jogada Invalida, tente novamente");
                    movCachorro(y, x, posY, posX, bot, mortes);
                    return;
                }
                    else{
                        mapa[posY][posX] = 0;
                        posY += 1;
                        mapa[posY][posX] = 1;
                    }
                break;
        case '3':
            if(ValidarJogada(1 , 1, posY, posX) != 0){
                    printf("\n Jogada Invalida, tente novamente");
                    movCachorro(y, x, posY, posX, bot, mortes);
                    return;
                }
                    else{
                        mapa[posY][posX] = 0;
                        posY += 1; posX += 1;
                        mapa[posY][posX] = 1;
                    }
                break;
        case 'd': case 'D':
        	dica(posY, posX, 1, bot, *y, *x);
        	movCachorro(y, x, posY, posX, bot, mortes);
        case 'p': case 'P':
        	pause();
        	movCachorro(y, x, posY, posX, bot, mortes);
        	return;
        	break;
        default:
            printf("\n Jogada Invalida, tente novamente");
            movCachorro(y, x, posY, posX, bot, mortes);
            return;
            break;
	}
	
    MostrarMapa(6, 5);
    if(bot == false)
    	movimentoOnca(y, x, mortes);
    else
    	cpu(y,x, mortes);
    return;
}

void movimentoOnca(int *OncaY, int *OncaX, short int mortes){
    char mov;
	
	
	printf("\n\n===============Turno da Onca==================\n");
	
    if(Possiveis(*OncaY, *OncaX, 2, true) == 0){
    	VitoriaC();
    	return;
    }
    printf("\n\nDigite a direcao: ");
    scanf("%c", &mov);
    
    if(mov == '\n')
    	scanf("%c", &mov);
    
    switch(mov){
        case '7':
            if(ValidarJogada(-1 , -1,*OncaY, *OncaX) == 2){
                printf("\n Jogada Invalida, tente novamente");
                movimentoOnca(OncaY, OncaX, mortes);
                return;
            }
            else{
                if(ValidarJogada(-1, -1,*OncaY, *OncaX) == 1){
                    mapa[*OncaY][*OncaX] = 0;
                    mapa[*OncaY - 1][*OncaX - 1] = 0;
                    *OncaY -= 2; *OncaX -= 2;
                    mapa[*OncaY][*OncaX] = 2;
                    mortes++;
                    if(mortes >= 5){
						VitoriaO();
						return;
					}
                    if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        MostrarMapa(6,5);
                        movimentoOnca(OncaY, OncaX, mortes);
                    }
                }
                else{
                    mapa[*OncaY][*OncaX] = 0;
                    *OncaY -= 1; *OncaX -= 1;
                    mapa[*OncaY][*OncaX] = 2;
                }
            }
            break;
            
        case '8':
            if(ValidarJogada(-1 , 0, *OncaY, *OncaX) == 2){
                printf("\n Jogada Invalida, tente novamente");
                movimentoOnca(OncaY, OncaX, mortes);
                return;
            }
            else{
                if(ValidarJogada(-1, 0,*OncaY, *OncaX) == 1){
                    mapa[*OncaY][*OncaX] = 0;
                    mapa[*OncaY - 1][*OncaX] = 0;
                    *OncaY -= 2; 
                    mapa[*OncaY][*OncaX] = 2;
                    mortes++;
                    if(mortes >= 5){
						VitoriaO();
						return;
					}
                    if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        MostrarMapa(6,5);
                        movimentoOnca(OncaY, OncaX, mortes);
                    }
                }
                else{
                    mapa[*OncaY][*OncaX] = 0;
                    *OncaY -= 1; 
                    mapa[*OncaY][*OncaX] = 2;
                }
            }
            break;
            
        case '9':
            if(ValidarJogada(-1 , 1,*OncaY, *OncaX) == 2){
                printf("\n Jogada Invalida, tente novamente");
                movimentoOnca(OncaY, OncaX, mortes);
                return;
            }
            else{
                if(ValidarJogada(-1, 1,*OncaY, *OncaX) == 1){
                    mapa[*OncaY][*OncaX] = 0;
                    mapa[*OncaY - 1][*OncaX + 1] = 0;
                    *OncaY -= 2; *OncaX += 2;
                    mapa[*OncaY][*OncaX] = 2;
                    mortes++;
                    if(mortes >= 5){
						VitoriaO();
						return;
					}
                    if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        MostrarMapa(6,5);
                        movimentoOnca(OncaY, OncaX, mortes);
                    }
                }
                else{
                    mapa[*OncaY][*OncaX] = 0;
                    *OncaY -= 1; *OncaX += 1;
                    mapa[*OncaY][*OncaX] = 2;
                }
            }
            break;
        case '4':
            if(ValidarJogada(0 , -1,*OncaY, *OncaX) == 2){
                    printf("\n Jogada Invalida, tente novamente");
                    movimentoOnca(OncaY, OncaX, mortes);
                    return;
                }
                else{
                    if(ValidarJogada(0, -1,*OncaY, *OncaX) == 1){
                        mapa[*OncaY][*OncaX] = 0;
                        mapa[*OncaY][*OncaX - 1] = 0;
                        *OncaX -= 2;
                        mapa[*OncaY][*OncaX] = 2;
                        mortes++;
                        if(mortes >= 5){
							VitoriaO();
							return;
						}
                        if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        	MostrarMapa(6,5);
                        	movimentoOnca(OncaY, OncaX, mortes);
                    	}
                    }
                    else{
                        mapa[*OncaY][*OncaX] = 0;
                        *OncaX -= 1;
                        mapa[*OncaY][*OncaX] = 2;
                    }
            }
                break;
        case '6':
            if(ValidarJogada(0 , 1,*OncaY, *OncaX) == 2){
                    printf("\n Jogada Invalida, tente novamente");
                    movimentoOnca(OncaY, OncaX, mortes);
                    return;
                }
                else{
                    if(ValidarJogada(0, 1,*OncaY, *OncaX) == 1){
                        mapa[*OncaY][*OncaX] = 0;
                        mapa[*OncaY][*OncaX + 1] = 0;
                        *OncaX += 2;
                        mapa[*OncaY][*OncaX] = 2;
                        mortes++;
                        if(mortes >= 5){
							VitoriaO();
							return;
						}
                        if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        	MostrarMapa(6,5);
                        	movimentoOnca(OncaY, OncaX, mortes);
                    	}
                    }
                    else{
                        mapa[*OncaY][*OncaX] = 0;
                        *OncaX += 1;
                        mapa[*OncaY][*OncaX] = 2;
                    }
                }
                break;
        case '1':
            if(ValidarJogada(1 , -1,*OncaY, *OncaX) == 2){
                    printf("\n Jogada Invalida, tente novamente");
                    movimentoOnca(OncaY, OncaX, mortes);
                    return;
                }
                else{
                    if(ValidarJogada(1, -1,*OncaY, *OncaX) == 1){
                        mapa[*OncaY][*OncaX] = 0;
                        mapa[*OncaY + 1][*OncaX - 1] = 0;
                        *OncaY += 2; *OncaX -= 2; 
                        mapa[*OncaY][*OncaX] = 2;
                        if(mortes >= 5){
							VitoriaO();
							return;
						}
                        mortes++;
                        if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        	MostrarMapa(6,5);
                        	movimentoOnca(OncaY, OncaX, mortes);
                    	}
                    }
                    else{
                        mapa[*OncaY][*OncaX] = 0;
                        *OncaY += 1; *OncaX -= 1;
                        mapa[*OncaY][*OncaX] = 2;
                    }
                }
                break;
        case '2':
            if(ValidarJogada(1 , 0,*OncaY, *OncaX) == 2){
                    printf("\n Jogada Invalida, tente novamente");
                    movimentoOnca(OncaY, OncaX, mortes);
                    return;
                }
                else{
                    if(ValidarJogada(1, 0,*OncaY, *OncaX) == 1){
                        mapa[*OncaY][*OncaX] = 0;
                        mapa[*OncaY + 1][*OncaX] = 0;
                        *OncaY += 2;  
                        mapa[*OncaY][*OncaX] = 2;
                        mortes++;
                        if(mortes >= 5){
							VitoriaO();
							return;
						}
                        if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        	MostrarMapa(6,5);
                        	movimentoOnca(OncaY, OncaX, mortes);
                    	}
                    }
                    else{
                        mapa[*OncaY][*OncaX] = 0;
                        *OncaY += 1;
                        mapa[*OncaY][*OncaX] = 2;
                    }
                }
                break;
        case '3':
            if(ValidarJogada(1 , 1,*OncaY, *OncaX) == 2){
                    printf("\n Jogada Invalida, tente novamente");
                    movimentoOnca(OncaY, OncaX, mortes);
                    return;
                }
                else{
                    if(ValidarJogada(1, 1,*OncaY, *OncaX) == 1){
                        mapa[*OncaY][*OncaX] = 0;
                        mapa[*OncaY + 1][*OncaX + 1] = 0;
                        *OncaY += 2;  *OncaX += 2;
                        mapa[*OncaY][*OncaX] = 2;
                        mortes++;
                        if(mortes >= 5){
							VitoriaO();
							return;
						}
                        if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        	MostrarMapa(6,5);
                        	movimentoOnca(OncaY, OncaX, mortes);
                    	}
                    }
                    else{
                        mapa[*OncaY][*OncaX] = 0;
                        *OncaY += 1; *OncaX += 1;
                        mapa[*OncaY][*OncaX] = 2;
                    }
                }
                break;
        case 'p': case 'P':
        	pause();
        	movimentoOnca(OncaY, OncaX, mortes);
        	return;
        case 'd': case 'D':
        	dica(*OncaY, *OncaX, 2, false, 0, 0);
        	movimentoOnca(OncaY, OncaX, mortes);
        	return;
        case 's': case 'S':
        	return;
        default:
            printf("\n Jogada Invalida, tente novamente");
            movimentoOnca(OncaY, OncaX, mortes);
            return;
            break;
    }
    
    
    MostrarMapa(6, 5);
    movimentoCacho(OncaY, OncaX, false, mortes);
    return;
}

void movimentoCacho(int *y, int *x, bool bot, short int mortes){
	
    int PosY, PosX;
    
    if(mortes >= 5){
		VitoriaO();
		return;
	}
    printf("\n\n=============Turno dos Cachorros=============\n");
    printf("\n\nQual cachorro quer selecionar? \n Linha:");
    scanf("%d", &PosY);
    printf(" Coluna:");
    scanf("%d", &PosX);
    
    
    PosY--; PosX--;
    
    if(Possiveis(PosY, PosX, 1, false) == 0){
    	printf("\nNenhuma Jogada Possivel para este cachorro\n");
    	movimentoCacho(y, x, bot, mortes);
    	return;
    }
    else{
    	if(Possiveis(PosY, PosX, 1, false) == 2){
    		printf("\nIsso nao e um cachorro...\n");
    			movimentoCacho(y, x, bot, mortes);
    		return;
    	}
}
    MostrarMapa(PosY, PosX);   
    
	movCachorro(y, x, PosY, PosX, bot, mortes);
}         

void cpu(int *OncaY, int *OncaX, short int mortes){
	
	if(Possiveis(*OncaY, *OncaX, 2, false) == 0){
    	VitoriaC();
    	return;
    }
	
	system("cls");
	
	
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++){
			long int clock();
			if(ValidarJogada(i, j, *OncaY, *OncaX) == 1){
				mapa[*OncaY + i + i][*OncaX + j + j] = 2;
				mapa[*OncaY + i][*OncaX + j] = 0; mapa[*OncaY][*OncaX] = 0;
				*OncaY += i + i; *OncaX += j + j;
				MostrarMapa(6, 5);
				printf("\n\n===============Turno da Onca==================\n");
				printf("\nOnca se moveu para Linha: %d e Coluna: %d \n", *OncaY + 1, *OncaX + 1);
				printf("\n\n===============================================\n");
				system("pause"); system("cls");
				mortes++;
                if(mortes >= 5){
						VitoriaO();
						return;
					}
                if(Possiveis(*OncaY, *OncaX, 2, false) == 2){
                        MostrarMapa(6,5);
                        cpu(OncaY, OncaX, mortes);
                        return;
                    }
                MostrarMapa(6,5);
                movimentoCacho(OncaY, OncaX, true, mortes);
                return;
			}
		}
		
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			for(int k = -1; k < 2; k++){
				for(int l = -1; l < 2; l++){
					if(ValidarJogada(i, j, *OncaY, *OncaX) == 0 && ValidarJogada(i, j, *OncaY + k, *OncaX + l) == 1 && mapa[*OncaY + i + k][*OncaX + j + l] == 1 && mapa[*OncaY + i + k + k][*OncaX + j + l + l] == 0){
						mapa[*OncaY + i][*OncaX + j] = 2;
						mapa[*OncaY][*OncaX] = 0;
						*OncaY += i; *OncaX += j;
						MostrarMapa(6, 5);
						printf("\n\n===============Turno da Onca==================\n");
						printf("\nOnca se moveu para Linha: %d e Coluna: %d\n", *OncaY + 1, *OncaX + 1);
						printf("\n\n===============================================\n");
						system("pause"); system("cls");
						MostrarMapa(6,5);
						movimentoCacho(OncaY, OncaX, true, mortes);
                		return;
					}
				}
			}
}
}
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++){
			for(int k = -1; k < 2; k++)
				for(int l = -1; l < 2; l++){
					if(ValidarJogada(i, j, *OncaY , *OncaX ) == 0){
						mapa[*OncaY + i][*OncaX + j] = 2;
						mapa[*OncaY][*OncaX] = 0;
						*OncaY += i; *OncaX += j;
						MostrarMapa(6, 5);
						printf("\n\n===============Turno da Onca==================\n");
						printf("\nOnca se moveu para Linha: %d e Coluna: %d  \n", *OncaY + 1, *OncaX + 1);
						printf("\n\n===============================================\n");
						system("pause"); system("cls");
						MostrarMapa(6,5);
						movimentoCacho(OncaY, OncaX, true, mortes);
                		return;
				}
		}
	}
}

void menu(){
	int OncaPosY, OncaPosX;
	char tecla;
	system("cls");
	printf("==================================\n\t  Jogo da Onca\n\tPor Lucas Medeiros\n==================================\n\n\tSelecione:\n\t(A)Jogar\n\t(B)Ajuda\n\t(F)Sair\n");
	scanf("%c", &tecla);
	
	switch(tecla){
		case 'a': case'A':
			system("cls");
		    printf("==================================\n\t  Jogar\n==================================\n\n\tSelecione:\n\t(A)Player VS Player\n\t(B)Player VS CPU\n\t(F)Voltar\n");
		    scanf("%c", &tecla);
		    if(tecla == '\n')
		    	scanf("%c", &tecla);
		    	
		    if(tecla == 'A' || tecla == 'a'){
		    	clock();
		    	OncaPosY = 2; OncaPosX = 2;
			    mapa[0][0] = 1; mapa[0][1] = 1; mapa[0][2] = 1; mapa[0][3] = 1; mapa[0][4] = 1; 
			    mapa[1][0] = 1; mapa[1][1] = 1; mapa[1][2] = 1; mapa[1][3] = 1; mapa[1][4] = 1; 
			    mapa[2][0] = 1; mapa[2][1] = 1; mapa[2][2] = 2; mapa[2][3] = 1; mapa[2][4] = 1; 
			    mapa[3][0] = 0; mapa[3][1] = 0; mapa[3][2] = 0; mapa[3][3] = 0; mapa[3][4] = 0;
			    mapa[4][0] = 0; mapa[4][1] = 0; mapa[4][2] = 0; mapa[4][3] = 0; mapa[4][4] = 0;
			    mapa[5][0] = 3; mapa[5][1] = 0; mapa[5][2] = 0; mapa[5][3] = 0; mapa[5][4] = 3;
			    mapa[6][0] = 3; mapa[6][1] = 0; mapa[6][2] = 0; mapa[6][3] = 0; mapa[6][4] = 3;
			    
			    MostrarMapa(6, 5);
			    movimentoOnca(&OncaPosY, &OncaPosX, 0);
			}
			else if(tecla == 'B' || tecla == 'b'){
				clock();
				OncaPosY = 2; OncaPosX = 2;
			    mapa[0][0] = 1; mapa[0][1] = 1; mapa[0][2] = 1; mapa[0][3] = 1; mapa[0][4] = 1; 
			    mapa[1][0] = 1; mapa[1][1] = 1; mapa[1][2] = 1; mapa[1][3] = 1; mapa[1][4] = 1; 
			    mapa[2][0] = 1; mapa[2][1] = 1; mapa[2][2] = 2; mapa[2][3] = 1; mapa[2][4] = 1; 
			    mapa[3][0] = 0; mapa[3][1] = 0; mapa[3][2] = 0; mapa[3][3] = 0; mapa[3][4] = 0;
			    mapa[4][0] = 0; mapa[4][1] = 0; mapa[4][2] = 0; mapa[4][3] = 0; mapa[4][4] = 0;
			    mapa[5][0] = 3; mapa[5][1] = 0; mapa[5][2] = 0; mapa[5][3] = 0; mapa[5][4] = 3;
			    mapa[6][0] = 3; mapa[6][1] = 0; mapa[6][2] = 0; mapa[6][3] = 0; mapa[6][4] = 3;
			    
			    cpu(&OncaPosY, &OncaPosX, 0);
			}
			else if(tecla == 'f' || tecla == 'F'){
				return;
			}
			menu();
			break;
		case 'b': case 'B':
			system("cls");
			printf("\n\tTutorial do Jogo da Onca\n Onca (X):\n  O objetivo da Onca consiste em capturar 5 cachorros para vencer o jogo, voce pode capturar pulando sobre as pecas dos cachorros que tem o caractere Z. Alem disso a Onca deve evitar ser imobilizada pelos cachorros.");
			printf("\n  Voce pode se mover usando os botoes: \n\n 789 \n 4 6 \n 123\n");
			printf("\n  Os botoes representam as direcoes que a Onca se movera; 7 sendo para superior esquerdo, 2 para baixo, 3 para inferior direito.");
			printf("\n\n Cachorros (Z):\n O objetivo dos cachorros e evitar ser capturado pela Onca e imobilizar ela, incapacitando que ela realize qualquer outro movimento no tabuleiro, e fazendo que os cachorros ganhem o jogo.");
			printf("\n Voce se move pelo tabuleiro, selecionando a linha e a coluna do cachorro que queira mover, e depois usando os botoes: \n\n 789 \n 4 6 \n 123\n\n");
			system("pause");
			break;
		case 'f': case 'F':
			return;
		default: 
			break;
	}
	menu();
	return;
}

int main(){
	
    menu();
    
    return 0;
}
