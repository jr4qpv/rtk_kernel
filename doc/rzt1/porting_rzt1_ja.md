T-Kernel for RZ/T1 移植メモ
==============================
本ファイルは、Markdown記法で書いています。

概要
----
Tronフォーラム（<http://www.tron.org/ja/>）で公開のオープンソース T-Kernel2.0 & Extensyon(T2EX)から、ルネサス[RZ/T1](https://www.renesas.com/ja-jp/products/microcontrollers-microprocessors/rz/rzt/rzt1.html) にポーティングしたリアルタイムＯＳ。

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
GitHubの下記URL。

<https://github.com/jr4qpv/yt-kernel.git>

サポートサイト
----------------
「yt-kernel for Raspberry Pi」については、下記URLのサポートサイトで、ビルド手順や実行方法などの技術情報を逐次提供しているので、詳細はそちらをご覧ください。

<https://www.yokoweb.net/dokuwiki/develop/yt-kernel/ytkernel-rzt1/start>

### 関連記事

* [【T-Kernel】Raspberry Pi と Renesas RZ/T1 用の T-Kernel「yt-kernel」をGitHubに公開](https://www.yokoweb.net/2019/09/29/raspberrypi-rzt1-ytkernel-github/)

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
