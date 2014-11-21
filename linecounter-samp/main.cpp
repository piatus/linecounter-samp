#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"

using namespace std;

static int find_directory (const char *dirname,int &count,int &alllines);
int print_filelines (string filename);

 
int main(int argc, char *argv[]) 
{
	int count=0, alllines=0;
	find_directory ("gamemodes", count, alllines);
    
	if(count)
		printf("Odnaleziono %d plik(ow) w ktorych jest %d linijek kodu. \n", count, alllines);
	else 
		printf("Nie odnaleziono zadnego pliku.\n");

	system("pause");
    return EXIT_SUCCESS;
}


static int find_directory(const char *dirname,int &count,int &alllines)//from dirent explames (modyfiket!)
{
    DIR *dir;
    char buffer[PATH_MAX + 2];
    char *p = buffer;
    const char *src;
    char *end = &buffer[PATH_MAX];
    int ok;
	int dtemp=0;
    src = dirname;
    while (p < end  &&  *src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';

    dir = opendir (dirname);
    if (dir != NULL) {
        struct dirent *ent;

        while ((ent = readdir (dir)) != NULL) {
            char *q = p;
            char c;

            if (buffer < q) {
                c = q[-1];
            } else {
                c = ':';
            }
            if (c != ':'  &&  c != '/'  &&  c != '\\') {
                *q++ = '/';
            }

            src = ent->d_name;
            while (q < end  &&  *src != '\0') {
                *q++ = *src++;
            }
            *q = '\0';

            switch (ent->d_type) {
            case DT_LNK:
            case DT_REG:
				if((dtemp=print_filelines(string(buffer)), dtemp)) alllines+=dtemp,count++;
                break;

            case DT_DIR:
                if (strcmp (ent->d_name, ".") != 0  
                        &&  strcmp (ent->d_name, "..") != 0) {
                    find_directory (buffer, count, alllines);
                }
                break;

            default:
               ;
            }

        }

        closedir (dir);
        ok = 1;

    } else {
        printf ("Nie mo¿na odnaleŸæ katalogu %s\n", dirname);
        ok = 0;
    }

    return count;
}
int print_filelines (string filename)
{
	if(filename.substr(filename.find_last_of(".") + 1) != "pwn" && filename.substr(filename.find_last_of(".") + 1) != "p" && filename.substr(filename.find_last_of(".") + 1) != "inc") return 0;
	
	printf ("%s", filename.c_str());

    FILE* fp;
    int countLines = 1;
    int i;

	fp = fopen(filename.c_str(), "r");
 
	while((i=fgetc(fp))!=EOF) if (i == '\n') countLines++;
	
	printf(" %d lines\n", countLines);
	return countLines;
}

