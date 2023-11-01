#include <iostream>
#include "ADFunctions.h"
// Este arquivo possui as funções responsáveis pelo funcionamento
// dos desafios/jogo

// IsDebuggerPresent() é uma função da API do Windows
// A função detecta se existe um depurador "acoplado" e retorna um valor diferente de zero se for verdadeiro.
// Se não houver depurador "acoplado" o retorno da função é zero
//
// Descrição Oficial: https://learn.microsoft.com/pt-br/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent

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
// Se a função detectar um depurador ela retorna um valor diferente de 0.
// caso contrário , retorna 0.
// O "Remote" não quer dizer necessariamente um computador diferente.
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

// A customCheckFunction01() é uma função criada que 
// escreve no Process Environment Block e seta a flag
// IsDebuggerPresent através de um inline assembly
bool customCheckFunction01()
{
	uint8_t isDebuggerPresentByte;
	_asm
	{
		mov eax, fs:[30h] // adiciona a PEB derreferenciada em eax
		mov eax, [eax + 2] // dereferencia a PEB + 2 bytes
		mov isDebuggerPresentByte, al // guarda o valor na variável isDebuggerPresentByte
	}
	return isDebuggerPresentByte;
}
// customCheckFunction01Caller chama customCheckFunction01
// O objetivo é gerar uma complicação adicional a análise do código.
// Se customCheckFunction01() retornar 1 , entao o depurador foi
// detectado. Além da detecção do depurador, existe ainda, a variável
// FlagChecker que precisa ser setada para 0 para que o desafio seja 
// vencido

bool customCheckFunction01Caller()
{
	bool FlagChecker = true; // segunda condição de checagem
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


// A customRDTSCFunctionCheck() é uma função que chama a função
// RDTSC em dois momentos e calcula a diferença de tempo entre os dois
// momentos. Normalmente um programa mantém uma regularidade no seu
// tempo de execução nas partes em que o código não precisa de ação
// humana.
// O código já possui definido, pois já foi calculado essa regularidade
// quando o código foi produzido. A tickcount não ultrapssa 200.000.

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
	// primeira verificacao através de uma chamada
	// de inline assembly
	_asm
	{
		// A função xor apenas zera o registrador ecx
		// o rdtsc guardar o tickcount guarda um valor
		// de 64bits em EDX:EAX
		xor ecx,ecx
		rdtsc  			  
		mov start.LowPart, eax
		mov start.HighPart, edx
	}
	// Loop só para preencher o código com algo.
	// Não possui nenhuma função relevante, além de forçar
	// o código a demorar um pouco para avançar.
	for (i = 0; i < 10000; i++)
	{
		justAnArray[i] = i;
	}
	// Setando a segunda condição de avanço do programa,
	// a sua única função é dificultar a conclusão do desafio.
	FlagChecker = true; 
	// segunda verificacao através de uma chamada
	// de inline assembly
	_asm
	{
		// A função xor apenas zera o registrador ecx
		// o rdtsc guardar o tickcount guarda um valor
		// de 64bits em EDX:EAX
		xor ecx, ecx
		rdtsc 
		mov end.LowPart, eax
		mov end.HighPart, edx
	}
	// Aqui é realizado um cálculo da diferença entre as duas medições,
	// apenas por motivo de distração, pois será gerado mais algumas
	// linhas de assembly por causa disso
	long int tickCount = end.QuadPart - start.QuadPart;
	// imprime a diferença, apenas para ajudar o jogador
	std::cout << tickCount << std::endl;
	// Se o tickcount for maior do que 200.000
	// o jogo encerra e o jogador perde
	if (tickCount > 200000)
	{
		printf("RDTSC Tick count Gotcha!");
		delete[] justAnArray;
		return false;
	}
	// Se o jogador não alterar o valor da segunda chegame
	// ele também tem o fluxo desviado para derrota.
	if (FlagChecker == true)
	{
		printf("RDTSC Tick count Gotcha! You forgot the Flag!");
		delete[] justAnArray;
		return false;
	}
	return true;
}
// apenas chama a funcao customRDTSCFunctionCheck()
// sua funcao é apenas dificultar a análise do código
bool customRDTSCFunctionCheckCaller()
{
	return customRDTSCFunctionCheck();
}

// GetLocalTimeCheck() é apenas uma uma função criada
// que chama a verdadeira fúnção GetLocalTime() que
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
	// Primeira chamada para verificação do tempo de Execução.
	// A função GetLocalTime() retorna o tempo e data locais
	// através do parâmetro. O parâmetro é uma estrutura
	// chamada SYSTEMTIME
	// Descrição Oficial: https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlocaltime
	GetLocalTime(&stStart);
	// Loop só para preencher o código com algo.
	// Não possui nenhuma função relevante, além de forçar
	// o código a demorar um pouco para avançar.
	for (j = 0; j < 100; j++)
	{
		for (i = 0; i < 100000; i++)
		{
			
			justAnArray[i] = i;
		}
	}
	// Segunda chamada para verificação do tempo de Execução.
	GetLocalTime(&stEnd);

	// SystemTimeToFileTime() converte de "system time" para o
	// padrão "file time"
	if (!SystemTimeToFileTime(&stStart, &ftStart))
		return false;
	if (!SystemTimeToFileTime(&stEnd, &ftEnd))
		return false;
	// As próximas 4 linhas unem os valores 
	// em uma unica variável para realizar
	// o cálculo da diferença
	uiStart.LowPart = ftStart.dwLowDateTime;
	uiStart.HighPart = ftStart.dwHighDateTime;
	uiEnd.LowPart = ftEnd.dwLowDateTime;
	uiEnd.HighPart = ftEnd.dwHighDateTime;
	// calcula a diferenca entre os tempos de execução
	timeCount = uiEnd.QuadPart - uiStart.QuadPart;
	// impressão do time count para facilitar o desafio
	std::cout << "Time: " << timeCount << std::endl;
	// libera a area de memoria utilizada pela array
	delete[] justAnArray;

	FlagChecker = true;
	// O programa compara a diferença calculada com
	// o elapsedTime já predeterminado em 400.000
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
// começou o programa com um debugador
// "acoplado", caso negativo os desafios
// não serão iniciados
void startingCondition()
{
	if (IsDebuggerPresent() == false)
	{
		std::cout << "You are not even using a Debugger." << std::endl;
		std::cout << "You don't wanna play, quit!!" << std::endl;
		quitProcess();
	}
}