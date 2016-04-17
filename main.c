#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int main(int argc, char **argv){
  if(argc<2){
    perror("File name not specified");
    return (-1);
  }

  setlocale(LC_ALL, "");

  const char *tmp_str=".tmp";
  const ssize_t tmp_str_len=strlen(tmp_str);
  const size_t str_len=80;
  wchar_t *str=malloc(sizeof(wchar_t)*str_len);
    
  FILE *fp;
  FILE *fph;
  char *line=NULL;
  size_t len=0;
  ssize_t read;
  int i;
  char *tmp_file_name;
  size_t tmp_file_name_len;

  size_t mbslen;
  wchar_t *wcs;
  size_t j;
  size_t k;
  size_t l;
  for (i = 1; i < argc; i++) {

    fp=fopen(argv[i], "r");
    if(fp==NULL){
      fprintf(stderr, "Can't open file: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }    

    tmp_file_name_len=strlen(argv[i]) + tmp_str_len;
    tmp_file_name=malloc(sizeof(char) * tmp_file_name_len);
    if (tmp_file_name == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

    strcpy(tmp_file_name, argv[i]);
    strcat(tmp_file_name, tmp_str);
    
    fph=fopen(tmp_file_name, "w+");
    if(fp==NULL){
      fprintf(stderr, "Can't open/create file: %s\n", tmp_file_name);
      exit(EXIT_FAILURE);
    }


    
    read=getline(&line,&len,fp);
    while(read!=-1){

      mbslen=read;
      if(mbslen>str_len){
	mbslen = mbstowcs(NULL, line, 0);
	if (mbslen == (size_t) -1) {
	  perror("mbstowcs");
	  exit(EXIT_FAILURE);
	}
      }
      if(mbslen > str_len){
	wcs=calloc(mbslen, sizeof(wchar_t));
	if (wcs == NULL) {
	  perror("calloc");
	  exit(EXIT_FAILURE);
	}
	if (mbstowcs(wcs, line, mbslen) == (size_t) -1) {
	  perror("mbstowcs");
	  exit(EXIT_FAILURE);
	}

	for (j=0; j<mbslen-1; j+=str_len) {
	  k=mbslen-1-j;
	    wcsncpy(str, wcs+j,str_len); 
	  if (k>str_len) {
	    for (l=str_len-1; l>0; l--) {
	      if(str[l]==' '){
		str[l]='\0';
		j-=str_len-l-1;
		break;
	      }
  
	    }

	  }
	    fprintf(fph,"%ls\n",str);
	}


      }
      else{
	  fprintf(fph,"%s",line);
      }
	   
      read=getline(&line,&len,fp);
    }
    fclose(fp);
    fclose(fph);
    free(tmp_file_name);
  }
  //if (line) {
  //free(line);
  //}
  //free(str);
  printf("\n");
  exit(EXIT_SUCCESS);
}
