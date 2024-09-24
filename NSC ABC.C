#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Função para criar a tabela de controle de ativos financeiros
void criar_tabela(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS ativos ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nome TEXT, "
                      "valor REAL, "
                      "tipo TEXT, "
                      "data_aquisicao TEXT, "
                      "descricao TEXT, "
                      "token_nsc TEXT);";  // Adicionando coluna para Token NSC
    
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Tabela de ativos financeiros criada com sucesso.\n");
    }
}

// Função para adicionar um ativo financeiro
void adicionar_ativo(sqlite3 *db, const char *nome, double valor, const char *tipo, const char *data_aquisicao, const char *descricao, const char *token_nsc) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO ativos (nome, valor, tipo, data_aquisicao, descricao, token_nsc) VALUES (?, ?, ?, ?, ?, ?);";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a instrução: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, valor);
    sqlite3_bind_text(stmt, 3, tipo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, data_aquisicao, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, descricao, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, token_nsc, -1, SQLITE_STATIC);  // Ligando o token NSC
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao adicionar ativo: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Ativo adicionado com sucesso.\n");
    }
    
    sqlite3_finalize(stmt);
}

// Exemplo de uso da função de adicionar ativo
int main() {
    sqlite3 *db;
    int rc = sqlite3_open("ativos_financeiros.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    criar_tabela(db);

    // Exemplo de operação
    adicionar_ativo(db, "Imóvel Comercial", 1000000, "Real Estate", "2024-01-10", "Loja no centro da cidade", "NSC ABC");

    // Fechar a conexão com o banco de dados ao finalizar o programa
    sqlite3_close(db);
    return 0;
}
