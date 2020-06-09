#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	unsigned char b6_b10[6];
	unsigned char b11_b15[6];
	unsigned char b16_b20[6];
	unsigned char b21_b25[6];
} BParsed;

typedef struct {
	unsigned char inst[4];
	unsigned char full_bin[33];
	unsigned char op[7];
	unsigned char fn[7];
	BParsed bp;
} BCode;

typedef struct {
	int num;
	int data;
} Register;

Register reg[32];
Register PC, HI, LO;

typedef struct {
	int i;
	int address;
	BCode bc;
} inst_Mem_4;

typedef struct {
	int i;
	int address;
	int data;
} data_Mem_4;

void initReg(Register* reg, Register* PC, Register* Hi, Register* LO);
void init_instMem(inst_Mem_4* m, int len);
void init_dataMem(data_Mem_4* m, int num);

void shell(char* c);
void readFile(FILE* f, BCode* li);
void dataFetch(FILE* f, data_Mem_4* m);

void setReg(Register* r, int n, int dat);
void inst_config(BCode* list, int len);
void hex2bin(unsigned char h, char* dd, int r);
void parse_inst_bin(BCode* b, int i);

void alprint_master(BCode b, int i);

void alprint_inst_3ar(BCode li, int i, const char* op, BParsed p);
void alprint_inst_3sh(BCode li, int i, const char* op, BParsed p);
void alprint_inst_3sl(BCode li, int i, const char* op, BParsed p);
void alprint_inst_md(BCode li, int i, const char* op, BParsed p);
void alprint_inst_1rs(BCode li, int i, const char* op, BParsed p);
void alprint_inst_mf(BCode li, int i, const char* op, BParsed p);
void alprint_inst_sys(BCode li, int i, const char* op);
void alprint_inst_j(BCode li, int i, const char* op, BParsed p);
void alprint_inst_2off(BCode li, int i, const char* op, BParsed p);
void alprint_inst_imm(BCode li, int i, const char* op, BParsed p);
void alprint_inst_1imm(BCode li, int i, const char* op, BParsed p);
void alprint_inst_1off(BCode li, int i, const char* op, BParsed p);
void alprint_unknown(BCode li, int i);

int run_inst_master(Register* r, Register* pc, inst_Mem_4* m, data_Mem_4* d);

void run_inst_3ar_sltu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_slt(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_nor(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_xor(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_or(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_and(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_sub(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_sub(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_add(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3ar_add(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3sh_srav(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3sh_srlv(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3sh_sllv(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3sl_srl(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3sl_sll(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_3sl_sra(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_imm_addi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_imm_addiu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_imm_slti(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_imm_sltiu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_imm_andi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_imm_ori(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_imm_xori(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_1imm_lui(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);

void run_inst_md_divu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_md_div(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_md_multu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_md_mult(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);

void run_inst_1rs_jalr(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_1rs_mtlo(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_1rs_mthi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_1rs_jr(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);

void run_inst_mfhi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_mflo(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);

int run_inst_sys(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);

void run_inst_j(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_jal(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);

void run_inst_2off_beq(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
void run_inst_2off_bne(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);

int run_inst_1off_lb(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
int run_inst_1off_lh(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
int run_inst_1off_lw(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
int run_inst_1off_lbu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
int run_inst_1off_lhu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
int run_inst_1off_sb(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
int run_inst_1off_sh(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);
int run_inst_1off_sw(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d);


long charbin2long(unsigned char* c);
int charbin2int(unsigned char* c);
char* mygets(char* s);

int main() {
	char command[100];
	char* object;
	int i = 0;
	int list_len = 0;
	int numof_data = 0;

	initReg(reg, &PC, &HI, &LO);
	BCode* inst_list = (BCode*)malloc(sizeof(BCode));

	inst_Mem_4* inst_memory = (inst_Mem_4*)malloc(sizeof(inst_Mem_4) * list_len);
	data_Mem_4* data_memory = (data_Mem_4*)malloc(sizeof(data_Mem_4) * numof_data);

	//BCode inst_list[100000];
	//inst_Mem_4 inst_memory[100000];
	//data_Mem_4 data_memory[100000];

	while (1) {
		shell(command);

		if (strcmp(command, "exit") == 0) {
			free(inst_list);
			free(inst_memory);
			free(data_memory);
			break;
		}

		else if (strlen(command) == 0)
			continue;

		else {
			object = strtok(command, " ");
			if (!strcmp(object, "read")) {
				if (object = strtok(NULL, " ")) {
					list_len = 0;
					i = 0;
					unsigned char buffer[4];
					FILE* len = fopen(object, "rb");
					if (!len)
						continue;
					while (fread(buffer, sizeof(unsigned char), 4, len) != 0)
						list_len++;
					fclose(len);
					inst_list = (BCode*)realloc(inst_list, sizeof(BCode) * list_len);

					FILE* f = fopen(object, "rb");
					readFile(f, inst_list);
					inst_config(inst_list, list_len);

					for (i; i < list_len; i++) {
						parse_inst_bin(inst_list, i);
						alprint_master(inst_list[i], i);
					}

					fclose(f);
					continue;
				}
				else {
					printf("Please choose a file to read...\n");
					continue;
				}
			}
			else if (strcmp(object, "loadinst") == 0) {
				if (object = strtok(NULL, " ")) {
					list_len = 0;
					unsigned char buffer[4];
					FILE* len = fopen(object, "rb");
					if (!len)
						continue;
					while (fread(buffer, sizeof(unsigned char), 4, len) != 0)
						list_len++;
					fclose(len);
					inst_list = (BCode*)realloc(inst_list, sizeof(BCode) * list_len);
					inst_memory = (inst_Mem_4*)realloc(inst_memory, sizeof(inst_Mem_4) * list_len);

					FILE* f = fopen(object, "rb");
					init_instMem(inst_memory, list_len);
					readFile(f, inst_list);
					inst_config(inst_list, list_len);

					for (i = 0; i < list_len; i++) {
						// printf("****%d**** %s %s %s %s %s %s %s\n", i, inst_list[i].op, inst_list[i].bp.b6_b10, inst_list[i].bp.b11_b15, inst_list[i].bp.b16_b20, inst_list[i].bp.b21_b25, inst_list[i].op, inst_list[i].full_bin);
						inst_memory[i].bc.bp = inst_list[i].bp;
					}
					for (i = 0; i < list_len; i++)
						inst_memory[i].bc = inst_list[i];

					fclose(f);
					continue;
				}
				else {
					printf("Please choose a file to read...\n");
					continue;
				}
			}
			else if (strcmp(object, "loaddata") == 0) {
				if (object = strtok(NULL, " ")) {
					numof_data = 0;
					unsigned char buffer[4];
					FILE* len = fopen(object, "rb");
					if (!len)
						continue;
					while (fread(buffer, sizeof(unsigned char), 1, len) != 0)
						numof_data++;
					fclose(len);
					data_memory = (inst_Mem_4*)realloc(data_memory, sizeof(inst_Mem_4) * numof_data);

					FILE* f = fopen(object, "rb");
					init_dataMem(data_memory, numof_data);
					dataFetch(f, data_memory);

					fclose(f);
					continue;
				}
				else {
					printf("Please choose a file to read...\n");
					continue;
				}
			}
			else if (strcmp(object, "run") == 0) {
				object = strtok(NULL, " ");
				int EOI = list_len;
				if (object)
					EOI = atoi(object);
				int state = 0;
				i = 0;
				initReg(reg, &PC, &HI, &LO);

				while (1) {
					state = run_inst_master(reg, &PC, inst_memory, data_memory);
					if (state == -1) {
						printf("unknown instruction\n");
						free(inst_list);
						free(inst_memory);
						free(data_memory);
						break;
					}
					else if (state == -2) {
						printf("Memory address out of range: 0x%08x\n", PC.data);
						free(inst_list);
						free(inst_memory);
						free(data_memory);
						break;
					}
					else if (state == -3) {
						printf("Memory address alignment error: 0x%08x\n", PC.data);
						free(inst_list);
						free(inst_memory);
						free(data_memory);
						break;
					}
					else if (state == -4) {
						printf("EXIT syscall\n");
						free(inst_list);
						free(inst_memory);
						free(data_memory);
						break;
					}
					else if (state == -5) {
						printf("Invalid syscall\n");
						free(inst_list);
						free(inst_memory);
						free(data_memory);
						break;
					}
					else if (PC.data / 4 == EOI+1)
						break;
					i++;
					printf("[PC] %d == executed %d ==\n", PC.data/4, i-1);
				}
				printf("Executed %d instructions\n", i);
			}
			else if (strcmp(object, "registers") == 0) {
				for (i = 0; i < 32; i++)
					printf("$%d: 0x%08x\n", i, reg[i].data);
				printf("HI: 0x%08x\n", HI.data);
				printf("LO: 0x%08x\n", LO.data);
				printf("PC: 0x%08x\n", PC.data);
			}
			else continue;
		}
	}
	return 0;
}

void initReg(Register* reg, Register* PC, Register* HI, Register* LO) {
	int i = 0;
	setReg(PC, -1, 0);
	setReg(HI, 99, 0);
	setReg(LO, 90, 0);

	for (i; i < 32; i++) {
		reg[i].num = i;
		reg[i].data = 0;
	}
}

void init_instMem(inst_Mem_4* m, int len) {
	int i = 0;
	for (i; i < len; i++) {
		strcpy(m[i].bc.full_bin, "11111111111111111111111111111111");
		m[i].i = i;
		m[i].address = m[i].i * 4;
	}
}

void init_dataMem(data_Mem_4* m, int num) {
	int i = 0;
	for (i; i < num; i++) {
		m[i].i = i;
		m[i].address = 0x10000000 + i;
		m[i].data = 0xFF;
	}
}

void shell(char* c) {
	printf("mips-sim> ");
	mygets(c);
	rewind(stdin);
}

void readFile(FILE* f, BCode* li) {
	int l = 0, i;
	unsigned char buffer[4];

	while (fread(buffer, sizeof(unsigned char), 4, f) != 0) {
		for (i = 0; i < 4; i++)
			li[l].inst[i] = buffer[i];
		l++;
	}
}

void dataFetch(FILE* f, data_Mem_4* m) {
	int l = 0;
	unsigned char buffer;
	while (fread(&buffer, sizeof(unsigned char), 1, f) != 0)
		m[l++].data = (int)buffer;
}

void setReg(Register* r, int n, int dat) {
	r->num = n;
	r->data = dat;
}

void inst_config(BCode* li, int len) {
	int i = 0;
	for (i; i < len; i++) {
		int j = 0;
		for (j; j < 33; j++)
			li[i].full_bin[j] = '\0';
		for (j = 0; j < 4; j++)
			hex2bin(li[i].inst[j], li[i].full_bin, 0);
		int k;
		for (k = 0; k < 6; k++) {
			li[i].op[k] = li[i].full_bin[k];
			li[i].fn[k] = li[i].full_bin[k + 26];
		}
		li[i].op[k] = '\0';
		li[i].fn[k] = '\0';
		for (k = 0; k < 5; k++) {
			li[i].bp.b6_b10[k] = li[i].full_bin[k + 6];
			li[i].bp.b11_b15[k] = li[i].full_bin[k + 11];
			li[i].bp.b16_b20[k] = li[i].full_bin[k + 16];
			li[i].bp.b21_b25[k] = li[i].full_bin[k + 21];
		}
		li[i].bp.b6_b10[k] = '\0';
		li[i].bp.b11_b15[k] = '\0';
		li[i].bp.b16_b20[k] = '\0';
		li[i].bp.b21_b25[k] = '\0';
		printf("[%d]===%s %s %s %s %s %s===\n", i, li[i].op, li[i].bp.b6_b10, li[i].bp.b11_b15, li[i].bp.b16_b20, li[i].bp.b21_b25, li[i].fn);
	}
}
void parse_inst_bin(BCode* b, int i) {
	int k = 0;
	for (k; k < 5; k++) {
		b[i].bp.b6_b10[k] = b[i].full_bin[k + 6];
		b[i].bp.b11_b15[k] = b[i].full_bin[k + 11];
		b[i].bp.b16_b20[k] = b[i].full_bin[k + 16];
		b[i].bp.b21_b25[k] = b[i].full_bin[k + 21];
	}
	b[i].bp.b6_b10[5] = '\0';
	b[i].bp.b11_b15[5] = '\0';
	b[i].bp.b16_b20[5] = '\0';
	b[i].bp.b21_b25[5] = '\0';
	b[i].bp.b21_b25[5] = '\0';
}

void hex2bin(unsigned char h, char* dd, int r) {
	if (r == 0) {
		hex2bin(h / 0x10, dd, 1);
		hex2bin(h % 0x10, dd, 1);
	}	
	else if (r == 1) {
		switch (h - 0x00)
		{
		case 0x00:
			strcat(dd, "0000");
			break;
		case 0x01:
			strcat(dd, "0001");
			break;
		case 0x02:
			strcat(dd, "0010");
			break;
		case 0x03:
			strcat(dd, "0011");
			break;
		case 0x04:
			strcat(dd, "0100");
			break;
		case 0x05:
			strcat(dd, "0101");
			break;
		case 0x06:
			strcat(dd, "0110");
			break;
		case 0x07:
			strcat(dd, "0111");
			break;
		case 0x08:
			strcat(dd, "1000");
			break;
		case 0x09:
			strcat(dd, "1001");
			break;
		case 0x0A:
			strcat(dd, "1010");
			break;
		case 0x0B:
			strcat(dd, "1011");
			break;
		case 0x0C:
			strcat(dd, "1100");
			break;
		case 0x0D:
			strcat(dd, "1101");
			break;
		case 0x0E:
			strcat(dd, "1110");
			break;
		case 0x0F:
			strcat(dd, "1111");
			break;
		default:
			break;
		}
	}
}

void alprint_master(BCode b, int i) {
	if (!strcmp(b.op, "000000")) {
		if (!strcmp(b.fn, "101011")) // SLTU
			alprint_inst_3ar(b, i, "sltu", b.bp);
		else if (!strcmp(b.fn, "101010")) // SLT
			alprint_inst_3ar(b, i, "slt", b.bp);
		else if (!strcmp(b.fn, "100111")) // NOR
			alprint_inst_3ar(b, i, "nor", b.bp);
		else if (!strcmp(b.fn, "100110")) // XOR
			alprint_inst_3ar(b, i, "xor", b.bp);
		else if (!strcmp(b.fn, "100101")) // OR
			alprint_inst_3ar(b, i, "or", b.bp);
		else if (!strcmp(b.fn, "100100")) // AND
			alprint_inst_3ar(b, i, "and", b.bp);
		else if (!strcmp(b.fn, "100011")) // SUBU
			alprint_inst_3ar(b, i, "subu", b.bp);
		else if (!strcmp(b.fn, "100010")) // SUB
			alprint_inst_3ar(b, i, "sub", b.bp);
		else if (!strcmp(b.fn, "100001")) // ADDU
			alprint_inst_3ar(b, i, "addu", b.bp);
		else if (!strcmp(b.fn, "100000")) // ADD
			alprint_inst_3ar(b, i, "add", b.bp);
		else if (!strcmp(b.fn, "000111")) // SRAV
			alprint_inst_3sh(b, i, "srav", b.bp);
		else if (!strcmp(b.fn, "000110")) // SRLV
			alprint_inst_3sh(b, i, "srlv", b.bp);
		else if (!strcmp(b.fn, "000100")) // SLLV
			alprint_inst_3sh(b, i, "sllv", b.bp);
		else if (!strcmp(b.fn, "000010")) // SRL
			alprint_inst_3sl(b, i, "srl", b.bp);
		else if (!strcmp(b.fn, "000000")) // SLL
			alprint_inst_3sl(b, i, "sll", b.bp);
		else if (!strcmp(b.fn, "000011")) // SRA
			alprint_inst_3sl(b, i, "sll", b.bp);
		else if (!strcmp(b.fn, "011011")) // DIVU
			alprint_inst_md(b, i, "divu", b.bp);
		else if (!strcmp(b.fn, "011010")) // DIV
			alprint_inst_md(b, i, "div", b.bp);
		else if (!strcmp(b.fn, "011001")) // MULTU
			alprint_inst_md(b, i, "multu", b.bp);
		else if (!strcmp(b.fn, "011000")) // MULT
			alprint_inst_md(b, i, "mult", b.bp);
		else if (!strcmp(b.fn, "001001")) // JALR
			alprint_inst_1rs(b, i, "jalr", b.bp);
		else if (!strcmp(b.fn, "010011")) // MTLO
			alprint_inst_1rs(b, i, "mtlo", b.bp);
		else if (!strcmp(b.fn, "010001")) // MTHI
			alprint_inst_1rs(b, i, "mthi", b.bp);
		else if (!strcmp(b.fn, "001000")) // JR
			alprint_inst_1rs(b, i, "jr", b.bp);
		else if (!strcmp(b.fn, "010010")) // MFLO
			alprint_inst_mf(b, i, "mflo", b.bp);
		else if (!strcmp(b.fn, "010000")) // MFHI
			alprint_inst_mf(b, i, "mfhi", b.bp);
		else if (!strcmp(b.fn, "001100")) // SYSCALL
			alprint_inst_sys(b, i, "syscall");
		else
			alprint_unknown(b, i);
	}
	else if (!strcmp(b.op, "000010")) // J
		alprint_inst_j(b, i, "j", b.bp);
	else if (!strcmp(b.op, "000011")) // JAL
		alprint_inst_j(b, i, "jal", b.bp);
	else if (!strcmp(b.op, "000100")) // BEQ
		alprint_inst_2off(b, i, "beq", b.bp);
	else if (!strcmp(b.op, "000101")) // BNE
		alprint_inst_2off(b, i, "bne", b.bp);
	else if (!strcmp(b.op, "001000")) // ADDI
		alprint_inst_imm(b, i, "addi", b.bp);
	else if (!strcmp(b.op, "001001")) // ADDIU
		alprint_inst_imm(b, i, "addiu", b.bp);
	else if (!strcmp(b.op, "001010")) // SLTI
		alprint_inst_imm(b, i, "slti", b.bp);
	else if (!strcmp(b.op, "001011")) // SLTIU
		alprint_inst_imm(b, i, "sltiu", b.bp);
	else if (!strcmp(b.op, "001100")) // ANDI
		alprint_inst_imm(b, i, "addi", b.bp);
	else if (!strcmp(b.op, "001101")) // ORI
		alprint_inst_imm(b, i, "ori", b.bp);
	else if (!strcmp(b.op, "001110")) // XORI
		alprint_inst_imm(b, i, "xori", b.bp);
	else if (!strcmp(b.op, "001111")) // LUI
		alprint_inst_1imm(b, i, "lui", b.bp);
	else if (!strcmp(b.op, "100000")) // LB
		alprint_inst_1off(b, i, "lb", b.bp);
	else if (!strcmp(b.op, "100001")) // LH
		alprint_inst_1off(b, i, "lh", b.bp);
	else if (!strcmp(b.op, "100011")) // LW
		alprint_inst_1off(b, i, "lw", b.bp);
	else if (!strcmp(b.op, "100100")) // LBU
		alprint_inst_1off(b, i, "lbu", b.bp);
	else if (!strcmp(b.op, "100101")) // LHU
		alprint_inst_1off(b, i, "lhu", b.bp);
	else if (!strcmp(b.op, "101000")) // SB
		alprint_inst_1off(b, i, "sb", b.bp);
	else if (!strcmp(b.op, "101001")) // SH
		alprint_inst_1off(b, i, "sh", b.bp);
	else if (!strcmp(b.op, "101011")) // SW
		alprint_inst_1off(b, i, "sw", b.bp);
	else
		alprint_unknown(b, i);
}

void alprint_inst_3ar(BCode li, int i, const char* op, BParsed p) {
	printf("inst %d: %02x%02x%02x%02x %s $%d, $%d, $%d\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b16_b20), charbin2int(p.b6_b10), charbin2int(p.b11_b15));
}
void alprint_inst_3sh(BCode li, int i, const char* op, BParsed p) {
	printf("inst %d: %02x%02x%02x%02x %s $%d, $%d, $%d\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b16_b20), charbin2int(p.b11_b15), charbin2int(p.b6_b10));
}
void alprint_inst_3sl(BCode li, int i, const char* op, BParsed p) {
	printf("inst %d: %02x%02x%02x%02x %s $%d, $%d, %d\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b16_b20), charbin2int(p.b11_b15), charbin2int(p.b21_b25));
}
void alprint_inst_md(BCode li, int i, const char* op, BParsed p) {
	printf("inst %d: %02x%02x%02x%02x %s $%d, $%d\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b6_b10), charbin2int(p.b11_b15));
}
void alprint_inst_1rs(BCode li, int i, const char* op, BParsed p) {
	printf("inst %d: %02x%02x%02x%02x %s $%d\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b6_b10));
}
void alprint_inst_mf(BCode li, int i, const char* op, BParsed p) {
	printf("inst %d: %02x%02x%02x%02x %s $%d\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b16_b20));
}
void alprint_inst_sys(BCode li, int i, const char* op) {
	printf("inst %d: %02x%02x%02x%02x %s\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op);
}
void alprint_inst_j(BCode li, int i, const char* op, BParsed p) {
	unsigned char targ[27];
	strcpy(targ, p.b6_b10);
	strcat(targ, p.b11_b15);
	strcat(targ, p.b16_b20);
	strcat(targ, p.b21_b25);
	strcat(targ, li.fn);
	printf("inst %d: %02x%02x%02x%02x %s %ld\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op, charbin2long(targ));
}
void alprint_inst_2off(BCode li, int i, const char* op, BParsed p) {
	unsigned char targ[17];
	strcpy(targ, p.b16_b20);
	strcat(targ, p.b21_b25);
	strcat(targ, li.fn);
	printf("inst %d: %02x%02x%02x%02x %s $%d, $%d, %ld\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b6_b10), charbin2int(p.b11_b15), charbin2long(targ));
}
void alprint_inst_imm(BCode li, int i, const char* op, BParsed p) {
	unsigned char targ[17];
	strcpy(targ, p.b16_b20);
	strcat(targ, p.b21_b25);
	strcat(targ, li.fn);
	printf("inst %d: %02x%02x%02x%02x %s $%d, $%d, %ld\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b11_b15), charbin2int(p.b6_b10), charbin2long(targ));
}
void alprint_inst_1imm(BCode li, int i, const char* op, BParsed p) {
	unsigned char targ[17];
	strcpy(targ, p.b16_b20);
	strcat(targ, p.b21_b25);
	strcat(targ, li.fn);
	printf("inst %d: %02x%02x%02x%02x %s $%d, %ld\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b11_b15), charbin2long(targ));
}
void alprint_inst_1off(BCode li, int i, const char* op, BParsed p) {
	unsigned char targ[17];
	strcpy(targ, p.b16_b20);
	strcat(targ, p.b21_b25);
	strcat(targ, li.fn);
	printf("inst %d: %02x%02x%02x%02x %s $%d, %ld($%d)\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3], op,
		charbin2int(p.b11_b15), charbin2long(targ), charbin2int(p.b6_b10));
}
void alprint_unknown(BCode li, int i) {
	printf("inst %d: %02x%02x%02x%02x unknown instruction\n",
		i, li.inst[0], li.inst[1], li.inst[2], li.inst[3]);
}

int run_inst_master(Register* r, Register* pc, inst_Mem_4* m, data_Mem_4* d) {
	int res = 0;
	if (pc->data < 0 || pc->data>0x00010000) {
		res = -2;
		return res;
	}
	int adOffset = pc->data / 4;
	if (!strcmp(m[adOffset].bc.op, "000000")) {
		if (!strcmp(m[adOffset].bc.fn, "101011")) // SLTU
			run_inst_3ar_sltu(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "101010")) // SLT
			run_inst_3ar_slt(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100111")) // NOR
			run_inst_3ar_nor(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100110")) // XOR
			run_inst_3ar_xor(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100101")) // OR
			run_inst_3ar_or(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100100")) // AND
			run_inst_3ar_and(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100011")) // SUBU
			run_inst_3ar_sub(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100010")) // SUB
			run_inst_3ar_sub(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100001")) // ADDU
			run_inst_3ar_add(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "100000")) // ADD
			run_inst_3ar_add(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "000111")) // SRAV
			run_inst_3sh_srav(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "000110")) // SRLV
			run_inst_3sh_srlv(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "000100")) // SLLV
			run_inst_3sh_sllv(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "000010")) // SRL
			run_inst_3sl_srl(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "000000")) { // SLL
			if (!strcmp(m[adOffset].bc.full_bin, "00000000000000000000000000000000")) {
				pc->data += 4;
				return res;
			}
			run_inst_3sl_sll(r, pc, m[adOffset], d);
		}
		else if (!strcmp(m[adOffset].bc.fn, "000011")) // SRA
			run_inst_3sl_sra(r, pc, m[adOffset], d);

		else if (!strcmp(m[adOffset].bc.fn, "011011")) // DIVU
			run_inst_md_divu(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "011010")) // DIV
			run_inst_md_div(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "011001")) // MULTU
			run_inst_md_multu(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "011000")) // MULT
			run_inst_md_mult(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "001001")) // JALR
			run_inst_1rs_jalr(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "010011")) // MTLO
			run_inst_1rs_mtlo(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "010001")) // MTHI
			run_inst_1rs_mthi(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "001000")) // JR
			run_inst_1rs_jr(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "010010")) // MFLO
			run_inst_mflo(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "010000")) // MFHI
			run_inst_mfhi(r, pc, m[adOffset], d);
		else if (!strcmp(m[adOffset].bc.fn, "001100")) // SYSCALL
			res = run_inst_sys(r, pc, m[adOffset], d);
		else {
			res = -1;
			pc->data += 4;
		}
	}
	else if (!strcmp(m[adOffset].bc.op, "000010")) // J
		run_inst_j(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "000011")) // JAL
		run_inst_jal(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "000100")) // BEQ
		run_inst_2off_beq(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "000101")) // BNE
		run_inst_2off_bne(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001000")) // ADDI
		run_inst_imm_addi(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001001")) // ADDIU
		run_inst_imm_addiu(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001010")) // SLTI
		run_inst_imm_slti(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001011")) // SLTIU
		run_inst_imm_sltiu(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001100")) // ANDI
		run_inst_imm_andi(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001101")) // ORI
		run_inst_imm_ori(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001110")) // XORI
		run_inst_imm_xori(r, pc, m[adOffset], d);
	else if (!strcmp(m[adOffset].bc.op, "001111")) // LUI
		run_inst_1imm_lui(r, pc, m[adOffset], d);

	else if (!strcmp(m[adOffset].bc.op, "100000")) { // LB
		res = run_inst_1off_lb(r, pc, m[adOffset], d);
	}
	else if (!strcmp(m[adOffset].bc.op, "100001")) { // LH
		res = run_inst_1off_lh(r, pc, m[adOffset], d);
	}
	else if (!strcmp(m[adOffset].bc.op, "100011")) { // LW
		res = run_inst_1off_lw(r, pc, m[adOffset], d);
	}
	else if (!strcmp(m[adOffset].bc.op, "100100")) { // LBU
		res = run_inst_1off_lbu(r, pc, m[adOffset], d);
	}
	else if (!strcmp(m[adOffset].bc.op, "100101")) { // LHU
		res = run_inst_1off_lhu(r, pc, m[adOffset], d);
	}
	else if (!strcmp(m[adOffset].bc.op, "101000")) { // SB
		res = run_inst_1off_sb(r, pc, m[adOffset], d);
	}
	else if (!strcmp(m[adOffset].bc.op, "101001")) { // SH
		res = run_inst_1off_sh(r, pc, m[adOffset], d);
	}
	else if (!strcmp(m[adOffset].bc.op, "101011")) { // SW
		res = run_inst_1off_sw(r, pc, m[adOffset], d);
	}
	else {
		res = -1;
		pc->data += 4;
	}
	
	return res;
}

void run_inst_3ar_sltu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = (unsigned)(r[charbin2int(m.bc.bp.b6_b10)].data) < (unsigned)(r[charbin2int(m.bc.bp.b11_b15)].data) ? 1 : 0;
	pc->data += 4;
}
void run_inst_3ar_slt(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b6_b10)].data < r[charbin2int(m.bc.bp.b11_b15)].data ? 1 : 0;
	pc->data += 4;
}
void run_inst_3ar_nor(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = ~(r[charbin2int(m.bc.bp.b6_b10)].data | r[charbin2int(m.bc.bp.b11_b15)].data);
	pc->data += 4;
}
void run_inst_3ar_xor(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b6_b10)].data ^ r[charbin2int(m.bc.bp.b11_b15)].data;
	pc->data += 4;
}
void run_inst_3ar_or(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b6_b10)].data | r[charbin2int(m.bc.bp.b11_b15)].data;
	pc->data += 4;
}
void run_inst_3ar_and(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b6_b10)].data & r[charbin2int(m.bc.bp.b11_b15)].data;
	pc->data += 4;
}
void run_inst_3ar_sub(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b6_b10)].data - r[charbin2int(m.bc.bp.b11_b15)].data;
	pc->data += 4;
}
void run_inst_3ar_add(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b6_b10)].data + r[charbin2int(m.bc.bp.b11_b15)].data;
	pc->data += 4;
}
void run_inst_3sh_srav(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b11_b15)].data >> r[charbin2int(m.bc.bp.b6_b10)].data;
	pc->data += 4;
}
void run_inst_3sh_srlv(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = (unsigned int)r[charbin2int(m.bc.bp.b11_b15)].data >> r[charbin2int(m.bc.bp.b6_b10)].data;
	pc->data += 4;
}
void run_inst_3sh_sllv(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = (r[charbin2int(m.bc.bp.b11_b15)].data) << r[charbin2int(m.bc.bp.b6_b10)].data;
	pc->data += 4;
}
void run_inst_3sl_srl(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = (unsigned int)(r[charbin2int(m.bc.bp.b11_b15)].data) >> (unsigned int)(charbin2int(m.bc.bp.b21_b25));
	pc->data += 4;
}
void run_inst_3sl_sll(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = (r[charbin2int(m.bc.bp.b11_b15)].data) << charbin2int(m.bc.bp.b21_b25);
	pc->data += 4;
}
void run_inst_3sl_sra(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = r[charbin2int(m.bc.bp.b11_b15)].data >> charbin2int(m.bc.bp.b21_b25);
	pc->data += 4;
}
void run_inst_imm_addi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	printf("addi\n");
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = r[charbin2int(m.bc.bp.b6_b10)].data + (int)(charbin2long(targ));
	pc->data += 4;
	printf("[[%d]]\n", r[charbin2int(m.bc.bp.b11_b15)].data);
}
void run_inst_imm_addiu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	printf("addiu\n");
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = (unsigned int)r[charbin2int(m.bc.bp.b6_b10)].data + (unsigned int)charbin2long(targ);
	pc->data += 4;
	printf("[[%u]]\n", r[charbin2int(m.bc.bp.b11_b15)].data);
}
void run_inst_imm_slti(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = r[charbin2int(m.bc.bp.b6_b10)].data < (int)(charbin2long(targ)) ? 1 : 0;
	pc->data += 4;
}
void run_inst_imm_sltiu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = (unsigned)r[charbin2int(m.bc.bp.b6_b10)].data < (unsigned int)(int)(charbin2long(targ)) ? 1 : 0;
	pc->data += 4;
}
void run_inst_imm_andi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = r[charbin2int(m.bc.bp.b6_b10)].data & (int)(charbin2long(targ));
	pc->data += 4;
}
void run_inst_imm_ori(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = r[charbin2int(m.bc.bp.b6_b10)].data | (int)(charbin2long(targ));
	pc->data += 4;
}
void run_inst_imm_xori(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = r[charbin2int(m.bc.bp.b6_b10)].data ^ (int)(charbin2long(targ));
	pc->data += 4;
}
void run_inst_1imm_lui(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	r[charbin2int(m.bc.bp.b11_b15)].data = (unsigned int)(int)(charbin2long(targ)) << 16;
	pc->data += 4;
}

void run_inst_md_divu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	HI.data = (unsigned int)(r[charbin2int(m.bc.bp.b6_b10)].data) % (unsigned int)(r[charbin2int(m.bc.bp.b11_b15)].data);
	LO.data = (unsigned int)(r[charbin2int(m.bc.bp.b6_b10)].data) / (unsigned int)(r[charbin2int(m.bc.bp.b11_b15)].data);
	pc->data += 4;
}
void run_inst_md_div(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	HI.data = r[charbin2int(m.bc.bp.b6_b10)].data % r[charbin2int(m.bc.bp.b11_b15)].data;
	LO.data = r[charbin2int(m.bc.bp.b6_b10)].data / r[charbin2int(m.bc.bp.b11_b15)].data;
	pc->data += 4;
}
void run_inst_md_multu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned int A = (unsigned int)(r[charbin2int(m.bc.bp.b6_b10)].data), B = (unsigned int)(r[charbin2int(m.bc.bp.b11_b15)].data);
	HI.data = A * B / (1 << 8);
	LO.data = A * B % (1 << 8);
	pc->data += 4;
}
void run_inst_md_mult(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	HI.data = r[charbin2int(m.bc.bp.b6_b10)].data * r[charbin2int(m.bc.bp.b11_b15)].data / (1 << 8);
	LO.data = r[charbin2int(m.bc.bp.b6_b10)].data * r[charbin2int(m.bc.bp.b11_b15)].data % (1 << 8);
	pc->data += 4;
}

void run_inst_1rs_jalr(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[charbin2int(m.bc.bp.b16_b20)].data = pc->data;
	pc->data = r[charbin2int(m.bc.bp.b6_b10)].data;
	pc->data += 4;
}
void run_inst_1rs_mtlo(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	LO.data = r[charbin2int(m.bc.bp.b6_b10)].data;
	pc->data += 4;
}
void run_inst_1rs_mthi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	HI.data = r[charbin2int(m.bc.bp.b6_b10)].data;
	pc->data += 4;
}
void run_inst_1rs_jr(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	pc->data = r[charbin2int(m.bc.bp.b6_b10)].data;
	pc->data += 4;
}

void run_inst_mfhi(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	printf("mfhi\n");
	r[charbin2int(m.bc.bp.b16_b20)].data = HI.data;
	pc->data += 4;
}
void run_inst_mflo(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	printf("mflo\n");
	r[charbin2int(m.bc.bp.b16_b20)].data = LO.data;
	pc->data += 4;
}

int run_inst_sys(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	int v = reg[2].data;
	int i = 0;
	switch(v) {
		case 1:
			printf("%d", d[reg[4].data].data);
			break;
		case 4:
			i = reg[4].data;
			while (d[i].data) {
				printf("%c", (char)(d[i].data));
			}
			break;
		case 10:
			return -4;
		default:
			return -5;
	}
	pc->data += 4;
}

void run_inst_j(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	pc->data = pc->data / (2 << 6) | ((charbin2int(m.bc.full_bin) % (2 << 6)) << 2);
}
void run_inst_jal(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	r[31].data = pc->data;
	pc->data = pc->data / (2 << 6) | ((charbin2int(m.bc.full_bin) % (2 << 6)) << 2);
}

void run_inst_2off_beq(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	if (r[charbin2int(m.bc.bp.b6_b10)].data == r[charbin2int(m.bc.bp.b11_b15)].data) {
		printf("[][][]%d %d[][][]\n", r[charbin2int(m.bc.bp.b6_b10)].data, r[charbin2int(m.bc.bp.b11_b15)].data);
		unsigned char targ[17];
		strcpy(targ, m.bc.bp.b16_b20);
		strcat(targ, m.bc.bp.b21_b25);
		strcat(targ, m.bc.fn);
		pc->data += (int)charbin2long(targ)*4;
	}
	else
		pc->data += 4;
}
void run_inst_2off_bne(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	if (r[charbin2int(m.bc.bp.b6_b10)].data != r[charbin2int(m.bc.bp.b11_b15)].data) {
		unsigned char targ[17];
		strcpy(targ, m.bc.bp.b16_b20);
		strcat(targ, m.bc.bp.b21_b25);
		strcat(targ, m.bc.fn);
		pc->data += (int)charbin2long(targ)*4;
	}
	else
		pc->data += 4;
}

int run_inst_1off_lb(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else {
		r[charbin2int(m.bc.bp.b11_b15)].data = (char)d[memAdd].data;
		pc->data += 4;
		return 0;
	}
}
int run_inst_1off_lh(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else if (memAdd / 2)
		return -3;
	else {
		r[charbin2int(m.bc.bp.b11_b15)].data = (short)(d[memAdd].data << 2 + d[memAdd + 1].data);
		pc->data += 4;
		return 0;
	}	
}
int run_inst_1off_lw(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else if (memAdd % 4)
		return -3;
	else {
		r[charbin2int(m.bc.bp.b11_b15)].data = ((d[memAdd].data%0x00000010) << 6) + ((d[memAdd + 1].data % 0x00000010) << 4) + ((d[memAdd + 2].data % 0x00000010) << 2) + (d[memAdd + 3].data % 0x00000010);
		pc->data += 4;
		return 0;
	}
}
int run_inst_1off_lbu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else {
		r[charbin2int(m.bc.bp.b11_b15)].data = (unsigned char)d[memAdd].data;
		pc->data += 4;
		return 0;
	}
}
int run_inst_1off_lhu(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else if (memAdd / 2)
		return -3;
	else {
		r[charbin2int(m.bc.bp.b11_b15)].data = (unsigned short)(d[memAdd].data << 2 + d[memAdd + 1].data);
		pc->data += 4;
		return 0;
	}
}
int run_inst_1off_sb(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else {
		d[memAdd].data = (char)r[charbin2int(m.bc.bp.b11_b15)].data;
		pc->data += 4;
		return 0;
	}
}
int run_inst_1off_sh(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else if (memAdd / 2)
		return -3;
	else {
		d[memAdd].data = (char)(r[charbin2int(m.bc.bp.b11_b15)].data / 0x00000100);
		d[memAdd+1].data = (char)(r[charbin2int(m.bc.bp.b11_b15)].data % 0x00000100);
		pc->data += 4;
		return 0;
	}
}
int run_inst_1off_sw(Register* r, Register* pc, inst_Mem_4 m, data_Mem_4* d) {
	unsigned char targ[17];
	strcpy(targ, m.bc.bp.b16_b20);
	strcat(targ, m.bc.bp.b21_b25);
	strcat(targ, m.bc.fn);
	
	int memAdd = charbin2int(targ) + r[charbin2int(m.bc.bp.b6_b10)].data;
	if (memAdd < 0 || memAdd>0x10010000)
		return -2;
	else if (memAdd / 4)
		return -3;
	else {
		d[memAdd].data = (char)(r[charbin2int(m.bc.bp.b11_b15)].data / 0x01000000);
		d[memAdd + 1].data = (char)(r[charbin2int(m.bc.bp.b11_b15)].data / 0x00010000);
		d[memAdd + 2].data = (char)(r[charbin2int(m.bc.bp.b11_b15)].data / 0x00000100);
		d[memAdd + 3].data = (char)(r[charbin2int(m.bc.bp.b11_b15)].data % 0x00000100);
		pc->data += 4;
		return 0;
	}
}


long charbin2long(unsigned char* c) {
	//printf("========%s=======\n", c);
	long s = -1 * (c[0] - '0');
	int i = 0;
	while (c[i + 1] != '\0') {
		if (c[i + 1] == '1')
			c[i] = c[i + 1] + s;
		else
			c[i] = c[i + 1] - s;
		i++;
	}
	c[i] = '\0';
	int d = strlen(c);
	long raw = atol(c);
	long res = 0;

	while (i > 0) {
		if (c[i - 1] == '1')
			res += (long)(pow(2.0, d - i));
		i--;
	}
	if (!s)
		return res;
	else
		return s * (res + 1);
}

int charbin2int(unsigned char* c) {
	int raw = atoi(c);
	int i = 0;
	int d = strlen(c);
	int res = 0;
	int n = 0;

	for (i = 0; i < d; i++) {
		n = pow(10.0, d - i - 1);
		if (raw / n) {
			res += pow(2.0, d - i - 1);
			raw = raw % n;
		}
	}
	return res;
}

char* mygets(char* s) {
	char buffer;
	int i = 0;


	do {
		buffer = (char)getchar();
		if (buffer != '\n') {
			s[i] = buffer;
			i++;
		}
		else {
			s[i] = '\0';
			break;
		}

	} while (1);
	rewind(stdin);
	return s;
}