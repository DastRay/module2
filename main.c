#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "structers.h"


int main()
{
   //setlocale(LC_ALL, "Rus");

   system("chcp 1251");
   system("cls");

   FILE* file;
   errno_t err = fopen_s(&file, "file.txt", "a+");

   if (err != 0 || !file)
   {
      perror("File cant't open!");
      return 1;
   }

   readFile(file);

   return 0;
}

