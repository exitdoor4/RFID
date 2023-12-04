## 프로젝트 설명
RFID를 이용하여 회사원이 일상생활에 사용하는 사원증을 이용하여
  
인증된 사람만 입장이 가능하는 시스템을 구축해보자

 let's create a system that uses RFID technology to restrict access 
 
 to certified individuals using their employee IDs.


---



## 최종 결과물

![1](https://github.com/exitdoor4/RFID/assets/74641060/854e7186-9e77-48b2-9646-99ac054fbfbc)





---



## 구성도

### 초기화면
![2](https://github.com/exitdoor4/RFID/assets/74641060/a3a1ed3c-3094-4a2e-9e0d-f917a871e50a)

처음 실행한 모습.


RFID와 DB가 활성화가 안돼어서 OFF로 표시

### MariaDB
![5](https://github.com/exitdoor4/RFID/assets/74641060/68bdb6b8-d739-4c63-af6d-29026f6cacd9)


데이터베이스 서버 구축


핀번호를 기본키로 사용하여 출입정보 확인가능


### 사원증 수정

![4](https://github.com/exitdoor4/RFID/assets/74641060/541074ff-6cf5-4985-a609-ee34522c2f9d)



![3](https://github.com/exitdoor4/RFID/assets/74641060/d1e81c4d-cc38-4e63-8cb1-7bd08f27eb1b)


수정하기 버튼을 클릭시 


이름과 부서, 사진을 수정할 수 있다.


### 수정 후, 출입정보 확인

![4](https://github.com/exitdoor4/RFID/assets/74641060/541074ff-6cf5-4985-a609-ee34522c2f9d)

이름과 부서, 사진의 절대경로가 변경


출입정보도 logout으로 체크가능하다.
