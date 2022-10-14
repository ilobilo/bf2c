extern int putchar(int __c);
extern int getchar(void);

int main()
{
    char array[30000] = { 0 };
    char *ptr = array;

    ((ptr == &array[29999]) ? ptr = array : ptr++);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    while (*ptr)
    {
        ((ptr == array) ? ptr = &array[29999] : ptr--);
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ((ptr == &array[29999]) ? ptr = array : ptr++);
        --*ptr;
    }
    ((ptr == array) ? ptr = &array[29999] : ptr--);
    putchar(*ptr);
    ((ptr == &array[29999]) ? ptr = array : ptr++);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    while (*ptr)
    {
        ((ptr == array) ? ptr = &array[29999] : ptr--);
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ((ptr == &array[29999]) ? ptr = array : ptr++);
        --*ptr;
    }
    ((ptr == array) ? ptr = &array[29999] : ptr--);
    ++*ptr;
    putchar(*ptr);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    putchar(*ptr);
    putchar(*ptr);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    putchar(*ptr);
    while (*ptr)
    {
        --*ptr;
    }
    ((ptr == &array[29999]) ? ptr = array : ptr++);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    while (*ptr)
    {
        ((ptr == array) ? ptr = &array[29999] : ptr--);
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ((ptr == &array[29999]) ? ptr = array : ptr++);
        --*ptr;
    }
    ((ptr == array) ? ptr = &array[29999] : ptr--);
    putchar(*ptr);
    ((ptr == &array[29999]) ? ptr = array : ptr++);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    while (*ptr)
    {
        ((ptr == array) ? ptr = &array[29999] : ptr--);
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ((ptr == &array[29999]) ? ptr = array : ptr++);
        --*ptr;
    }
    ((ptr == array) ? ptr = &array[29999] : ptr--);
    --*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    --*ptr;
    putchar(*ptr);
    while (*ptr)
    {
        --*ptr;
    }
    ((ptr == &array[29999]) ? ptr = array : ptr++);
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    while (*ptr)
    {
        ((ptr == array) ? ptr = &array[29999] : ptr--);
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ++*ptr;
        ((ptr == &array[29999]) ? ptr = array : ptr++);
        --*ptr;
    }
    ((ptr == array) ? ptr = &array[29999] : ptr--);
    ++*ptr;
    putchar(*ptr);
    while (*ptr)
    {
        --*ptr;
    }
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    ++*ptr;
    putchar(*ptr);
    ((ptr == &array[29999]) ? ptr = array : ptr++);
    ++*ptr;
    while (*ptr)
    {
        *ptr = getchar();
    }
}