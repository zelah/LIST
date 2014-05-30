#define DEFINE_ZED_TYPE(type_) typedef type_ * type_##P;typedef struct type_##List type_##List;typedef struct type_##GarbageList type_##GarbageList;struct type_##GarbageList{struct type_##List *garbage;struct type_##GarbageList *next;};struct type_##List{type_ value;struct type_##List *values;struct type_##List *next;type_##GarbageList *garbage};typedef struct type_##List * type_##ListP;typedef struct type_##GarbageList * type_##GarbageListP;typedef type_ ZED##type_;typedef type_##P ZED##type_##P;typedef struct type_##GarbageList ZED##type_##GarbageList;typedef type_##GarbageListP ZED##type_##GarbageListP;typedef struct type_##List ZED##type_##List;typedef type_##ListP ZED##type_##ListP;static type_##P type_##ArrayNew(ulonglong size){return malloc(size*sizeof(type_));}static type_ type_##ArrayRef(ulonglong index,type_##P array){return array[index-1];}static type_##P type_##ArraySet(ulonglong index,type_ value,type_##P array){array[index-1]=value;return array;}static type_##ListP type_##ListNew();static type_##ListP type_##ListValuePush(type_ value,type_##ListP list);static type_##ListP type_##ListValuesPush(type_##ListP values,type_##ListP list);static type_##ListP type_##ListPop(type_##ListP list);static uchar type_##ListAssertNull(type_##ListP list);static uchar type_##ListAssertValues(type_##ListP list);static uchar type_##ListFree(type_##ListP list);static uchar type_##GarbageListFree(type_##GarbageListP garbage);static type_ type_##ListValueTop(type_##ListP list);static type_##ListP type_##ListValuesTop(type_##ListP list);static void type_##ListCollect(type_##ListP list);static void type_##GarbageListFeed(type_##GarbageListP garbage1,type_##GarbageListP garbage2);static void type_##ListCollect1(type_##GarbageListP all,type_##GarbageListP garbage);static type_##ListP type_##ListValuesTop(type_##ListP list){return list->values;}static type_ type_##ListValueTop(type_##ListP list){return list->value;}static void type_##ListCollect(type_##ListP list){type_##GarbageListFeed(list->values->garbage,list->garbage);type_##ListCollect1(list->garbage,list->garbage->next);}static void type_##ListCollect1(type_##GarbageListP all,type_##GarbageListP garbage){if(garbage->next==NULL){garbage->garbage->garbage=all;}else{garbage->garbage->garbage=all;type_##ListCollect1(all,garbage->next);}}static void type_##GarbageListFeed(type_##GarbageListP garbage1,type_##GarbageListP garbage2){if(garbage2->next==NULL){garbage2->next=garbage1;}else{type_##GarbageListFeed(garbage1,garbage2->next);}}static type_##ListP type_##ListNew(){type_##ListP list=malloc(sizeof(type_##List));type_##GarbageListP garbage=malloc(sizeof(type_##GarbageList));list->next=NULL;list->garbage=garbage;garbage->next=NULL;garbage->garbage=list;return list;}static type_##ListP type_##ListValuePush(type_ value,type_##ListP list){type_##ListP tempList=malloc(sizeof(type_##List));type_##GarbageListP tempGarbageList=malloc(sizeof(type_##GarbageList));tempList->value=list->value;tempList->values=list->values;tempList->garbage=list->garbage->next;tempList->next=list->next;list->value=value;list->values=NULL;list->garbage->garbage=list;list->garbage->next=tempGarbageList;list->next=tempList;tempGarbageList->garbage=tempList;tempGarbageList->next=tempList->garbage;tempList->garbage=list->garbage;return list;}static type_##ListP type_##ListValuesPush(type_##ListP values,type_##ListP list){type_##ListP tempList=malloc(sizeof(type_##List));type_##GarbageListP tempGarbageList=malloc(sizeof(type_##GarbageList));tempList->value=list->value;tempList->values=list->values;tempList->garbage=list->garbage->next;tempList->next=list->next;list->values=values;list->garbage->garbage=list;list->garbage->next=tempGarbageList;list->next=tempList;tempGarbageList->garbage=tempList;tempGarbageList->next=tempList->garbage;tempList->garbage=list->garbage;type_##ListCollect(list);return list;}static type_##ListP type_##ListPop(type_##ListP list){return list->next;}static uchar type_##ListAssertNull(type_##ListP list){return list->next==NULL;}static uchar type_##ListAssertValues(type_##ListP list){return !(list->values==NULL);}static uchar type_##ListFree(type_##ListP list){type_##GarbageListFree(list->garbage);return 0;}static uchar type_##GarbageListFree(type_##GarbageListP garbage){type_##GarbageListP next=garbage->next;free(garbage->garbage);free(garbage);if(next==NULL){return 0;}else{return type_##GarbageListFree(next);}}static type_##ListP type_##ListReverse(type_##ListP list){return type_##ListReverse1( list,type_##ListNew());}static type_##ListP type_##ListReverse1(type_##ListP list,type_##ListP stack){if(type_##ListAssertNull(list)){return stack;}else if(type_##ListAssertValues(list)){return type_##ListReverse1(type_##ListPop(list),type_##ListValuesPush(type_##ListValuesTop(list),stack));}else{return type_##ListReverse1(type_##ListPop(list),type_##ListValuePush(type_##ListValueTop(list),stack));}}
