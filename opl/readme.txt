ヤマハOPL2音源のファームウェアです。
VGMPlay(https://www.grauw.nl/projects/vgmplay-msx/)でOPLサウンドが再生出来ます。
また、OPL音源機能のみが機能するMSX-AUDIOとしても動作するようです。

音声データの生成にemu8950(great!)を使用しています。
https://github.com/digital-sound-antiques/emu8950

御注意①
MSXπ✨✨✨✨✨✨✨に配線を追加する必要があります。mod.jpgの通りに配線して下さい。
配線を行なわないと割り込み信号を使用したプログラムが正常動作しません。
VGMPlayはこれに該当しますがvgmplay-1.4_disable_opl_timer以下にあるパッチ版のvgmplay.comは配線を行わなくても動作します。

御注意➋
データバスがきちんとプルアップされていないMSX機種の場合、起動時にハングする、call audioで異常動作する等の
不具合が発生する場合があります。そのような機種で使用する場合はopl.binの代わりにopl_alt.binを使用して下さい。
opl_alt.binはターボRに対応しません。ターボRでは使用しないで下さい。

使用法

1. opl.binファイルの後ろにMSX-AUDIOのROMファイルを連結します。

ROMファイルはhttps://frs.badcoffee.info/tools.htmlの
MSX-Audio BIOS v1.3bに含まれるmsxaudio13.OPL3_mono.romを使用します。

unixのcatコマンドを使用する例
$ cat opl.bin msxaudio13.OPL3_mono.rom > firmware.bin

windowsのcopyコマンドを使用する例
>copy /b opl.bin + msxaudio13.OPL3_mono.rom firmware.bin

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

IOポート仕様

0xc0 (read) ステータス読み込み
0xc0 (write) アドレス書込み
0xc1 (write) データ書き込み

opl_alt.binの場合は上記に加え
0xe4-0xe7 (read) 0xffを返す(プルアップされたデータバスの再現)
