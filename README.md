NDE is a Native Development Environment
=======================================

NDE é um ambiente de desenvolvimento nativo, para ajudar o desenvolvedor na árdua tarefa
de preparar seus ambientes com suas várias bibliotecas...

## Construindo no Windows

> __NOTA:__ Você precisa estar em um _prompt de comandos_ do [Visual C++ Build Tools 2015 ou posterior](http://landinghub.visualstudio.com/visual-cpp-build-tools)

```powershell
# Instala o CMake localmente para build
.\bootstrap.ps1

# Cria um diretório para os artefatos de build
mkdir build
cd build

# Se preferir pode adicionar ".cmake\bin" ao PATH e executar somente `cmake ...`
.\.cmake\bin\cmake.exe -G "NMake Makefiles" ..
.\.cmake\bin\cmake.exe --build .
```

Isso é o suficiente para gerar o executável `.\build\nde.exe`!

## Construindo no Linux

> __NOTA:__ Você precisa do [GCC 4 ou posterior](https://gcc.gnu.org/) e do [GNU Make](https://www.gnu.org/software/make/). Eles normalmente são instalados no [Ubuntu](https://www.ubuntu.com/) através do comando `sudo apt-get install build-essential`.

```bash
# Instala o CMake localmente para build
./bootstrap.sh

# Cria um diretório para os artefatos de build
mkdir build
cd build

# Se preferir pode adicionar ".cmake/bin" ao PATH e executar somente `cmake ...`
./.cmake/bin/cmake -G "Unix Makefiles" ..
./.cmake/bin/cmake --build .
```

Isso é o suficiente para gerar o executável `./build/linux/nde`!

## Construindo no macOS

> TODO: ...
