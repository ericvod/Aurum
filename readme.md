# Aurum Programming Language

[English](#english) | [Português](#português)

<a name="english"></a>
## English

### Overview
Aurum is a simple, interpreted programming language designed for educational purposes. It supports basic arithmetic operations, variable declarations, and includes features like type inference and a built-in `print()` function.

### Features
- Basic arithmetic operations (+, -, *, /)
- Variable declaration with type inference using `var`
- Explicit type declaration (number, string, bool)
- Built-in `print()` function
- Ability to run scripts from files

### Getting Started
#### Prerequisites
- C++ compiler with C++17 support
- CMake (version 3.10 or higher)

#### Building the Project
1. Clone the repository:
   ```
   git clone https://github.com/ericvod/aurum.git
   cd aurum
   ```

2. Create a build directory and navigate to it:
   ```
   mkdir build && cd build
   ```

3. Generate the build files and compile:
   ```
   cmake ..
   make
   ```

#### Running Aurum
- Interactive mode:
  ```
  ./aurum
  ```
- Run a script:
  ```
  ./aurum path/to/your/script.am
  ```

### Usage Examples
```
Aurum> var x = 10
10
Aurum> print(x)
10
Aurum> string s = "Hello, Aurum!"
"Hello, Aurum!"
Aurum> print(s)
Hello, Aurum!
Aurum> bool b = true
true
Aurum> print(b)
true
```

---

<a name="português"></a>
## Português

### Visão Geral
Aurum é uma linguagem de programação interpretada simples, projetada para fins educacionais. Ela suporta operações aritméticas básicas, declarações de variáveis e inclui recursos como inferência de tipos e uma função `print()` integrada.

### Características
- Operações aritméticas básicas (+, -, *, /)
- Declaração de variáveis com inferência de tipo usando `var`
- Declaração explícita de tipo (number, string, bool)
- Função `print()` integrada
- Capacidade de executar scripts a partir de arquivos

### Começando
#### Pré-requisitos
- Compilador C++ com suporte a C++17
- CMake (versão 3.10 ou superior)

#### Construindo o Projeto
1. Clone o repositório:
   ```
   git clone https://github.com/ericvod/aurum.git
   cd aurum
   ```

2. Crie um diretório de build e navegue até ele:
   ```
   mkdir build && cd build
   ```

3. Gere os arquivos de build e compile:
   ```
   cmake ..
   make
   ```

#### Executando Aurum
- Modo interativo:
  ```
  ./aurum
  ```
- Executar um script:
  ```
  ./aurum caminho/para/seu/script.am
  ```

### Exemplos de Uso
```
Aurum> var x = 10
10
Aurum> print(x)
10
Aurum> string s = "Olá, Aurum!"
"Olá, Aurum!"
Aurum> print(s)
Olá, Aurum!
Aurum> bool b = true
true
Aurum> print(b)
true
```