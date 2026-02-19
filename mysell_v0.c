#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


#define MAX_LINE 1024  
#define MAX_TOKENS 100

 
int main() {
    char line[MAX_LINE];
    while (1) { 
        printf("myshell> ");
        fflush(stdout);      
        if (!fgets(line, sizeof(line), stdin))
            break;   
 
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0)
            continue;

        // ============================================
        // TODO: Students implement the following:
        //
        // 1. Parse the input line into tokens
        //    - Split by whitespace
       char *tokens[MAX_TOKENS];
        int ntokens = 0;
        char *token=strtok(line, " \t");
        while (token != NULL && ntokens <MAX_TOKENS-1){
            tokens[ntokens++]= token;
            token = strtok(NULL, " ");
        }
        tokens [ntokens]=NULL;
        if (ntokens ==0){
             continue;
        }
       
        // 2. Check for built-in commands
        //    - "cd [dir]" - change directory
        //    - "exit" - exit the shell
        if (strcmp(tokens[0], "exit") == 0){
            break;
        }
       
        if (strcmp(tokens[0], "cd") == 0) {
            if (tokens[1] == NULL){
                chdir(getenv("HOME"));}
            else{
                chdir(tokens[1]);
            }
        continue;
        }

        // 4. Handle redirection
        //    - < for input redirection
        //    - > for output redirection
        //    - >> for append redirection
        char *input_file=NULL;
        char *output_file=NULL;
        int append=0;
        for (int i=0;i<ntokens;i++){
            if (strcmp(tokens[i], "<")==0){
                input_file=tokens[i+1];
                tokens[i]=NULL;
                break;
            }
            if (strcmp(tokens[i], ">")==0){
                output_file=tokens[i+1];
                append=0;
                tokens[i]=NULL;
                break;            
            }
            if (strcmp(tokens[i], ">>")==0){
                output_file=tokens[i+1];
                append=1;
                tokens[i]=NULL;
                break;
            }

        }


        // 3. Execute external commands
        //    - fork() to create child process
        //    - execvp() to run the command
        //    - waitpid() to wait for completion
        pid_t pid = fork();
        if (pid == 0) {
        // CHILD: input redirection
            if (input_file) {
                int fl_dr = open(input_file, O_RDONLY);
                if (fl_dr<0){
                    perror("Open Input");
                    exit(1);
                }
                dup2(fl_dr, STDIN_FILENO);
                close(fl_dr);
            }
        
        // output redirection
            if (output_file) {
                int fl_dr;
                if (append){
                    fl_dr = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else{
                    fl_dr = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }
                if (fl_dr <0){
                    perror ("Open Output");
                    exit(1);
                }
                dup2(fl_dr, STDOUT_FILENO);
                close(fl_dr);
                
            }
            execvp(tokens[0], tokens);
            perror("execvp");
            exit(1);
        }
        else {
            // PARENT
            waitpid(pid, NULL, 0);
        }
       
    }

    printf("\nGoodbye!\n");
    return 0;
}