# LLVM_Pass_Skeleton# LLVM_Pass_Skeleton
TODO : new PM 소스 추가, LLVM build 방법 README

##
## LLVM-13 설치 및 PATH 설정

Ubuntu 20.04.4 LTS
```
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -

apt-add-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-13 main" 

apt-get update

apt-get install -y llvm-13 llvm-13-dev libllvm13 clang-13 llvm-13-tools libmlir-13 libmlir-13-dev
```

> apt-repository 참고 : https://apt.llvm.org/
> 
> 설치 dir : /usr/lib/llvm-13 
>
> PATH 환경변수에 "/usr/lib/llvm-13/bin" 추가

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
> 해당 Pass 사용 시에는 -O1 옵션 사용해야만 정상 작동함. 
### use legacy Pass-Manager
```
opt -load ./libSamplePass.so --samplepass -enable-new-pm=0 -disable-output ../../sample/sample.ll
```

### use new Pass-Manager
```
opt -load-pass-plugin ./libSamplePass.so -passes=sample-pass -disable-output ../../sample/sample.ll
```

