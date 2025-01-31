	org	0x8000

	; ROMヘッダ
	db	#0x41, #0x42, #0x10, #0x80, #0x00, #0x00, #0x00, #0x00
	db	#0x00, #0x00, #0x00, #0x00, #0x00, #0x00, #0x00, #0x00

	; 画面設定
	ld	a, #0x00
	ld	(0xf3ea), a
	ld	(0xf3eb), a
	ld	a, #0x01
	call	0x005f

	; MSX2以降ならパレット設定
	di
	ld	a, (0x002d)
	or	a
	jr	z, skip		; MSXならスキップ
	ld	a, (0x0007)	; 0x98(0x88)
	ld	c, a
	inc	c		; 0x99(0x89)
	ld	a, #0x00
	out	(c), a
	ld	a, #0x80+16	; レジスタ16
	out	(c), a
	inc	c		; 0x9a(0x8a)
	ld	b, #32
	ld	hl, #palette
	otir

skip:
	; 全ページをこのROMに設定
	in	a, (0xa8)
	and	a, #0b00110000
	ld	b, a		; b = a = #0b00110000
	rlca			; a = #0b01100000
	rlca			; a = #0b11000000
	or	a, b		; a = #0b11110000
	ld	b, a		; b = a = #0b11110000
	rrca			; a = #0b01111000
	rrca			; a = #0b00111100
	rrca			; a = #0b00011110
	rrca			; a = #0b00001111
	or	a, b		; a = #0b11111111
	out	(0xa8), a

	; 拡張スロットも設定
	ld	a, (0xffff)
	cpl
	and	a, #0b00110000
	ld	b, a		; b = a = #0b00110000
	rlca			; a = #0b01100000
	rlca			; a = #0b11000000
	or	a, b		; a = #0b11110000
	ld	b, a		; b = a = #0b11110000
	rrca			; a = #0b01111000
	rrca			; a = #0b00111100
	rrca			; a = #0b00011110
	rrca			; a = #0b00001111
	or	a, b		; a = #0b11111111
	ld	(0xffff), a

	; ジョイスティック1選択
	ld	a, #15
	out	(0xa0), a
	in	a, (0xa2)	; Read register 15
	and	#0b10001111
	out	(0xa1), a	; Select Joystick port 1
	ld	a, #14
	out	(0xa0), a	; Set register 14 as accessible

	; ジョイスティック関数を0xf420に配置
	ld	hl, joypad1
	ld	de, #0xf420
	ld	bc, end - joypad1
	ldir

	; ロム起動
	im	0
	ld	sp, #0xfffe
	jp	0

palette:
	db	#0x00, #0x00	; Color 0
	db	#0x00, #0x00	; Color 1
	db	#0x11, #0x05	; Color 2
	db	#0x33, #0x06	; Color 3
	db	#0x26, #0x02	; Color 4
	db	#0x37, #0x03	; Color 5
	db	#0x52, #0x02	; Color 6
	db	#0x27, #0x06	; Color 7
	db	#0x62, #0x02	; Color 8
	db	#0x63, #0x03	; Color 9
	db	#0x52, #0x05	; Color A
	db	#0x63, #0x06	; Color B
	db	#0x11, #0x04	; Color C
	db	#0x55, #0x02	; Color D
	db	#0x55, #0x05	; Color E
	db	#0x77, #0x07	; Color F

joypad1:			; Start at 0F420h
	push	bc
	ld	a, #15
	out	(0xa0), a
	in	a, (0xa2)	; Read register 15
	and	#0b10001111
	out	(0xa1), a	; Select Joystick port 1
	ld	a, #14
	out	(0xa0), a
	in	a, (0xa2)	; Read register 14
	and	#0x3f
	ld	b, a
	ld	a, #15
	out	(0xa0), a
	in	a, (0xa2)	; Read register 15
	or	#0b01000000
	out	(0xa1), a	; Select Joystick port 2
	ld	a, #14
	out	(0xa0), a
	in	a, (0xa2)	; Read register 14
	rra
	rra
	rra
	and	#0xc0
	or	b
	pop	bc
	ret

joypad2:			; Start at 0F44Ch
	in	a, (0xa2)	; Read register 14
	rra
	rra
	or	#0xf0
	ret

end:
	org	0x8200
