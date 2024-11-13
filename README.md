<p align="center"><img alt="1" src="https://github.com/user-attachments/assets/c464f54b-1e88-4a0b-8b89-1836ed310c95"></p>

<h1>DirectX11 포트폴리오 : Have a Nice Death</h1>



> DirectX11 을 활용한 2D Game Copy Project
> 
<a target="_blank" rel="noopener noreferrer nofollow" href="https://aback-bunny-566.notion.site/Copycat-s-Have-a-Nice-Death-ddd308253af647b89185014930b2832a?pvs=4"><img src="https://img.shields.io/badge/Notion-%23000000.svg?style=for-the-badge&logo=notion&logoColor=white)" data-canonical-src="	https://img.shields.io/badge/Notion-000000?style=for-the-badge&logo=notion&logoColor=white" style="max-width: 100%;"></a>
<br>
<br>

<h2>프로젝트 영상</h2>

시연 영상

<h4>이미지를 클릭하면 youtube링크로 이동합니다</h4>

[![Video Label](https://github.com/user-attachments/assets/89cbbe45-1c00-4691-8a1e-be5d4ae8cf0e)](https://youtu.be/OB0M-_r7OZA?si=sKDGdixgh7xdeGEb)



<br>
<br>

<h2>프로젝트 개요</h2>
<p align="center"><img width="550" alt="1" src="https://github.com/user-attachments/assets/71dccc97-bea6-4518-93ea-686207a58511"></p>

```
2023년 Magic Design Studios 에서 출시된 "Have a Nice Death" 의 모작으로, 
C++, DirectX11 을 활용해 제작했습니다.

개발자는 ImGui 라이브러리를 활용하여 게임 내 Object의 Component를 직접 설정할수 있고,
Animation Editor 및 Sprite Editor를 통하여 Animation과 Sprite를 제작할수 있으며
Collider Tool을 통해서 Platform의 지형을 직접 설정할 수 있습니다.

직관적인 인터페이스를 통해 개발 효율성과 확장성을 증가시켰습니다.
또 원작 게임의 컨텐츠를 차용하여, 사용자는 스킬 사용을 통한 몬스터 사냥, 보스레이드 등
Ability의 성장을 경험할 수 있습니다.
```
<br>
<br>
<h2>프로젝트 설명</h2>

<b>게임 설명</b>
<p align="center"><img width="250" src="https://github.com/user-attachments/assets/57a64929-e315-4e12-ab89-270b9188d4e7"></p>
<p align="center"><img width="610" alt="image" src="https://github.com/user-attachments/assets/9bc2c3e0-06b5-42dc-8714-f3fa8f6f712b"></p>
<br>
<b>프로젝트에 반영된 게임의 특징</b>
<br><br>


* 게임 플레이 및 매커니즘
```
Have a Nice Death는 좌/우/점프키를 활용하는
2D 횡스크롤 Action RPG 입니다.


캐릭터가 갖고 있는 고유 스킬을 활용하여
해당 Level내 필드의 몬스터를 사냥합니다.

보스 스테이지는 다양한 보스의 스킬 패턴을
피하며 클리어 할 수 있습니다.
```


* 캐릭터
```
게임 플레이에 사용되는 캐릭터는
원작 게임의 주인공인 Death(사신) 입니다.

캐릭터는 기본이동 / 대시 / (2단)점프 를
포함하며 공격 스킬로는 
- 기본콤보(4개 state)
- 원거리 공격
- 강한 데미지의 공격
- 범위공격
으로 구성되며, 몬스터와 보스 타격 시
각 스킬의 데미지별 몬스터 / 보스의
HP에 영향을 줍니다.
```

* 스테이지
```
원작 게임을 고증하여 게임 시작 시,
Player의 사무실에서 플레이를 시작합니다.

Level Change 트리거가 있는 문이나,
엘리베이터 등을 이동하면, 이동 애니메이션과
함께 Level이 이동됩니다.

스테이지는 총 3개로 구성되어 있으며,
Office - Monster Field, Boss Stage로
구성됩니다.
```

* 몬스터 및 보스
```
원작 게임과 동일한 느낌을 주기 위하여
필드에서는 총 3종의 Monster를 구현했습니다.

각 몬스터는 플레이어의 영향을 받는
Trace 기능을 추가했으며, 방향 및 거리에 따라
Player를 따라오고, 공격을 합니다.
각 Monster별 Attack Damnage에 따라 타격시
플레이어의 HP UI가 줄어들게 구현했습니다.

보스는 Evil Pumpkin이며, Trace AI 구현,
플레이어의 위치에 따른 방향전환, 
3가지 공격 패턴을 사용합니다.
```



<br>
<h2>프로젝트 핵심 구현</h2>

```
🛠️ ImGui 라이브러리를 사용한 Edit Tool 제작
```
* Sprite Edit Tool
<img width="680" alt="image" src="https://github.com/user-attachments/assets/5c4f94f8-8c11-41f5-bf76-48672e76e5b7">

<br><br>

* Animation Edit Tool
<img width="680" alt="image" src="https://github.com/user-attachments/assets/10116863-4040-46f9-9b19-06ea1b5eb45d">

<br><br>

* 조작 방식
<img width="600" alt="image" src="https://github.com/user-attachments/assets/2b7e6262-514b-4c67-bd4d-d41b6718e701">



