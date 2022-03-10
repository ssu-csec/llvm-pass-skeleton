# LLVM_Pass_Skeleton

TODO : new PM 소스 추가
### llvm-toolkits 명령어
> .c 소스파일 to .ll llvm IR코드
> -O0 -O1 -O2 Optimization 필요단계에 따라 적용해야함.
```
clang -S -emit-llvm -O0 <sample.c> -o <sample.ll>
```
> .ll llvm IR코드 to .bc llvm 비트코드
```
llvm-as <sample.ll> -o <sample.bc>
```
> .bc llvm 비트코드 to .ll llvm IR코드
```
llvm-dis <sample.bc> -o <sample.ll>
```

##
## LLVM-13 설치 및 PATH 설정

### Ubuntu 20.04.4 LTS apt 패키지를 이용한 설치.
```
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -

apt-add-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-13 main" 

apt-get update

apt-get install -y llvm-13 llvm-13-dev libllvm13 clang-13 llvm-13-tools libmlir-13 libmlir-13-dev
```


### github llvm-projcet를 직접 컴파일하기
```
apt-get update && apt-get install -y \
    git \
    cmake \
    ninja-build \
    build-essential \

git clone --branch release/13.x --depth 1 https://github.com/llvm/llvm-project

mkdir <install dir>

mkdir llvm-project/build

cd llvm-project/build

cmake -G Ninja \
        -DLLVM_ENABLE_PROJECTS=clang \
        -DLLVM_TARGETS_TO_BUILD=X86 \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$LLVM_DIR \
        -DLLVM_INSTALL_UTILS=ON \
        ../llvm

cmake --build . --target install

(option) rm -r /llvm-project

```

> apt-repository 참고 : https://apt.llvm.org/
> 
> 설치 dir : <install dir> 본인 지정.
>
> PATH 환경변수에 "<install dir>/bin" 추가

##
## How to build
```
mkdir ./src/<legacyPM or newPM>/build

cd ./src/<legacyPM or newPM>//build

cmake ..

make
```

##
## How to use
### use legacy Pass-Manager
```
opt -load ./libSamplePass.so --samplepass -enable-new-pm=0 -disable-output ../../sample/sample.ll
```

### use new Pass-Manager
```
opt -load-pass-plugin ./libSamplePass.so -passes=sample-pass -disable-output ../../sample/sample.ll
```

