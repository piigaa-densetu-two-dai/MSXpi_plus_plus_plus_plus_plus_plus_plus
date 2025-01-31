SCC音源+FM音源(MSX-MUSICC)のファームウェアです。
同一スロットにFMBIOSとSCCレジスターを配置しました。
スロット拡張は行なっていないので拡張スロットでも使用出来ます。

音声データの生成にemu2413(great!)を使用しています。
https://github.com/digital-sound-antiques/emu2413

使用法

1. sccfm.binファイルの後ろにMSX-MUSIC(MSX2PMUS.rom)のROMファイルを連結します。

unixのcatコマンドを使用する例
$ cat sccfm.bin MSX2PMUS.rom > firmware.bin

windowsのcopyコマンドを使用する例
>copy /b sccfm.bin + MSX2PMUS.rom firmware.bin

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

5. 書込みが終わったらPCから外します。
