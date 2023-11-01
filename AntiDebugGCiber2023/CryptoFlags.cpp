// Esse arquivo possui as fun��es necess�rias para cria��o e 
// por aumentar a dificuldade de se encontrar as Flags
#pragma once
#include "CryptoFlags.h"
#include <bitset>
#include <iostream>
#include <algorithm>
#include <stdio.h>

// Fun��o para pegar o tamanho de um array de Chars
int getLength(char* arrayChar)
{
	int i = 0;
	while (arrayChar[i] != '\x00')
	{
		++i;
	}
	return i + 1;
}

// a Fun��o toHexCrypt() recebe um array de Chars e uma Chave
// essa chave ser� utilizada como chave para realizar um XOR
// com cada caractere da array de Chars e imprimir na tela 
// a chave em um formato para que ela seja colada e utilizada
// para posteriormente ser decriptada pelo unHexCrypt

void toHexCrypt(char* arrayChar, int key)
{
	int length = 0;
	length = getLength(arrayChar);
	for (int i = 0; i < length; i++)
	{
		arrayChar[i] = arrayChar[i] ^ key;
		printf("\'\\x%x\',", arrayChar[i]);
	}
	printf("\n");
	
}

// A fun��o unHexCrypt recebe um array de chars
// no formato criado pelo toHexCrypt e decripta
// a flag. � necess�rio atentar para utiliza��o
// da mesma chave utilizada na fun��o toHexCrypt.
// Al�m disso, imprime na tela a flag.
// O objetivo da fun��o � desofuscar a Flag ofuscada
// atrav�s ta fun��o toHexCrypt
//
void unHexCrypt(char* arrayChar,int length, int key)
{
	//char arrayCharCopy[length] = 0;
	char arrayCharCopy[100];
	for (int i = 0; i < length ; i++)
	{
		if (arrayChar[i] != ' ')
		{
			arrayCharCopy[i] = arrayChar[i] ^ key;
			printf("%c", arrayCharCopy[i]);
		}			
	}
	printf("\n");
}


