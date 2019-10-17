T-Kernel for RZ/T1 移植メモ
==============================
本ファイルは、Markdown記法で書いています。

概要
----
Tronフォーラム（<http://www.tron.org/ja/>）で下記公開のオープンソース T-Kernel2.0 & Extensyon(T2EX)から、ルネサス[RZ/T1](https://www.renesas.com/ja-jp/products/microcontrollers-microprocessors/rz/rzt/rzt1.html) にポーティングしたリアルタイムＯＳ。

1. [T-Kernel 2.02.00 Software Package](http://www.tron.org/download/index.php?route=product/product&product_id=133)
    - `2015/06/08  18:35  396,299 tkernel_source.tar.gz`
2. [T-Kernel 2.0 Extension（T2EX 2.01.00）](http://www.tron.org/download/index.php?route=product/product&product_id=134)
    - `2015/06/09  13:16  419,593 t2ex_source.tar.gz`
    - `2015/03/25  17:12  1,219,629 bsd_source.tar.gz`

### 【対応機種】
TYPE_RZTは、コンパイル時にRZ/T1の機種を区別しているmake変数。

|機種                           |TYPE_RZT|備考                    |
|:------------------------------|:------:|:-----------------------|
|Renesas Starter Kit+ for RZ/T1 | 0      |                        |
| ------                        | 1      | 予約                   |

* 「Renesas Starter Kit+ for RZ/T1」は下記URL参照  
<https://www.renesas.com/jp/ja/products/software-tools/boards-and-kits/starter-kits/renesas-starter-kitplus-for-rz-t1.html>


Gitリポジトリ
---------------
<https://github.com/jr4qpv/yt-kernel.git>


サポートサイト
----------------
下記URLで、ビルド手順や実行方法などの技術情報を逐次提供しているので、詳細はそちらをご覧ください。

<https://www.yokoweb.net/dokuwiki/develop/yt-kernel/start>


ビルド環境
-----------
動作確認した環境。GCCのバージョンは多少異なっても大丈夫と思う。インストール手順は参考リンク[1.][2.][3.]を参照。

#### 【Windows】
* Windows10 Pro x64 ver1903
* [msys2](https://msys2.github.io/)
* [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)  6 2017-q2-update

#### 【Mac】
* macOS v10.15 Catalina
* [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)  7-2017-q4-major

#### 【Linux】
* [Ubuntu 18.04 LTS Server](https://www.ubuntulinux.jp/home)
* [gcc-arm-none-eabi package in Ubuntu](https://launchpad.net/ubuntu/+source/gcc-arm-none-eabi)  6.3.1 20170620


コンパイル手順
--------------
以下、Windowsのmsys2環境での例に説明する。MacやLinuxでも同様なのでそれぞれの環境に読み換えてください。T-Monitor,config,T-Kernel３つのファイルを作成する。

コンパイル実行するには、下記環境変数が設定されている事が必要。

|環境変数 |説明                       |備考          |
|:--------|:--------------------------|:-------------|
|BD       |T-Kernelソースのベースパス |              |
|GNU_BD   |ARMコンパイラのベースパス  |              |

#### 環境変数の設定
`$HOME/.bashrc`に下記設定を追記しておくと便利。本プログラムは `C:¥work¥` にgitで取得したものとする。

```
export BD=/C/work/yt-kernel/tkernel_source
export GNU_BD='/C/Program Files (x86)/GNU Tools ARM Embedded/6 2017-q2-update'
```

#### ■T-Monitorのコンパイル
下記フォルダにて `make` を実行する事でコンパイルする。

|ビルドフォルダ                            |備考        |
|:-----------------------------------------|:-----------|
|$BD/monitor/tmmain/build/app_rzt1         |            |
|$BD/monitor/tmmain/build/app_rzt1.ram     |RAM起動     |

* `.debug`ついたフォルダでコンパイルするとデバック情報を付加する
* `make clean`で生成されたファイルを削除

生成されるT-Monitorオブジェクトファイル

|ファイル名    |説明                       |備考          |
|:-------------|:--------------------------|:-------------|
|tmonitor      |elfファイル                |              |
|tmonitor.mot  |Sフォーマットファイル      |              |

#### ■config情報のコンパイル
下記フォルダにて `make` を実行する事でconfigファイルを作成する。

|ビルドフォルダ                            |備考       |
|:-----------------------------------------|:----------|
|$BD/config/build/app_rzt1                 |           |

* `make clean`で生成されたファイルを削除

生成されるconfigオブジェクトファイル

|ファイル名      |説明                       |備考          |
|:---------------|:--------------------------|:-------------|
|rominfo-rom     |elfファイル                |              |
|rominfo-rom.bin |バイナリファイル           |←これを利用  |
|rominfo-rom.mot |Sフォーマットファイル      |              |

#### ■T-Kernelのコンパイル
下記フォルダにて `make` を実行する事でコンパイルする。

|ビルドフォルダ                            |機種                |備考     |
|:-----------------------------------------|:-------------------|:--------|
|$BD/kernel/sysmain/build/app_rzt          |RSK評価基板         |         |

* `.debug`ついたフォルダでコンパイルするとデバック情報を付加する
* `make clean`で生成されたファイルを削除

生成されるT-Kernelオブジェクトファイル

|ファイル名       |説明                       |備考          |
|:----------------|:--------------------------|:-------------|
|kernel-rom.rom   |elfファイル                |              |
|kernel-rom.bin   |バイナリファイル           |←これを利用  |
|kernel-rom.mot   |Sフォーマットファイル      |              |

#### コンパイルの実行例
```
$ cd $BD/monitor/tmmain/build/app_rzt1
$ make
$ cd $BD/config/build/app_rzt1
$ make
$ $BD/kernel/sysmain/build/app_rzt1
$ make
```

シリアルコンソール
------------------
ルネサス評価基板のJ8コネクタでUSB接続する。

※基板内部の通信仕様は下記(SCIFA#2)

ボーレート :115200、データ長 :8bit、パリティー :なし、ストップビット :1、フロー制御 :なし

T-Kernelの起動
--------------
作成した下記ファイルを、シリアルフラッシュメモリに書き込み電源リセット。

1. `tmonitor.bin`
2. `rominfo-rom.bin`
3. `kernel-rom.bin`

起動メッセージが下記のように表示されたら、無事T-Kernelが起動。この例では、アプリの実行コードが認識できないので、サンプルアプリ(簡易シェル)の入力待ちとなっている。

```
T-Kernel Version 2.02.00 for RZ/T1 r0.60 [Thu Oct 10 16:35:44     2019]

ConsoleIO - OK
userinit(0x30080000) code not found.
usermain start.
T2EX >>
```

メモリマップ
-------------
実装仕様書`doc/T-Kernel2.0/doc/impl-tef_em1d.txt`からの差分

(1)物理メモリマップ

```
|addr       | 説明                       |容量  |
|:----------|:---------------------------|:----:|
|0000 0000h |ATCM                        |512KB |
|0008 0000h |予約領域                    |      |
|0080 0000h |BTCM                        |32KB  |
|0080 8000h |予約領域                    |      |
|0400 0000h |Instruction RAM             |512KB |
|0408 0000h |予約領域                    |      |
|1000 0000h |SPIシリアルフラッシュ       |8MB   |
|1080 0000h |予約領域                    |      |
|2000 0000h |Data RAM                    |512KB |
|2008 0000h |予約領域                    |      |
|2200 0000h |Data RAM ミラー             |512KB |
|2208 0000h |予約領域                    |      |
|2400 0000h |Instruction RAM ミラー      |512KB |
|2408 0000h |予約領域                    |      |
|3000 0000h |SPIシリアルフラッシュ ミラー|8MB   |
|3080 0000h |予約領域                    |      |
|4800 0000h |CS2 SDRAM ミラー            |8MB   |
|4880 0000h |予約領域                    |      |
|6800 0000h |CS2 SDRAM                   |8MB   |
|6880 0000h |予約領域                    |      |
|A000 0000h |周辺IOレジスタ              |1MB   |
|A010 0000h |予約領域                    |      |

```

例外ベクターテーブル
--------------------

【工事中】


```
2.4 例外ベクターテーブル
                                               ベクター番号
         0x00000000 +-----------------------+
                    |デフォルトハンドラ     |       0
                    |未定義命令             |       1
                    |プリフェッチアボート   |       2
                    |データアボート         |       3
         0x00000010 +-----------------------+
                    |スーパーバイザ SVC 4   |       4
                    |コール          :      |       |
                    |               SVC 28  |       28
         0x00000074 +-----------------------+
                    |デバッグアボート   命令|       29
                    |                 データ|       30
         0x0000007c +-----------------------+
                    |高速割込       FIQ     |       31
         0x00000080 +-----------------------+
                    |割込           IRQ 0   |       32
                    |                :      |       |
                    |               IRQ 95  |       127
         0x00004200 +-----------------------+
                    |予備           IRQ 96  |       128
                    |                :      |       |
                    |               IRQ  127|       255
         0x00004400 +-----------------------+

    ・デフォルトハンドラは、ハンドラが登録されていない例外・割込が発生した場
      合に呼び出されるハンドラ。NULL を未登録とする。
    ・ベクター番号は、tk_def_int() の割込定義番号(dintno)として使用する。
    ・ベクター番号は、SVC 命令の番号(イミディエート値)として使用する。
    ・IRQ 0〜95 は、割込コントローラ(INT)の INT 0〜95 に対応する
```

シリアルポート割り当て
----------------------
T-Kernel/T-Monitorではシリアルポートは、SCIFA#2を利用

タイマー
--------
システムタイマーとしてCMT#0を使用。割り込み周期はconfigで変更できるが、デフォルトでは1msecに設定。

LED割り当て
-----------
T-MonitorのcpuLED()関数で、LED操作ができる。LED表示の為に下記のGIIOポートを割り当てている。

【工事中】

ユーザアプリケーション
----------------------
T-Kernelが起動すると、opt_main()タスクが起動され（`tkernel_source/kernel/sysmain/src/opt_main.c`）、rominfoに記述したアプリ開始番地から起動を試みる。ヘッダ情報が不正の場合は、T-Monitorに戻る。

又、Kernelとリンクしたアプリの場合は、opt_main()からユーザ定義のアプリケーションプログラムを記述していく。

仕様書
------
T-Kernel関連の仕様書は[Tronフォーラム](http://www.tron.org/ja/)を参照ください。

1. [T-Kernel 2.0 仕様書](http://www.tron.org/ja/wp-content/themes/dp-magjam/pdf/specifications/TEF020-S001-02.01.00_ja.pdf)
2. [T-Kenrel 2.0 Extension 仕様書 (T2EX)](http://www.tron.org/ja/wp-content/themes/dp-magjam/pdf/specifications/ja/TEF020-S009-02.00.00_ja.pdf)
3. [T-Monitor仕様書](http://www.tron.org/ja/wp-content/themes/dp-magjam/pdf/specifications/ja/TEF020-S002-01.00.01_ja.pdf)

ライセンス
----------
T-License2.1に従う。添付ドキュメント`TEF000-218-150401.pdf`を参照ください。

ディストリビューションucode
---------------------------
T-Kernel再配布規約に従い、本ソフトウェアのディストリビューション番号は「`00070059`」。同梱ファイル `yt-kernel_distmark.png` を参照。

免責
----
本プログラムの使用にあたっては、使用者自身の責任で行ってください。作者は何の保証もしないし、本プログラムを利用した上で生じたいかなる障害や損害についても、作者は責任を負いません。

参考リンク
---------
1. [【msys2】ARMのコンパイル環境を構築する](https://www.yokoweb.net/2016/08/31/msys2-arm-gcc/)
2. [【macOS】ARMのコンパイル環境を構築する](https://www.yokoweb.net/2018/05/16/macos-gcc-arm-brew-install/)
3. [【Ubuntu 18.04 LTS Server】ARMのコンパイル環境を構築する](https://www.yokoweb.net/2018/05/16/ubuntu-18_04-gcc-arm-install/)

作者関連サイト
-------------
* [GitHub (jr4qpv)](https://github.com/jr4qpv/)
* [新石器Wiki](https://www.yokoweb.net/dokuwiki/)
* [The modern stone age.](https://www.yokoweb.net/)

来歴
----
* 2019/09/28 r0.60公開
