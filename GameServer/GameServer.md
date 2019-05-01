# GameServer
- Winsock 라이브러리의 iocp와 비동기 통신 함수들을 사용했습니다.

## NoobBasic
- 서버에 필요한 기초라이브러리들 입니다.

## PacketGenerator
- 두 언어 간의 원활한 통신을 위해 각각의 언어로 패킷을 만들어주는 툴입니다.
- 중간 언어로 xml을 사용합니다.
- 기본 자료형, 구조체, enum 각종 컨테이너를 패킷에 담을 수 있습니다.
- C# 과 C++ 을 지원합니다.

## AWS
- 현재 Noob Game Server 는 aws에서 동작하고 있습니다.
- 읽기 권한만 가지고 있는 iam 계정으로 구성 환경을 직접 확인하실 수 있습니다.
    - url : https://293419094569.signin.aws.amazon.com/console
    - Id : GuestForInterview
    - Pass : kW=vx2sOiJqE
    - 권한(읽기) : vpc, ec2, s3

![aws_architecture](aws_arc.png)