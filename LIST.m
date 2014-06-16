#include<stdio.h>
#include<stdlib.h>

#define DEFINE_ZED_TYPE(type_) typedef type_ ZED##type_;typedef type_ * type_##P;typedef type_##P ZED##type_##P;static type_##P type_##ArrayNew(ulonglong size){return (type_##P)malloc(size*sizeof(type_));}static type_ type_##ArrayRef(ulonglong index,type_##P array){return array[index-1];}static type_##P type_##ArraySet(ulonglong index,type_ value,type_##P array){array[index-1]=value;return array;}

typedef unsigned char uchar;
typedef unsigned long long ulonglong;
DEFINE_ZED_TYPE(uchar)
DEFINE_ZED_TYPE(ulonglong)

ucharP newList(){return ucharArraySet(3,')',ucharArraySet(2,'0',ucharArraySet(1,'(',ucharArrayNew(3))));}

ulonglong extent2(ulonglong character){return character-'0';}

ulonglong extent1(ulonglong index,ucharP list,ulonglong value){if(list[index]==')'){return value;}else{return extent1(index+1,list,extent2(list[index])+value*10);}}

ulonglong extent(ucharP list){return extent1(1,list,0);}

ulonglong selfExtent1(ulonglong extent,ulonglong length,ulonglong magnitude){if(extent<magnitude){return length;}else{return selfExtent1(extent,length+1,magnitude*10);}}

ulonglong selfExtent(ulonglong extent){return selfExtent1(extent,3,10);}

void extend1(ulonglong length,ulonglong index,ucharP temp){if(index>0){temp[index]=length%10+'0';extend1(length/10,index-1,temp);}}

void extend2(ulonglong length,ulonglong listIndex,ucharP list,ulonglong tempIndex,ucharP temp){if(length>0){temp[tempIndex]=list[listIndex];extend2(length-1,listIndex+1,list,tempIndex+1,temp);}}

ucharP extend(uchar character,ucharP list){ulonglong oldExtent=extent(list);ulonglong newExtent=oldExtent+1;ulonglong oldSelfExtent=selfExtent(oldExtent);ulonglong newSelfExtent=selfExtent(newExtent);ucharP temp=(ucharP)malloc((newSelfExtent+newExtent)*sizeof(uchar));temp[0]='(';extend1(newExtent,newSelfExtent-2,temp);temp[newSelfExtent-1]=')';temp[newSelfExtent]=character;extend2(oldExtent,oldSelfExtent,list,newSelfExtent+1,temp);free(list);return temp;}

ucharP copy1(ucharP list,ucharP temp,ulonglong length){if(length==0){return temp;}else{temp[length-1]=list[length-1];return copy1(list,temp,length-1);}}

ucharP copy(ucharP list){ulonglong newExtent=extent(list);ulonglong newSelfExtent=selfExtent(newExtent);ulonglong length=newExtent+newSelfExtent;ucharP temp=(ucharP)malloc(length*sizeof(uchar));return copy1(list,temp,length);}

void displayNumber1(ulonglong index,ulonglong end,ucharP list){if(index<end){printf("%c",list[index]);displayNumber1(index+1,end,list);}}

void displayNumber(ucharP list){ulonglong ext=extent(list);ulonglong start=selfExtent(ext);ulonglong end=start+ext;displayNumber1(start,end,list);}

ulonglong lengthString1(char* string,ulonglong index){if(string[index]==0){return index;}else{return lengthString1(string,index+1);}}

ulonglong lengthString(char* string){return lengthString1(string,0);}

char* reverseString(char* str){ulonglong i;ulonglong j=lengthString(str)-1;ulonglong k=j/2;char temp;for(i=0;i<=k;i++){temp=str[j];str[j]=str[i];str[i]=temp;j--;}return str;}

char* copyString1(ulonglong index,char* str1,char* str2){if(str1[index]==0){str2[index]=0;return str2;}else{str2[index]=str1[index];return copyString1(index+1,str1,str2);}}

char* copyString(char* str){char* copy=(char*)malloc((1+lengthString(str))*sizeof(char));return copyString1(0,str,copy);}

ucharP newNumber1(ulonglong index,char* string,ucharP number){if(string[index]==NULL){return number;}else{return newNumber1(index+1,string,extend((uchar)string[index],number));}}

ucharP newNumber(char* string){ucharP number=newList();return newNumber1(0,reverseString(copyString(string)),number);}

int main(){

ucharP number1=newNumber("1234512345123451234512345123451234512345123451234512345");
ucharP number2=copy(number1);

displayNumber(number1);
free(number1);
printf("\n");
displayNumber(number2);
free(number2);

return 0;
}
