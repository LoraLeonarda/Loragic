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
		void adicionar_regra_simples(string fato, vector<string> condicoes)
		{
			Rule r;
			r.fato_de_saida = fato;
			r.and_de_fatos = condicoes;
			regras.push_back(r);
		}
		void adicionar_regra(string fato, vector<vector<string>> condicoes)
		{
			for(vector<string> cond : condicoes)
			{
				adicionar_regra_simples(fato, cond);
			}
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
						if(cond.at(0) == '!')
						{
							if(contem(cond.substr(1), fatos)){aplicar_regra = false;break;}
						}
						else
						{
							if(!contem(cond, fatos)){aplicar_regra = false;break;}
						}
						
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

	// Fatos iniciais: clima, companhia, recursos
	motor.adicionar_fato("sol");
	motor.adicionar_fato("tem_companhia");
	motor.adicionar_fato("tem_dinheiro");
	// motor.adicionar_fato("chuva");
	// motor.adicionar_fato("tem_guarda_chuva");

	// Regras
	// atividade_externa se:
	//   (sol e tem_companhia)  OU  (neve e tem_equipamento)
	motor.adicionar_regra("atividade_externa", {
		{"sol", "tem_companhia"},
		{"neve", "tem_equipamento"}
	});

	// Se chuva e NÃO tem_guarda_chuva -> fica_em_casa
	motor.adicionar_regra("fica_em_casa", {
		{"chuva", "!tem_guarda_chuva"}
	});

	// Se fica_em_casa e tem_video_game -> joga_video_game
	motor.adicionar_regra("joga_video_game", {
		{"fica_em_casa", "tem_video_game"}
	});
	motor.adicionar_fato("tem_video_game");

	// Se atividade_externa e tem_dinheiro -> viaja
	motor.adicionar_regra("viaja", {
		{"atividade_externa", "tem_dinheiro"}
	});

	// Processa tudo
	motor.processar();

	// Exibe recomendações
	cout << "=== Recomendações para o fim de semana ===" << endl;
	if (motor.eh_fato("viaja")) {
		cout << "- Que tal uma viagem? (atividade externa + dinheiro)" << endl;
	}
	if (motor.eh_fato("atividade_externa")) {
		cout << "- Aproveite o ar livre!" << endl;
	}
	if (motor.eh_fato("fica_em_casa")) {
		cout << "- Melhor ficar em casa..." << endl;
	}
	if (motor.eh_fato("joga_video_game")) {
		cout << "- Hora de ligar o video game!" << endl;
	}
	if (!motor.eh_fato("atividade_externa") && !motor.eh_fato("fica_em_casa")) {
		cout << "- Nenhuma recomendação específica." << endl;
	}
}