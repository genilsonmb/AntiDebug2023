// Esse arquivo possui as funções necessárias para criação e 
// por aumentar a dificuldade de se encontrar as Flags
#pragma once
#include "CryptoFlags.h"
#include <bitset>
#include <iostream>
#include <algorithm>
#include <stdio.h>

// Função para pegar o tamanho de um array de Chars
int getLength(char* arrayChar)
{
	int i = 0;
	while (arrayChar[i] != '\x00')
	{
		++i;
	}
	return i + 1;
}

// a Função toHexCrypt() recebe um array de Chars e uma Chave
// essa chave será utilizada como chave para realizar um XOR
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

// A função unHexCrypt recebe um array de chars
// no formato criado pelo toHexCrypt e decripta
// a flag. É necessário atentar para utilização
// da mesma chave utilizada na função toHexCrypt.
// Além disso, imprime na tela a flag.
// O objetivo da função é desofuscar a Flag ofuscada
// através ta função toHexCrypt
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


