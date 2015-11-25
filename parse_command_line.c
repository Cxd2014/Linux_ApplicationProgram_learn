/*
* 利用 getopt_long 函数解析命令行参数
* 尝试执行以下命令查看解析效果:
* ./main -o cd -v fd
* ./main -v cd -o fd
* ./main -h
*/
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/* 保存本程序的名字 */
const char* program_name;

/* -h or --help 打印帮助信息 */
void print_usage(FILE *stream,int exit_code)
{
	fprintf(stream, "Usage: %s options [ inputfile ... ]\n",program_name);
	fprintf(stream,
			"	-h --help Display this usage information.\n"
			"	-o --output filename Write output to file.\n"
			"	-v --verbose Print verbose messages.\n");
	exit(exit_code);
}


int main(int argc, char* const argv[])
{
	int next_option;
	int verbose = 0; /* 判断-v选项是否执行 */
	int cnt = 0;

	/* 存放需要输出的文件名 */
	const char* output_filename = NULL;

	/* 将程序名存放在 program_name 中 */
	program_name = argv[0];

	/* 短选项列表 */
	/* 当选项后面要跟参数时加一个冒号来区别 o: */
	const char* const short_options = "ho:v";

	/* 长选项结构体数组 */
	const struct option long_options[] = {
		{"help",    0,NULL,'h'},
		{"output",  1,NULL,'o'}, /* 后面跟参数的写法 */
		{"verbose", 0,NULL,'v'},
		{"NULL",    0,NULL, 0 }
	};

	/* 解析命令选项 */
	do {

		cnt++; /* 计循环次数 */
		printf("the cnt is %d\n",cnt);

		/* 解析命令参数 */
		next_option = getopt_long(argc,argv,short_options,long_options,NULL);
		
		switch(next_option){

			case 'h':   /* -h or --help */
				print_usage(stdout,0); /* 打印帮助信息,并退出程序 */
				break;

			case 'o':   /* -o or --output */
				/*
				* 当处理一个带参数的选项时,全局变量 optarg 会指向这个字符串参数
				*/
				output_filename = optarg;
				printf("The file name is %s\n",output_filename);
				break;

			case 'v':   /* -v or --verbose */
				verbose = 1;
				break;

			case -1: /* 没有任何选项 */
				break;

			default: /* 发生错误 */
				printf("No such option !\n");
				exit(-1);
				break;
		}
	}
	while(next_option != -1);

	if(verbose) {

		int i;
		/*
		* 当 getopt_long 完成了所有选项的解析后,全局变量 optind 包含第一个
		* 非选项参数在argv中的索引
		*/
		for(i = optind; i < argc; i++)
			printf("the Argument is: %s\n", argv[i]);
	}
	
	return 0;
}