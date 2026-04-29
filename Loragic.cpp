#include <iostream>
#include <vector>
using namespace std;

//---------------------------------
// CLASSES PARA PROGRAMAÇÃO LÓGICA
//---------------------------------
bool contem(string s, vector<string> vs)
{
	for(string i : vs)
	{
		if(s == i)
		{
			return true;
		}
	}
	return false;
}
class Rule
{
	public:
		string fato_de_saida;
		vector<string> and_de_fatos;
};
class Loragic
{
	public:
	
		// vetor de fatos e regras
		vector<string> fatos;
		vector<Rule> regras;
		
		// deletters
		void apagar_fatos()
		{
			fatos = {};
		}
		void apagar_regras()
		{
			regras = {};
		}
		
		// adders
		void adicionar_fato(string fato){fatos.push_back(fato);}
		void adicionar_regra(string fato, vector<string> condicoes)
		{
			Rule r;
			r.fato_de_saida = fato;
			r.and_de_fatos = condicoes;
			regras.push_back(r);
		}
		
		// verifica de fato é verdadeiro
		bool eh_fato(string fato)
		{
			return contem(fato, fatos);
		}
		
		// aplica regras até o numero de fatos parar de aumentar (colapsou)
		void processar()
		{
			int n_fatos = fatos.size();
			while(true)
			{
				for(Rule rl : regras)
				{
					bool aplicar_regra = true;
					for(string cond : rl.and_de_fatos)
					{
						if(!contem(cond, fatos)){aplicar_regra = false;break;}
					}
					if(aplicar_regra && !contem(rl.fato_de_saida, fatos))
					{
						fatos.push_back(rl.fato_de_saida);
					}
				}
				if(fatos.size() == n_fatos){break;}
				n_fatos = fatos.size();
			}
		}
};

int main()
{
	Loragic motor;

	// Adiciona fatos iniciais
	motor.adicionar_fato("tem_penas");
	motor.adicionar_fato("tem_bico");
	motor.adicionar_fato("voa");

	// Adiciona regras
	// Se tem penas E tem bico E voa -> passaro
	motor.adicionar_regra("passaro", {"tem_penas", "tem_bico", "voa"});
	// Se tem_pernas E tem_penas -> vertebrado
	motor.adicionar_regra("vertebrado", {"tem_pernas", "tem_penas"});

	// Processa
	motor.processar();

	// Verifica fatos deduzidos
	if (motor.eh_fato("passaro")) {
		cout << "O animal é uma ave!" << endl;
	}
	if (motor.eh_fato("vertebrado")) {
		cout << "É um vertebrado." << endl;
	}

	return 0;
}