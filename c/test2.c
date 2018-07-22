int main() {
	int *a, b[10]={10, 11, 12, 13};
	*(a = b+2) = *(b+3);
    printf("%d %d %d %d\n", *a, b[0], b[1], b[2]);
}

