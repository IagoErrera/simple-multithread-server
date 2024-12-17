void error_msg(const char* msg) {
    printf("[ERROR] %s \r\n", msg);
    fflush(stdout);
    exit(1);
}