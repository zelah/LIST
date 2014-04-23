#include <stdio.h>
#include <stdlib.h>
typedef long double longdouble;
typedef long long longlong;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;
#define DEFINE_ZED_TYPE(type_) typedef type_ * type_##P;typedef struct type_##List type_##List;typedef struct type_##GarbageList type_##GarbageList;struct type_##GarbageList{struct type_##List *garbage;struct type_##GarbageList *next;};struct type_##List{type_ value;struct type_##List *values;struct type_##List *next;type_##GarbageList *garbage};typedef struct type_##List * type_##ListP;typedef struct type_##GarbageList * type_##GarbageListP;typedef type_ ZED##type_;typedef type_##P ZED##type_##P;typedef struct type_##GarbageList ZED##type_##GarbageList;typedef type_##GarbageListP ZED##type_##GarbageListP;typedef struct type_##List ZED##type_##List;typedef type_##ListP ZED##type_##ListP;type_##P type_##ArrayNew(ulonglong size){return malloc(size*sizeof(type_));}type_ type_##ArrayRef(ulonglong index,type_##P array){return array[index-1];}type_##P type_##ArraySet(ulonglong index,type_ value,type_##P array){array[index-1]=value;return array;}type_##ListP type_##ListNew();type_##ListP type_##ListValuePush(type_ value,type_##ListP list);type_##ListP type_##ListValuesPush(type_##ListP values,type_##ListP list);type_##ListP type_##ListPop(type_##ListP list);uchar type_##ListAssertNull(type_##ListP list);uchar type_##ListAssertValues(type_##ListP list);uchar type_##ListFree(type_##ListP list);static uchar type_##GarbageListFree(type_##GarbageListP garbage);type_ type_##ListValueTop(type_##ListP list);type_##ListP type_##ListValuesTop(type_##ListP list);

DEFINE_ZED_TYPE(char)
DEFINE_ZED_TYPE(uchar)
DEFINE_ZED_TYPE(int)
DEFINE_ZED_TYPE(uint)
DEFINE_ZED_TYPE(long)
DEFINE_ZED_TYPE(ulong)

static void ucharListCollect(ucharListP list);
static void ucharGarbageListFeed(ucharGarbageListP garbage1,ucharGarbageListP garbage2);
static void ucharListCollect1(ucharGarbageListP all,ucharGarbageListP garbage);

ucharListP ucharListValuesTop(ucharListP list){return list->values;}

uchar ucharListValueTop(ucharListP list){return list->value;}

static void ucharListCollect(ucharListP list){ucharGarbageListFeed(list->values->garbage,list->garbage);ucharListCollect1(list->garbage,list->garbage->next);}

static void ucharListCollect1(ucharGarbageListP all,ucharGarbageListP garbage){printf("c%dc",garbage->garbage->garbage);printf("d%dd",all);if(garbage->next==NULL){garbage->garbage->garbage=all;}else{garbage->garbage->garbage=all;ucharListCollect1(all,garbage->next);}}

static void ucharGarbageListFeed(ucharGarbageListP garbage1,ucharGarbageListP garbage2){if(garbage2->next==NULL){garbage2->next=garbage1;}else{ucharGarbageListFeed(garbage1,garbage2->next);}}

ucharListP ucharListNew(){ucharListP list=malloc(sizeof(ucharList));ucharGarbageListP garbage=malloc(sizeof(ucharGarbageList));list->next=NULL;list->garbage=garbage;garbage->next=NULL;garbage->garbage=list;return list;}

ucharListP ucharListValuePush(uchar value,ucharListP list){ucharListP tempList=malloc(sizeof(ucharList));ucharGarbageListP tempGarbageList=malloc(sizeof(ucharGarbageList));tempList->value=list->value;tempList->values=list->values;tempList->garbage=list->garbage->next;tempList->next=list->next;list->value=value;list->values=NULL;list->garbage->garbage=list;list->garbage->next=tempGarbageList;list->next=tempList;tempGarbageList->garbage=tempList;tempGarbageList->next=tempList->garbage;tempList->garbage=list->garbage;return list;}

ucharListP ucharListValuesPush(ucharListP values,ucharListP list){ucharListP tempList=malloc(sizeof(ucharList));ucharGarbageListP tempGarbageList=malloc(sizeof(ucharGarbageList));tempList->value=list->value;tempList->values=list->values;tempList->garbage=list->garbage->next;;tempList->next=list->next;list->values=values;list->garbage->garbage=list;list->garbage->next=tempGarbageList;list->next=tempList;tempGarbageList->garbage=tempList;tempGarbageList->next=tempList->garbage;tempList->garbage=list->garbage;ucharListCollect(list);return list;}

ucharListP ucharListPop(ucharListP list){return list->next;}

uchar ucharListAssertNull(ucharListP list){return list->next==NULL;}

uchar ucharListAssertValues(ucharListP list){return !(list->values==NULL);}

uchar ucharListFree(ucharListP list){ucharGarbageListFree(list->garbage);return 0;}

static uchar ucharGarbageListFree(ucharGarbageListP garbage){ucharGarbageListP	next=garbage->next;free(garbage->garbage);free(garbage);printf("free");if(next==NULL){return 0;}else{return ucharGarbageListFree(next);}}
 
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
