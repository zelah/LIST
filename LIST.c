#include <stdio.h>
#include <stdlib.h>
typedef long double longdouble;
typedef long long longlong;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;

#include "MACRO.h"
 
DEFINE_ZED_TYPE(char)
DEFINE_ZED_TYPE(uchar)
DEFINE_ZED_TYPE(int)
DEFINE_ZED_TYPE(uint)
DEFINE_ZED_TYPE(long)
DEFINE_ZED_TYPE(ulong)
 
int main(){
    ucharListP list=ucharListNew();
    ucharListP sublist=ucharListNew();
    printf("\n%dlist%dlist\n",list->garbage,list->garbage->next);
    printf("\n%dsub%dsub\n",sublist->garbage,sublist->garbage->next);
    sublist=ucharListValuePush(1,sublist);
    printf("\n%dsub%dsub%dsub\n",sublist->garbage,sublist->garbage->next,sublist->garbage->next->next);
    list=ucharListValuesPush(sublist,list);
    printf("\n%dlist%dlist%dlist%dlist%dlist\n",list->garbage,list->garbage->next,list->garbage->next->next,list->garbage->next->next->next,list->garbage->next->next->next->next);
    list=ucharListValuePush(222,list);
    printf("\n%dlist%dlist%dlist%dlist%dlist%dlist\n",list->garbage,list->garbage->next,list->garbage->next->next,list->garbage->next->next->next,list->garbage->next->next->next->next,list->garbage->next->next->next->next->next);
    list=ucharListValuesPush(ucharListValuePush(111,ucharListNew()),list);
    printf("\n%dlist%dlist%dlist%dlist%dlist%dlist%dlist%dlist%dlist\n",list->garbage,list->garbage->next,list->garbage->next->next,list->garbage->next->next->next,list->garbage->next->next->next->next,list->garbage->next->next->next->next->next,list->garbage->next->next->next->next->next->next,list->garbage->next->next->next->next->next->next->next,list->garbage->next->next->next->next->next->next->next->next);
 
printf("\n%d\n",list->next->next->values->next->garbage);
 
  ucharListFree(list->next->next->values->next);
 
return 0;
}
