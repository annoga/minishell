#include "../../inc/minishell.h"
static void init_signal(t_sigaction *sigact, int signal)
{
    if(sigemptyset(&(*sigact).sa_mask) == -1)
    {
        perror("sigemptyset");
        exit(EXIT_FAILURE);
    }
    if(sigaddset(&(*sigact).sa_mask, signal) == -1)
    {
        perror("sigaddset");
        exit(EXIT_FAILURE);
    }
    sigact->sa_flags = 0;
    sigaction(signal, sigact, NULL);

}

void ft_strappend(char **dest, const char *src) {
    if (!dest || !src) return;

    size_t dest_len = (*dest) ? strlen(*dest) : 0;
    size_t src_len = strlen(src);
    char *new_str = realloc(*dest, dest_len + src_len + 1); // +1 for null terminator

    if (new_str) {
        *dest = new_str;
        memcpy(*dest + dest_len, src, src_len); // Append src to dest
        (*dest)[dest_len + src_len] = '\0';      // Null-terminate
    }
}

static void rl_blank_line(void) {
    int i;
    char *og_line;
    char *temp = NULL;

    og_line = ft_strdup(rl_line_buffer);
    if (!og_line) return;  // Check for memory allocation failure

    i = ft_strlen(rl_line_buffer) + 2; // Adjust for extra spaces and newline
    while (i-- > 0) {
        ft_strappend(&temp, " ");
    }
    rl_on_new_line();
    rl_replace_line(temp, 1);    // Replace with blank line
    rl_redisplay();
    free(temp);                   // Free the temporary blank line
    rl_replace_line(og_line, 1);  // Restore the original line
    rl_redisplay();
    free(og_line);                // Free the original line
}


void handle_idle_signal(int signal) {
    rl_blank_line();                        // Clear the line and refresh the prompt
    if (signal == SIGINT) {
        // Clear the line and refresh the prompt without displaying ^C
        write(STDOUT_FILENO, "\n", 1);        // Move to a new line
        rl_replace_line("", 0);               // Clear the input line
        rl_on_new_line();                     // Reset the prompt position
        rl_redisplay();                       // Redisplay the prompt
    }
    else if (ft_strlen(rl_line_buffer) <= 2) {
                                                // For SIGQUIT, clear the line and refresh the prompt without displaying ^
        rl_replace_line("", 0);               // Clear the input line                      // Redisplay the prompt
    }
}


void handle_update_signal(t_signal *signals, enum e_signal_handle mode)
{
    if (mode == SIG_HANDLE_IDLE)
        signals->ctrl_c.sa_handler = handle_idle_signal;
    else if (mode == SIG_HANDLE_HDOC)
        signals->ctrl_c.sa_handler = SIG_DFL;
    else if (mode == SIG_HANDLE_EXEC)
        signals->ctrl_c.sa_handler = SIG_IGN;
    else if (mode == SIG_HANDLE_BLCK)
        signals->ctrl_c.sa_handler = SIG_IGN;
    else
        signals->ctrl_c.sa_handler = SIG_DFL;

    if(mode == SIG_HANDLE_HDOC)
        signals->ctrl_slash.sa_handler = SIG_IGN;
    else
        signals->ctrl_slash.sa_handler = signals->ctrl_c.sa_handler;
    init_signal(&signals->ctrl_c, SIGINT);
    init_signal(&signals->ctrl_slash, SIGQUIT);
}
