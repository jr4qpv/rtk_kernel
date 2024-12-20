rtk_kernel
===========
TRON Forum T-Kernel for Raspberry Pi and Renesas RZ/T1

概要
----
Tronフォーラム（<http://www.tron.org/ja/>）で下記公開のオープンソース T-Kernel2.0 & Extensyon(T2EX)からポーティングしたリアルタイムＯＳ。

1. [T-Kernel 2.02.00 Software Package](http://www.tron.org/download/index.php?route=product/product&product_id=133)
    - `2015/06/08  18:35  396,299 tkernel_source.tar.gz`
2. [T-Kernel 2.0 Extension（T2EX 2.01.00）](http://www.tron.org/download/index.php?route=product/product&product_id=134)
    - `2015/06/09  13:16  419,593 t2ex_source.tar.gz`
    - `2015/03/25  17:12  1,219,629 bsd_source.tar.gz`

以前、[Raspberry Pi](https://ja.wikipedia.org/wiki/Raspberry_Pi)用にテスト作成した構成を見直し、RTOS(T-Kernel)部分のみを分離し独立させ保守性を向上。更に、ルネサスの[RZ/T1](https://www.renesas.com/jp/ja/products/microcontrollers-microprocessors/rz/rzt/rzt1.html)マイコン用のコードも同梱。

本プロジェクトを直接修正して利用する事もできるが、アプリプロジェクト内にGitサブモジュール機能でサブディレクトリとして登録して使う事を想定。

T-Kernelに一緒にリンクして動かすサンプルアプリは同梱して動くようにしてある（T2EXの簡易シェル）。

### T2EXについて
[T-Kernel 2.0 Extension (T2EX)](https://www.tron.org/ja/tron-project/what-is-t-kernel/t2ex/) は、T-Kernel にネットワーク機能などを追加する拡張モジュール。

本プロジェクトには、参考にT2EXのコードも同梱しているが、現状ではT2EXの機能は殆ど利用してない。（簡易シェルのコードはサンプルとして利用）

* t2ex用のビルドフォルダも残っているが現状メンテナンスしていない。（今後、ネットワークドライバ等が必要になった時には使うかも？）

Gitリポジトリ
---------------
GitHubの下記URL。

<https://github.com/jr4qpv/rtk_kernel.git>


サポートサイト
----------------
下記URLで、ビルド手順や実行方法などの技術情報を逐次提供しているので、詳細はそちらをご覧ください。

<https://www.yokoweb.net/dokuwiki/develop/rtk_kernel/start>

### 関連記事

* [【T-Kernel】Raspberry Pi と Renesas RZ/T1 用の T-Kernel「rtk_kernel」をGitHubに公開](https://www.yokoweb.net/2019/09/29/raspberrypi-rzt1-rtk_kernel-github/)

対応機種
----------

### １）Raspberry Pi 対応機種
`TYPE_RPI`は、コンパイル時にRasperry Piの機種を区別しているmake変数。

|モデル        | TYPE_RPI |備考                    |
|:-------------|:--------:|:-----------------------|
|Pi Zero       | 1        |                        |
|Pi 1 Model B+ | 1        |動作未確認              |
|Pi 2 Model B  | 2        |シングルコア動作        |
|Pi 3 Model B  | 3        |32bit,シングルコア動作  |

### ２）Renesas RZ/T1 対応機種
`TYPE_RZT`は、コンパイル時にRZ/T1の機種を区別しているmake変数。

|モデル                               | TYPE_RZT |備考                    |
|:------------------------------------|:--------:|:-----------------------|
|Renesas Starter Kit+ for RZ/T1       | 0        |                        |
| ---                                 | 1        |予約                    |

* 「Renesas Starter Kit+ for RZ/T1」は下記URL参照  
<https://www.renesas.com/jp/ja/products/software-tools/boards-and-kits/starter-kits/renesas-starter-kitplus-for-rz-t1.html>


プロジェクトのファイル＆フォルダ説明
--------------------------

| フォルダ名                | 説明                       | 備考            |
|:-------------------------|:--------------------------|:---------------|
| `README.md`              | 説明ファイル                | Markdownで記述   |
| `TEF000-218-150401.pdf`  | ライセンス規約              | T-License2.1    |
| `rtk_kernel_distmark.png` | T-Kernelディストリビューションucode  |          |
| `tkernel_source/`        | T-Kenelソース本体フォルダ    | ポーティングしたもの  |
| `doc/`                   | 関連ドキュメントフォルダ      |               |
| `_misc/`                 | その他                     |               |
| `.cproject`              | e2 Studio用               | RZ/T1         |
| `.project`               | e2 Studio用               | RZ/T1         |
| `.setting/`              | e2 Studio用               | RZ/T1         |
| `*.launch`               | e2 Studioデバック用        | RZ/T1          |
| `*.jlink`                | e2 Studio J-Linkデバック用  | RZ/T1         |

ビルド環境
----------
作者が確認した環境。GCCのバージョンは多少異なっても大丈夫と思う。コンパイル環境のインストール手順などは「[サポートサイト](https://www.yokoweb.net/dokuwiki/develop/rtk_kernel/start)」を参照。

#### 【Windows】
* Windows10 Pro x64 ver1903
* [msys2](https://msys2.github.io/)
* [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)  6 2017-q2-update

#### 【macOS】
* macOS v10.15 Catalina
* [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)  8-2018-q4-major

#### 【Linux】
* [Ubuntu 18.04 LTS Server](https://www.ubuntulinux.jp/home)
* [gcc-arm-none-eabi package in Ubuntu](https://launchpad.net/ubuntu/+source/gcc-arm-none-eabi)  6.3.1 20170620

### コンパイルに必要な環境変数
コンパイル実行するには、下記環境変数が設定されている事が必要。

|環境変数  |説明                     |例            |
|:--------|:-----------------------|:-------------|
|BD       |T-Kernelソースのベースパス |`/C/work/rtk_kernel/tkernel_source`  |
|GNU_BD   |ARMコンパイラのベースパス   |`/C/Program Files (x86)/GNU Tools ARM Embedded/6 2017-q2-update` |

仕様書
------
T-Kernel関連の仕様書は[Tronフォーラム](http://www.tron.org/ja/)を参照。

1. [T-Kernel 2.0 仕様書](http://www.tron.org/ja/wp-content/themes/dp-magjam/pdf/specifications/TEF020-S001-02.01.00_ja.pdf)
2. [T-Kenrel 2.0 Extension 仕様書 (T2EX)](http://www.tron.org/ja/wp-content/themes/dp-magjam/pdf/specifications/ja/TEF020-S009-02.00.00_ja.pdf)
3. [T-Monitor仕様書](http://www.tron.org/ja/wp-content/themes/dp-magjam/pdf/specifications/ja/TEF020-S002-01.00.01_ja.pdf)

ライセンス
----------
T-License2.1に従う。同梱ファイル `TEF000-218-150401.pdf` を参照。

ディストリビューションucode
---------------------------
T-Kernel再配布規約に従い、本ソフトウェアのディストリビューション番号は「`00070059`」。同梱ファイル `rtk_kernel_distmark.png` を参照。

免責
----
本プログラムの使用にあたっては、使用者自身の責任で行ってください。作者は何の保証もしないし、本プログラムを利用した上で生じたいかなる障害や損害についても、作者は責任を負いません。

作者関連サイト
---------------

* [GitHub (jr4qpv)](https://github.com/jr4qpv/)
* [新石器Wiki](https://www.yokoweb.net/dokuwiki/)
* [The modern stone age.](https://www.yokoweb.net/)

来歴
----
* 2019/09/28 r0.60公開
* 2020/01/07 プロジェクト名を「yt-kernel」から「rtk_kernel」に変更
