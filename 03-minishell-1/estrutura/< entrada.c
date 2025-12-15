< entrada.txt cat | grep "erro fatal" > log.txt

token_1 address: 0x100
{
    type: TOKEN_REDIR_IN
    raw:  "<"
    next: 0x200
}

token_2 address: 0x200
{
    type: TOKEN_WORD
    raw:  "entrada.txt"
    next: 0x300
}

token_3 address: 0x300
{
    type: TOKEN_WORD
    raw:  "cat"
    next: 0x400
}

token_3 address: 0x300
{
    type: TOKEN_WORD
    raw:  "cat"
    next: 0x400
}

token_4 address: 0x400
{
    type: TOKEN_PIPE
    raw:  "|"
    next: 0x500
}

token_5 address: 0x500
{
    type: TOKEN_WORD
    raw:  "grep"
    next: 0x600
}

token_6 address: 0x600
{
    type: TOKEN_WORD
    raw:  "erro fatal"  // Nota: As aspas foram removidas pelo lexador (geralmente)
    next: 0x700
}

token_7 address: 0x700
{
    type: TOKEN_REDIR_OUT
    raw:  ">"
    next: 0x800
}

token_8 address: 0x800
{
    type: TOKEN_WORD
    raw:  "log.txt"
    next: NULL  // Fim da lista
}