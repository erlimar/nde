NDE is a Native Development Environment
=======================================

NDE é um ambiente de desenvolvimento nativo, para ajudar o desenvolvedor na árdua tarefa
de preparar seus ambientes com suas várias bibliotecas...

## Construindo no Windows

> __NOTA:__ Você precisa estar em um _prompt de comandos_ do [Visual C++ Build Tools 2015 ou posterior](http://landinghub.visualstudio.com/visual-cpp-build-tools)

```powershell
cd .\win
nmake -f Makefile
```

Isso é o suficiente para gerar o executável __"nde.exe"__ em `.\build\win\nde.exe`!

## Construindo no Linux

> __NOTA:__ Você precisa do [GCC 4 ou posterior](https://gcc.gnu.org/) e do [GNU Make](https://www.gnu.org/software/make/). Eles normalmente são instalados no [Ubuntu](https://www.ubuntu.com/) através do comando `sudo apt-get install build-essential`.

```shell
cd ./linux
make -f Makefile
```

Isso é o suficiente para gerar o executável __"nde"__ em `./build/linux/nde`!

## Construindo no macOS

> TODO: ...
