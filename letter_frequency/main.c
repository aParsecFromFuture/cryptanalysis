#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	FILE *inp,*out,*freq;
	int i,max_freq = 0,max_freq_index = 0,order = 0,table_size = 0,text_size = 0;
	int text_freq_table[26] = {0},is_used[26] = {0};
	char *text,lang_freq_table[26],ch;
	if(argc != 4){
		fprintf(stderr,"Usage : ./main <input-file> <output-file> <frequency-file>\n");
		exit(1);
	}

	inp = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	freq = fopen(argv[3],"r");

	if(!inp || !out || !freq){
		perror("fopen");
		exit(1);
	}

	ch = fgetc(freq);
	while(ch != EOF){
		if(ch == '\n'){
			table_size++;
		}
		ch = fgetc(freq);
	}
	fseek(freq,0,SEEK_SET);

	for(i = 0;i < table_size;i++){
		fscanf(freq,"%c\n",&lang_freq_table[i]);
	}
	for(i = table_size;i < 26;i++){
		lang_freq_table[i] = lang_freq_table[table_size - 1];
	}
	fclose(freq);

	fseek(inp,0,SEEK_END);
	text_size = ftell(inp);
	fseek(inp,0,SEEK_SET);

	text = malloc(sizeof(char) * text_size);

	for(i = 0;i < text_size;i++){
		ch = fgetc(inp);
		if('a' <= ch && ch <= 'z'){
			text_freq_table[ch - 'a']++;
		}else if('A' <= ch && ch <= 'Z'){
			text_freq_table[ch - 'A']++;
		}
		text[i] = ch;
	}

	for(order = 0;order < 26;order++){
		max_freq = -1;
		for(i = 0;i < 26;i++){
			if(!is_used[i] && max_freq < text_freq_table[i]){
				max_freq = text_freq_table[i];
				max_freq_index = i;
			}
		}
		text_freq_table[max_freq_index] = order;
		is_used[max_freq_index] = 1;
	}

	for(i = 0;i < text_size;i++){
		ch = text[i];
		if('a' <= ch && ch <= 'z'){
			ch = lang_freq_table[text_freq_table[ch - 'a']];
		}else if('A' <= ch && ch <= 'Z'){
			ch = lang_freq_table[text_freq_table[ch - 'A']] - 32;
		}
		fputc(ch,out);
	}
	
	fclose(inp);
	fclose(out);
}
