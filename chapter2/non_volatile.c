void wait_while_0(int *p) {
    while (*p == 0);
}

int main(void) {
    wait_while_0((int *) 0x10);
    return 0;
}
