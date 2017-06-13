/*
 * Humpbacked titmouse v0.9
 * Multibase numbers converter, supports 2-36 bases
 *
 * Wrote by Kurashov A.K. (author homepage: saahriktu.org), 2013
 * Under GNU GPLv3
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int
main(int argc, char **argv){
 long long int num_dec = 0, tmp_v;
 int num_len, source_base, destination_base, ptr_i = 0;
 char *tmp_s, *tmp_s2;
 if (argc < 4) {
  printf ("Error: Too few arguments.\nUsage: humpbacktitmouse number source_base destination_base\n");
  return 1;
 }
 source_base = atoi(argv[2]);
 destination_base = atoi(argv[3]);

 // bases limitation
 if (source_base > 36 || destination_base > 36 || source_base < 2 || destination_base < 2) {
  printf("Error: Base out of range.\n");
  return 1;
 }
 // source processing
 num_len = strlen(argv[1]);
 tmp_s = (char *) malloc(sizeof(char));
 for (ptr_i = 0; ptr_i < num_len; ptr_i++) {
  strncpy(tmp_s, argv[1] + ptr_i, (size_t) 1);
  // prevention of trash in number
  if (tmp_s[0] < 48 || (tmp_s[0] > 57 && tmp_s[0] < 65) || (tmp_s[0] > 90 && tmp_s[0] < 97) || tmp_s[0] > 122) {
   printf("Error: Wrong number digit: `%s'.\n", tmp_s);
   free(tmp_s);
   return 1;
  }
  // process digit
  if (tmp_s[0] > 47 && tmp_s[0] < 58) tmp_v = atoi(tmp_s);
  else {
   if (tmp_s[0] > 90) tmp_v = tmp_s[0] - 87;
   else tmp_v = tmp_s[0] - 55;
  } 
  // prevention of wrong numbers
  if (tmp_v >= source_base) {
   printf("Error: Number digit out of base: `%s'.\n", tmp_s);
   free(tmp_s);
   return 1;
  }
  num_dec += tmp_v * pow(source_base, num_len - ptr_i - 1);
 }
 free(tmp_s);
 // decimal number processing
 if (num_dec == 0) {
  printf("%d\n", num_dec);
  return 0;
 }
 tmp_s = (char *) malloc((1 + floor(log10(num_dec) / log10(destination_base))) * sizeof(char));
 tmp_s2 = (char *) malloc(sizeof(char));
 while (num_dec > 0){
  tmp_v = floor(num_dec % destination_base);
  if (tmp_v < 10) sprintf(tmp_s2, "%c", (char) tmp_v + 48);
  else sprintf(tmp_s2, "%c", (char) tmp_v + 87);
  strcat(tmp_s, tmp_s2);
  num_dec = floor(num_dec / destination_base);
 }
 // output reverse string
 num_len = strlen(tmp_s);
 for (ptr_i = 0; ptr_i < num_len; ptr_i++) {
  strncpy(tmp_s2, tmp_s + num_len - ptr_i - 1, (size_t) 1);
  printf("%s", tmp_s2);
 }
 // terminate line
 printf("\n");
 // cleaning memory and exit
 free(tmp_s);
 free(tmp_s2);
 return 0;
}
