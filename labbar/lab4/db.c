#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "../lab3/utils-lab3.h" 

typedef struct item item_t;

struct item{
    char *name;
    char *desc;
    char *shelf;
    int price;
};

void print_item(item_t *it){
    printf("name: %s\n desc; %s\n price: %d,00 SEK\n shelf: %s\n",it->name,it->desc,it->price/100,it->shelf);
}

item_t make_item(char *na,char *de, int pr, char *sh){
    item_t m = {
        .name = na,
        .desc = de,
        .shelf = sh,
        .price = pr
    };
    return m; 
}

bool shelf_check(char *str){

    if(isalpha(str[0]) && strlen(str)>1){
        for(int i =1; str[i] != '\0'; i++){
            if(!isdigit(str[i])){return false;}   
        }
        return true;
    }
    else {return false;}
}

char *ask_question_shelf(char *question){
    return ask_question(question,shelf_check,(convert_func *) strdup).string_value;
}

item_t input_item(void){
    item_t it = {
        .name = ask_question_string("Varans namn"),
        .desc = ask_question_string("Beskrivning av vara"),
        .price = ask_question_int("varans pris i öre"),
        .shelf = ask_question_shelf("varans hylla")
    };
    return it; 
}

char *magick(char *arr1[], char *arr2[], char *arr3[], int len){
    int bufsiz = 255;
    char buf[bufsiz];

   
    int tal1 = rand() % len; // random tal ej större än len
    int tal2 = rand() % len; 
    int tal3 = rand() % len; 

    char *wrd1 = arr1[tal1];
    char *wrd2 = arr2[tal2];
    char *wrd3 = arr3[tal3]; 

    strcpy(buf,wrd1);
    strcat(buf,"-");
    strcat(buf,wrd2);
    strcat(buf," ");
    strcat(buf,wrd3);
    //strcpy(buf,'\0');

    return strdup(buf);
}

void list_db(item_t *items, int no_items){
    for(int i = 0;i<no_items;i++){
         printf("%d. %s\n", i+1, items[i].name);
    } 
}

item_t *edit_db(item_t *db,int db_siz){
    //int em;
    int em = ask_question_int("nummer på vilken vara vill du ändra?:");
    em = em-1;

    if(0 <= em && em < db_siz){

        print_item(&db[em]);

        item_t new_item = input_item(); 
        db[em].name = new_item.name;
        db[em].desc = new_item.desc;
        db[em].price = new_item.price;
        db[em].shelf = new_item.shelf;
    }
    else{puts("ingen vara med det nummer");}
    return db;
}


int main(int argc, char *argv[])
{

  srandom(time(NULL)); 

  char *array1[] = { "stekt","elak","dunder" }; // TODO: Lägg till!
  char *array2[] = { "liten","mega","lagom" }; // TODO: Lägg till!
  char *array3[] = { "tung tung sahur","jägerman","gurka" }; // TODO: Lägg till!

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, strdup(shelf));

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
     list_db(db,db_siz);
     edit_db(db,db_siz);
     list_db(db,db_siz);
  }
  return 0;
}
