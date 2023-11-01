/*
ESTE PROGRAMA FOI CRIADO COMO PROJETO NA CONCLUS�O DO CURSO DE GUERRA CIBERN�TICA PARA OFICIAIS 2023
O C�DIGO FOI CRIADO PELOS ALUNOS 
CAP FRANNOEL
CAP MAR�AL

O OBJETIVO DESTE JOGO/PROGRAMA/DESAFIO � INTRODUZIR O JOGADOR/DESAFIANTE A 5 M�TODOS UTILIZADOS PARA 
DIFICULTAR A DEPURA��O DE PROGRAMAS. O ASSUNTO EST� LONGE DE SER ESGOTADO NESTE PROJETO, POIS OS 
M�TODOS UTILIZADOS S�O INCONT�VEIS E MUITAS VEZES DEPENDEM APENAS DA CRIATIVIDADE DO PROGRAMADOR E
DO TAMANHO DO SEU INTERESSE EM PROTEGER SEU C�DIGO.

O PROGRAMA POSSUI 3 ARQUIVOS PRINCIPAIS E 2 ARQUIVOS HEADERS. 
AntiDebugGCiber2023.cpp que possui a main()
ADFunctions.cpp que possui as fun��es de anti-debugging
CryptoFlags.cpp fun��o para ofuscar e desofuscar as Flags
ADFunctions.h e CryptFlags.h que possuem apenas as declara��es das fun��es.
*/

#include <iostream>
#include "ADFunctions.h"
#include "CryptoFlags.h"
#include <stdio.h>

int main()
{   // Essas s�o as flags que foram utilizadas na Fun��o ToHexCrypt() no final do arquivo
    //char string1[] = "Flag{IsDebuggerPresentPwned}";
    //char string2[] = "Flag{YoupassedCheckRemoteDebbugerPresent}";
    //char string3[] = "Flag{PwnedInlineAssemblyPEB}";
    //char string4[] = "Flag{YouJustDidRDTSC}";
    //char string5[] = "Flag{YouveGotGetTimeCheck}";
    char a = 'b';
    //Flag{IsDebuggerPresentPwned} with key x01
    char cc[] = {'\x47','\x6d','\x60','\x66','\x7a','\x48','\x72','\x45','\x64','\x63','\x74','\x66','\x66','\x64','\x73','\x51','\x73','\x64','\x72','\x64','\x6f','\x75','\x51','\x76','\x6f','\x64','\x65','\x7c','\x1'};
    //Flag{YouveGotGetTimeCheck} with key x02
    char dd[] = {'\x44','\x6e','\x63','\x65','\x79','\x5b','\x6d','\x77','\x72','\x63','\x71','\x71','\x67','\x66','\x41','\x6a','\x67','\x61','\x69','\x50','\x67','\x6f','\x6d','\x76','\x67','\x46','\x67','\x60','\x60','\x77','\x65','\x67','\x70','\x52','\x70','\x67','\x71','\x67','\x6c','\x76','\x7f','\x2'};
    //Flag{YoupassedCheckRemoteDebbugerPresent} with key x03
    char ee[] = {'\x45','\x6f','\x62','\x64','\x78','\x53','\x74','\x6d','\x66','\x67','\x4a','\x6d','\x6f','\x6a','\x6d','\x66','\x42','\x70','\x70','\x66','\x6e','\x61','\x6f','\x7a','\x53','\x46','\x41','\x7e','\x3'};
    //Flag{PwnedInlineAssemblyPEB} with key x04
    char ff[] = {'\x42','\x68','\x65','\x63','\x7f','\x5d','\x6b','\x71','\x4e','\x71','\x77','\x70','\x40','\x6d','\x60','\x56','\x40','\x50','\x57','\x47','\x79','\x4'};
    //Flag{YouJustDidRDTSC} with key x05
    char gg[] = {'\x43','\x69','\x64','\x62','\x7e','\x5c','\x6a','\x70','\x73','\x60','\x42','\x6a','\x71','\x42','\x60','\x71','\x51','\x6c','\x68','\x60','\x46','\x6d','\x60','\x66','\x6e','\x78','\x5'};

    while (a != '0')
    {
        std::cout << "Chose your option!\n";
        std::cout << "Press  1 to IsDebuggerPresent!\n";
        std::cout << "Press  2 to CheckRemoteDebuggerPresentCaller\n";
        std::cout << "Press  3 to CustomCheckFunction\n";
        std::cout << "Press  4 to RDTSC\n";
        std::cout << "Press  5 to GetLocalTimeCheck\n";
        std::cout << "Press  6 to EncryptString\n";
        std::cout << "Press  7 to Decrypt Flags\n";
        std::cout << "Press  0 to quit!\n";
        std::cin >> a;
        // Os switchs chamam as fun��es que iniciam os desafios
        // caso o jogador ven�a o desafio, a flag sera decryptada 
        // e impressa
        switch (a)
        {
        case '1':
            if (IsDebuggerPresentCaller())
                unHexCrypt(cc, sizeof(cc), 0x01);
            else
                quitProcess();
            break;
        case '2':
            if (CheckRemoteDebuggerPresentCaller())
                unHexCrypt(dd, sizeof(dd), 0x02);
            else
                quitProcess();
            break;
        case '3':
            if (customCheckFunction01Caller())
                unHexCrypt(ee, sizeof(ee), 0x03);
            else
                quitProcess();
            break;
        case '4':
            if (customRDTSCFunctionCheckCaller())
                unHexCrypt(ff, sizeof(ff), 0x04);
            else
                quitProcess();
            break;
        case '5':
            if (GetLocalTimeCheckCaller())
                unHexCrypt(gg, sizeof(gg), 0x05);
            else
                quitProcess();
            break;
        case '6':            
            break;
        case '7':
           //toHexCrypt(string1, 0x01);
           //toHexCrypt(string2, 0x02);
           //toHexCrypt(string3, 0x03);
           //toHexCrypt(string4, 0x04);
           //toHexCrypt(string5, 0x05);

            break;
        }
    }
    return 0;
}



