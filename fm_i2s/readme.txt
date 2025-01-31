FM音源(MSX-MUSIC/FMPAC)のファームウェアです。
I2S出力版なので別途、PCM5102等のI2S対応DACモジュールが必用です。
使用するROMファイルによりMSX-MUSIC又はFMPACとして機能します。
但しFMPACのPAC機能(SRAMバックアップ機能)は機能しません

音声データの生成にemu2413(great!)を使用しています。
https://github.com/digital-sound-antiques/emu2413

結線方法

MSXπ側	DACモジュール側
VCC	VIN
GND	GND
IO32	LRCK
IO34	DIN
IO33	BCK
IO35	SCK(不必要な配線なので繋がなくても構いません)

音声フォーマットは16ビット、ステレオ2CH、サンプルレート49716Hzです。

使用法

1. fm_i2s.binファイルの後ろにMSX-MUSIC(MSX2PMUS.rom)又はFMPAC(FMPAC.rom)のROMファイルを連結します。

unixのcatコマンドを使用する例
$ cat fm_i2s.bin MSX2PMUS.rom > firmware.bin

windowsのcopyコマンドを使用する例
>copy /b fm_i2s.bin + MSX2PMUS.rom firmware.bin

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
