# CartPole-for-CPP

これはOpenAI Gymの['CartPole-v0'](https://github.com/openai/gym/wiki/CartPole-v0)をC/C++とGnuplotで書き直したものです．PythonではなくC/C++で機械学習のテストがしたいという方向けに開発しました．

## OpenAI GymのCarPoleとは
[OpenAI Gym](https://github.com/openai/gym)とは人工知能を研究する非営利企業[OpenAI](https://openai.com/)が提供する強化学習のシミュレーション用プラットフォームです．


# DEMO

Q学習で強化学習した例

![learned](https://user-images.githubusercontent.com/56115620/76943403-a1b56880-6942-11ea-90d1-4135a84e7d9a.gif)

# Environment
環境は本家と同じです．
## Algorithm

## Simulation Setting
状態変数の有効範囲は本家の値をそのまま引用し，次のように設定しています．
|Variable|Min|Max|
|:---|:---|:---|
|Cart Position|-2.4|2.4|
|Cart Velocity|-inf|inf|
|Pole Angle|-41.8^\circ|41.8^\circ|

### observation variable


# Requirement
 
* C++17
* g++ 7.5.0
* gnuplot 5.2 patchlevel 2
* vlc
 
# Installation
 
```bash
sudo apt install gnuplot
```
 
# Usage
 
インストールからサンプルプログラム実行まで
 
```bash
git clone https://github.com/H1dek1/CartPole-for-CPP.git
cd cartpole_cpp
./sample.sh
vlc result.mp4
```

# Sample Program

```bash
#include "cartpole.hpp"
```

```bash
Cartpole env;
```
 
# Note
 
注意点
 
# Author

* H1dek1
 
# License

ライセンス
