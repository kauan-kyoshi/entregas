#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- 1. Definição das Estruturas --- */

typedef enum e_redir_type
{
    REDIR_IN,    // <
    REDIR_OUT,   // >
    HEREDOC,     // <<
    APPEND       // >>
} t_redir_type;

typedef struct s_redir
{
    t_redir_type    type;
    char            *file;
    struct s_redir  *next;
} t_redir;

typedef struct s_cmd
{
    char            **args;
    t_redir         *redirs;
    struct s_cmd    *next;
} t_cmd;

/* --- 2. Funções Auxiliares (Para facilitar a criação manual) --- */

// Cria um nó de redirecionamento
t_redir *new_redir(t_redir_type type, char *filename)
{
    t_redir *node = malloc(sizeof(t_redir));
    node->type = type;
    node->file = strdup(filename); // Duplica a string para simular alocação real
    node->next = NULL;
    return (node);
}

// Cria um nó de comando
t_cmd *new_cmd(char **args)
{
    t_cmd *node = malloc(sizeof(t_cmd));
    node->args = args;
    node->redirs = NULL;
    node->next = NULL;
    return (node);
}

/* --- 3. A Função Solicitada: "O Parser Simulado" --- */

t_cmd *populate_struct_manual(void)
{
    // Vamos construir: < entrada.txt cat | grep "erro fatal" > log.txt

    // --- PARTE A: Primeiro Comando (cat) ---
    // 1. Criar os argumentos: {"cat", NULL}
    char **args1 = malloc(sizeof(char *) * 2);
    args1[0] = strdup("cat");
    args1[1] = NULL;

    t_cmd *cmd1 = new_cmd(args1);

    // 2. Adicionar o redirecionamento: < entrada.txt
    // Note que o parser identifica que isso pertence ao cmd1, mesmo estando antes
    cmd1->redirs = new_redir(REDIR_IN, "entrada.txt");


    // --- PARTE B: Segundo Comando (grep) ---
    // 1. Criar os argumentos: {"grep", "erro fatal", NULL}
    char **args2 = malloc(sizeof(char *) * 3);
    args2[0] = strdup("grep");
    args2[1] = strdup("erro fatal"); // Parser já removeu as aspas aqui
    args2[2] = NULL;

    t_cmd *cmd2 = new_cmd(args2);

    // 2. Adicionar o redirecionamento: > log.txt
    cmd2->redirs = new_redir(REDIR_OUT, "log.txt");


    // --- PARTE C: Conectar os Vagões (O Pipe) ---
    cmd1->next = cmd2;

    // Retorna a cabeça da lista (o primeiro vagão)
    return (cmd1);
}

/* --- 4. Função de Debug (Para ver se funcionou) --- */

void print_pipeline_structure(t_cmd *cmd_list)
{
    t_cmd *current = cmd_list;
    int i = 1;

    while (current)
    {
        printf("--- COMANDO %d ---\n", i);
        
        // Imprimir Argumentos
        printf("  Args: ");
        int j = 0;
        while (current->args[j])
        {
            printf("[%s] ", current->args[j]);
            j++;
        }
        printf("\n");

        // Imprimir Redirecionamentos
        t_redir *r = current->redirs;
        while (r)
        {
            char *symbol = (r->type == REDIR_IN) ? "<" : 
                           (r->type == REDIR_OUT) ? ">" : "?";
            printf("  Redir: %s %s\n", symbol, r->file);
            r = r->next;
        }

        if (current->next)
            printf("       |\n       V (pipe)\n");
        else
            printf("       (fim)\n");

        current = current->next;
        i++;
    }
}

t_cmd *pupulate_struct(void)
{
    printf("Simulando Parser para: < entrada.txt cat | grep \"erro fatal\" > log.txt\n\n");
    
    t_cmd *pipeline = populate_struct_manual();
    
    // print_pipeline_structure(pipeline);

    // Nota: Em um código real, você precisaria de uma função free_pipeline aqui!
    return (pipeline);
}