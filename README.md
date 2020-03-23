# CartPole-for-CPP

これはOpenAI Gymの['CartPole-v0'](https://github.com/openai/gym/wiki/CartPole-v0)をC/C++とgnuplotで書き直したものです．PythonではなくC/C++で機械学習のテストがしたいという方向けに開発しました．パスの設定などは一切必要なく，cartpole_cpp.hppをインクルードするだけで実行できるため，linuxなどに詳しくない方でもすぐに使えます．

## OpenAI GymのCartPoleとは
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
 
 環境はUbuntu　18.04ですが，linuxであればなんでも動くと思います．
 
```bash
sudo apt install g++
sudo apt install gnuplot
sudo apt install vlc
git clone https://github.com/H1dek1/CartPole-for-CPP.git
```

 CartPole-for-CPPにはライブラリの他に使い方の例としてサンプルプログラムが含まれています．サンプルプログラムを実行するには以下を実行します．
 
```bash
cd cartpole_cpp
./sample.sh
vlc result.mp4
```
これで動画が再生されればインストール完了です．
 
# Usage
このプログラムはcartpole_cpp.hppをインクルードするだけで利用できます．

```bash
#include "cartpole_cpp.hpp"
```

以下のコマンドで環境のインスタンスを作成し，環境を初期化します．

```bash
CartPole env;
std::vector<double> observation = env.reset();
```
cartの位置と速度，poleの角度と角速度は本家と同じく-0.05~+0.05の範囲の中で乱数によって初期化されます．reset()関数は返り値としてcartの位置，cartの速度，poleの位置，poleの速度を，double型の配列（要素数4）で返します．

|Num|observation|Min|Max|
|:---|:---|:---|:---|
|0|Cart Position|-2.4|2.4|
|1|Cart Velocity|-inf|inf|
|2|Pole Angle|-41.8 degree|41.8 degree|
|3|Pole Angular Velocity|-inf|inf|

(引用：[CartPole-v0](https://github.com/openai/gym/wiki/CartPole-v0))

step関数は環境を1ステップ進める関数です．第一引数のflagはbool値で，falseにすると，外力を受けなくなります．第二引数のactionは本家と同じく，

```bash
std::tie(observation, reward, done) = env.step(flag, action);
```

第一引数のflagはbool型で，falseにすると，外力を受けなくなります．第二引数のactionは本家と同じく，次のように設定しています．

|Num|Action|
|:---|:---|
|0|Push cart to the left|
|1|Push cart to the right|

(引用：[CartPole-v0](https://github.com/openai/gym/wiki/CartPole-v0))

返り値についても基本的には本家を踏襲しています．返り値はdouble型配列observationとdouble型変数reward，bool型変数doneです．rewardは報酬で，cartの位置とpoleの角度が上の表の範囲にあるときには1を，範囲外にあるときは0を返します．doneは初期状態でfalseに設定され，cartの位置かpoleの角度が範囲外に出たとき，またはステップ数が200を超えるとtrueを返します．

```bash
env.render(filename);
```
render()関数はそのステップのときの環境を外部ファイルに記録する関数です．動画にしたい試行では，毎ステップこの関数を実行することでlogファイルを作成し，動画にすることができます．引数のfilenameは出力するlogファイルを指定します．プログラムを実行するディレクトリからの相対パスをstring型で渡してください．

# Environment

本プログラムの環境は次のようなものです．
![cartpole](https://user-images.githubusercontent.com/56115620/77053217-5918b080-6a11-11ea-846a-49924e6765c8.png)

## Motion Equation & Algorithm

プログラムのアルゴリズムの元になる系のラグランジュの運動方程式を示します．cartの位置は<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\left(&space;X,&space;0&space;\right&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;\left(&space;X,&space;0&space;\right&space;)" title="\left( X, 0 \right )" /></a>，poleの重心位置は<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\left(&space;X&plus;lsin\theta,&space;lcos\theta&space;\right&space;)" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\left(&space;X&plus;lsin\theta,&space;lcos\theta&space;\right&space;)" title="\left( X+lsin\theta, lcos\theta \right )" /></a>であるから，ラグランジアンは，

<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;L=K-U=\frac{M}{2}{\dot{X}}^2&plus;\frac{m}{2}\left(\dot{x}^2&plus;\dot{y}^2&space;\right&space;)-mglcos\theta" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;L=K-U=\frac{M}{2}{\dot{X}}^2&plus;\frac{m}{2}\left(\dot{x}^2&plus;\dot{y}^2&space;\right&space;)-mglcos\theta" title="L=K-U=\frac{M}{2}{\dot{X}}^2+\frac{m}{2}\left(\dot{x}^2+\dot{y}^2 \right )-mglcos\theta" /></a>

これより<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;X" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;X" title="X" /></a>に関する運動方程式は，

<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{X}}&space;\right)-\frac{\partial&space;L}{\partial&space;X}=F\Leftrightarrow&space;\ddot{X}=\frac{F}{m&plus;M}-\frac{ml}{m&plus;M}\left(&space;\ddot{\theta}cos\theta-\dot{\theta}^2sin\theta&space;\right&space;)" target="_blank"><img src="https://latex.codecogs.com/png.latex?\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{X}}&space;\right)-\frac{\partial&space;L}{\partial&space;X}=F\Leftrightarrow&space;\ddot{X}=\frac{F}{m&plus;M}-\frac{ml}{m&plus;M}\left(&space;\ddot{\theta}cos\theta-\dot{\theta}^2sin\theta&space;\right&space;)" title="\frac{d}{dt}\left( \frac{\partial L}{\partial \dot{X}} \right)-\frac{\partial L}{\partial X}=F\Leftrightarrow \ddot{X}=\frac{F}{m+M}-\frac{ml}{m+M}\left( \ddot{\theta}cos\theta-\dot{\theta}^2sin\theta \right )" /></a>

<a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;\theta" target="_blank"><img src="https://latex.codecogs.com/png.latex?\inline&space;\theta" title="\theta" /></a>に関する運動方程式は，

<a href="https://www.codecogs.com/eqnedit.php?latex=\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{\theta}}&space;\right)-\frac{\partial&space;L}{\partial&space;\theta}=0\Leftrightarrow&space;\ddot{\theta}=\frac{g}{l}sin\theta-\frac{\ddot{X}}{l}cos\theta" target="_blank"><img src="https://latex.codecogs.com/png.latex?\frac{d}{dt}\left(&space;\frac{\partial&space;L}{\partial&space;\dot{\theta}}&space;\right)-\frac{\partial&space;L}{\partial&space;\theta}=0\Leftrightarrow&space;\ddot{\theta}=\frac{g}{l}sin\theta-\frac{\ddot{X}}{l}cos\theta" title="\frac{d}{dt}\left( \frac{\partial L}{\partial \dot{\theta}} \right)-\frac{\partial L}{\partial \theta}=0\Leftrightarrow \ddot{\theta}=\frac{g}{l}sin\theta-\frac{\ddot{X}}{l}cos\theta" /></a>

これらより，

<a href="https://www.codecogs.com/eqnedit.php?latex=\ddot{X}=\frac{F-mgsin\theta&space;cos\theta&space;&plus;&space;ml\dot{\theta}^2&space;sin\theta}{msin^2\theta&plus;M}" target="_blank"><img src="https://latex.codecogs.com/png.latex?\ddot{X}=\frac{F-mgsin\theta&space;cos\theta&space;&plus;&space;ml\dot{\theta}^2&space;sin\theta}{msin^2\theta&plus;M}" title="\ddot{X}=\frac{F-mgsin\theta cos\theta + ml\dot{\theta}^2 sin\theta}{msin^2\theta+M}" /></a>

本プログラムでは以上の式から入力を外力<a href="https://www.codecogs.com/eqnedit.php?latex=F" target="_blank"><img src="https://latex.codecogs.com/png.latex?F" title="F" /></a>として，cartの位置，poleの角度を更新している．
 
# Note
 
# Author

* H1dek1
 
# License

* H1dek1
