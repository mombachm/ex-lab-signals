#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define _POSIX_SOURCE

void sinal_chegou(int signum) {
    run_firefox("www.google.com");
}

void run_firefox(const char* s) {
    execlp("firefox", "firefox", s, NULL);
    err_exit("execlp falhou.");
}

void err_exit(char* msgerro){
    perror(msgerro);
    exit(EXIT_FAILURE);
}

void init_sigaction(struct sigaction* conf_sinal) {
    memset(conf_sinal, 0, sizeof(struct sigaction));
    conf_sinal->sa_flags = 0;
    conf_sinal->sa_restorer = NULL;
    sigemptyset(&conf_sinal->sa_mask);
    conf_sinal->sa_handler = NULL;
}


int main()
{
    const char* msg = "Eu não sou o firefox";
    sleep(3);
    //sinal_chegou();

    struct sigaction conf_sinal;
    init_sigaction(&conf_sinal);
    conf_sinal.sa_handler = &sinal_chegou;

    conf_sinal.sa_handler(78);

    sigaction(SIGINT, &conf_sinal, NULL);

    while(1) {
        printf("%s\n", msg);
        sleep(1);
    }

    return EXIT_SUCCESS;
}

