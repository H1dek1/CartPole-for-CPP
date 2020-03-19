# CartPole-for-CPP

これはOpenAI Gymの['CartPole-v0'](https://github.com/openai/gym/wiki/CartPole-v0)をC/C++とgnuplotで書き直したものです．PythonではなくC/C++で機械学習のテストがしたいという方向けに開発しました．パスの設定などは一切必要なく，cartpole_cpp.hppをインクルードするだけで実行できるため，linuxなどに詳しくない方でもすぐに使えます．

## OpenAI GymのCarPoleとは
[OpenAI Gym](https://github.com/openai/gym)とは人工知能を研究する非営利企業[OpenAI](https://openai.com/)が提供する強化学習のシミュレーション用プラットフォームです．その中でCartPoleは台車の上に載った棒をどれだけ長い時間立てていられるかというシミュレーションです．ユーザーは各タイムステップで，台車を左に押すか右の押すかのどちらかの行動をとり，棒が倒れないように台車を動かします．


# DEMO

Q学習で強化学習した例

![learned](https://user-images.githubusercontent.com/56115620/76943403-a1b56880-6942-11ea-90d1-4135a84e7d9a.gif)


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

# Environment

本プログラムの環境は次のようなものです．
![cartpole](https://user-images.githubusercontent.com/56115620/77053217-5918b080-6a11-11ea-846a-49924e6765c8.png)

## Motion Equation

プログラムのアルゴリズムの元になる系のラグランジュの運動方程式を示します．cartの位置は<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\left(&space;X,&space;0&space;\right&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\left(&space;X,&space;0&space;\right&space;)" title="\left( X, 0 \right )" /></a>，poleの重心位置は<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\left(&space;X&plus;lsin\theta,&space;lcos\theta&space;\right&space;)" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\left(&space;X&plus;lsin\theta,&space;lcos\theta&space;\right&space;)" title="\left( X+lsin\theta, lcos\theta \right )" /></a>であるから，ラグランジアンは，

<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;L=K-U=\frac{M}{2}{\dot{X}}^2&plus;\frac{m}{2}\left(\dot{x}^2&plus;\dot{y}^2&space;\right&space;)-mglcos\theta" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;L=K-U=\frac{M}{2}{\dot{X}}^2&plus;\frac{m}{2}\left(\dot{x}^2&plus;\dot{y}^2&space;\right&space;)-mglcos\theta" title="L=K-U=\frac{M}{2}{\dot{X}}^2+\frac{m}{2}\left(\dot{x}^2+\dot{y}^2 \right )-mglcos\theta" /></a>

これより<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;X" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;X" title="X" /></a>に関する運動方程式は，

<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{x}}&space;\right)-\frac{\partial&space;L}{\partial&space;x}=F" target="_blank"><img src="https://latex.codecogs.com/png.latex?\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{x}}&space;\right)-\frac{\partial&space;L}{\partial&space;x}=F" title="\frac{d}{dt}\left( \frac{\partial L}{\partial \dot{x}} \right)-\frac{\partial L}{\partial x}=F" /></a>

<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\theta" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\theta" title="\theta" /></a>に関する運動方程式は，

<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{\theta}}&space;\right)-\frac{\partial&space;L}{\partial&space;\theta}=F\Leftrightarrow&space;\ddot{\theta}=\frac{g}{l}sin\theta-\frac{\ddot{X}}{l}cos\theta" target="_blank"><img src="https://latex.codecogs.com/png.latex?\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{\theta}}&space;\right)-\frac{\partial&space;L}{\partial&space;\theta}=F\Leftrightarrow&space;\ddot{\theta}=\frac{g}{l}sin\theta-\frac{\ddot{X}}{l}cos\theta" title="\frac{d}{dt}\left( \frac{\partial L}{\partial \dot{\theta}} \right)-\frac{\partial L}{\partial \theta}=F\Leftrightarrow \ddot{\theta}=\frac{g}{l}sin\theta-\frac{\ddot{X}}{l}cos\theta" /></a>


 
# Note
 
注意点
 
# Author

* H1dek1
 
# License

ライセンス
