#!/bin/bash

# Script de testes para o parsing do minishell
# Testa todos os aspectos mencionados no enunciado

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

MINISHELL="./minishell"
TOTAL=0
PASSED=0
FAILED=0

print_test() {
    echo -e "${YELLOW}[TEST $1]${NC} $2"
}

print_pass() {
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASSED++))
}

print_fail() {
    echo -e "${RED}✗ FAIL${NC} $1"
    ((FAILED++))
}

run_test() {
    ((TOTAL++))
    print_test "$TOTAL" "$1"
    
    # Executa o comando no minishell
    output=$(echo "$2" | $MINISHELL 2>&1)
    
    # Verifica se não houve segfault ou erro crítico
    if [ $? -eq 139 ]; then
        print_fail "Segmentation fault"
        return 1
    fi
    
    if [ -n "$3" ]; then
        if echo "$output" | grep -q "$3"; then
            print_pass
            return 0
        else
            print_fail "Expected output: $3"
            echo "Got: $output"
            return 1
        fi
    else
        print_pass
        return 0
    fi
}

echo "================================================"
echo "      MINISHELL PARSER - BATERIA DE TESTES     "
echo "================================================"
echo ""

# ============================================
# 1. TESTES DE ASPAS SIMPLES E DUPLAS
# ============================================
echo -e "${YELLOW}=== 1. ASPAS SIMPLES E DUPLAS ===${NC}"

run_test "Aspas simples - sem expansão de variáveis" "echo 'Hello \$USER'" "Hello \$USER"
run_test "Aspas simples - com metacaracteres" "echo 'test | grep'" "test | grep"
run_test "Aspas duplas - expansão de variáveis" "echo \"Hello \$USER\"" ""
run_test "Aspas duplas - sem expansão de metacaracteres" "echo \"test | grep\"" "test | grep"
run_test "Aspas mistas" "echo 'single' \"double\"" ""
run_test "Aspas vazias simples" "echo ''" ""
run_test "Aspas vazias duplas" "echo \"\"" ""

echo ""

# ============================================
# 2. TESTES DE REDIRECIONAMENTOS
# ============================================
echo -e "${YELLOW}=== 2. REDIRECIONAMENTOS ===${NC}"

# Preparar arquivo de teste
echo "test content" > /tmp/test_input.txt

run_test "Redirecionamento de entrada <" "cat < /tmp/test_input.txt" "test content"
run_test "Redirecionamento de saída >" "echo 'output test' > /tmp/test_output.txt && cat /tmp/test_output.txt" "output test"
run_test "Redirecionamento append >>" "echo 'line1' > /tmp/test_append.txt && echo 'line2' >> /tmp/test_append.txt && cat /tmp/test_append.txt" "line1"
run_test "Múltiplos redirecionamentos" "echo 'test' > /tmp/out1.txt > /tmp/out2.txt && cat /tmp/out2.txt" "test"

# Limpar arquivos de teste
rm -f /tmp/test_input.txt /tmp/test_output.txt /tmp/test_append.txt /tmp/out1.txt /tmp/out2.txt

echo ""

# ============================================
# 3. TESTES DE HEREDOC (<<)
# ============================================
echo -e "${YELLOW}=== 3. HEREDOC ===${NC}"

run_test "Heredoc simples" "cat << EOF
line1
line2
EOF" "line1"

run_test "Heredoc com expansão de variáveis" "cat << EOF
USER: \$USER
EOF" "USER:"

run_test "Heredoc sem expansão (delimitador entre aspas)" "cat << 'EOF'
\$USER should not expand
EOF" "\$USER"

echo ""

# ============================================
# 4. TESTES DE PIPES
# ============================================
echo -e "${YELLOW}=== 4. PIPES ===${NC}"

run_test "Pipe simples" "echo 'hello' | cat" "hello"
run_test "Múltiplos pipes" "echo 'test' | cat | cat | cat" "test"
run_test "Pipe com grep" "echo -e 'line1\nline2\nline3' | grep line2" "line2"
run_test "Pipe com redirecionamento" "echo 'data' | cat > /tmp/pipe_test.txt && cat /tmp/pipe_test.txt" "data"

rm -f /tmp/pipe_test.txt

echo ""

# ============================================
# 5. TESTES DE VARIÁVEIS DE AMBIENTE
# ============================================
echo -e "${YELLOW}=== 5. VARIÁVEIS DE AMBIENTE ===${NC}"

run_test "Expansão de variável simples" "echo \$USER" ""
run_test "Expansão de \$PATH" "echo \$PATH" ""
run_test "Variável inexistente" "echo \$NONEXISTENT_VAR_12345" ""
run_test "Variável com texto" "echo prefix\${USER}suffix" ""
run_test "\$? - exit status" "ls /nonexistent 2>/dev/null ; echo \$?" ""

echo ""

# ============================================
# 6. TESTES DE COMANDOS SIMPLES
# ============================================
echo -e "${YELLOW}=== 6. COMANDOS SIMPLES ===${NC}"

run_test "echo simples" "echo hello" "hello"
run_test "echo com -n" "echo -n hello" "hello"
run_test "echo múltiplos argumentos" "echo hello world test" "hello world test"
run_test "pwd" "pwd" ""
run_test "env (verifica se mostra variáveis)" "env | head -1" ""

echo ""

# ============================================
# 7. TESTES DE CAMINHOS
# ============================================
echo -e "${YELLOW}=== 7. CAMINHOS (relativos e absolutos) ===${NC}"

run_test "Caminho absoluto" "/bin/echo 'absolute path'" "absolute path"
run_test "Comando no PATH" "ls /tmp > /dev/null" ""
run_test "Comando inexistente" "nonexistent_command_xyz" ""

echo ""

# ============================================
# 8. TESTES DE CASOS ESPECIAIS
# ============================================
echo -e "${YELLOW}=== 8. CASOS ESPECIAIS ===${NC}"

run_test "Comando vazio" "" ""
run_test "Apenas espaços" "   " ""
run_test "Múltiplos espaços entre argumentos" "echo    hello    world" "hello"
run_test "Tabs entre argumentos" "echo	hello	world" "hello"
run_test "Aspas não fechadas devem ser ignoradas (não crashar)" "echo 'unclosed" ""

echo ""

# ============================================
# 9. TESTES DE COMBINAÇÕES
# ============================================
echo -e "${YELLOW}=== 9. COMBINAÇÕES COMPLEXAS ===${NC}"

run_test "Pipe + redirecionamento" "echo 'test' | cat > /tmp/combo.txt && cat /tmp/combo.txt" "test"
run_test "Aspas + variáveis + pipe" "echo \"\$USER\" | cat" ""
run_test "Múltiplos pipes + redirecionamento" "echo 'data' | cat | cat > /tmp/multi.txt && cat /tmp/multi.txt" "data"

rm -f /tmp/combo.txt /tmp/multi.txt

echo ""

# ============================================
# 10. TESTES DE EDGE CASES
# ============================================
echo -e "${YELLOW}=== 10. EDGE CASES ===${NC}"

run_test "Redirecionamento sem arquivo" "echo test >" ""
run_test "Pipe sem comando após" "echo test |" ""
run_test "Caracteres especiais em aspas" "echo 'test; test'" "test; test"
run_test "Barra invertida (não deve interpretar)" "echo 'test\\ntest'" "test\\ntest"

echo ""

# ============================================
# RESUMO DOS TESTES
# ============================================
echo "================================================"
echo "              RESUMO DOS TESTES                 "
echo "================================================"
echo -e "Total de testes: ${YELLOW}$TOTAL${NC}"
echo -e "Testes passados: ${GREEN}$PASSED${NC}"
echo -e "Testes falhados: ${RED}$FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}✓ TODOS OS TESTES PASSARAM!${NC}"
    exit 0
else
    echo -e "\n${RED}✗ ALGUNS TESTES FALHARAM${NC}"
    exit 1
fi
