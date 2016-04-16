#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
  if(argc<2){
    fprintf(stderr, "File name not specified");
    return (-1);
  }

  const char *tmp_str=".tmp";
  const ssize_t tmp_str_len=strlen(tmp_str);
  const size_t str_len=79;
    
  FILE *fp;
  FILE *fph;
  char *line=NULL;
  size_t len=0;
  ssize_t read;
  int i;
  char *tmp_file_name;
  size_t tmp_file_name_len;

  size_t j;
  size_t line_len;
  for (i = 1; i < argc; i++) {

    fp=fopen(argv[i], "r");
    if(fp==NULL){
      fprintf(stderr, "Can't open file: %s\n", argv[i]);
      return (-1);
    }    

    tmp_file_name_len=strlen(argv[i]) + tmp_str_len;
    tmp_file_name=malloc(sizeof(char) * tmp_file_name_len);
    strcpy(tmp_file_name, argv[i]);
    strcat(tmp_file_name, tmp_str);
    
    fph=fopen(tmp_file_name, "w+");
    if(fp==NULL){
      fprintf(stderr, "Can't open/create file: %s\n", tmp_file_name);
      return (-1);
    }
    fflush(fph);
    while((read=getline(&line,&len,fp))!=-1){
      line_len=strlen(line);
      for (j=0;j<line_len; j+=str_len) {
	fwrite(line+j,str_len,sizeof(char),fph);
	fwrite("\n",1,sizeof(char),fph);
      }
    }
    fclose(fp);
    fclose(fph);
    free(tmp_file_name);
  }
  //if (line) {
  //free(line);
  //}
  printf("\n");
  return (1);
}
