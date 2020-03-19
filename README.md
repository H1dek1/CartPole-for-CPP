# CartPole-for-CPP

これはOpenAI Gymの['CartPole-v0'](https://github.com/openai/gym/wiki/CartPole-v0)をC/C++とgnuplotで書き直したものです．PythonではなくC/C++で機械学習のテストがしたいという方向けに開発しました．

## OpenAI GymのCarPoleとは
[OpenAI Gym](https://github.com/openai/gym)とは人工知能を研究する非営利企業[OpenAI](https://openai.com/)が提供する強化学習のシミュレーション用プラットフォームです．


# DEMO

Q学習で強化学習した例

![learned](https://user-images.githubusercontent.com/56115620/76943403-a1b56880-6942-11ea-90d1-4135a84e7d9a.gif)

# Environment

本プログラムの環境は次のようなものです．
![cartpole](https://user-images.githubusercontent.com/56115620/77049920-451e8000-6a0c-11ea-8106-803f517d0716.png)

## Motion Equation

プログラムのアルゴリズムの元になる系の運動方程式を示します．cartの位置は，poleの重心位置は

環境は本家と同じです．
運動方程式など

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
## Cloning 

CartPole-for-CPPをクローンする方法

```bash
git clone https://github.com/H1dek1/CartPole-for-CPP.git
```

## Details

プログラムの詳細
 
## Run Sample Program

CartPole-for-CPPにはライブラリの他に使い方の例としてサンプルプログラムが含まれています．サンプルプログラムを実行するには以下を実行します．
 
```bash
cd cartpole_cpp
./sample.sh
vlc result.mp4
```
 
# Note
 
注意点
 
# Author

* H1dek1
 
# License

ライセンス
