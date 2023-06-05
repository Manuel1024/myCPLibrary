# myCPLibrary
競技プログラミングで使用するライブラリたち

* 使い方はソースコード内のコメントに書いてあります
* 実装は AtCoder Library や蟻本などを参考にしています

## 実装済みのライブラリ

### 数学
* Combination.cpp: 二項係数 `nCr` を特定の素数で割った余りを計算する

### データ構造
* FenwickTree.cpp: Fenwick Tree
    * 数列の区間和計算，1点更新がそれぞれ `O(log N)` で行える
* SegTree.cpp: Segment Tree
    * 数列の区間に対する演算（min, max, 足し算，他），1点更新がそれぞれ `O(log N)` で行える
* LazySegTree.cpp: 遅延評価付き Segment Tree
    * 数列の区間に対する演算（min, max, 足し算，他），区間に対する更新がそれぞれ `O(log N)` で行える

### グラフ
* MaxFlow.cpp: 最大流問題を解く アルゴリズムは Dinic法
* SCC.cpp: 有向グラフを強連結成分分解する

### 文字列
* RollingHash_32bit.cpp: Rolling Hash を扱う構造体
    * 文字列Sの l文字目からr文字目までのhashを 前計算`O(|S|)`, ハッシュ取得 `O(1)` で計算できる
    * hashの計算で 32bit整数に収まる素数2つを使用
* RollingHash_64bit.cpp: Rolling Hash を扱う構造体
    * 基本的には RollingHash_32bit.cpp と同様
    * hashの計算で 64bit整数に収まる素数1つを使用
* Z_Algorithm.cpp: Z Algorithm