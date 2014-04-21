#include <stdio.h>
#include <stdlib.h>
typedef long double longdouble;
typedef long long longlong;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;
#define DEFINE_ZED_TYPE(type_) typedef type_ * type_##P;typedef struct type_##List type_##List;typedef struct type_##GarbageList type_##GarbageList;struct type_##GarbageList{struct type_##List *garbage;struct type_##GarbageList *next;};struct type_##List{type_ value;struct type_##List *values;struct type_##List *next;type_##GarbageList *garbage};typedef struct type_##List * type_##ListP;typedef struct type_##GarbageList * type_##GarbageListP;typedef type_ ZED##type_;typedef type_##P ZED##type_##P;typedef struct type_##GarbageList ZED##type_##GarbageList;typedef type_##GarbageListP ZED##type_##GarbageListP;typedef struct type_##List ZED##type_##List;typedef type_##ListP ZED##type_##ListP;type_##P type_##ArrayNew(ulonglong size){return malloc(size*sizeof(type_));}type_ type_##ArrayRef(ulonglong index,type_##P array){return array[index-1];}type_##P type_##ArraySet(ulonglong index,type_ value,type_##P array){array[index-1]=value;return array;}type_##ListP type_##ListNew();type_##ListP type_##ListValuePush(type_ value,type_##ListP list);type_##ListP type_##ListValuesPush(type_##ListP values,type_##ListP list);type_##ListP type_##ListPop(type_##ListP list);uchar type_##ListAssertNull(type_##ListP list);uchar type_##ListAssertValue(type_##ListP list);uchar type_##ListFree(type_##ListP list);static uchar type_##GarbageListFree(type_##GarbageListP garbage);static void type_##ListCollect(type_##ListP list);static void type_##ListFeed(type_##GarbageListP garbage,type_##ListP values);type_ type_##ListValueTop(type_##ListP list);type_##ListP type_##ListValuesTop(type_##ListP list);type_##ListP type_##ListValuesTop(type_##ListP list){return list->values;}type_ type_##ListValueTop(type_##ListP list){return list->value;}static void type_##ListCollect(type_##ListP list){type_##ListFeed(list->garbage,list->values);}static void type_##ListFeed(type_##GarbageListP garbage,type_##ListP values){if(type_##ListAssertNull(values)){values->next=garbage;}else{type_##ListFeed(garbage,values->next);}}type_##ListP type_##ListNew(){type_##ListP list=malloc(sizeof(type_##List));type_##GarbageListP garbage=malloc(sizeof(type_##GarbageList));list->next=NULL;list->garbage=garbage;garbage->next=NULL;garbage->garbage=list;return list;}type_##ListP type_##ListValuePush(type_ value,type_##ListP list){type_##ListP tempList=malloc(sizeof(type_##List));type_##GarbageListP tempGarbageList=malloc(sizeof(type_##GarbageList));tempList->value=list->value;tempList->values=list->values;tempList->garbage=list->garbage->next;tempList->next=list->next;list->value=value;list->values=NULL;list->garbage->garbage=list;list->garbage->next=tempGarbageList;list->next=tempList;tempGarbageList->garbage=tempList;tempGarbageList->next=tempList->garbage;tempList->garbage=list->garbage;return list;}type_##ListP type_##ListValuesPush(type_##ListP values,type_##ListP list){type_##ListP tempList=malloc(sizeof(type_##List));type_##GarbageListP tempGarbageList=malloc(sizeof(type_##GarbageList));tempList->value=list->value;tempList->values=list->values;tempList->garbage=list->garbage->next;;tempList->next=list->next;list->values=values;list->garbage->garbage=list;list->garbage->next=tempGarbageList;list->next=tempList;tempGarbageList->garbage=tempList;tempGarbageList->next=tempList->garbage;tempList->garbage=list->garbage;type_##ListCollect(list);return list;}type_##ListP type_##ListPop(type_##ListP list){return list->next;}uchar type_##ListAssertNull(type_##ListP list){return list->next==NULL;}uchar type_##ListAssertValues(type_##ListP list){return !(list->values==NULL);}uchar type_##ListFree(type_##ListP list){type_##GarbageListFree(list->garbage);return 0;}static uchar type_##GarbageListFree(type_##GarbageListP garbage){type_##GarbageListP next=garbage->next;if(type_##ListAssertValues(garbage->garbage)){type_##ListFree(garbage->garbage->values);}free(garbage->garbage);free(garbage);if(next==NULL){return 0;}else{return type_##GarbageListFree(next);}}
 
DEFINE_ZED_TYPE(char)
DEFINE_ZED_TYPE(uchar)
DEFINE_ZED_TYPE(double)
DEFINE_ZED_TYPE(float)
DEFINE_ZED_TYPE(int)
DEFINE_ZED_TYPE(uint)
DEFINE_ZED_TYPE(long)
DEFINE_ZED_TYPE(ulong)
DEFINE_ZED_TYPE(longdouble)
DEFINE_ZED_TYPE(longlong)
DEFINE_ZED_TYPE(ulonglong)
DEFINE_ZED_TYPE(short)
DEFINE_ZED_TYPE(ushort)
DEFINE_ZED_TYPE(charP)
DEFINE_ZED_TYPE(ucharP)
DEFINE_ZED_TYPE(doubleP)
DEFINE_ZED_TYPE(floatP)
DEFINE_ZED_TYPE(intP)
DEFINE_ZED_TYPE(uintP)
DEFINE_ZED_TYPE(longP)
DEFINE_ZED_TYPE(ulongP)
DEFINE_ZED_TYPE(longdoubleP)
DEFINE_ZED_TYPE(longlongP)
DEFINE_ZED_TYPE(ulonglongP)
DEFINE_ZED_TYPE(shortP)
DEFINE_ZED_TYPE(ushortP)
DEFINE_ZED_TYPE(charListP)
DEFINE_ZED_TYPE(ucharListP)
DEFINE_ZED_TYPE(doubleListP)
DEFINE_ZED_TYPE(floatListP)
DEFINE_ZED_TYPE(intListP)
DEFINE_ZED_TYPE(uintListP)
DEFINE_ZED_TYPE(longListP)
DEFINE_ZED_TYPE(ulongListP)
DEFINE_ZED_TYPE(longdoubleListP)
DEFINE_ZED_TYPE(longlongListP)
DEFINE_ZED_TYPE(ulonglongListP)
DEFINE_ZED_TYPE(shortListP)
DEFINE_ZED_TYPE(ushortListP)
 
int main(){
    ucharListPP array1=ucharListPArrayNew(1024);
    ucharListPArraySet(55,ucharListPop(ucharListValuePush(211,ucharListValuePush(122,ucharListValuePush(121,ucharListValuePush(112,ucharListValuePush(111,ucharListNew())))))),array1);
    printf("%d\n",ucharListPArrayRef(55,array1)->value);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->value);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->next->value);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->next->next->value);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->next->next->next->next);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->next->garbage->garbage->value);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->next->garbage->next->garbage->value);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->next->garbage->next->next->garbage->value);
    printf("%d\n",ucharListPArrayRef(55,array1)->next->next->garbage->next->next->next->garbage->value);
    ucharP array=ucharArrayNew(1024);
    ucharArraySet(55,222,array);
    printf("\n%d\n",ucharArrayRef(55,array));
    ucharGarbageListP x=NULL;
    ulongListP y=NULL;
    ucharListP list=ucharListNew();
    list=ucharListValuesPush(ucharListNew(),list);
    list=ucharListValuePush(222,list);
    list=ucharListValuesPush(ucharListValuePush(111,ucharListNew()),list);
    printf("\n%d\n",list->values->value);
  
  printf("\n%d %d %d\n",list->garbage,list->next->garbage,list->next->next->garbage);
  
  ucharListFree(list->next->next);
  printf("\n%d\n",list->values->value);
 
return 0;
}
 
 
