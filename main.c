#include <stdio.h>
#include <locale.h>

#include "structers.h"


int main()
{
   setlocale(LC_ALL, "Rus");

   FILE* file;
   errno_t err = fopen_s(&file, "file.txt", "r");

   if (err != 0 || !file)
   {
      perror("File cant't open!");
      return 1;
   }

   readFile(file);

   return 0;
}

