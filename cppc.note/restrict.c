//使用1：
int array[10];
int *ptrArray = array;

// restrict关键字使得编译器保证ptr是修改该返回内存的唯一方式，因而对代码进行优化
int * restrict ptr = (int *) malloc(10*sizeof(int)); 

for( int n=0; n<10; n++)
{
	array[n] += 5;
	ptrArray[n] *= 2;
	array[n] += 3; //这里编译器就不可以优化了

	ptr[n] += 5;
	ptr[n] += 3; //因为ptr是restrict修饰的，编译器可以进行优化：ptr[n] += 8
}


//使用2：
void * memcpy(void * restrict s1, const void * restrict s2, size_t n);
//提示用户s1,s2指向的内存不应该重叠，因为s1指向的内存只由s1所修改

void * memove(void * s1, const void * s2, size_t n);
//s1,s2指向的内存可以重叠
