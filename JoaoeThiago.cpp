#include <iostream> 
#include <cstring>
#include <cctype>


#define tmax 100
using namespace std;

void relatorioAcervo(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int &ex );
void addExemplaresAcervo(string vetISBN[], int vetExem[], int ex);
void ordenavetores(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int ex);
void excluiLivro(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int &ex );
string lernomeInteiro();
void apresentarAutor(string autor);
string validaIsbn();
int validaInt(string frase);
string validaString( string frase);
void addlivro(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int &ex );
void achouISBN(string vetIsbn[], int ex, bool &achou, int &indice);
void pesquisaLivro(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int ex );

int main (){
    string vetISBN[tmax], vetTitulo[tmax], vetAutor[tmax],vetEdit[tmax];
    int vetExem[tmax], op;
    int ex = 0;
    bool continuar;
    do{
        cout <<" 1. adicionar um livro no acervo" << endl;
        cout <<" 2. consultar um livro por ISBN" << endl;
        cout <<" 3. excluir um livro" << endl;
        cout <<" 4. adicionar exemplares do livro no acervo" << endl;
        cout <<" 5. relatorio do acervo" << endl;
        cout <<" 6. sair do programa" << endl;                                     
        cout <<" digite uma opcao: " << endl;
        cin >> op;
        cin.ignore();

        switch (op){
            case 1:
                addlivro(vetISBN, vetTitulo, vetAutor, vetEdit,vetExem,ex);
                ordenavetores(vetISBN, vetTitulo, vetAutor, vetEdit,vetExem,ex);
                break;
            case 2:
                pesquisaLivro(vetISBN,vetTitulo, vetAutor, vetEdit,vetExem,ex);
                break;
            case 3:
                excluiLivro(vetISBN,vetTitulo, vetAutor, vetEdit,vetExem,ex);
                ordenavetores(vetISBN,vetTitulo, vetAutor, vetEdit,vetExem,ex);
                break;
            case 4:
                addExemplaresAcervo(vetISBN,vetExem,ex);
                break;
            case 5:
                relatorioAcervo(vetISBN,vetTitulo, vetAutor, vetEdit,vetExem,ex);
                break;
            case 6: 
                continuar = false;
                break;
            default:
                cout << "opcao invalida" << endl;
                break;
        }

    }while(!continuar);

    return 0;
}

string lernomeInteiro(){
    string info, nome, sobrenome, nomecompleto; 
    bool validada; 
    unsigned int i; 
    do{ 
        validada=true; 
        cout <<"Nome: "; 
        getline(cin,info); 
        if(info=="") // se for string vazia 
            validada= false; 
        for(unsigned int i=0; i<info.length(); i++) // varre letra a letra 
            if(not isalpha(info[i]) and info[i]!=' ') 
            validada= false; //erro se nao eh letra do alfabeto nem branco 
        if(not validada) 
            cout <<"Entrada invalida, digite novamente"<< endl; 
    }while(not validada); 
    nome = info; // copia entrada para a variavel nome 
    do{ 
        validada=true; 
        cout <<"Sobrenome: "; 
        getline(cin,info); 
        if(info=="") // se for string vazia 
            validada= false; 
        for(i=0; i<info.length(); i++) // varre letra a letra 
            if(not isalpha(info[i]) and info[i]!=' '){
                validada= false; //erro se nao eh letra do alfabeto nem branco 
            }
        if(not validada) 
            cout <<"Entrada invalida, digite novamente"<< endl; 
        } 
    while(not validada); 
    sobrenome = info; // copia entrada para a variavel sobrenome 
    nomecompleto = nome+" "+sobrenome; 
    cout <<"Nome completo:"<<nomecompleto<<endl;
    return nomecompleto; 
}
void apresentarAutor(string autor) {
  string nome1, nome2, nome3, maiusculo = "";
  char inicial1, inicial2;
  unsigned int cont = 0;

  while (cont < autor.size() && autor.at(cont) != ' ') {
    nome1 += autor.at(cont);
    cont++;
  }
  cont++;

  while (cont < autor.size() && autor.at(cont) != ' ') {
    nome2 += autor.at(cont);
    cont++;
  }
  cont++;

  while (cont < autor.size()) {
    nome3 += autor.at(cont);
    cont++;
  }
  for(unsigned int i = 0; i < nome3.size(); i++){
    maiusculo += toupper(nome3[i]);
  }
  inicial1 = toupper(nome1[0]);
  inicial2 = toupper(nome2[0]);

  cout << maiusculo << ", " << inicial1 << "." << inicial2 << "."; 
  
}
string validaIsbn(){
    string x, isbn = "";
    bool valido;
    int cont;
    long long int num, div = 1000000000000, result = 0;
    do {
        valido = true;
        cont = 0;
        cout << "digite o ISBN: ";
        getline(cin, x);
        if (x == " ") {
            valido = false;
            cout << "erro digite o isbn novamente" << endl;
        } else {
            if (x.size() != 17) {
                valido = false;
                cout << "erro digite o isbn novamente" << endl;
            } 
            else {
                if (!isdigit(x[0])) {
                    valido = false;
                    cout << "erro digite o isbn novamente" << endl;
                } else {
                    for (unsigned int i = 0; i < x.size(); i++) {
                        if (isdigit(x[i])) {
                            isbn += x[i];
                        } else if (x[i] == '-' && cont < 4) {
                            cont++;
                        } else {
                            valido = false;
                            cout << "erro digite o isbn novamente" << endl;
                            break;
                        }
                    }
                if (cont != 4 and !valido) {
                valido = false;
                cout << "erro digite o isbn novamente" << endl;
            } else {
                num = atoll(isbn.c_str());
                for (int i = 1; i < 13; i++) {
                    if (i % 2 == 0) {
                        result += ((num / div) % 10) * 3;
                        div = div / 10;
                    } else {
                        result += ((num / div) % 10);
                        div = div / 10;
                    }
                }
                if(result%10 != 0){
                    result = 10 - (result %10);
                    if(result != num%10){
                        valido = false;
                        cout << "isbn invalido digite novamente" << endl;
                    }
                }
                else if (num%10 != 0){
                    valido = false;
                    cout << "isbn invalido digite novamente" << endl;
                }
            }
       }
    }
            
        }
    } while (!valido);
    return x;
}
int validaInt(string frase){
    bool validada;
    string info;
    int x;
    do{ 
        validada=true; // p/ ver se tem erro, considera valida inicialmente 
        cout <<frase; 
        getline(cin,info); // ler string!!!
        
        if(info=="") // se for string vazia 
            validada=false; 
        else 
        if(not isdigit(info[0])) //se nao for digito/sinal 
            validada=false;     
        else 
        for(unsigned int i=1; i<info.length(); i++) {// varre demais posicoes 
            if(not isdigit(info[i])){ // se nao for digito 
            validada=false; 
            break; 
            } 
        }
        if(not validada) 
            cout <<"Numero invalido, digite novamente."<<endl; 
    } while(not validada); 
    x=atoi(info.c_str()); // faz conversao pq entrada foi correta 
    return x;
}
string validaString( string frase){
    string nome;
    do{
        cout << frase;
        getline(cin,nome);
    }while(nome == " ");
    return nome;
}
void addlivro(string vetISBN[], string vetTitulo[],string vetAutor[], string vetEditora[], int vetExem[], int &ex ){
    string isbn = validaIsbn();
    bool achou = false;
    for(int i = 0; i < ex; i++){
        if(isbn == vetISBN[i]){
            cout << "livro ja existente" << endl;
            achou = true;
        }
    }
    if(achou == false){
        vetISBN[ex] = isbn;
        cout << " autor(a) " << endl;
        vetAutor[ex] = lernomeInteiro();
        vetExem[ex] = validaInt("digite o numero de exemplares: ");
        vetTitulo[ex] = validaString("insira o titulo do livro: ");
        vetEditora[ex] = validaString("digite o nome da editora: ");
        cout << "inclusao feita com sucesso.";
        ex++;
    }
}
void pesquisaLivro(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int ex ){
    bool achou;
    int indice;
    achouISBN(vetISBN,ex,achou,indice);
    if(achou){
        cout << "Titulo: " << vetTitulo[indice] << endl;
        cout << "Autor: "; apresentarAutor(vetAutor[indice]);
        cout << endl;
        cout << "Editor(a): " << vetEditora[indice] << endl;
        cout << "ISBN: " << vetISBN[indice] << endl;
        cout << "Num de exemplares: " << vetExem[indice] << endl;

    }

}
void relatorioAcervo(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int &ex ){
    for(int i = 0; i < ex; i++){
        cout << i+1 << " Livro do Acervo: " << endl;
        cout << "Titulo: " << vetTitulo[i] << endl;
        cout << "Autor: "; apresentarAutor(vetAutor[i]); 
        cout << endl;
        cout << "Editor(a): " << vetEditora[i] << endl;
        cout << "ISBN: " << vetISBN[i] << endl;
        cout << "Num de exemplares: " << vetExem[i] << endl;
        cout << endl;
    }
}
void achouISBN(string vetIsbn[], int ex, bool &achou, int &indice){
    string isbn = validaIsbn();
    indice = 0;
    achou = false;
    for(int i = 0; i < ex; i++){
        if(isbn == vetIsbn[i]){
            cout << "Livro encontrado" << endl;
            indice=i;
            achou =  true;
        }
    }
    if (!achou){
        cout <<"livro inexistente";
    }
}
void excluiLivro(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[], int &ex ){
    int indice;
    bool achou;
    achouISBN(vetISBN,ex,achou,indice);
    if (achou){
        for(int i = indice; i < ex - 1; i++){
            vetISBN[i] = vetISBN[i+1];
            vetTitulo[i] = vetTitulo[i+1];
            vetAutor[i] = vetAutor[i+1];
            vetEditora[i] = vetEditora[i+1];
            vetExem[i] = vetExem[i+1];
        }
        cout << "Livro Excluido." << endl;
        ex--;
    }
}
void ordenavetores(string vetISBN[], string vetTitulo[], string vetAutor[], string vetEditora[], int vetExem[],int ex){
    for (int i = 0; i < ex; i++){
        for(int j = 0; j < ex-i-1; j++){
            if(vetTitulo[j] > vetTitulo[j+1]){
                swap(vetTitulo[j],vetTitulo[j+1]);
                swap(vetISBN[j],vetISBN[j+1]);
                swap(vetAutor[j],vetAutor[j+1]);
                swap(vetEditora[j],vetEditora[j+1]);
                swap(vetExem[j],vetExem[j+1]);
            }
        }
    }
}
void addExemplaresAcervo(string vetISBN[], int vetExem[], int ex){
    int indice, nLivros=0;
    bool achou;
    achouISBN(vetISBN,ex,achou,indice);
    if (achou){
        nLivros=validaInt("Numero de livros a serem adicionados?");
        vetExem[indice]+= nLivros;
        cout << "Exemplares incluidos" << endl;
    }
}



