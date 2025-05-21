# CryptoSpy 2.0

## Objetivo do Projeto
O CryptoSpy 2.0 é um sistema de gerenciamento de usuários e transações em criptomoedas (Bitcoin, Ethereum, Ripple). Permite:
- Cadastro e autenticação de usuários via CPF e senha.
- Depósitos e saques em BRL com registro de transações.
- Compra e venda de criptomoedas com aplicação de taxas de compra e venda.
- Emissão de extrato detalhado (data/hora, tipo, valor, taxa, criptomoeda e quantidade), exibido na tela ou salvo em arquivo.

## Compilação e Execução
Para compilar o programa em um ambiente Linux/Unix ou Windows com GCC instalado, execute:

```sh
gcc *.c
```

Para executar:

```sh
./a.out
```

## Uso do Programa
1. **Registro**: ao iniciar, escolha a opção "Registrar" e informe nome, CPF (11 dígitos) e senha numérica.  
2. **Login**: selecione "Login" e informe CPF e senha para acessar o menu principal.  
3. **Menu Principal**:
   - **Depósito**: informa valor em BRL e registra transação de depósito.  
   - **Saque**: solicita valor, valida saldo e registra transação de saque.  
   - **Saldo**: exibe saldo em BRL e saldos em BTC, ETH e XRP.  
   - **Extrato**: exibe ou salva em `extratos/extrato_<cpf>.txt` o histórico completo de transações.  
   - **Comprar Crypto**: escolha a moeda, informe valor em BRL, aplique taxa de compra e registre a transação.  
   - **Vender Crypto**: escolha a moeda, informe quantidade, aplique taxa de venda e registre a transação.  
   - **Mostrar/Atualizar Cotação**: exibe cotações atuais e permite ajuste aleatório.  
   - **Sair**: salva usuários e criptomoedas em arquivos binários e encerra.  

Use entradas numéricas (via `userinput`) para navegar e confirme cada operação quando solicitado.

## Integrantes do Grupo
- **Kaique Medeiros** – Matrícula: 22.224.005-3 
- **Thayane Andrade** – Matrícula: 22.224.003-8  
