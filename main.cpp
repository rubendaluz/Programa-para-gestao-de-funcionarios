#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define MAX 50

class Funcionario {
public:
    int num_funcionario;
    std::string nome;
    float salario;

    Funcionario() : num_funcionario(0), nome(""), salario(0.0) {}

    void inserir() {
        std::cout << "Introduza o numero do funcionario: ";
        std::cin >> num_funcionario;
        std::cout << "Introduza o nome do funcionario: ";
        std::cin.ignore();
        std::getline(std::cin, nome);
        std::cout << "Introduza o salario ganho pelo funcionario: ";
        std::cin >> salario;
    }
};

int menu() {
    int op;

    std::cout << "MENU:" << std::endl;
    std::cout << "\t1-Inserir funcionario." << std::endl;
    std::cout << "\t2-Contar funcionarios." << std::endl;
    std::cout << "\t3-Listar funcionarios por salario." << std::endl;
    std::cout << "\t0-Sair" << std::endl;
    std::cout << "Selecione>> ";
    std::cin >> op;

    return op;
}

void inserirFuncionario(std::ofstream& fout) {
    Funcionario funcionario;
    funcionario.inserir();

    fout.write(reinterpret_cast<const char*>(&funcionario), sizeof(Funcionario));
    if (!fout) {
        std::cout << "Erro ao gravar dados do funcionario." << std::endl;
    }
}

int contagem(std::ifstream& fin) {
    fin.seekg(0, std::ios::end);
    int n_fun = fin.tellg() / sizeof(Funcionario);
    return n_fun;
}

void lerFicheiro(std::ifstream& fin, int qtd, std::vector<Funcionario>& funcionarios) {
    fin.seekg(0, std::ios::beg);
    funcionarios.resize(qtd);
    fin.read(reinterpret_cast<char*>(funcionarios.data()), qtd * sizeof(Funcionario));
    if (!fin) {
        std::cout << "Erro na leitura dos dados do ficheiro." << std::endl;
    }
}

bool compareSalario(const Funcionario& a, const Funcionario& b) {
    return a.salario > b.salario;
}

void ordenarPorSalario(std::vector<Funcionario>& funcionarios) {
    std::sort(funcionarios.begin(), funcionarios.end(), compareSalario);

    std::cout << "NUMERO \tNOME \t\tSALARIO" << std::endl;
    for (const auto& funcionario : funcionarios) {
        std::cout << funcionario.num_funcionario << "\t" << funcionario.nome << "\t\t" << funcionario.salario << std::endl;
    }
}

int main() {
    int qtd, opcao;
    std::vector<Funcionario> funcionarios;
    std::fstream fout;

    fout.open("dados.dat", std::ios::binary | std::ios::out | std::ios::app);
    if (!fout) {
        std::cout << "Erro na abertura do ficheiro que guarda os dados do programa!!" << std::endl;
        return EXIT_FAILURE;
    }

    do {
        opcao = menu();
        switch (opcao) {
        case 1:
            inserirFuncionario(fout);
            break;
        case 2:
            qtd = contagem(fout);
            std::cout << "Foram inseridos " << qtd << " funcionarios no ficheiro." << std::endl;
            break;
        case 3:
            qtd = contagem(fout);
            lerFicheiro(fout, qtd, funcionarios);
            ordenarPorSalario(funcionarios);
            break;
        case 0:
            std::cout << "Programa encerrado" << std::endl;
            fout.close();
            break;
        default:
            std::cout << "Opcao inserida eh invalida!!!" << std::endl;
            break;
        }
    } while (opcao != 0);

    fout.close();
    return 0;
}
