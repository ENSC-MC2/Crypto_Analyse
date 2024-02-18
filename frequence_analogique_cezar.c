#include <stdio.h>
#include <string.h>
// Include this for malloc and free
#include <stdlib.h> 

typedef struct freq_analogique
{
    char lettre;
    double freq; 
} t_freq_analogique;


int nbr_letter_iter(char s[45], char c);

char* cesar_chiffre(char *s, int n);

t_freq_analogique* freq_in_char(char *s);

t_freq_analogique* remplir_freq();

int main() {
    char mssg_input[45];

    t_freq_analogique *all_freq_in_lettre, *apparition;

    printf("#############################   Frequence Analysis In Cezar #################################\n");
    printf("donner un message :");
    fgets(mssg_input, sizeof(mssg_input), stdin);

    // printf("le nombre de lettre est : %d \n", nbr_letter_iter(s, 'h'));

    printf("le chiffrement de message %s en cezar est : %s", mssg_input, cesar_chiffre(mssg_input, 3));

    all_freq_in_lettre = freq_in_char(mssg_input);

    printf("la frequece de chaque lettre dans le message est : \n");

    for (int i = 0; i < 26; i++) {
        printf("la lettre est : %c le pourcentage %f \n", all_freq_in_lettre[i].lettre, all_freq_in_lettre[i].freq);
    }

    apparition = remplir_freq();

    // Frequency analysis comparison
    double min_diff = __FLT_MAX__;
    int best_shift = 0;

    for (int shift = 0; shift < 26; shift++) {
        double diff = 0.0;
        for (int i = 0; i < 26; i++) {
            int index = (i + shift) % 26;
            diff += fabs(all_freq_in_lettre[i].freq - apparition[index].freq);
        }
        if (diff < min_diff) {
            min_diff = diff;
            best_shift = shift;
        }
    }

    printf("Best shift found: %d \n", best_shift);


    // Free allocated memory
    free(all_freq_in_lettre);
    free(apparition);

    return 0;
}

int nbr_letter_iter(char s[45], char c) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            count++;
        }
    }
    return count;
}

t_freq_analogique* freq_in_char(char *s) {
    t_freq_analogique *res = malloc(sizeof(t_freq_analogique) * 26); // Allocate memory
    float freq;
    char lettres[26] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 26; ++i) {
        freq = (float)nbr_letter_iter(s, lettres[i]) / strlen(s);
        res[i].lettre = lettres[i];
        res[i].freq = freq*100;
    }

    return res;
}

t_freq_analogique* remplir_freq() {
    char str[26] = "abcdefghijklmnopqrstuvwxyz";
    double freq[26] = {8.15, 0.97, 5.28, 3.15, 2.80, 3.73, 1.21, 17.39, 6.64, 1.12, 8.14, 0.97, 7.22, 0.85, 6.38, 7.31, 1.64, 0.45, 0.03, 0.02, 0.41, 5.69, 0.28, 2.87, 0.15};
    t_freq_analogique *res = malloc(sizeof(t_freq_analogique) * 26); // Allocate memory
    for (int i = 0; i < 26; ++i) {
        res[i].lettre = str[i];
        res[i].freq = freq[i];
    }

    return res;
}

char* cesar_chiffre(char *s, int n) {
    char *res = malloc(strlen(s) + 1); // Allocate memory
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            res[i] = 'a' + (s[i] - 'a' + n) % 26; 
        } else {
            res[i] = s[i];
        }
    }
    res[strlen(s)] = '\0';
    return res;
}
