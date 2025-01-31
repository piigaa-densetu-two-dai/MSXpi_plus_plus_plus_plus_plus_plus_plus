PSG音源(内蔵音源)+PPI音源(内蔵1bit音源)+FM音源(MSX-MUSICC)+SCC音源のファームウェアです。
同一スロットにFMBIOSとSCCレジスターを配置しました。
スロット拡張は行なっていないので拡張スロットでも使用出来ます。

S/PDIF出力版なので別途、S/PDIF送信用コネクターが必用です。
例: https://akizukidenshi.com/catalog/g/g109596/

音声データの生成にemu2149/emu2413(great!)を使用しています。
https://github.com/digital-sound-antiques/emu2149
https://github.com/digital-sound-antiques/emu2413

結線方法

MSXπ側  S/PDIF送信用コネクター側
VCC     VCC
GND     GND
IO32    信号入力

音声フォーマットは16ビット、ステレオ2CH(左:PSG+PPI+SCC 右:FM)、サンプルレート44100Hzです。
※起動時・リセット時にFUNCTIONボタンが押されていた場合はモノラル音声(全ての音源が混合された音が左右から出力される)となります。

使用法

1. psg_ppi_fm_scc_spdif.binファイルの後ろにMSX-MUSIC(MSX2PMUS.rom)のROMファイルを連結します。

unixのcatコマンドを使用する例
$ cat psg_ppi_fm_scc_spdif.bin MSX2PMUS.rom > firmware.bin

windowsのcopyコマンドを使用する例
>copy /b psg_ppi_fm_scc_spdif.bin + MSX2PMUS.rom firmware.bin

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
