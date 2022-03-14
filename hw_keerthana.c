#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include"argv_cmd.h"
typedef int Myfunptr(const char *, char *, int);
static Myfunptr myfunptr;
int sub_dir(char *SUB_PATH);
int type_of_file(char *in_path,char *,int);  /* function for type of file */
int file_size(char * path,int);
int file_type(char *name,int type,int size);
 char *SUB;
 char E_P[500000]={0};
int main(int argc,char *argv[])
{
	char *PATH = NULL;
	int iRet   = 0;
#if 0
	if(argc > 1) /* PATH Specified by the user */
	{
		PATH = argv[1];
	}
	else  /* current working directory*/
	{
		system("pwd");
		PATH = "./";
	}
#endif
	main_args(argc,argv);

	if(AA.E == 1)
	{
		  strcat(E_P,AA.Ecmd) ;
		  strcat(E_P,"*") ;
#if 0
		char *pp= AA.Ecmd;
		char *p;
		int i;
		 p = strtok(pp,"  *\n");
		 for(i=0;p !=NULL;i++)
		 {
		  strcat(E_P,p) ;
		  strcat(E_P,"*") ;
		  p = strtok(NULL," ");
		 }
#endif
		printf("%s\n",E_P);	 
	}
	//iRet = PParent_Dir(PATH); /*list of current directory */
	iRet = sub_dir(AA.path); /*list of current directory */

	//printf("%s\n",E_P);	
	if(AA.E == 1)
	{
		pid_t AA_PID;
		AA_PID = fork();
			if(AA_PID >0)
			{
				wait(NULL);
			}
			else
			{ 
				char *AA[1000]={0};
				char *pp= E_P;
				char *p;
				unsigned int i;
				p = strtok(pp," *\n");
				for(i=0;p !=NULL;i++)
				{
					AA[i]= p;
					p = strtok(NULL," *\n");

				}
				//for(i=0;AA[i] !=NULL;i++)
				//	printf("%s \n",AA[i]);
				execvp(AA[0],AA);
			}
	}

	

	return 0;
}
#if 0
int PParent_Dir(char *PATH) /* list the path specified by the user */
{
	DIR *PDir=NULL;
	struct dirent *PDir_list=NULL;
	PDir = opendir(PATH);

	if(PDir == NULL)
	{ printf("Error: In Directory opening\n");
		return -1;
	}
	//struct dirent {
	//*	ino_t          d_ino;       /* Inode number */
	//	off_t          d_off;       /* Not an offset; see below */
	//	unsigned short d_reclen;    /* Length of this record */
	//	unsigned char  d_type;      /* Type of file; not supported
	//				       by all filesystem types */
	//	char           d_name[256]; /* Null-terminated filename */
	//	};
	while(PDir_list = readdir(PDir))
	{	
		if((strcmp(PDir_list->d_name,".") != 0) && (strcmp(PDir_list->d_name,"..")  !=0))
		{
			//	printf("FILE :%s\n",dir_list->d_name);
			type_of_file(PATH,PDir_list->d_name ,PDir_list->d_type,PDir_list->d_reclen); /* find out the Type of file */
		}
	}
	closedir(PDir);





	return 0;
}
#endif
int sub_dir(char *SUB_PATH) /* this function for find out the sub directory this function working recursively*/
{
	DIR *SUB_Dir=NULL;
	struct dirent *SUB_Dir_list=NULL;
	SUB_Dir = opendir(SUB_PATH);
	SUB  = SUB_PATH;
	if(SUB_Dir == NULL)
	{ 
		printf("Error: In Directory opening\n");
		closedir(SUB_Dir);
		return 0;
	}
	while(SUB_Dir_list = readdir(SUB_Dir))
	{	
		if(strcmp(SUB_Dir_list->d_name,".") != 0 && strcmp(SUB_Dir_list->d_name,"..")  !=0)
		{
			char path[1000]={0};
			strcpy(path,SUB_PATH); /* path for inner sub directory */
			strcat(path,"/");
			strcat(path,SUB_Dir_list->d_name);
			type_of_file(path,SUB_Dir_list->d_name,SUB_Dir_list->d_type); /* for finding the type of file */
			if(SUB_Dir_list->d_type == DT_DIR)
			sub_dir(path);
		}
	}

	closedir(SUB_Dir);
	return -1;


}
#define CHILD 0
int type_of_e(char *in_path)
{
	printf("str=%s\n",AA.ecmd);
        if(AA.ecmd == NULL)
		{printf("!\n");	return -1;}
	char *argv[10]={NULL};
	char *pe ;
	char buff[10];
	strcpy(buff,AA.ecmd);
	char ie=0;
//	char *str = AA.ecmd; 
	  pe = strtok(buff," ");
	

	do
	{
	  argv[ie] = pe;
	  pe = strtok(NULL," ");
	  ie++;
	 // printf("iE=%d ",ie);
	}while(pe != NULL);
	  argv[ie] = in_path;
	  argv[ie+1] = NULL;
	  //printf("iE=%d ",ie);
	  //for(int i=0;i<ie;i++)
	  //	  printf("# %s\n",argv[i]);
#if 1
  	  pid_t AAPID;
	int AASS;
	AAPID = fork();
	if(AAPID < 0)
	{
	  printf("error in child creation\n");
	  return -1;
	}
	if(AAPID ==CHILD)
	{
       		if(execvp(argv[0],argv) <0)
			 perror("execvp");
	}
	else
	{
		wait(&AASS);
	       	//waitpid(-1,NULL,0);
		return 0;
	}
#endif
}

int type_of_file(char *in_path,char *name,int type)  /* function for type of file */
{
	struct stat stat_buf;
	int Ret;
	if(lstat(in_path,&stat_buf) < 0)
	{
		printf("Error in file open stat:%s\n",in_path);
		return 0;
	}
	//if( AA.file)
	{
	//	printf("size%d\n",AA.size_n);
		if(((AA.file == 1)  && 	(strstr(in_path,AA.str) != NULL )) || ((AA.size_f ==1) && (stat_buf.st_size >= AA.size_n)))
	        	 Ret = file_type(name,type,stat_buf.st_size);
		else if((AA.file !=1)  && (AA.size_f != 1)) 
	        	 Ret = file_type(name,type,stat_buf.st_size);
		else
			Ret =-1;
		if((AA.e==1) && (Ret ==0 && type != DT_DIR))
		{ type_of_e(in_path);}

		if(AA.E ==1)
		{
		  
		  strcat(E_P,in_path) ;
		  strcat(E_P,"*") ;
		}
	}
}
int file_type(char *name,int type,int size)
{	
	char *space;
//	printf(" $ %s\n",name);
        if((AA.type ==1))
		if( ((AA.dir ==1) && (type != DT_DIR))  | ((AA.reg ==1) &&(type != DT_REG)))
			return 0;
	 if(strcmp(SUB,AA.path) != 0)
		 space = "\t";
	 else
		 space ="";


	switch(type)
	{
		case DT_BLK :     printf("%-20s ->\t%s ",name,"Block device");
				  break;
		case DT_CHR:      printf("%-20s ->\t%s",name,"Character device");
				  break;
		case DT_FIFO:     printf("%-20s ->\t%s",name,"Named pipe (FIFO)");
				  break;
		case DT_DIR:
				  printf("%s%-20s ->\t%s  ",space,name,"Directory");
	 			  //file_size(path,0);
				  ///sub_dir(path);
				  break;
		case DT_LNK:      printf("%-20s ->\t%s",name,"symbolic link");
				  break;
		case DT_REG:      printf("%s%-20s ->\t%s ",space,name,"Regular file");
				  break;
		case DT_SOCK:      printf("%-20s ->\t%s ",name,"UNIX domain socket");
				   break;
		default :
				   //printf("%-20s ->\t%s ",name,"File type could not be determined.");
				   printf("%-20s ->\t%s ",name,"F");
	}
	  if(AA.Size | AA.size_f )
		  printf(" (%d) \n",size);
	  else
		  printf("\n");
	 //file_size(path,0);
	return 0;
}
int file_size(char * path,int size)
{
 	struct stat file_info;
    
     if(lstat(path,&file_info) < 0)
     {
	 printf("Error in stat open %s\n",path);
     	 return 0;
     }
     if(file_info.st_size >= size || size ==0)
     	printf( " (%d) \n",(int)file_info.st_size);
	

     return 0;


}
