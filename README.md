# 어드벤처 디자인: 이미지 처리 프로그램

## 프로젝트 개요
본 프로젝트는 이미지 처리 콘솔 프로그램으로, 이미지 반전 처리 및 사각형 그리기와 같은 주요 기능을 제공합니다. 이 프로그램은 이미지의 픽셀 데이터를 분석, 처리하며 다양한 응용 가능성을 제공합니다.

### 주요 기능
- **이미지 반전 처리**: PGM, PPM 파일 형식의 반전 처리 지원.
- **사각형 그리기**: 기존 이미지 위 또는 새로운 이미지 위에 사각형을 그리는 기능.
- **파일 입출력**: 이미지 로드 및 수정 후 저장 기능.
- **다중 파일 처리**: 여러 소스 파일과 헤더 파일을 통한 효율적인 모듈 구성.
- **사용자 입력 기반 처리**: 메뉴 기반으로 동작하며 사용자의 직관적 입력 지원.

---

## 실행 방법

1. **프로그램 실행**: 콘솔에서 프로그램을 실행하면 메뉴가 출력됩니다.

    <img src="https://github.com/user-attachments/assets/901e0eef-2619-4ef9-bffd-5b93abf4e5bd" width="30%">

2. **메뉴 선택**:
    
    <img src="https://github.com/user-attachments/assets/fc31df43-7eeb-4a56-9cde-823e51eb8f29" width="30%">

    - `1`: 이미지 목록 출력 및 선택한 파일 반전 처리 후 저장.
    
    <img src="https://github.com/user-attachments/assets/2c645656-b7c8-4907-9e4b-11fbc54e30fa" width="50%">

    - `2`: 사각형 그리기:
        - 옵션 1: 기존 이미지 위에 사각형 추가.
        - 옵션 2: 흰 바탕의 새로운 이미지에 사각형 추가.
    
    <img src="https://github.com/user-attachments/assets/cc5e0f32-0104-4cd0-b47d-1e92bf0e6b26" width="50%">

    - `3`: 프로그램 종료.

2. **이미지 저장**: 반전된 이미지 또는 사각형이 추가된 이미지는 지정된 폴더에 저장됩니다.

---

## 주요 알고리즘
<img src="https://github.com/user-attachments/assets/8bee81da-a81b-4fa6-85ba-4005886f10af" width="80%">

### 반전 처리
- 각 픽셀에 대해 최대 밝기 값 - 현재 값 계산.

### 사각형 그리기
- 사용자가 입력한 위치, 크기, 색상에 따라 이미지 데이터를 수정.

---

## 실행 화면
1. **프로그램 메뉴**
  ```
   1. 이미지 반전 처리
   2. 사각형 그리기
   3. 종료
  ```
3. **이미지 반전 처리**
   - 선택한 이미지를 반전 처리 후 `_inverted`라는 이름으로 저장.
     ![image](https://github.com/user-attachments/assets/01233d94-907e-46bb-aa21-fb71fc8d65d3)
     ![image](https://github.com/user-attachments/assets/b0a3a415-6c28-45fc-b35f-6968c2d2051b)

4. **사각형 그리기**
   - 기존 이미지 또는 흰 바탕 이미지 위에 사각형 추가.
     ![image](https://github.com/user-attachments/assets/95b9f94e-6f52-4c85-b733-ebab88d01f5d)

---

## 설계 제한 요소
- **파일 형식**: PGM, PPM 형식만 지원.
- **사용자 입력**: 텍스트 기반 입력 및 메뉴 선택.
- **성능 제한**: 메모리 사용과 이미지 크기에 제한.

---

## 실행 흐름도

<img src = https://github.com/user-attachments/assets/ce696467-3676-499b-9ef8-d9fd2cc0d06b width="80%">

---

## 모듈 설계

<img src = https://github.com/user-attachments/assets/72ef49be-bf73-4067-87dd-664eb1a0d81b width="80%">

---

## 개발 환경
- **언어**: C++
- **IDE**: Microsoft Visual Studio

---

## 결론
이 프로젝트를 통해 이미지 반전 및 사각형 그리기 프로그램을 개발했습니다. 향후에는 GUI 추가 및 더 복잡한 이미지 처리 기능을 개발하여 다양한 응용 분야에 활용할 수 있는 프로그램으로 확장할 계획입니다.

---

## 느낀 점
이 프로젝트를 진행하며 파일 처리와 이미지 처리의 기초를 배우고 다양한 기술을 습득할 수 있었습니다. 설계와 분석의 중요성을 다시 한번 느끼며 체계적인 개발 과정의 필요성을 깨달았습니다.


## 개발일
- 2023년 9월 24일까지
