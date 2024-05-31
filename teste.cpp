#include <iostream>

using namespace std; 
void apresentarAutor(string autor);

int main (){
    string nome;
    cout << "digite um autor: ";
    getline(cin,nome);
    apresentarAutor(nome);
}

void apresentarAutor(string autor) {
    unsigned int j = 0;
    string nome = "";
    string vet[10];
    for(int i = 0; i < autor.size(); i++){
        if (autor[i] != ' '){
            nome += toupper(autor[i]);
        }
        else{
            vet[j] = nome;
            nome = "";
            j++;
        }
    }
    if( nome != ""){
        vet[j] = nome;
        j++;
    }
    for (int i = 0; i < j; i++){
        if (vet[i] == "DOS" or vet[i] == "DA" or vet[i] == "DE" or vet[i] == "DAS"){
            for( int y = i; y < j - 1; y++){
                vet[y] = vet[y+1];
                
            }
            j--;
        }
    }
    cout << vet[3] << " " << vet[0][0] << "." << vet[1][0];

}