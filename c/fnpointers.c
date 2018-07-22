void hello_world( void)
{
    printf("hello world\n");
}

int main( void )
{
    void (*fn)(void) = hello_world;

    (*fn)();
}
