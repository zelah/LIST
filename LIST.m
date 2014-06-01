#include<stdio.h>
#include<stdlib.h>

#define DEFINE_ZED_TYPE(type_) typedef type_ ZED##type_;typedef type_ * type_##P;typedef type_##P ZED##type_##P;static type_##P type_##ArrayNew(ulonglong size){return malloc(size*sizeof(type_));}static type_ type_##ArrayRef(ulonglong index,type_##P array){return array[index-1];}static type_##P type_##ArraySet(ulonglong index,type_ value,type_##P array){array[index-1]=value;return array;}

typedef unsigned char uchar;
typedef unsigned long long ulonglong;
DEFINE_ZED_TYPE(uchar)
DEFINE_ZED_TYPE(ulonglong)

ucharP newList(){return ucharArraySet(3,')',ucharArraySet(2,'0',ucharArraySet(1,'(',ucharArrayNew(3))));}

void test(ucharP x){printf("\n%d\n",sizeof(x));}

int main(){
ucharP list=newList();
printf("\n%c%c%c\n",list[0],list[1],list[2]);
test(list);

return 0;
}
