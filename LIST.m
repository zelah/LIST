#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned long long ulonglong;

#include "MACRO.h"
 
DEFINE_ZED_TYPE(uchar)
DEFINE_ZED_TYPE(ulonglong)

static ucharListP ucharListReverse1(ucharListP list,ucharListP stack){if(ucharListAssertNull(list)) {return stack;}else if(ucharListAssertValues(list)){return ucharListReverse1(ucharListPop(list),ucharListValuesPush(ucharListValuesTop(list),stack));}else{return ucharListReverse1(ucharListPop(list),ucharListValuePush(ucharListValueTop(list),stack));}}

static ucharListP ucharListReverse(ucharListP list){return ucharListReverse1(list,ucharListNew());}
 
int main(){
    ucharListP list=ucharListNew();
    list=ucharListValuePush(1,list);
    list=ucharListValuePush(2,list);
    list=ucharListValuePush(3,list);
    list=ucharListValuePush(4,list);
    //list=ucharListPop(list);
    //list=ucharListPop(list);
    //list=ucharListPop(list);
    printf("\n%d",ucharListValueTop(list));
    list=ucharListReverse(list);
    printf("\n%d",ucharListValueTop(list));
    ucharListFree(list);
 
return 0;
}
