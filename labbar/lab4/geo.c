#include <stdio.h>
#include <stdlib.h>

typedef struct point point_t;

typedef struct rect rect_t;


struct point
{
  int x;
  int y;
};

struct rect
{
    point_t tl;
    point_t br;
};


void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}

point_t print_point(point_t *str){
    printf("point(%d,%d)",str->x,str->y);
    return *str;
}

point_t make_point(int a, int b){
    point_t p = {
        .x=a,
        .y=b};
        return p; 
    }
   


void print_rec(rect_t *rec){
    printf("rectangle(upperleft ");
    print_point(&rec->tl);
    printf(" bottomright ");
    print_point(&rec->br);
    printf(")\n");
}

rect_t make_rect(int a, int b, int c, int d){
    point_t topleft = make_point(a,b);
    point_t botrig = make_point(c,d);
    rect_t rec = {
        .tl=topleft,
        .br=botrig};
    return rec; 
}

int area_rect(rect_t *rec){
    int tx = rec->tl.x;
    int ty = rec->tl.y;
    int bx = rec->br.x;
    int by = rec->br.y;

    int area = (tx-bx)*(ty-by);
    return area;
}


int main(void){
    //point_t mkt = make_point(6,7);
    //point_t lkt = make_point(1,1);
    //rect_t r = {mkt,lkt};
    rect_t rec = make_rect(1,1,4,4);
    printf("%d\n",area_rect(&rec));
    print_rec(&rec);
    //print_point(&mkt);
    //point_t p = { .x = 10, .y = -42};
    //print_point(&p);
    return 0;
}

