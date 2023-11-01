#include <iostream>
#include "ADFunctions.h"
// Este arquivo possui as fun��es respons�veis pelo funcionamento
// dos desafios/jogo

// IsDebuggerPresent() � uma fun��o da API do Windows
// A fun��o detecta se existe um depurador "acoplado" e retorna um valor diferente de zero se for verdadeiro.
// Se n�o houver depurador "acoplado" o retorno da fun��o � zero
//
// Descri��o Oficial: https://learn.microsoft.com/pt-br/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent

bool IsDebuggerPresentCaller()
{
	char a = 'b';
	startingCondition();
	std::cout << "Will you bypass IsDebugger Present?" << std::endl;
	std::cout << "Press 1 to start." << std::endl;
	std::cin >> a;
		// searches the PEB for IsDebuggerPresent and return 0 if it is not being debugged
		if (IsDebuggerPresent())
		{
			std::cout << "Stop debugging my software you scum bag." << std::endl;
			std::cout << "You were caught by IsDebuggerPresent()" << std::endl;
			return false;
		}
		return true;
}


// CheckRemoteDebuggerPresent() verificado se existe algum depurador "acoplado" ao programa.
// Se a fun��o detectar um depurador ela retorna um valor diferente de 0.
// caso contr�rio , retorna 0.
// O "Remote" n�o quer dizer necessariamente um computador diferente.
bool CheckRemoteDebuggerPresentCaller()
{
	char a = 'b';
	bool FlagChecker = true;
	startingCondition();
	std::cout << "Will you bypass RemoteDebuggerPresentCaller?" << std::endl;
	std::cout << "Press 1 to start." << std::endl;
	std::cin >> a;
	BOOL bDebuggerPresent;
	// Similar to IsDebuggerPresent but get process handle as parameter
	// returns a nonzero value if being debugger
	if (TRUE == CheckRemoteDebuggerPresent(GetCurrentProcess(), &bDebuggerPresent) &&
		TRUE == bDebuggerPresent )
	{
		std::cout << "You were caught by CheckRemoteDebuggerPresent()" << std::endl;
		return false;
	}
	return true;
}

// A customCheckFunction01() � uma fun��o criada que 
// escreve no Process Environment Block e seta a flag
// IsDebuggerPresent atrav�s de um inline assembly
bool customCheckFunction01()
{
	uint8_t isDebuggerPresentByte;
	_asm
	{
		mov eax, fs:[30h] // adiciona a PEB derreferenciada em eax
		mov eax, [eax + 2] // dereferencia a PEB + 2 bytes
		mov isDebuggerPresentByte, al // guarda o valor na vari�vel isDebuggerPresentByte
	}
	return isDebuggerPresentByte;
}
// customCheckFunction01Caller chama customCheckFunction01
// O objetivo � gerar uma complica��o adicional a an�lise do c�digo.
// Se customCheckFunction01() retornar 1 , entao o depurador foi
// detectado. Al�m da detec��o do depurador, existe ainda, a vari�vel
// FlagChecker que precisa ser setada para 0 para que o desafio seja 
// vencido

bool customCheckFunction01Caller()
{
	bool FlagChecker = true; // segunda condi��o de checagem
	char a = 'b';
	startingCondition();
	std::cout << "Will you bypass a manual Inline PEB Checker?" << std::endl;
	std::cout << "Press 1 to start." << std::endl;
	std::cin >> a;
	if (customCheckFunction01() == 1 || FlagChecker == true)
	{
		std::cout << "You were caught by PEB manualCheckFunction()" << std::endl;
		return false;
	}
	return true;
}


// A customRDTSCFunctionCheck() � uma fun��o que chama a fun��o
// RDTSC em dois momentos e calcula a diferen�a de tempo entre os dois
// momentos. Normalmente um programa mant�m uma regularidade no seu
// tempo de execu��o nas partes em que o c�digo n�o precisa de a��o
// humana.
// O c�digo j� possui definido, pois j� foi calculado essa regularidade
// quando o c�digo foi produzido. A tickcount n�o ultrapssa 200.000.

bool customRDTSCFunctionCheck()
{
	bool FlagChecker = true;
	int i = 0;
	ULARGE_INTEGER start, end;
	int* justAnArray = new int[100000];
	int a;
	startingCondition();
	std::cout << "Will you bypass RDTSC Function Time Check?" << std::endl;
	std::cout << "Press 1 to start." << std::endl;
	std::cin >> a;
	// primeira verificacao atrav�s de uma chamada
	// de inline assembly
	_asm
	{
		// A fun��o xor apenas zera o registrador ecx
		// o rdtsc guardar o tickcount guarda um valor
		// de 64bits em EDX:EAX
		xor ecx,ecx
		rdtsc  			  
		mov start.LowPart, eax
		mov start.HighPart, edx
	}
	// Loop s� para preencher o c�digo com algo.
	// N�o possui nenhuma fun��o relevante, al�m de for�ar
	// o c�digo a demorar um pouco para avan�ar.
	for (i = 0; i < 10000; i++)
	{
		justAnArray[i] = i;
	}
	// Setando a segunda condi��o de avan�o do programa,
	// a sua �nica fun��o � dificultar a conclus�o do desafio.
	FlagChecker = true; 
	// segunda verificacao atrav�s de uma chamada
	// de inline assembly
	_asm
	{
		// A fun��o xor apenas zera o registrador ecx
		// o rdtsc guardar o tickcount guarda um valor
		// de 64bits em EDX:EAX
		xor ecx, ecx
		rdtsc 
		mov end.LowPart, eax
		mov end.HighPart, edx
	}
	// Aqui � realizado um c�lculo da diferen�a entre as duas medi��es,
	// apenas por motivo de distra��o, pois ser� gerado mais algumas
	// linhas de assembly por causa disso
	long int tickCount = end.QuadPart - start.QuadPart;
	// imprime a diferen�a, apenas para ajudar o jogador
	std::cout << tickCount << std::endl;
	// Se o tickcount for maior do que 200.000
	// o jogo encerra e o jogador perde
	if (tickCount > 200000)
	{
		printf("RDTSC Tick count Gotcha!");
		delete[] justAnArray;
		return false;
	}
	// Se o jogador n�o alterar o valor da segunda chegame
	// ele tamb�m tem o fluxo desviado para derrota.
	if (FlagChecker == true)
	{
		printf("RDTSC Tick count Gotcha! You forgot the Flag!");
		delete[] justAnArray;
		return false;
	}
	return true;
}
// apenas chama a funcao customRDTSCFunctionCheck()
// sua funcao � apenas dificultar a an�lise do c�digo
bool customRDTSCFunctionCheckCaller()
{
	return customRDTSCFunctionCheck();
}

// GetLocalTimeCheck() � apenas uma uma fun��o criada
// que chama a verdadeira f�n��o GetLocalTime() que
// faz parte da API do Window. 
bool GetLocalTimeCheck()
{
	int i = 0;
	int j = 0;
	bool FlagChecker = true;
	int elapsedTime = 400000;
	int* justAnArray = new int[100000];
	long int timeCount;
	SYSTEMTIME stStart, stEnd;
	FILETIME ftStart, ftEnd;
	ULARGE_INTEGER uiStart, uiEnd;
	int a;
	startingCondition();
	std::cout << "Will you bypass GetLocalTimeCheck?" << std::endl;
	std::cout << "Press 1 to start." << std::endl;
	std::cin >> a;
	// Primeira chamada para verifica��o do tempo de Execu��o.
	// A fun��o GetLocalTime() retorna o tempo e data locais
	// atrav�s do par�metro. O par�metro � uma estrutura
	// chamada SYSTEMTIME
	// Descri��o Oficial: https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlocaltime
	GetLocalTime(&stStart);
	// Loop s� para preencher o c�digo com algo.
	// N�o possui nenhuma fun��o relevante, al�m de for�ar
	// o c�digo a demorar um pouco para avan�ar.
	for (j = 0; j < 100; j++)
	{
		for (i = 0; i < 100000; i++)
		{
			
			justAnArray[i] = i;
		}
	}
	// Segunda chamada para verifica��o do tempo de Execu��o.
	GetLocalTime(&stEnd);

	// SystemTimeToFileTime() converte de "system time" para o
	// padr�o "file time"
	if (!SystemTimeToFileTime(&stStart, &ftStart))
		return false;
	if (!SystemTimeToFileTime(&stEnd, &ftEnd))
		return false;
	// As pr�ximas 4 linhas unem os valores 
	// em uma unica vari�vel para realizar
	// o c�lculo da diferen�a
	uiStart.LowPart = ftStart.dwLowDateTime;
	uiStart.HighPart = ftStart.dwHighDateTime;
	uiEnd.LowPart = ftEnd.dwLowDateTime;
	uiEnd.HighPart = ftEnd.dwHighDateTime;
	// calcula a diferenca entre os tempos de execu��o
	timeCount = uiEnd.QuadPart - uiStart.QuadPart;
	// impress�o do time count para facilitar o desafio
	std::cout << "Time: " << timeCount << std::endl;
	// libera a area de memoria utilizada pela array
	delete[] justAnArray;

	FlagChecker = true;
	// O programa compara a diferen�a calculada com
	// o elapsedTime j� predeterminado em 400.000
	// e verifica se a FlagChecker teve seu valor
	// alterado
	if ((uiEnd.QuadPart - uiStart.QuadPart) > elapsedTime || FlagChecker == true)
		return false;
	else 
		return true;
}

// Apenas chama a GetLocalTimeCheck()
// e verifica seu retorno para imprimir
// a mensagem de derrota
bool GetLocalTimeCheckCaller()
{
	if (GetLocalTimeCheck() == false)
	{
		std::cout << "You get caught by GetLocalTime() Check" << std::endl;
		return false;
	}
	return true;
}
void quitProcess()
{
	char a;
	getchar();
	getchar();
	ExitProcess(-1);
}
// startingConditon checa se o jogador
// come�ou o programa com um debugador
// "acoplado", caso negativo os desafios
// n�o ser�o iniciados
void startingCondition()
{
	if (IsDebuggerPresent() == false)
	{
		std::cout << "You are not even using a Debugger." << std::endl;
		std::cout << "You don't wanna play, quit!!" << std::endl;
		quitProcess();
	}
}