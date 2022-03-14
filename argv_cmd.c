#include<stdio.h>

struct aa{
  int Size;
  int size_f;
  int size_n;
  int file;
  char *str;
  int type;
  int reg;
  int dir;
  char *path;
  char e;
  char *ecmd;
  char E;
  char *Ecmd;

}AA;
int main_args(int argc,char **argv)
{
	memset(&AA,0,sizeof(AA));
	for(int i=1;i<argc ; i++)
	{
#if 1
		if(strcmp(argv[i],"-S")==0)
			AA.Size = 1;
		else if(strcmp(argv[i],"-s")==0)
			{ 
				AA.size_f = 1;
				i++;
				if(i < argc)
				AA.size_n = atoi(argv[i]);
			}
		else if(strcmp(argv[i],"-f")==0)
			{ 
				AA.file = 1;
				i++;
				if(i < argc)
				AA.str = argv[i];
			}
		else if(strcmp(argv[i],"-e")==0)
			{ 
				//printf("e SET\n");
				AA.e = 1;
				i++;
				if(i < argc)
				AA.ecmd = argv[i];
			}
		else if(strcmp(argv[i],"-E")==0)
			{ 
				//printf("E SET\n");
				AA.E = 1;
				i++;
				if(i < argc)
				AA.Ecmd = argv[i];
			}
		else if(strcmp(argv[i],"-t")==0)
			{ 
				AA.type = 1;
				i++;
				if(i < argc)
				{	if(strcmp(argv[i],"d")==0)
					AA.dir =1;
					else if(strcmp(argv[i],"f")==0)
					AA.reg =1;
					else
					AA.type = 0;
				}
			}
		else
			AA.path = argv[i];
		
		
#endif
 //		printf("%d %s\n",i,argv[i]);
	}
	if(AA.path == NULL)
		AA.path = ".";
#if 0	
	printf("-S=%d\n",AA.Size);
	printf("-s=%d %d\n",AA.size_f,AA.size_n);
	printf("-f=%d  %s\n",AA.file,AA.str);
	printf("-e=%d  %s\n",AA.e,AA.ecmd);
	printf("-E=%d  %s\n",AA.E,AA.Ecmd);
	printf("-t=%d D=%d f=%d\n",AA.type,AA.dir,AA.reg);
	printf("path=%s\n",AA.path);
#endif
	return 0;
}
