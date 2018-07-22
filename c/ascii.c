int main(int argc, char ** argv)
{
	int start_range, end_range, i;
	char ch;

	if (argc < 2) {
		start_range = 30;
		end_range = 255;
	}

	for (i = start_range; i < end_range; i += 5)
		printf("%x %c \t %x %c \t %x %c \t %x %c \t %x %c \n",i,i,i+1,i+1,i+2,i+2,i+3,i+3,i+4,i+4);
	scanf("%c", &ch);
	printf("%x \n", ch);
 
}
		
