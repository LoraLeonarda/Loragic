# Loragic: Lóra's Magic Logic
Esse repositório contém uma implementação simples e curta de um sistema de programação lógica em C++.

Esse sistema simples foi criado para resolver problemas simples de classificação lógica, e será usado para desenvolver possíveis partes de solução para problemas com um sistema especialista em meus projetos futuros

## Funcionalidades

- Armazenamento de **fatos** (afirmações verdadeiras).
- Definição de **regras** no formato: `se (condição1 OU (condição2 E !condição3) OU ...) então (fato_conclusão)`.
- Motor de inferência **forward chaining** (encadeamento para frente): aplica regras repetidamente até que nenhum fato novo possa ser deduzido.
- API simples para adicionar fatos, adicionar regras e processar a base de conhecimento.
- Vetor de condições de uma regra é um OR de ANDs, e o prefixo `!` pode ser utilizado para NOT.

## Como funciona

O sistema mantém dois vetores principais:

- `fatos`: lista de strings representando fatos conhecidos.
- `regras`: lista de objetos `Rule`, cada um contendo um `fato_de_saida` e uma lista `and_de_fatos` (condições que devem ser todas verdadeiras).

O método `processar()` executa o fechamento dedutivo:
1. Para cada regra, verifica se todas as suas condições estão presentes nos fatos atuais.
2. Se a conclusão da regra ainda não é um fato conhecido, ela é adicionada.
3. Repete até que nenhum fato novo seja gerado.

## Estrutura do código

### Classe `Rule`
Representa uma regra lógica.

| Atributo           | Tipo               | Descrição |
|--------------------|--------------------|-----------|
| `fato_de_saida`    | `string`           | O fato que pode ser deduzido. |
| `and_de_fatos`     | `vector<string>`   | Lista de fatos que devem ser verdadeiros (conjunção). |

### Classe `Loragic`
Gerencia fatos, regras e executa a inferência.

| Método                          | Descrição |
|---------------------------------|-----------|
| `apagar_fatos()`                | Remove todos os fatos. |
| `apagar_regras()`               | Remove todas as regras. |
| `adicionar_fato(string fato)`   | Insere um fato na base. |
| `adicionar_regra(string fato, vector<vector<string>> condicoes)` | Adiciona uma regra. |
| `adicionar_regra_simples(string fato, vector<string> condicoes)` | Adiciona uma regra composta somente por ANDs. |
| `eh_fato(string fato)`          | Verifica se um fato já está presente. |
| `processar()`                   | Aplica as regras até saturação. |

## Exemplo de uso

```cpp
#include <iostream>
#include "Loragic.cpp"

int main() {
    Loragic motor;

    // Adiciona fatos iniciais
    motor.adicionar_fato("tem_penas");
    motor.adicionar_fato("tem_bico");
    motor.adicionar_fato("voa");

    // Adiciona regras
    // Se tem penas E tem bico E voa -> passaro
    motor.adicionar_regra("passaro", {{"tem_penas", "tem_bico", "voa"}});
    // Se tem_pernas E tem_penas -> vertebrado
    motor.adicionar_regra("vertebrado", {{"tem_pernas", "tem_penas"}});

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