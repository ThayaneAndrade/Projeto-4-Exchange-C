# CryptoSpy 2.0

## Objetivo do Projeto
O CryptoSpy 2.0 é um sistema de gerenciamento de usuários e transações em criptomoedas (Bitcoin, Ethereum, Ripple). Permite:
- Cadastro e autenticação de usuários via CPF e senha.
- Depósitos e saques em BRL com registro de transações.
- Compra e venda de criptomoedas com aplicação de taxas de compra e venda.
- Emissão de extrato detalhado (data/hora, tipo, valor, taxa, criptomoeda e quantidade), exibido na tela ou salvo em arquivo.

## Execução

Para executar:

# Módulo do Usuário:
```sh
./a.out
```
# Módulo do Administrador:
```sh
./admin
```

## Uso do Programa
1. **Login**: selecione "Login" e informe CPF e senha para acessar o menu principal.  
2. **Menu Principal**:
   - **Depósito**: informa valor em BRL e registra transação de depósito.  
   - **Saque**: solicita valor, valida saldo e registra transação de saque.  
   - **Saldo**: exibe saldo em BRL e saldos em BTC, ETH e XRP.  
   - **Extrato**: exibe ou salva em `extratos/extrato_<cpf>.txt` o histórico completo de transações.  
   - **Comprar Crypto**: escolha a moeda, informe valor em BRL, aplique taxa de compra e registre a transação.  
   - **Vender Crypto**: escolha a moeda, informe quantidade, aplique taxa de venda e registre a transação.  
   - **Mostrar/Atualizar Cotação**: exibe cotações atuais e permite ajuste aleatório.  
   - **Sair**: salva usuários e criptomoedas em arquivos binários e encerra.
   - 
## Administrador:
1. **Login**: selecione "Login" e informe CPF e senha do administrador para acessar o menu administrativo.
2. **Menu Administrativo**:
   - **Consultar Extrato do Usuário**: informe um cpf e consulte o extrato completo do usuário
   - **Registrar Usuário**: Inicia o registro de um usuário com cpf e senha
   - **Excluir Usuário**: informe um cpf e o usuário correspondente será removido do exchange
   - **Consultar Usuário**: Informe um cpf e receberá o saldo completo do usuário correspondente
   - **Criar Criptomoeda**: Crie uma criptomoeda inserindo seu nome, valor, taxa de compra e taxa de venda
   - **Excluir Criptomoeda**: Informe o nome de uma criptomoeda para exclui-la do exchange
   - **Mostrar criptomoedas**: Mostra todas as criptomoedas disponíveis atualmente no exchange
   - **Atualizar Cotacao**: Atualiza a cotacao das criptomoedas disponiveis, aumenta ou abaixa em 5%
   - **Lista de usuários**: Mostra todos os usuários com conta no exchange atualmente.
   - **Sair** Encerra o programa.

Use entradas numéricas (via `userinput`) para navegar e confirme cada operação quando solicitado.

## Integrantes do Grupo
- **Kaique Medeiros** – Matrícula: 22.224.005-3 
- **Thayane Andrade** – Matrícula: 22.224.003-8  
