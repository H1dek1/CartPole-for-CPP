# CartPole-for-CPP

これはOpenAI Gymの'CartPole-v0'をC/C++とGnuplotで書き直したものです．PythonではなくC/C++で機械学習のテストがしたいという方向けに開発しました．

# DEMO

Q学習で強化学習した例

![learned](https://user-images.githubusercontent.com/56115620/76943403-a1b56880-6942-11ea-90d1-4135a84e7d9a.gif)
 
# Features

<a href="https://www.codecogs.com/eqnedit.php?latex=e^{i\pi}=-1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?e^{i\pi}=-1" title="e^{i\pi}=-1" /></a>
 
# Requirement
 
* C++17
* g++ 7.5.0
* gnuplot 5.2 patchlevel 2
 
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
