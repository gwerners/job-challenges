#!/bin/bash

#https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
#para sair ao acontecer algum erro no script:
set -euo pipefail

#mostrar comandos a medida que executa (apenas para debug)
#set -x

#move para o diretorio do script caso seja executado de outro diretorio:
cd "$(dirname "${0}")"

#salva dir base
BASE=$(pwd)

function ExplainUsage {
  read -p "Esse script vai baixar o google benchmark compilar e linkar com o teste. Para cancelar aperte [Ctrl + c] ou [Enter] para continuar"
}

function CheckNeeded {
  NEEDED=$(which ${1})
  if [ ! -f "${NEEDED}" ]; then
    echo "${1} é uma dependência desse projeto"
    exit 0
  fi

}
function MKDIR {
  if [ ! -d "${1}" ]; then
    mkdir ${1}
  fi
}
function RMDIR {
  if [ -d "${1}" ]; then
    rm -rf ${1}
  fi
}
function CLEANUP {
  echo "Limpando arquivos temporarios..."
  RMDIR benchmark
  RMDIR lib
  RMDIR build
  rm -rf *.tar.gz

  exit 1
}

function TAR {
  #cria tar para evitar baixar novamente
  if [ ! -f "${1}.tar.gz" ]; then
    tar -czf ${1}.tar.gz $1
  fi
  if [ ! -d "${1}" ]; then
    if [ -f "${1}.tar.gz" ]; then
      tar -xzf ${1}.tar.gz
    fi
    if [ -f "${1}.zip" ]; then
      unzip ${1}.zip
    fi
  fi
}
function DownloadGBench {
  if [ ! -f "benchmark.tar.gz" ]; then
    if [ ! -d "benchmark" ]; then
        git clone https://github.com/google/benchmark.git
        git clone https://github.com/google/googletest.git benchmark/googletest
    fi
  fi
  TAR benchmark
}
function FixGBenchCMake {
  #remover linhas que geram erro na compilacao do google benchmark
  #add_cxx_compiler_flag(-pedantic)
  #add_cxx_compiler_flag(-pedantic-errors)
  sed --in-place '/  add_cxx_compiler_flag(-pedantic)/d' ./benchmark/CMakeLists.txt 
  sed --in-place '/  add_cxx_compiler_flag(-pedantic-errors)/d' ./benchmark/CMakeLists.txt
}
function BuildGBench {
  cd benchmark
  MKDIR build && cd build
  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=${1} ..
  make
  cd ../..
  MKDIR lib
  cp benchmark/build/src/*.a lib/
  cp benchmark/build/lib/*.a lib/
}
function BuildProgram {
  if [ ! -d "build" ]; then
    MKDIR build
  fi
  cd build
  cmake -DCMAKE_BUILD_TYPE=$1 ..
  make
  cd ..
}



#checa se foi passado argumento
if [ ${#} -ne 0 ]; then
  if [ "${1}" == "clean" ]; then
    CLEANUP
  fi
    if [ "${1}" == "fix" ]; then
    ./fixFormat.sh
  fi
fi

CheckNeeded tar  || exit 1
CheckNeeded sed  || exit 1
CheckNeeded git  || exit 1
CheckNeeded cmake || exit 1
CheckNeeded gcc || exit 1
CheckNeeded g++ || exit 1
ExplainUsage

BUILD_TYPE=Release
DownloadGBench
FixGBenchCMake
BuildGBench $BUILD_TYPE
BuildProgram $BUILD_TYPE
./build/bench_string_invert
./build/mock_string_invert
