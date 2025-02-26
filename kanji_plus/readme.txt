MSXView漢字ROM、松下12px第一水準漢字ROMファームウェアです。
MSXView漢字ROMはMGSEL等で使用可能です。松下12px第一水準漢字ROMはcall kanji1/kanji3で使用されます。
スロット拡張は行なっていないので拡張スロットでも使用出来ます。

以下の機種の松下12px第一水準漢字ROMで動作を確認しました。
National FS-4600F
Panasonic FS-A1FM

使用法

1. kanji_plus.binファイルの後ろにMSXView漢字ROM(192k)と松下12px漢字ROM(128k)を連結します。

unixのcatコマンドを使用する例
$ cat kanji_plus.bin msxview.rom kanjifont12.rom > firmware.bin

windowsのcopyコマンドを使用する例
>copy /b kanji_plus.bin + msxview.rom + kanjifont12.rom firmware.bin

※
msxview.rom: MSXView漢字ROM(192k)
kanjifont12.rom: 松下12px漢字ROM(128k) FS-4600F, FS-A1FMで使用されているもの

2. uf2conv.exeを用いて1で作成したfirmware.binをuf2ファイルに変換します。

例: windowsコマンドプロンプト上で
uf2conv.exe firmware.bin firmware.uf2

uf2conv.exeはhttps://github.com/piigaa-densetu-two-dai/MSXpi_plus_plus_plus_plus_plus_plus_plusにあります。

3. MSXに刺さっていない状態のMSXπ✨✨✨✨✨✨✨をブートモードでPCに接続します。

MSXπ✨✨✨✨✨✨✨のBOOTSELボタンを押しながらPCとUSB接続して下さい。
接続が成功するとドライブが認識されます。

4. MSXπ✨✨✨✨✨✨✨に2で作成したfirmware.uf2ファイルを書き込みします。

3で認識されたドライブにfirmware.uf2をドラッグアンドドロップ(コピー)します。
コピーが完了するとドライブが見えなくなります。

5. 書込みが終わったらPCから外して完了
