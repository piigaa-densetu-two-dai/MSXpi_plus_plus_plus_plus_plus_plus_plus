#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "loader.h"
#include "SG1000.DAT.h"

#define VDP0 0x98 /* VDPポート0 */
#define VDP1 0x99 /* VDPポート1 */

typedef struct {
	uint8_t org;
	uint8_t mod;
	uint16_t addr;
} __attribute__((packed)) patch_t;

static uint8_t get_patch(patch_t *patch)
{
	uint8_t cnt, i;
	static const uint8_t *ptr;

	if (!patch) {
		ptr = SG1000_DAT;
		return 0;
	}
	cnt = *ptr++;
	memcpy(patch, ptr, 4 * cnt);
	ptr += (4 * cnt);

	for (i = 0 ; i < cnt ; i++) {
		if ((patch[i].org == 0xbe) && (patch[i].mod == 0x98)) {
			patch[i].mod = VDP0;
		}
		if ((patch[i].org == 0xbf) && (patch[i].mod == 0x99)) {
			patch[i].mod = VDP1;
		}
		if ((patch[i].org == 0x98) && (patch[i].mod == 0xbe)) {
			patch[i].org = VDP0;
		}
		if ((patch[i].org == 0x99) && (patch[i].mod == 0xbf)) {
			patch[i].org = VDP1;
		}
	}

	return cnt;
}

static void patch_vdp(uint8_t *rom, uint32_t size)
{
	uint32_t i;

	/* ロレッタの肖像対策 */
	if (size > (1024 * 64)) {
		size = (1024 * 64);
	}

	/* mingwにはmemmem()が無い模様 */
	for (i = 0 ; i < (size - 1) ; i++) {
		if ((rom[i] == 0xdb) && (rom[i + 1] == 0xbe)) { /* IN 0xbe */
			rom[i + 1] = VDP0;
		}
		if ((rom[i] == 0xd3) && (rom[i + 1] == 0xbe)) { /* OUT 0xbe */
			rom[i + 1] = VDP0;
		}
		if ((rom[i] == 0xdb) && (rom[i + 1] == 0xbf)) { /* IN 0xbf */
			rom[i + 1] = VDP1;
		}
		if ((rom[i] == 0xd3) && (rom[i + 1] == 0xbf)) { /* OUT 0xbf */
			rom[i + 1] = VDP1;
		}
	}
}

static int conv(const char *src, const char *dst)
{
	uint8_t rom[1024 * 128];
	struct stat st;
	FILE *fp;
	uint8_t cnt;
	uint32_t i;
	patch_t patch[256];

	memset(rom, 0x00, sizeof(rom));

	if (stat(src, &st)) {
		perror(src);
		return 1;
	}
	if (st.st_size > sizeof(rom)) {
		fprintf(stderr, "%s: サイズオーバーですぞ\n", src);
		return 1;
	}
	if (!(fp = fopen(src, "rb"))) {
		perror(src);
		return 1;
	}
	if (fread(rom, 1, st.st_size, fp) != st.st_size) {
		return 1;
	}
	fclose(fp);

	/* VDPパッチ */
	patch_vdp(rom, st.st_size);

	get_patch(NULL);
	while ((cnt = get_patch(patch))) {
		for (i = 0 ; i < cnt ; i++) { /* パッチが適合するかを確認 */
			if (rom[patch[i].addr - 0x1000] != patch[i].org) {
				break;
			}
		}
		if (i != cnt) { /* 適合しない */
			continue;
		}
		/* 個別パッチ */
		for (i = 0 ; i < cnt ; i++) {
			rom[patch[i].addr - 0x1000] = patch[i].mod;
		}
		break;
	}
	if (cnt == 0) {
		fprintf(stderr, "%s: 対応パッチがありません。。。\n", src);
		return 1;
	}

	if (!(fp = fopen(dst, "wb"))) {
		perror(dst);
		return 1;
	}
	for (i = sizeof(rom) - 1 ; i >= st.st_size ; i--) { /* SpaceSlalom対策 */
		if (rom[i]) {
			st.st_size = i + 1;
			break;
		}
	}
	if (fwrite(rom, 1, st.st_size, fp) != st.st_size) {
		perror(dst);
		return 1;
	}
	if (fwrite(loader_rom, 1, sizeof(loader_rom), fp) != sizeof(loader_rom)) {
		perror(dst);
		return 1;
	}
	fclose(fp);

	fprintf(stderr, "%s: 変換完了\n", src);

	return 0;
}

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *ent;
	struct stat st;
	char name[1024];
	char *ptr;


	if ((argc != 2) && (argc != 3)) {
		fprintf(stderr, "～ ピーガー伝説のSG1000【ロムの嵐エディション】～\n");
		fprintf(stderr, "使い方\n");
		fprintf(stderr, "	%s <SGファイル> <SGAファイル>\n", argv[0]);
		fprintf(stderr, "	%s <ディレクトリ>\n", argv[0]);
		return 1;
	}

	if (argc == 3) {
		return conv(argv[1], argv[2]);
	}

	if (chdir(argv[1])) {
		perror(argv[1]);
		return 1;
	}
	if (!(dir = opendir("."))) {
		perror(argv[1]);
		return 1;
	}
	while ((ent = readdir(dir))) {
		if (stat(ent->d_name, &st)) {
			continue;
		}
		if (!S_ISREG(st.st_mode)) {
			continue;
		}
		strcpy(name, ent->d_name);
		if (!(ptr = strrchr(name, '.'))) {
			continue;
		}
		if (!strcasecmp(ptr, ".bin") || !strcasecmp(ptr, ".sg") || !strcasecmp(ptr, ".sms")) {
			strcpy(ptr, ".sga");
			conv(ent->d_name, name);
		}
	}
	closedir(dir);

	return 0;
}
