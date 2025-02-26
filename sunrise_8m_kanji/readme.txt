Nextor対応！Sunrise IDE + 8192kメモリーマッパー + 漢字ロム・漢字ドライバーエミュレーターです。

USBメモリをSunrise IDEのマスター側に接続されたハードディスクとして使用する事ができます。
漢字ロム・漢字ドライバー機能も含まれているので漢字ロム・漢字ドライバーの無い環境でも日本語表示が可能です。

ご注意
ターボRモード非対応です。
内部的にスロットを拡張するので拡張スロットでは動作しません。基本スロットに挿してご使用ください。
8192kメモリーマッパーは4096k x2のメモリーマッパーとして動作します。

使用法

1. SunriseIDE用のNextorカーネルをダウンロードします。

Nextorのgithubから以下のファイルをダウンロードして下さい。

https://github.com/Konamiman/Nextor/releases/download/v2.1.2/Nextor-2.1.2.SunriseIDE.MasterOnly.ROM
又は
https://github.com/Konamiman/Nextor/releases/download/v2.1.2/Nextor-2.1.2.SunriseIDE.ROM

(下のファイルを使用すると起動が僅かに遅くなります)

2. sunrise_8m_kanji.binファイルの後ろに1でダウンロードしたNextorカーネル(128k)と漢字ベーシック(漢字ドライバー)ROM(32k)と漢字ROM(256k)を連結します。

unixのcatコマンドを使用する例
$ cat sunrise_8m_kanji.bin Nextor-2.1.2.SunriseIDE.MasterOnly.ROM kanjibasic.rom kanjifont.rom > firmware.bin

windowsのcopyコマンドを使用する例
>copy /b sunrise_8m_kanji.bin + Nextor-2.1.2.SunriseIDE.MasterOnly.ROM + kanjibasic.rom + kanjifont.rom firmware.bin

※
kanjibasic.rom: 漢字ベーシックROM(32k)
kanjifont.rom: 漢字ROM(256k)

3. uf2conv.exeを用いて2で作成したfirmware.binをuf2ファイルに変換します。

例: windowsコマンドプロンプト上で
uf2conv.exe firmware.bin firmware.uf2

uf2conv.exeはhttps://github.com/piigaa-densetu-two-dai/MSXpi_plus_plus_plus_plus_plus_plus_plusにあります。

4. MSXに刺さっていない状態のMSXπ✨✨✨✨✨✨✨をブートモードでPCに接続します。

MSXπ✨✨✨✨✨✨✨のBOOTSELボタンを押しながらPCとUSB接続して下さい。
接続が成功するとドライブが認識されます。

5. MSXπ✨✨✨✨✨✨✨に3で作成したfirmware.uf2ファイルを書き込みします。

4で認識されたドライブにfirmware.uf2をドラッグアンドドロップ(コピー)します。
コピーが完了するとドライブが見えなくなります。

6. 書込みが終わったらPCから外して完了

7. MSXπ✨✨✨✨✨✨✨にUSBメモリを取り付けて完了

Nextorのセットアップ方法についてはこちらを参考にして下さい。
https://github.com/Konamiman/Nextor/releases/tag/v2.1.2
https://github.com/Konamiman/Nextor/blob/v2.1/docs/Nextor%202.1%20Getting%20Started%20Guide.md

注意
USBメモリ以外のUSB装置を接続しないでください。
USB装置のホットスワップに対応していません。
