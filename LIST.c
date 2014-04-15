#define payload(_type) unsigned _type
#define ZEDListP(_type) typedef struct{payload(_type) value;payload(ZED_typeList*) next;}ZED_typeList;

int main(){
return 0;
}
