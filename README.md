# Qt 를 이용한 학생 출결 관리 시스템

학생 출결 관리 시스템 클라이언트 입니다.

## 📂 프로젝트 구조

- `client.h`: 클라이언트 헤더 파일
- `client.cpp`: 클라이언트 구현 파일
- `*.json`: 사용자 정보 및 출결 정보 파일 (서버에 저장됨)

## 🚀 실행 방법

```bash
# 클라이언트 실행
git clone https://github.com/your-username/veda_project1.git
cd veda_project1
qmake
make
./veda_project1

# 실행 시 서버가 실행되고 있지 않다면
cd ..
git clone https://github.com/your-username/veda_project1_server.git
cd veda_project1_server
qmake
make
./veda_project1_server
```

## 🛠️ 기술 스택

- Qt 6.11.0
- C++
