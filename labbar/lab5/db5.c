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


void print_menu(){
    printf(
        "[L]ägg till en vara\n"
        "[T]a bort vara\n"
        "[R]edigera vara\n"
        "Ån[g]ra senaste ändring\n"
        "Lista [h]ela varukatalog\n"
        "[A]vsluta\n"
        );
}

bool is_LlTtRrGgHhAa(char *let){
    int c = toupper(let[0]);

    if (strlen(let)<1){return false;}

    if(c == 'L' || c == 'T' || c == 'R' || c == 'G' || c == 'A' || c == 'H'){return true;}

    else{return false;}
}

char *ask_question_menu(char *question){
    return ask_question(question,is_LlTtRrGgHhAa,(convert_func *) strdup).string_value;
}

item_t *add_item_db(item_t *db,int *db_siz){
    puts("Lägg till vara:");
    
    db = realloc(db, (*db_siz+1) * sizeof(item_t));

    item_t add_it = input_item();
    db[*db_siz] = add_it;
    *db_siz = *db_siz + 1;    

    return db;
}




item_t *remove_item(item_t *db, int *db_siz){
    int em = ask_question_int("nummer på vilken vara vill du ta bort?:");
    em = em-1;

    //int i = 0;
    //item_t tmp;

    if(0 <= em && em < *db_siz){
        while(em!=*db_siz-1){
            db[em] = db[em+1];
            em++;
        }
        *db_siz = *db_siz - 1;    
    }
    else{puts("ange korrekt nummer");}
    return db;
}



int *event_loop(item_t *db,int *db_siz){

    //char x;
    char *ans;
    do{
    print_menu();
    ans = ask_question_menu("välj alternativ:");
    //x = toupper(ans[0]);

    if(*ans=='L'){db = add_item_db(db, db_siz);}
    else if(*ans=='T'){remove_item(db,db_siz);}
    else if(*ans=='R'){edit_db(db,*db_siz);}
    else if(*ans=='g'){puts("ej implemerat");}
    else if(*ans=='h'){list_db(db,*db_siz);}
    else if(*ans=='A'){return 0;}
    else{puts("ange ett valid svar");}

    } while(*ans != 'A');
    return 0;
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

    int size = 16*sizeof(item_t);
    item_t *db = malloc(size);                   // Array med plats för 16 varor
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
     //list_db(db,db_siz);
     //edit_db(db,db_siz);
     //db = add_item_db(db,&db_siz);
     //remove_item(db,&db_siz);
     //list_db(db,db_siz);
    // db = add_item_db(db,&db_siz);
    // list_db(db,db_siz);
    event_loop(db, &db_siz);
  }
  return 0;
}
