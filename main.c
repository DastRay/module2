#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "structers.h"

void Replace(char* str_)
{
   int i = 0;

   while (str_[i] != '\0')
   {
      if (str_[i] == 'я' || str_[i] == 'Я')
      {
         str_[i] = ' ';
      }
      else
      {
         str_[i] = str_[i] + 1;
      }
      i++;
   }
}

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


   /*char str[] = "Строка Яя!";

   printf("Исходная строка: %s\n", str);

   Replace(str);

   printf("Измененная строка: %s\n", str);*/

   return 0;
}


